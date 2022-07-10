<?php
/*

    ContractCheck

    2022-04-06

	sudo chmod -R 777 /var/www/html/f-invoice

	{
		"_group" : "Company",
		"_action" : "ContractCheck",
        "_user_id" : "69",
		"_operator_id" : "1"
	}	
    Rpkty true, means need a sign
*/

class ContractCheckClass extends BaseClass {

	private $userId;
	private $operatorId;
	private $contractId;
	private $reply;

	public function _($data) {
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0", "denied_code"=>"parameter-fail");
		}
        $this->contractId = 3;
	
        if ($this->companyPrivCheck() == false) {
			return array("code"=>"0");
		}

		if ($this->peoplePrivCheck() == false) {
			return array("code"=>"0");
		}
		 
        if ($this->contractCheck() == false) {
			return array("code"=>"0");
		}

        $reply = new stdClass();
        // Need a sign
		$reply->code = '1';
		return $reply;
	}

	private function parameterCheck($data) {
		if (isset($data->_user_id)) {
			$this->userId = trim($data->_user_id);
			if (!is_numeric($this->userId)) {
				return false;
			}
		}
		else {
			return false;
		}
		if (isset($data->_operator_id)) {
			$this->operatorId = trim($data->_operator_id);
			if (!is_numeric($this->operatorId)) {
				return false;
			}
		}
		else {
			return false;
		}
		
		return true;
	}

    private function companyPrivCheck() {
        $sql = "SELECT company_id FROM company WHERE company_id = $this->userId AND priv_on = 'y'";
        $res = $this->_Get($sql);
        if ($res['code'] == '1') {
            return true;
        }
        else {
            // No need for control
            return false;
        }
    }

	private function peoplePrivCheck() {
        $sql = "SELECT cp_id FROM company_people ";
		$sql .= "WHERE company_id = $this->userId AND ";
		$sql .= "people_id = $this->operatorId AND ";
		$sql .= "priv = 'su'";
        $res = $this->_Get($sql);
        if ($res['code'] == '1') {
            return true;
        }
        else {
            return false;
        }
    }

	private function contractCheck() {
        $sql = "SELECT company_sign_id FROM company_sign WHERE company_id = $this->userId AND company_contract_id = $this->contractId";
        $res = $this->_Get($sql);
        if ($res['code'] == '1') {
            return false;
        }
        else {
            return true;
        }
    }

}

?>
