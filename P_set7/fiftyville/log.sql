-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Step 1: Providing information such as: time of theft, exact location, witnesses present
SELECT * FROM crime_scene_reports
WHERE year = 2024 AND month = 7 AND day = 28
  AND street = 'Humphrey Street';

-- Step 2: Interviews on 2024-07-28
SELECT * FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28;

-- Step 3: Bakery security logs from 10:15 to 10:25
SELECT * FROM bakery_security_logs
WHERE year = 2024 AND month = 7 AND day = 28
  AND hour = 10
  AND minute BETWEEN 15 AND 25;

-- Step 4: Bakery security logs from 10:15 to 10:25 — match license plates to people
SELECT DISTINCT p.*
FROM people p
JOIN bakery_security_logs b ON p.license_plate = b.license_plate
WHERE b.year = 2024 AND b.month = 7 AND b.day = 28
  AND b.hour = 10
  AND b.minute BETWEEN 15 AND 25;

-- Step 5: ATM transactions on Leggett Street on 2024-07-28
SELECT DISTINCT p.*
FROM people p
JOIN bank_accounts a ON a.person_id = p.id
JOIN atm_transactions t ON t.account_number = a.account_number
WHERE t.year = 2024 AND t.month = 7 AND t.day = 28
  AND t.transaction_type = 'withdraw'
  AND t.atm_location LIKE '%Leggett%';

--Clue: Iman, Luca, Diana, Bruce (People who have withdrawn money from the ATM and have not been to the bakery)

-- Step 6: Short phone calls (<1 minute) on 2024-07-28
SELECT pc.*, caller.name AS caller_name, callee.name AS callee_name
FROM phone_calls pc
JOIN people caller ON caller.phone_number = pc.caller
JOIN people callee ON callee.phone_number = pc.receiver
WHERE pc.year = 2024 AND pc.month = 7 AND pc.day = 28
  AND pc.duration < 60;

-- Clue: Bruce were both at the bakery, getting money from the ATM, and had a call for less than a minute to Robin.

-- Step 7b: Earliest flight on 2024-07-29 from Fiftyville (origin_airport_id = 8)
SELECT *
FROM flights
WHERE year = 2024 AND month = 7 AND day = 29
  AND origin_airport_id = 8
ORDER BY hour ASC, minute ASC
LIMIT 1;

 -- Mohammadreza_mokhtari_kia
