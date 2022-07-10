<?php
/*
	Handling all action regarding to OCR

*/
class Ocrno {
	
	public function checkSerie1($ocrno, $db) {
		$sql = "SELECT fi.people_id, fi.credit_id, cr.credit_status ";
		$sql .= "FROM first_invoice fi, credit cr ";
		$sql .= "WHERE ocrno = '$ocrno'";
		$reply =  $db->_Get($sql);
		print_r($reply);
	}
}