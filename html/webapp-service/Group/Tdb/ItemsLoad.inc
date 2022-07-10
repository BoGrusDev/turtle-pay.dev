<?php
/*
   ItemsLoadClass

    Gateway

	{
        "_group" : "App",
        "_action" : "ItemsLoad",
        "_item_code" : "882E3A6B7B0DD6A1CF2A60F5F68C025D"
    }	
*/

class ItemsLoadClass extends AjaxClass {

    private $invoiceEventItemCode;
    
    public function _($data) {
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"3");
        }
		$data->_group = 'WebAppTdb';
      	return $this->_RestApiCall($data);
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