import os
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# --- DB bootstrap: create transactions table if it doesn't exist ---
db.execute("""
    CREATE TABLE IF NOT EXISTS transactions (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        user_id INTEGER NOT NULL,
        symbol TEXT NOT NULL,
        shares INTEGER NOT NULL,            -- positive for buys, negative for sells
        price NUMERIC NOT NULL,            -- executed price per share
        transacted TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
        FOREIGN KEY(user_id) REFERENCES users(id)
    )
""")
db.execute("CREATE INDEX IF NOT EXISTS idx_tx_user ON transactions(user_id)")
db.execute("CREATE INDEX IF NOT EXISTS idx_tx_user_symbol ON transactions(user_id, symbol)")
db.execute("CREATE INDEX IF NOT EXISTS idx_tx_time ON transactions(transacted)")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks with current prices and totals"""

    user_id = session["user_id"]

    # Aggregate current holdings: sum of shares per symbol (ignore those with 0 or negative total)
    rows = db.execute("""
        SELECT symbol, SUM(shares) AS shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING SUM(shares) > 0
        ORDER BY symbol
    """, user_id)

    holdings = []
    portfolio_total = 0.0

    for row in rows:
        symbol = row["symbol"]
        shares = int(row["shares"])
        quote = lookup(symbol)
        if not quote:
            # If lookup fails, skip this symbol but keep the portfolio responsive
            price = 0.0
            name = symbol
        else:
            price = float(quote["price"])
            name = quote["name"]

        total = shares * price
        portfolio_total += total
        holdings.append({
            "symbol": symbol,
            "name": name,
            "shares": shares,
            "price": price,
            "total": total
        })

    # Current cash
    cash_row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]
    cash = float(cash_row["cash"])
    grand_total = cash + portfolio_total

    return render_template("index.html",
                           holdings=holdings,
                           cash=cash,
                           portfolio_total=portfolio_total,
                           grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    # POST
    symbol_raw = request.form.get("symbol", "").strip()
    shares_raw = request.form.get("shares", "").strip()

    # Validate symbol
    if not symbol_raw:
        return apology("must provide symbol", 400)
    quote = lookup(symbol_raw)
    if not quote:
        return apology("invalid symbol", 400)

    # Validate shares (must be positive integer)
    if not shares_raw.isdigit():
        return apology("shares must be a positive integer", 400)
    shares = int(shares_raw)
    if shares <= 0:
        return apology("shares must be a positive integer", 400)

    price = float(quote["price"])
    cost = price * shares

    # Check user cash
    user_id = session["user_id"]
    cash = float(db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"])
    if cost > cash:
        return apology("can't afford", 400)

    # Record transaction and update cash
    db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
               user_id, quote["symbol"], shares, price)
    db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", cost, user_id)

    flash(f"Bought {shares} share(s) of {quote['symbol']} at {usd(price)}")
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    rows = db.execute("""
        SELECT symbol, shares, price, transacted
        FROM transactions
        WHERE user_id = ?
        ORDER BY transacted DESC, id DESC
    """, user_id)

    # Format for template
    tx = []
    for r in rows:
        tx.append({
            "symbol": r["symbol"],
            "type": "BUY" if r["shares"] > 0 else "SELL",
            "shares": abs(int(r["shares"])),
            "price": float(r["price"]),
            "time": r["transacted"]
        })

    return render_template("history.html", tx=tx)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 403)
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        session["user_id"] = rows[0]["id"]
        return redirect("/")

    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    session.clear()
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    symbol_raw = request.form.get("symbol", "").strip()
    if not symbol_raw:
        return apology("must provide symbol", 400)

    quote = lookup(symbol_raw)
    if not quote:
        return apology("invalid symbol", 400)

    return render_template("quoted.html", quote=quote)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    username = request.form.get("username", "").strip()
    password = request.form.get("password", "")
    confirmation = request.form.get("confirmation", "")

    # Validation
    if not username:
        return apology("must provide username", 400)
    if not password:
        return apology("must provide password", 400)
    if password != confirmation:
        return apology("passwords do not match", 400)

    hash_ = generate_password_hash(password)

    # Insert user; handle duplicate usernames via try/except
    try:
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_)
    except ValueError:
        return apology("username already exists", 400)

    # Auto-login newly registered user
    user = db.execute("SELECT id FROM users WHERE username = ?", username)[0]
    session["user_id"] = user["id"]
    flash("Registered successfully!")
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    if request.method == "GET":
        # Load symbols the user owns (with positive total shares)
        symbols = db.execute("""
            SELECT symbol
            FROM transactions
            WHERE user_id = ?
            GROUP BY symbol
            HAVING SUM(shares) > 0
            ORDER BY symbol
        """, user_id)
        return render_template("sell.html", symbols=[r["symbol"] for r in symbols])

    # POST
    symbol = request.form.get("symbol", "").strip()
    shares_raw = request.form.get("shares", "").strip()

    if not symbol:
        return apology("must select symbol", 400)

    if not shares_raw.isdigit():
        return apology("shares must be a positive integer", 400)
    shares = int(shares_raw)
    if shares <= 0:
        return apology("shares must be a positive integer", 400)

    # Check how many shares owned
    owned_row = db.execute("""
        SELECT COALESCE(SUM(shares), 0) AS owned
        FROM transactions
        WHERE user_id = ? AND symbol = ?
    """, user_id, symbol)[0]
    owned = int(owned_row["owned"])

    if shares > owned:
        return apology("too many shares", 400)

    quote = lookup(symbol)
    if not quote:
        return apology("invalid symbol", 400)

    price = float(quote["price"])
    proceeds = price * shares

    # Record sale as negative shares; add cash
    db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
               user_id, symbol.upper(), -shares, price)
    db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", proceeds, user_id)

    flash(f"Sold {shares} share(s) of {symbol.upper()} at {usd(price)}")
    return redirect("/")


# ---- Personal Touch: Add Cash ----
@app.route("/add-cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Allow user to add cash to their account"""
    if request.method == "GET":
        return render_template("add_cash.html")

    amount_raw = request.form.get("amount", "").strip()
    try:
        amount = float(amount_raw)
    except ValueError:
        return apology("amount must be a number", 400)

    if amount <= 0:
        return apology("amount must be positive", 400)

    db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", amount, session["user_id"])
    flash(f"Added {usd(amount)} to your account.")
    return redirect("/")

# Mohammadreza_mokhtari_kia
