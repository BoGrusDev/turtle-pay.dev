<?php
/*
   ProcessClass

    Gateway

*/

class ProcessClass extends AjaxClass {
 
    public function _($data) {
  		$data->_group = 'WebAppTdb';
      	return $this->_RestApiCall($data);
    }

}