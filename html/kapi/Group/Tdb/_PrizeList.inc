<?php
/*
    PrizeListClass
   	

	https://app.equipe.com/organizers/515/meetings.json

	
	{
		"_group" : "Tdb",
		"_action" : "Prize",
        "_event_id" : "636",
		"_user_id" : "69",
        "_operator_id" : "1"
	}	

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
        
        /*
            Check if there are any tdb_eco or tdb_people that have the actioon 'proc' for this event,
            if so remove them, meaning set action to 'del' 
        */
        // $this->notProcessedRemove();
        
        // die('removed');

        /*
            Get latest invoice id for this event
            if so set invoicingIdPrev to latest or 0 if first
        */

        if ($this->invoicingLastIdGet() == false) {
            return array("code"=>"0", "denide_code"=>"no-invocing-done");
        }
        
        // echo $this->invoicingLastId;
        $this->prizeGetList();

        return $this->prizeList;



        /*
            Crete index to match option in event inti matchIndex
            use the extermal ref in selection_ setting
        */
        // -- $this->matchIndexCreate();
        

        /*
        if (is_array($this->list) == false) {
            return array("code"=>"0");
        }
        */ 
        /*
            Create name index, to add to the eco record. nameIndex
        */
        // -- $this->nameIndexCreate();

        /*
            Create the Tdb Invocing group
        */

        // - if ($this->tdbInvoicingCreate() == false) {
			// - return array("code"=>"0");
		// - }
        
        /*
            Process the json file and inserti it to tdb_peope, tdb_eco aand td_part
            action vill be set to proc = mean wil be processed
        */
        // - $this->fileProcess();
        

        /*
            Process each person with eco record.
            It will also look back in history and se if something changed
        */
        // - $this->ecoProcess();
        

        // - $this->_peopleRemovedCredit() ;

        // die('eco');

        // -$this->invoiceCreate();

        // $reply = new stdClass();
        //$reply->processed = sizeof($this->list);
        // $reply->invoiced = $this->invoiceCounter;
        // $reply->code = '1';
        // return $reply;
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

    private function notProcessedRemove() {
        /*
            Remove people and eco thats has not processed yet.
            This handle if something gonne wrong before.
        */
        $sql = "UPDATE tdb_eco SET action='del' WHERE action='proc' AND event_id = $this->eventId";
        $this->_Query($sql);

        $sql = "UPDATE tdb_people SET action='del' WHERE action='proc' AND event_id = $this->eventId";
        $this->_Query($sql);
       
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

}