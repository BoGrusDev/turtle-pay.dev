<?php
/*
   RequestClass

    Gateway

*/

class RequestClass extends AjaxClass {

    private $invoiceEventItemCode;
    
    public function _($data) {
  		$data->_group = 'WebAppTdb';
      	return $this->_RestApiCall($data);
    }

}