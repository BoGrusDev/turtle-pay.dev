<?php
/*
   SignCollectClass

    Gateway

    {
        "_group" : "BankId",
        "_action" : "SignCollect",
        "_order_ref" : "fbc141a1-321c-4ef6-bee0-bd460beea91b"
    }
*/

class SignCollectClass extends AjaxClass {

    public function _($data) {
        
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denied_code"=>"param-fail");
        }
  		$data->_group = 'BankId';
        
      	return $this->_RestApiCall($data, INTERNAL_API);
    }

	private function parameterCheck($data) {
        if (isset($data->_order_ref)) {
        }
		else {
			return false;
		}
		return true;
	}
}