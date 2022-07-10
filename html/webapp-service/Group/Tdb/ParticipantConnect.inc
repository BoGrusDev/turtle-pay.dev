<?php

/*
    SelectionsLoadLoadClass 
   	{
		"_group" : "Tdb",
		"_action" : "ParticipantConnect",
		"_event_item_id" : "12466",
		"_user_id" : "134"
	}
*/

class ParticipantConnectClass extends AjaxClass {

	private $eventItemId;

    public function _($data) {

		// Check if all demand paramer exist
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0");
		}	
        $data->_group = 'WebAppTdb';
      	return $this->_RestApiCall($data);
	}

	private function parameterCheck($data) {
        if (isset($data->_event_item_id)) {
			$this->eventItemId = trim($data->_event_item_id);
		}
		else {
			return false;
		}
		return true;
	}
}
