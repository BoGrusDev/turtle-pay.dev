<?php
/*
    SelectionsLoadLoadClass 
   	{
		"_group" : "Tdb",
		"_action" : "SelectionsLoad",
		"_item_code" : "882E3A6B7B0DD6A1CF2A60F5F68C025D",
		"_user_id" : "69"
	}	
*/

class SelectionsLoadClass extends AjaxClass {

	private $itemCode;
	private $reply;

    public function _($data) {

		// Check if all demand paramer exist
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0");
		}
	
        $data->_group = 'WebAppTdb';
      	return $this->_RestApiCall($data);

		return $this->reply;

	}

	private function parameterCheck($data) {
        if (isset($data->_item_code)) {
			$this->itemCode = trim($data->_item_code);
		}
		else {
			return false;
		}
		return true;
	}

}