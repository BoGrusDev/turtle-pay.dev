<?php
/*

    ContractCheck

    2022-04-06

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
        // $this->contractId = 3;
		
		// Check if company has Priv on enabled
        if ($this->companyPrivCheck() == false) {
			return array("code"=>"0", "denied_code"=>"company-no-privon");
		}

		// Check if person is su - Superuser
		if ($this->peoplePrivCheck() == false) {
			return array("code"=>"0", "denied_code"=>"superuser-no");
		}
		
		// Chec if company has sign contract
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

		// Get latest contract
		$sql = "SELECT * FROM company_contract WHERE enabled = 'y' ORDER BY company_contract_id DESC LIMIT 1";
		$resContract = $this->_Get($sql);
		$contractId = $resContract['company_contract_id'];
		// Check if company has valid sign
        $sql = "SELECT company_sign_id FROM company_sign WHERE company_id = $this->userId AND company_contract_id = $contractId";
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
