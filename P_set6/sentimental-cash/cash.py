while True:
    try:
        dollars = float(input("Change owed: "))  # Get input as float
        if dollars >= 0:  # If the number was positive
            break
    except ValueError:
        pass  # If input is not a number, ask again

# Convert dollars to cents to avoid floating point issues
num_cent = round(dollars * 100)

# Calculate number of 25-cent coins
A_25 = num_cent // 25
R_25 = num_cent % 25

# Calculate number of 10-cent coins
A_10 = R_25 // 10
R_10 = R_25 % 10

# Calculate number of 5-cent coins
A_5 = R_10 // 5
R_5 = R_10 % 5

# Calculate number of 1-cent coins
A_1 = R_5 // 1
R_1 = R_5 % 1

# Add all coins to find the minimum number needed
ANS = A_25 + A_10 + A_5 + A_1

print(ANS)  # Print the answer

# Mohammadreza_mokhtari_kia
