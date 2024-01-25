-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description FROM crime_scene_reports; -- basically to just get and understanding of the discription of the crimes
SELECT * FROM crime_scene_reports WHERE description LIKE '%duck%'; -- get a crime related to the CS50 duck  
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
SELECT * FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28; -- get bakery log at day of crime
SELECT license_plate FROM bakery_security_logs
WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND activity = 'exit'; -- accessing each license plate of people that exited building at 10, after the crime
SELECT * FROM interviews WHERE year = 2023 AND month = 7 AND day = 28; -- information on bakery; got some stuff with atm transaction earlier this morning
--  ******* theif left within 10 minutes of crime; withdrew from ATM earlier in day at Leggett Street; 
-- called accomplis for less then minute to purchase plane ticket - plan to take earliest flight tmr *********;
SELECT * FROM bakery_security_logs
WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute < 25; -- add minute to exclude 1 license plate, condenced
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute < 25); -- getting names from people present 
-- now I will see the flight records and atm transactions to see if both add up to the names present 
SELECT account_number FROM bank_accounts 
WHERE person_id IN (SELECT id FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute < 25)); -- getting the account # to connect it to ATM transactions
SELECT * FROM atm_transactions WHERE account_number IN (SELECT account_number FROM bank_accounts
WHERE person_id IN (SELECT id FROM people 
WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute < 25))) AND year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street'; 

-- selects all transactions the day of robery from people present at it
SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute < 25) AND year = 2023 AND month = 7 AND day = 28
AND atm_location = 'Leggett Street'; -- ***** GETS 4 PEOPLE WHO USED ATM AT LEGGOTT STREET AND LEFT bakery around time of theft

-- selects all calls from people present at atm and robery
SELECT * FROM phone_calls WHERE caller IN(SELECT phone_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs
WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute < 25) AND year = 2023 AND month = 7 AND day = 28
AND atm_location = 'Leggett Street') AND year = 2023 AND month = 7 AND day = 28; -- gets all phone calls that happened
-- **** IM GOING TO ASSUME CALLER ONLY MADE 1 PHONE CALL SO PHONE NUMBER == (770) 555-1861 and the person name: Diana
-- the person who called diana is accomplice -- name is Philip

-- trying to find where missis diana escape too now >:)
SELECT * FROM flights WHERE year = 2023 AND month = 7 AND day = 29;
SELECT * FROM flights JOIN passengers ON flights.id = passengers.flight_id WHERE year = 2023 AND month = 7 AND day = 29;
SELECT * FROM airports WHERE id = (SELECT destination_airport_id FROM flights JOIN passengers ON flights.id = passengers.flight_id 
WHERE year = 2023 AND month = 7 AND day = 29 AND passport_number = (SELECT passport_number FROM people WHERE name = 'Diana')); -- GET DESTINATION AYYAYAYAYAYA

-- ONE LONG QUERY I WANT TO SEE IF I WILL GET IT RIGHT