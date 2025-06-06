-- Keep a log of any SQL queries you execute as you solve the mystery.

-- TO FIND OUT:
-- The THIEF is?
-- The city the thief ESCAPED TO?
-- The ACCOMPLICE is?

-- CLUES:
-- 1. The crime was commited at 10:15am of 28/07/2024
-- 2. There are three witnesses.

-- Get the crime description of Humphrey Street.
SELECT description
  FROM crime_scene_reports
 WHERE month = 7 AND day = 28
   AND street = 'Humphrey Street';

-- Get the interviews transcript to find out more clues.
SELECT *
  FROM interviews
 WHERE month = 7 AND day = 28;

-- Get the bakery security logs at 10am and get the people information by the license plate.
SELECT *
  FROM bakery_security_logs
  JOIN people
    ON people.license_plate = bakery_security_logs.license_plate
 WHERE month = 7 AND day = 28 AND hour = 10;

-- Get the people who took the fly from Fiftyville the same day.
SELECT hour, minute, people.name, people.license_plate,
       ori.abbreviation AS abbreviation_o, ori.full_name AS full_name_o, ori.city AS city_o,
       dest.abbreviation, dest.full_name, dest.city
  FROM flights
  JOIN airports AS ori
    ON ori.id = flights.origin_airport_id
  JOIN airports AS dest
    ON dest.id = flights.destination_airport_id
  JOIN passengers
    ON passengers.flight_id = flights.id
  JOIN people
    ON people.passport_number = passengers.passport_number
 WHERE flights.month = 7 AND flights.day = 29 AND ori.city = 'Fiftyville' AND flights.hour = 8
 ORDER BY hour ASC, minute ASC;

-- SUSPECTS
-- * Sofia  G412CB7
-- * Bruce  94KL13X
-- * Kelsey 0NTHK55
-- * Taylor 1106N58
-- * Luca   4328GD8

-- Get the people who made a call and last less then a minute the day of the theft.
SELECT *
  FROM phone_calls
  JOIN people
    ON people.phone_number = phone_calls.caller
 WHERE month = 7 AND day = 28 AND duration < 60;


-- UDATED SUSPECTS
-- * Sofia  G412CB7
-- * Bruce  94KL13X
-- * Kelsey 0NTHK55
-- * Taylor 1106N58

-- Get information of the ATM transactions, following one of the clue from the interviewers.
SELECT *
  FROM atm_transactions
  JOIN bank_accounts
    ON bank_accounts.account_number = atm_transactions.account_number
  JOIN people
    ON people.id = bank_accounts.person_id
 WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- UDATED SUSPECTS
-- * Bruce  94KL13X
-- * Taylor 1106N58

-- Looking at who withdrew money from the ATM, made a call that day,
-- and took an earlier flight the next day, these two people coincide.
-- By the earlier flight, I can see that they ESCAPED to 'New York City’.

-- Get the receiver of the calls of Bruce and Taylor.
SELECT *
  FROM phone_calls
  JOIN people AS cal
    ON cal.phone_number = phone_calls.caller
  JOIN people AS rec
    ON rec.phone_number = phone_calls.receiver
 WHERE month = 7 AND day = 28 AND duration <= 60;

-- Check if Robin or James appear in the call history, because the accomplice was contacted only one time.
SELECT people.name, phone_calls.receiver, COUNT(*) AS times_called
  FROM phone_calls
  JOIN people
    ON phone_calls.receiver = people.phone_number
 GROUP BY people.name, phone_calls.receiver
 ORDER BY times_called;

-- !!! Robin doesn't appear in the call history so must be Bruce the thief and Robin the accomplice.

-- RESULT:
-- The THIEF is: Bruce
-- The city the thief ESCAPED TO: New York City
-- The ACCOMPLICE is: Robin

