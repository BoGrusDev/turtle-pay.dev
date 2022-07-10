<?php
/*
     EventCloseClass
   	Get the compentions for a organization and return all 
	that today day no expieer

	https://app.equipe.com/organizers/515/meetings.json

	prodOn means get from API else get from local file

	{
		"_group" : "Tdb",
		"_action" : "EventClose",
        "_event_id" : "659",
		"_user_id" : "134",
        "_operator_id" : "1"
	}	

*/
require_once 'Group/Tdb/TdbBase.inc';

class EventCloseClass extends TdbBaseClass {

    private $userId;
	private $operatorId;
    private $eventId; 
  
    public function _($data) {

        /*
            Cobtroll that all needed paramer is set
        */
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0","denide_code"=>"param-fail");
		}

        if ($this->eventClose() == false) {
            return array("code"=>"0", "denide_code"=>"event-close-fail");
        }

        $reply = new stdClass();
        $reply->code = '1';
        return $reply;

    }
	private function parameterCheck($data) {
		
		if (isset($data->_user_id)) {
			$this->userId = trim($data->_user_id);
		}
		else {
			return false;
		}
        if (isset($data->_event_id)) {
			$this->eventId = trim($data->_event_id);
		}
		else {
			return false;
		}
        return true;
	}

    private function eventClose() {
        $param = new stdClass();
        $param->tdb_closed = 'y';
        $res = $this->_Update('event_v4', 'event_id', $this->eventId, $param);
        if ($res['code'] == '1') {
            return true;
        }
        else {
            return false;
        }
    }


}