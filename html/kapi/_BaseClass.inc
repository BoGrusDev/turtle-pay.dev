<?php
/**
    BaseClass.inc
 */

class BaseClass {

	protected $db;
	public $Setting;

	public function __construct($DB_HOST, $DB_NAME, $DB_USER, $DB_PASS) {
		$this->db = new PDO('mysql:host=' . $DB_HOST . ';dbname=' . $DB_NAME . ';charset=utf8', $DB_USER , $DB_PASS, $setting = null);
	}

	
    public function _PrivilegeGet($data) {

		//$data->_company_id = $data->_user_id;

		$actionMethod = 'action' . $data->_action;

		$sql = "SELECT COUNT(*) principal FROM company_people ";
		$sql .= "WHERE people_id = $data->_people_id AND company_id = $data->_company_id AND priv = 'pr'";
		$result = $this->_Get($sql);
		if ($result['code'] == '1' && $result['principal'] == '1' ) {
			echo $this->$actionMethod($data);
		}
		else {
			$reply = new StdClass();
			$reply->code = "8"; // not allowed
			echo json_encode($reply);
		}

	}

	function _RestApiCall($param, $api) {
		$json = json_encode($param);
		$curl = curl_init($api);
		curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_setopt($curl, CURLOPT_POSTFIELDS, $json);
		curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($curl, CURLOPT_HTTPHEADER, array(
			'Content-Type: application/json',
			'Content-Length: ' . strlen($json))
		);
		if (ENV_TYPE != 'prod') {	
			curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, 0);
        	curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, 0);
		}
		$result = curl_exec($curl);
		/*
			if (curl_errno($curl)) {
				$error_msg = curl_error($curl);
				print_r($error_msg);
			}
			die('stop');
		*/
		curl_close($curl);
		return json_decode($result);
		
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
			if ((int) phpversion() < 7) {
				mt_srand((double)microtime()*10000);//optional for php 4.2.0 and up.
			}
			else {
				srand((double) microtime() * 1000000);
			}
			$charid = strtoupper(md5(uniqid(rand(), true)));
			return $charid;
		}
	}

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
		$setting = (object) $baseResult;
		$setting->customerInterest = (float) $setting->base_interest + (float) $setting->customer_interest_margin;
		return $setting;

	}


}
