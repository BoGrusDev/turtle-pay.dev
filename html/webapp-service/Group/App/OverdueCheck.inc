<?php
/*
   OverdueCheckClass

    Gateway

	{
        "_group" : "App",
        "_action" : "OverdueCheck",
		"_personal_id_number" : "195711040054"
    }	
*/
class OverdueCheckClass extends AjaxClass {

    //private $personalIdNumber;
    
    public function _($data) {
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0");
        }
		$data->_group = 'WebApp';
        $reply =  $this->_RestApiCall($data);
      	return $this->_RestApiCall($data);
    }
    
	private function parameterCheck($data) {
        if (isset($data->_personal_id_number)) {
			$this->personalIdNumber = trim($data->_personal_id_number);
		}
		else {
			return false;
		}
		return true;
	}
}