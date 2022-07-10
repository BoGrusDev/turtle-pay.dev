-- KYC Report
SELECT p.personal_id_number, p.first_name, p.last_name, p.address, p.postcode, p.city, k.*
FROM people p, kyc k
WHERE p.people_id = k.kyc_id AND p.people_id IN (341);

SELECT p.personal_id_number, p.first_name, p.last_name, p.rca
FROM people p
WHERE p.pep <> 'p'
ORDER BY p.personal_id_number;

-- Change remider next and time on allread påminnanda
SELECT reminder_next_date, reminder_times  
FROM invoice_event_item 
WHERE invoice_event_id = 72 AND invoice_event_item_status = 'r'

-- Change remider day next and time on allready sent
SELECT reminder_next_date, reminder_times  
FROM invoice_event_item 
WHERE invoice_event_id = 72 AND invoice_event_item_status = 'r'

