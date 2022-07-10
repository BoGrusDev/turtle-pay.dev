<?php
/**
    ApiBase.class.inc
 */

class ApiBase {

	protected $db;
	public $Setting;

	public function __construct($DB_HOST, $DB_NAME, $DB_USER, $DB_PASS) {
		$this->db = new PDO('mysql:host=' . $DB_HOST . ';dbname=' . $DB_NAME . ';charset=utf8', $DB_USER , $DB_PASS);
	}

	function _Close() {
		$stmt = $this->db = null;
	}

	function _GetList($sql) {
		$stmt = $this->db->prepare($sql);
		$stmt->execute();
		if ($stmt->errorCode() == 0) {
			return $stmt->fetchAll(PDO::FETCH_ASSOC);
		} else {
			//return -1;
			$errors = $stmt->errorInfo();
			return $errors[0] . ":" . $errors[1] . ":" . $errors[2];
		}
	}

	function _Get($sql) {
		$stmt = $this->db->prepare($sql);
		$stmt->execute();
		if ($stmt->errorCode() == 0) {
			if($stmt->rowCount() > 0) {
				$result =  $stmt->fetch(PDO::FETCH_ASSOC);
				$result['code'] = "1";
				return $result;
			} else {
				$result =  array();
				$result['code'] = "0";
				return $result;
			}
		} else {
			$code = $stmt->errorCode() * -1;
			$result =  array();
			//$result['code'] = $code;
			$result['code'] = "0";
			return $result;
		}
	}

	function _Insert($table, $data) {

		$sql = 'INSERT INTO ' . $table . '(';
		$values = "";
		foreach($data as $key => $value) {
			if (substr($key, 0, 1) != '_') {
				$sql .= $key . ',';
				$values .= '"' . $value . '",';
			}
		}
		$sql = rtrim($sql, ",");
		$values = rtrim($values, ",");
		$sql .= ') VALUES (' . $values . ')';
		$stmt = $this->db->prepare($sql);

		//if ($table == "first_invoice") {
			 //echo $sql;
		 //}

		$stmt->execute();
		if ($stmt->errorCode() == '00000') {
			$result =  array();
			$result['code'] = "1";
			$result['id'] = $this->db->lastInsertId();
			return $result;
		} else {

			$code = $stmt->errorCode();
			if ($code == "23000") {
				$result =  array();
				$result['code'] = "0";
				$result['denied_code'] = "duplicated";
				return $result;
			} else {
				$result =  array();
				$result['code'] = "0";
				$result['denied_code'] = "error_when_insert";
				//return $result;
				echo $sql;
				print_r($stmt->errorInfo());
				$code = $stmt->errorCode() * -1;
				return $code;
			}
		}
	}

	function _InsertSql($sql) {
		$stmt = $this->db->prepare($sql);
		$stmt->execute();
		if ($stmt->errorCode() == '0000') {
			$result =  array();
			$result['code'] = "1";
			$result['id'] = $this->db->lastInsertId();
			return $result;
		} else {

			$code = $stmt->errorCode();
			if ($code == "23000") {
				$result =  array();
				$result['code'] = "0";
				$result['denied_code'] = "duplicated";
				return $result;
			} else {
				$result =  array();
				$result['code'] = "0";
				$result['denied_code'] = "error_when_insert";
				//return $result;
				echo $sql;
				print_r($stmt->errorInfo());
				//$code = $stmt->errorCode() * -1;
				return $code;
			}
		}
	}

	function _Update($table, $primary_key, $id, $data) {
	
		$prepare = "UPDATE $table SET ";
		$paramArray = array();
		foreach($data as $key => $value) {
			if (substr($key, 0, 1) != '_') {
				$prepare .= $key . "='" . $value . "',";
			}
		}
		$prepare = rtrim($prepare, ",");
		$prepare .= " WHERE $primary_key = '" . $id . "'";
		
		// echo $prepare; // die('');

		$stmt = $this->db->prepare($prepare);

		$stmt->execute();
		if ($stmt->errorCode() == 0) {
			$result =  array();
			$result['code'] = "1";
			return $result;
		} else {
			print_r($stmt->errorInfo());
			$result =  array();
			$result['code'] = "0";
			//$result['error'] = $stmt->errorCode();
			return $result;
			//$code = $stmt->errorCode() * -1;
			//$stmt->errorCode();
			//print_r($stmt);
			//return $code;
		}
	}

	function _Delete($table, $primary_key, $id) {
		$prepare = "DELETE FROM $table WHERE $primary_key = $id";

		$stmt = $this->db->prepare($prepare);
		$stmt->execute();
		if ($stmt->errorCode() == 0) {
			$result =  array();
			$result['code'] = "1";
			return $result;
		} 
		else {
			$result =  array();
			$result['code'] = "0";
			return $result;	
		}
	}

	function _Query($sql) {
		$stmt = $this->db->prepare($sql);
		$stmt->execute();
		$result =  array();
		if ($stmt->errorCode() == 0) {
			$result['code'] = "1";
			return $result;
		} else {
			$result['code'] = "0";
			return $result;
		}
	}

	function _BeginTrans() {
		$this->db->beginTransaction();
	}

