<?php
/*
    PrizeListClass
   	

	https://app.equipe.com/organizers/515/meetings.json

	
	{
		"_group" : "Tdb",
		"_action" : "PrizeList",
        "_event_id" : "671",
		"_user_id" : "139",
        "_operator_id" : "1"
	}	

    Acrion - Status
    priz - Betalas
    prix - Manuel markerad som Ej betals
    pric -  Utbetald
    prip - Pågående, Faktura ej hämtad
*/
require_once 'Group/Tdb/TdbBase.inc';

class PrizeListClass extends TdbBaseClass {

    private $userId;
	private $operatorId;
    private $eventId; 
    
    private $eventName;
    private $invoicingLastId;
    private $eventRef;
    private $invoicingId;
    private $tdbApikey;
	private $tdbOrgno;
    private $competionsIndex;
	private $list;
   
    public function _($data) {

        /*
            Cobtroll that all needed paramer is set
        */
		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0","denide_code"=>"param-fail");
		}

        /*
            Get information about the Event,
            eventName, eventRef, InvoiceEventId and tdb tdbMettingNo
        */
        if ($this->eventGet() == false) {
            return array("code"=>"0", "denide_code"=>"event-load-fail");
        }
        
        if ($this->invoicingLastIdGet() == false) {
            return array("code"=>"0", "denide_code"=>"no-invocing-done");
        }
        
        // echo $this->invoicingLastId;
        $this->prizeGetList();

        $this->actionPripCheck();

        return $this->prizeList;

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

    private function eventGet() {
        $sql = "SELECT event_name, ref, invoice_event_id, tdb_meeting_no FROM event_v4 WHERE event_id = $this->eventId ";
        $res = $this->_Get($sql);
        if ($res['code'] == '1') {
            $this->eventName = $res['event_name'];
            $this->invoiceEventId = $res['invoice_event_id'];
            $this->eventRef = $res['ref'];
            $this->meetingNo = $res['tdb_meeting_no'];
            return true;
        }
        else {
            return false;
        }
    }

    private function invoicingLastIdGet() {
        // Get previous Invoicing ID
        $sql = "SELECT tdb_invoicing_id FROM tdb_invoicing WHERE event_id = $this->eventId ORDER BY tdb_invoicing_id DESC LIMIT 1";
        $res = $this->_Get($sql);
        if ($res['code'] == '1') {
            $this->invoicingLastId = $res['tdb_invoicing_id'];
            return true;
        }
        else {
            $this->invoicingLastId = 0;
            return false;
        }
    }

    private function prizeGetList() {    
        $sql = "SELECT ";
        $sql .= "e.tdb_eco_id, e.tdb_people_id, e.realrnr ,e.name AS rider, e.description, e.competition_no, e.total,e.horse_name,e.horse_num,e.action, ";
        $sql .= "p.rnr, p.name ";
        $sql .= "FROM tdb_eco e, tdb_people p ";
        $sql .= "WHERE e.tdb_invoicing_id = $this->invoicingLastId AND ";
        $sql .= "e.action IN('priz','prix','pric') AND ";
        $sql .= "e.tdb_people_id = p.tdb_people_id ";
        $sql .= "ORDER BY e.competition_no, e.tdb_people_id";
        $this->prizeList = $this->_GetList($sql);
    }

    private function actionPripCheck() {
        /*
           SELECT p.item_code FROM tdb_people p, tdb_eco e WHERE p.event_id = 671 AND p.tdb_people_id = e.tdb_people_id AND e.rnr = p.rnr AND p.action = 'sign' AND e.tdb_eco_id = '3381'
        */
        if (sizeof($this->prizeList) > 0) {
            for ($i=0; $i<sizeof($this->prizeList); $i++) {
                if ($this->prizeList[$i]['action'] == 'priz') {
                    //print_r($this->prizeList[$i]);
                    $sql = "SELECT p.item_code FROM tdb_people p, tdb_eco e "; 
                    $sql .= "WHERE p.event_id = $this->eventId AND ";
                    // $sql .= "p.tdb_people_id = e.tdb_people_id AND ";
                    $sql .= "e.rnr = p.rnr AND ";
                    $sql .= "p.action = 'sign' AND ";
                    $sql .= "e.tdb_eco_id = '" . $this->prizeList[$i]['tdb_eco_id'] . "'";
                    // echo $sql; // die('');
                    //if ($this->prizeList[$i]['tdb_eco_id']== 3381) {
                        //echo $sql; die('');
                    //}
                    $res = $this->_Get($sql);
                    if ($res['code'] == '0') {
                        $this->prizeList[$i]['action'] = 'prip';
                    }
                }
            } 
        }
        
        /*
            SELECT p.item_code, p.* FROM tdb_people p, tdb_eco e 
            WHERE p.event_id = 671 AND        
            e.rnr = p.rnr AND p.action = 'sign' AND 
            e.tdb_eco_id = '3259';

             //p.tdb_people_id = e.tdb_people_id AND 
        */


    }
}