<?php

class Db {

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
				return (object) $result;
			} else {
				$result =  array();
				$result['code'] = "0";
				return  (object) $result;
			}
		} else {
			$code = $stmt->errorCode() * -1;
			$result =  array();
			//$result['code'] = $code;
			$result['code'] = "0";
			return  (object) $result;
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

}
