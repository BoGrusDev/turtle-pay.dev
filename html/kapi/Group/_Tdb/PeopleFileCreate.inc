<?php
/*
     PeopleFileCreateClass
   	Get the compentions for a organization and return all 
	that today day no expieer

	https://app.equipe.com/organizers/515/meetings.json

	prodOn means get from API else get from local file

	{
        "_group": "Tdb",
        "_action": "PeopleFileCreate",
        "_token": "57559D3E4F1DE94A4735967B9F515958",
        "_user_id": "69",
        "_event_id": "648",
        "_people_id": "1"
    }

*/
require_once 'Group/Tdb/TdbBase.inc';

class PeopleFileCreateClass extends TdbBaseClass {

    private $userId;
	private $operatorId;
    private $eventId; 
    private $tdbApikey;
	private $tdbOrgno;
    private $meetingNo;
	private $list;
    
    public function _($data) {

        /*
            Cobtroll that all needed paramer is set
        */
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0", "param-fail");
		}
      
        // Get meetings id
        if ($this->eventGet() == false) {
            return array("code"=>"0", "event-load-fail");
        }

        $today = date('Y-m-d-Hm');        
        $fileName = $this->userId . '-' . $this->eventId . '-' . $today . '.json';

        $this->list = $this->_RestApiTdb('meetings/' . $this->meetingNo . '/people.json', $this->tdbApikey);
		if (is_array($this->list) == false) {
			return array("code"=>"0");
		}
        if (sizeof($this->list) > 0) {
            // for ($i=0; $i<10; $i++) {
            for ($i=0; $i<sizeof($this->list); $i++) {
                $this->list[$i]->eco = $this->_RestApiTdb('meetings/' . $this->meetingNo . '/people/' . $this->list[$i]->rnr . '/economies.json', $this->tdbApikey);
            }

        // https://app.equipe.com/meetings/41991/people/132/economies.json
            $fp = fopen('tdb-files/' . $fileName , 'w');
            fwrite($fp, json_encode($this->list));
            fclose($fp);
        }

        $reply = new stdClass();
        $reply->code = '1';
        if (sizeof($this->list) > 0) {
            $reply->counter = sizeof($this->list);
            $reply->file_name = $fileName;
        }
        else {
            $reply->counter = '0';
        }
        

        return $reply;

        //$this->json = json_decode(file_get_contents("tdb-files/test.json")); 
        
        //$list = $this->_RestApiTdb('meetings/' . $data->_competion_id . '/people.json', $data->_company_id );

        //$res = $this->_RestApiTdb('meetings/' . $competionId . '/people/' . $peopleId . '/economies.json', $companyId );


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
        
		$reply= $this->TdbSettingGet($this->userId);
		if ($reply['code'] != '1') {
			return false;
		}
		$this->tdbApikey = $reply['tdb_apikey'];
		$this->tdbOrgno = $reply['tdb_orgno'];
		return true;
	}

    private function eventGet() {
        $sql = "SELECT tdb_meeting_no FROM event_v4 WHERE event_id = $this->eventId ";
        $res = $this->_Get($sql);
        if ($res['code'] == '1') {
            $this->meetingNo = $res['tdb_meeting_no'];
            return true;
        }
        else {
            return false;
        }
    }



}