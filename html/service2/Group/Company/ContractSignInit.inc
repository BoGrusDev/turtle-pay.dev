<?php
/*
   SignInitClass

    Gateway

    {
		"_group" : "Company",
		"_action" : "ContractSignInit",
        "_user_id" : "69",
        "_token" : "AD1E5395150A9010C9558A2E90F85EFD",
		"bankid_text" : "Signering av Avtal om samarbete och personuppgiftsbiträde för "
	}	
*/

class ContractSignInitClass extends AjaxClass {

    private $SignInit;
    
    public function _($data) {

        $this->reply = new stdClass();
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denied_code"=>"param-fail");
        }

        if ($this->tokenCheck() == false) {
            return array("code"=>"0");
        }

        if ($this-> companyContractSignInfo() == false) {
            return array("code"=>"0", "denied_code"=>'not-supersuer');
        }
        
        $this->bankIdSignInit();
      	return $this->reply;
    }

	private function parameterCheck($data) {
        if (isset($data->_token)) {
            $this->token = $data->_token;
		}
		else {
			return false;
		}
        if (isset($data->_user_id)) {
            $this->userId = $data->_user_id;
		}
		else {
			return false;
		}
        if (isset($data->bankid_text)) {
            $this->bankIdText = $data->bankid_text;
		}
		else {
			return false;
		}
		return true;
	}
    
    private function tokenCheck() {
        $res = $this->_TokenCheckCall($this->token, $this->userId);
        if ($res->code == '1') {
            $this->operatorId = $res->operator_id;
            return true;
        }
        else {
            return false;
        }
    }

    private function companyContractSignInfo() {
        $param = new stdClass();
        $param->_group = 'Company';
        $param->_action ='ContractSignInfo';
        $param->_operator_id = $this->operatorId;
        $param->_user_id = $this->userId;
        $res = $this->_RestApiCall($param);
        if ($res->code == '1') {
            $this->personalIdNumber = $res->personal_id_number;
            $this->peopleName = $res->people_name;
            $this->companyName = $res->company_name;
            return true;
        }
        else {
            return false;
        }
    }

    private function bankIdSignInit() {
        $param = new stdClass();
        $param->_group = 'BankId';
        $param->_action = 'SignInit';
        $param->_personal_id_number = $this->personalIdNumber;
		$param->_bankid_text = $this->bankIdText . $this->companyName . '.';
        $param->_group = 'BankId';
      	$this->reply = $this->_RestApiCall($param, INTERNAL_API);
	}	
       
}