
SELECT count(*) AS number_of_outstanding_credits 
FROM credit WHERE start_date <= '2019-12-31' AND 
credit_status IN ('p','a','o') AND people_id NOT IN(1,4,5, 39, 34)

SELECT t.credit_id, sum(t.amount) AS amount_of_1380 
FROM btrans t, booking b WHERE b.booking_date <= '2019-12-31' AND t.account_no='1380' AND 
b.booking_id=t.booking_id AND t.people_id NOT IN(1,4,5, 39, 34) AND t.prel='n'
GROUP BY t.credit_id;

SELECT t.credit_id sum(t.amount) AS amount_of_1380 
FROM btrans t, booking b WHERE b.booking_date <= '2019-12-31' AND t.account_no='1380' AND 
b.booking_id=t.booking_id AND t.people_id NOT IN(1,4,5, 39, 34) AND t.prel='n' 
GROUP BY t.credit_id;
HAVING amount_of_1380 > 0

// korrekt
SELECT t.credit_id, sum(t.amount) AS amount_of_1380 FROM btrans t, booking b 
WHERE b.booking_date <= '2019-12-31' AND t.account_no='1380' AND b.booking_id=t.booking_id AND 
t.people_id NOT IN(1,4,5, 39, 34) AND t.prel='n' 
GROUP BY t.credit_id 
HAVING amount_of_1380 > 0 


// FI
$sql = "SELECT sum(t.amount) AS interest_income FROM btrans t, booking b WHERE ";
$sql .= "b.booking_date >= '$data->_date_from' AND b.booking_date <= '$data->_date_to' AND ";
$sql .= "(t.account_no = '8300' OR t.account_no = '8301') AND ";
$sql .= "b.booking_id = t.booking_id AND t.people_id NOT IN($data->_excluded) AND t.prel = 'n'";
$result = $this->_Get($sql);
$reply->interest_income = $result['interest_income'] * -1;

$sql = "SELECT t.account_no, a.account_name, SUM(t.amount) AS sum_account FROM btrans t, account a, booking b ";
$sql .= "WHERE t.account_no = a.account_no AND b.booking_id = t.booking_id ";
$sql .= " AND b.prel IN ('n') AND  t.prel IN ('n') AND ";
$sql .= "b.booking_date >= '" . $data->_from_date . "' AND b.booking_date <= '" . $data->_to_date .  "'";
$sql .= "GROUP BY t.account_no, a.account_name";

SELECT sum(t.amount) AS interest_income FROM btrans t, booking b WHERE 
b.booking_date >= '2019-01-01' AND b.booking_date <= '2019-12-31' AND 
(t.account_no = '8300' OR t.account_no = '8301') AND 
b.booking_id = t.booking_id AND t.people_id NOT IN(1,4,5, 39, 34) AND t.prel = 'n'


SELECT t.account_no, a.account_name, SUM(t.amount) AS sum_account FROM btrans t, account a, booking b 
WHERE t.account_no = a.account_no AND b.booking_id = t.booking_id 
 AND b.prel IN ('n') AND  t.prel IN ('n') AND 
b.booking_date >= '2019-01-01' AND b.booking_date <= '2019-12-31'
GROUP BY t.account_no, a.account_name