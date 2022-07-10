<?php
/*
   SignInitClass

    Gateway

{
		"_group" : "Priv",
		"_action" : "SignInit",
        "_personal_id_number" : "195711040054",
		"_bankid_text" : "Testa av ny signering"
	}	
*/

class SignInitClass extends AjaxClass {

    private $SignInit;
    
    public function _($data) {
        
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denied_code"=>"param-fail");
        }
        $data->_group = 'BankId';

      	return $this->_RestApiCall($data, INTERNAL_API);
    }

	private function parameterCheck($data) {
        if (isset($data->_personal_id_number)) {
		}
		else {
			return false;
		}
        if (isset($data->_bankid_text)) {
		}
		else {
			return false;
		}
		return true;
	}
    
}