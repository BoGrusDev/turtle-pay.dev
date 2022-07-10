<?php
/*
	Handling all action regarding  to OCR
    Updated 2021-11-09
*/
class Balances {
    
    public function credit($creditId, $toDate, $db, $prel = 'n') {
        $sql = "SELECT SUM(t.amount) AS balance ";
        $sql .= "FROM btrans t, booking b WHERE t.account_no = '1380' AND ";
        $sql .= "t.prel = '$prel' AND ";
        $sql .= "t.credit_id = $creditId AND t.booking_id = b.booking_id AND ";
        $sql .= "b.booking_date <= '$toDate'";
        $result = $db->_Get($sql);
        if (is_null($result['balance'])) {
            return 0;
        }
        return $result['balance'];
    }

    public function people($peopleId, $toDate, $db, $prel = 'n') {
        $sql = "SELECT SUM(t.amount) AS balance ";
        $sql .= "FROM btrans t, booking b WHERE t.account_no IN ('1380','1680') AND ";
        $sql .= "t.prel = '$prel' AND ";
        $sql .= "t.people_id = $peopleId AND t.booking_id = b.booking_id AND ";
        $sql .= "b.booking_date <= '$toDate'";
        $result = $db->_Get($sql);
        if (is_null($result['balance'])) {
            return 0;
        }
        return $result['balance'];
    }
        
    public function peopleOverDue($peopleId, $toDate, $db, $prel = 'n') {
        $sql = "SELECT SUM(t.amount) AS balance ";
        $sql .= "FROM btrans t, booking b WHERE t.account_no = '1680' AND ";
        $sql .= "t.prel = '$prel' AND ";
        $sql .= "t.people_id = $peopleId AND t.booking_id = b.booking_id AND ";
        $sql .= "b.booking_date <= '$toDate'";
        $result = $db->_Get($sql);
        if (is_null($result['balance'])) {
                return 0;
        }
        return $result['balance'];
    }
}