	function _Rollback() {
		$this->db->rollback();
	}

	function _Commit() {
		$this->db->commit();
	}

	function _Lock($table) {
		$stmt = $this->db->exec("LOCK TABLES $table WRITE");
	}

	function _Unlock($table) {
		$stmt = $this->db->exec("UNLOCK TABLES");
	}

	function _GUI(){
		// Return 2F8672B9-1BB8-2FFA-C56D-C5F8E8946FEF
		if (function_exists('com_create_guid')){
			return com_create_guid();
		}	else{
			mt_srand((double)microtime()*10000);//optional for php 4.2.0 and up.
			$charid = strtoupper(md5(uniqid(rand(), true)));
			return $charid;
		}
	}


	/*
		Customize setting for Turtle pay
	*/

    /*

	function _Settings($company_id = null, $people_id = null) {

		// 2018-10-05
		//
		// Settings settting_typ
		// s = system base
		// c = _company
		// p = personalbonus

		// Load standard Settings
		$sql = "SELECT * FROM setting WHERE setting_type = 's' ORDER BY setting_id DESC LIMIT 1";
		$baseResult = $this->_Get($sql);

		if (isset($company_id)) {
			$sql = "SELECT * FROM setting WHERE setting_type = 'c' AND id = $company_id AND status_setting = 'a' ORDER BY setting_id DESC LIMIT 1";
			$companyResult = $this->_Get($sql);
			foreach ($companyResult as $key => $value) {
				if ($value != null) {
					$baseResult[$key] =  $value;
				}
			}
		}

		if (isset($people_id)) {
			$sql = "SELECT * FROM setting WHERE setting_type = 'p' AND id = $people_id AND status_setting = 'a' ORDER BY setting_id DESC LIMIT 1";
			$peopleResult = $this->_Get($sql);
			if (sizeof($peopleResult) > 0) {
				foreach ($peopleResult as $key => $value) {
					if ($value != null) {
						$baseResult[$key] =  $value;
					}
				}
			}
		}

		$this->Setting = (object) $baseResult;

		$this->Setting->customerInterest = (float) $this->Setting->base_interest + (float)$this->Setting->customer_interest_margin;
		//print_r($this->Setting);

	}

	function _bookNew($data) {

		//print_r($data);
		//print_r($data->_trans);
		//die('');

		// Check balans zero
		$balance = 0;
		for ($i=0; $i<sizeof($data->_trans); $i++) {
			$balance =  $balance + $data->_trans[$i]->amount;
		}
		$balance = round($balance, 2);

		//print_r($data->booking);
		//$this->_BeginTrans();
		$reply = $this->_Insert('booking', $data );

		if ($reply['code'] =! "0") {
			$bookingId = $reply['id'];
			for ($i=0; $i<sizeof($data->_trans); $i++) {
				$data->_trans[$i]->booking_id = $bookingId;
				$this->_Insert('btrans', $data->_trans[$i]);
			}
			if ($balance != 0) {
				$trans = new stdClass();
				$trans->trans_type = "equaliz";
				$trans->account_no = '8193';
				$trans->amount = $balance;
				$this->_Insert('btrans', $trans);
			}
		} else {
			// Error with save Booking
			//$this->_Rollback();
			$reply['code'] = "0";
		}

		return $reply['id'];
	}

	function _CompanyCreditLimitCheck($company_id, $amount) {

		// -- Get the companies credit limit, default value
		$sql = "SELECT company_credit_limit FROM setting WHERE setting_type = 's' ORDER BY setting_id DESC LIMIT 1";
		$resSetting = $this->_Get($sql);

		$sql = "SELECT company_credit_limit ";
		$sql .= "FROM setting ";
		$sql .= "WHERE setting_type = 'c' ";
		$sql .= "AND id = $company_id ";
		$sql .= "ORDER BY setting_id DESC ";
		$sql .= "LIMIT 1";
		$resSettingCompany = $this->_Get($sql);

		if ($resSettingCompany['company_credit_limit'] != null) {
			$creditLimit = $resSettingCompany['company_credit_limit'];
		}
		else {
			$creditLimit = $resSetting['company_credit_limit'];
		}
		
		// Extra check 
		if (!is_numeric($creditLimit)) {
			$creditLimit = $resSetting['company_credit_limit'];
		}
		// Extra check, more lika a block 
		if (!is_numeric($creditLimit)) {
			$creditLimit = "0";
		}
		
		// get company balance

		$sql = "SELECT SUM(amount) AS sum ";
		$sql .= "FROM btrans ";
		$sql .= "WHERE account_no = '2981' AND prel = 'n' ";
		$sql .= "AND company_id = $company_id";
		$resBalance = $this->_Get($sql);
		if ($resBalance['sum'] == null) {
			$balance = "0";
		}
		else {
			$balance = $resBalance['sum'];
		}
		
		$balance = $balance + $amount;

		//limit: 5000.00 : 11911.50) overdue is + tp own -
		$reply = new stdClass();
		if ($creditLimit >= $balance) {
			$reply->code = '1';
		}
		else {
			$reply->code = '0';
		}

		return json_encode($reply);

	}
	*/

}
