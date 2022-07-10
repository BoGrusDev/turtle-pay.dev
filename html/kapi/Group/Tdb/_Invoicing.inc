<?php
/*
     InvoicingClass
   	Get the compentions for a organization and return all 
	that today day no expieer

	https://app.equipe.com/organizers/515/meetings.json

	prodOn means get from API else get from local file

	{
		"_group" : "Tdb",
		"_action" : "Invoicing",
        "_event_id" : "663",
		"_user_id" : "138",
        "_operator_id" : "1",
        "_file_name" : vasby-fixed.json"
	}	

*/
require_once 'Group/Tdb/TdbBase.inc';

class InvoicingClass extends TdbBaseClass {

    private $userId;
	private $operatorId;
    private $eventId; 
    private $fileName;
    private $eventName;
    private $invoiceEventId;
    private $eventRef;
    private $invoicingId;
    private $tdbApikey;
	private $tdbOrgno;
    private $competionsIndex;
	private $list;
    private $matchIndex;
    private $invoiceCounter;
    private $invoicingIdPrev;
    private $tdb_last;
  
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
        $this->notProcessedRemove();
        
        // die('removed');

        /*
            Get latest invoice id for this event
            if so set invoicingIdPrev to latest or 0 if first
        */
        $this->invoicingIdPrevGet();
        
        /*
            Crete index to match option in event inti matchIndex
            use the extermal ref in selection_ setting
        */
        $this->matchIndexCreate();
        

        /*
            Get the test data
        */  

        //$this->fileName = '69-648-2022-03-09-1303.json';
        // $this->fileName = '69-134-test-1.json';
        $this->list = json_decode(file_get_contents('tdb-files/' . $this->fileName)); 
        //$this->list = json_decode(file_get_contents("Group/Tdb/people-41991.json")); 

        /*
            Get the real data and create a file for that
        */

        // $list = $this->_RestApiTdb('meetings/' . $data->_competion_id . '/people.json', $data->_company_id );

        if (is_array($this->list) == false) {
            return array("code"=>"0");
        }

        /*
            Create name index, to add to the eco record. nameIndex
        */
        $this->nameIndexCreate();

        /*
            Create the Tdb Invocing group
        */
        if ($this->tdbInvoicingCreate() == false) {
			return array("code"=>"0");
		}
        
        /*
            Process the json file and inserti it to tdb_peope, tdb_eco aand td_part
            action vill be set to proc = mean wil be processed
        */
        $this->fileProcess();
        

        /*
            Process each person with eco record.
            It will also look back in history and se if something changed
        */
        $this->ecoProcess();
        

        $this->_peopleRemovedCredit() ;

        // die('eco');

        $this->invoiceCreate();

        $this->eventLastInvoiced();

        $reply = new stdClass();
        $reply->processed = sizeof($this->list);
        $reply->invoiced = $this->invoiceCounter;
        $reply->tdb_last = $this->tdb_last;
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
        if (isset($data->_file_name)) {
			$this->fileName = trim($data->_file_name);
		}
		else {
			return false;
		}
        return true;

        /*
            $reply= $this->TdbSettingGet($this->userId);
            if ($reply['code'] != '1') {
                return false;
            }
            $this->tdbApikey = $reply['tdb_apikey'];
            $this->tdbOrgno = $reply['tdb_orgno'];
            return true;
        */
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

    private function invoicingIdPrevGet() {
        // Get previous Invoicing ID
        $sql = "SELECT tdb_invoicing_id FROM tdb_invoicing WHERE event_id = $this->eventId ORDER BY tdb_invoicing_id DESC LIMIT 1";
        $res = $this->_Get($sql);
        if ($res['code'] == '1') {
            $this->invoicingIdPrev = $res['tdb_invoicing_id'];
        }
        else {
            $this->invoicingIdPrev = 0;
        }
    }

    private function matchIndexCreate() {
        /*
            Match with event form
        */
        $sql = "SELECT s.external_id, s.text, s.external_type, o.value, o.event_option_setting_id ";
        $sql .= "FROM event_selection_setting s, event_option_setting o ";
        $sql .= "WHERE event_id = $this->eventId AND ";
        $sql .= "s.event_selection_setting_id = o.event_selection_setting_id";
        $this->matchIndex = $this->_GetList($sql);
        for ($i=0; $i<sizeof($this->matchIndex); $i++) {
            $this->matchIndex[$i]['external_id'] = $this->_nullFix($this->matchIndex[$i]['external_id']);
        }
    }

    private function tdbInvoicingCreate() {
        $param = new stdClass();
        $param->event_id = $this->eventId;
        $reply = $this->_Insert('tdb_invoicing', $param); 
        if ($reply['code'] == '1') {
            $this->invoicingId = $reply['id'];
            return true;
        }
        else {
            return false;
        }
    }

    private function nameIndexCreate() {
        // - Create Nameindex for Lookup Riders
        $this->nameIndex = array();
		for ($i=0; $i<sizeof($this->list); $i++) {	
            $this->nameIndex[$this->list[$i]->rnr] = new stdClass();
            $this->nameIndex[$this->list[$i]->rnr]->name = $this->list[$i]->name;
            $this->nameIndex[$this->list[$i]->rnr]->first_name = $this->list[$i]->first_name;
            $this->nameIndex[$this->list[$i]->rnr]->last_name = $this->list[$i]->last_name;
		}
    }

	private function fileProcess() {
        /*
            Insert into tdb_people and tdb_eco
            Onlye people who has eco records will be inserted, 
            and the eco_post for that person.
            Also riders name will be macthed with the nameIndex.
            Connection with the Webforms is matched with the matchIndex.
            tdb_people.active = p (be procces)
            tdb_eco.active = pro (be processed)
        */
        for ($i=0; $i<sizeof($this->list); $i++) {
        // for ($i=0; $i<1; $i++) {
            $param = new stdClass();
            $param->tdb_invoicing_id = $this->invoicingId;
            $param->event_id = $this->eventId;
            if ($this->list[$i]->rnr) {
                $param->rnr = $this->list[$i]->rnr;
            }
            if ($this->list[$i]->internet_rnr) {
                $param->internet_rnr = $this->list[$i]->internet_rnr;
            }
            if ($this->list[$i]->knr) {
                $param->knr = $this->list[$i]->knr;
            }
            $param->name = $this->list[$i]->name;
            $param->first_name = $this->list[$i]->first_name;
            $param->last_name = $this->list[$i]->last_name;
            $param->company = $this->list[$i]->company;
            $param->epost = $this->list[$i]->epost;
            if ($this->list[$i]->rlic) {
                $param->rlic = $this->list[$i]->rlic;
            }
            $param->mobil = $this->list[$i]->mobil;
            $res = $this->_Insert('tdb_people', $param);
            $tdbPeopleId = $res['id'];
            if (sizeof($this->list[$i]->eco->economies) > 0) {
                for ($j=0; $j<sizeof($this->list[$i]->eco->economies); $j++) {
                    if (( float) $this->list[$i]->eco->economies[$j]->total == 0) {
                        // SKIP IF NO COST
                    }
                    else {
                        $param2 = new stdClass();
                        $param2->tdb_people_id = $tdbPeopleId;
                        $param2->event_id = $this->eventId;
                        $param2->tdb_invoicing_id = $this->invoicingId;
                        if ($this->list[$i]->eco->economies[$j]->id) {
                            $param2->id = $this->list[$i]->eco->economies[$j]->id;
                        }
                        $param2->fee_type = $this->_nullFix($this->list[$i]->eco->economies[$j]->fee_type);
                        $param2->rnr = $this->list[$i]->eco->economies[$j]->rnr;
                        if (isset($this->nameIndex[$this->list[$i]->eco->economies[$j]->realrnr])) {
                            $param2->name =  $this->nameIndex[$this->list[$i]->eco->economies[$j]->realrnr]->name;
                            $param2->first_name =  $this->nameIndex[$this->list[$i]->eco->economies[$j]->realrnr]->first_name;
                            $param2->last_name =  $this->nameIndex[$this->list[$i]->eco->economies[$j]->realrnr]->last_name;
                        }
                        else {
                            $param2->name = '';
                            $param2->first_name = '';
                            $param2->last_name = '';
                        }
                        if ($this->list[$i]->eco->economies[$j]->realrnr) {
                            $param2->realrnr = $this->list[$i]->eco->economies[$j]->realrnr;
                        }
                        if ($this->list[$i]->eco->economies[$j]->hnr) {
                            $param2->hnr = $this->list[$i]->eco->economies[$j]->hnr;
                        }
                        $param2->qty = $this->list[$i]->eco->economies[$j]->qty;
                        $param2->description = $this->list[$i]->eco->economies[$j]->description;
                        $param2->vat = $this->list[$i]->eco->economies[$j]->vat;
                        $param2->amount = $this->list[$i]->eco->economies[$j]->amount;
                        $param2->total = $this->list[$i]->eco->economies[$j]->total;
                        if ($this->list[$i]->eco->economies[$j]->tax_percent) {
                            $param2->tax_percent = $this->list[$i]->eco->economies[$j]->tax_percent;
                        }
                        if ($this->list[$i]->eco->economies[$j]->competition_no) {
                            $param2->competition_no = $this->_nullFix($this->list[$i]->eco->economies[$j]->competition_no);
                        }
                        if ($this->list[$i]->eco->economies[$j]->horse_name) {
                            $horseName = $this->list[$i]->eco->economies[$j]->horse_name;
                            //echo $horseName;
                            $horseName = str_replace('"', '', $horseName);
                            //echo $horseName;
                            $param2->horse_name = $horseName;
                        }
                        if ($this->list[$i]->eco->economies[$j]->horse_num) {
                            $param2->horse_num = $this->list[$i]->eco->economies[$j]->horse_num;
                        }
                        if ($this->list[$i]->eco->economies[$j]->removable) {
                            $param2->removable = 'y';
                        }
                        else {
                            $param2->removable = 'n';
                        }
                        /*
                            Get Text from the Webform
                         */
                        if ($param2->fee_type == 'discount') {
                            $param2->text = 'Rabatt';
                            $param2->event_option_setting_id = 0; 
                        }
                        else {
                            $matchObj = $this->_matchGetFromIndex(    
                                $this->list[$i]->eco->economies[$j]->amount, 
                                $this->list[$i]->eco->economies[$j]->competition_no,
                                $this->list[$i]->eco->economies[$j]->description,
                                $param2->fee_type
                            );
                            $param2->text = $matchObj->text;
                            $param2->event_option_setting_id = $matchObj->event_option_setting_id;
                        }
                        $res2 = $this->_Insert('tdb_eco', $param2);
                    }
                }
            }
            if (sizeof($this->list[$i]->eco->payers) > 0) {
                for ($j=0; $j<sizeof($this->list[$i]->eco->payers); $j++) {
                    $param3 = new stdClass();
                    $param3->tdb_people_id = $tdbPeopleId;
                    $param3->id = $this->list[$i]->eco->payers[$j]->id;
                    $param3->name = $this->list[$i]->eco->payers[$j]->name;
                    $res3 = $this->_Insert('tdb_payer', $param3);
                }
            }
        }
       
	}

    private function _matchGetFromIndex($amount, $competitionNo, $description, $feeType) {
        $reply = new stdClass();
        $reply->text = $description;
        $competitionNo = $this->_nullFix($competitionNo);
        $reply->event_option_setting_id = -1;
        if ($feeType == 'entry') {
            $feeColumn = 'anm,anmb';
        }
        else if ($feeType == 'late-entry') {
            $feeColumn = 'eanma,eanmb';
        }
        else {
            $feeColumn = '';
        }
        $text = '';
        $eventOptionSettingId = -1;
       
        for ($i=0; $i<sizeof($this->matchIndex); $i++) {
            if ($competitionNo == $this->matchIndex[$i]['external_id']) {
                if ($amount == $this->matchIndex[$i]['value'] && strpos($feeColumn, $this->matchIndex[$i]['external_type']) >=0 ) {
                    // Extact match
                    $reply->text = $this->matchIndex[$i]['text'];
                    $reply->event_option_setting_id = $this->matchIndex[$i]['event_option_setting_id'];
                   
                }
            }
        }
        // Not found Get first in same competion 
        
        if ($reply->event_option_setting_id == -1) {
            for ($i=0; $i<sizeof($this->matchIndex); $i++) {
                if ($competitionNo == $this->matchIndex[$i]['external_id']) {
                    $reply->text = $this->matchIndex[$i]['text'];
                    $reply->event_option_setting_id = $this->matchIndex[$i]['event_option_setting_id'];
                    break;
                }
            }
        }
        return $reply;
    }

    private function ecoProcess() {
        /*
            Check each eco record thats has a proc
            action same for bith people and eco.
            proc = top be processed
            inv = to be invoiced
            cre = credit to be
            cred = credit
            priz = prise record
            paym = external payment or direct to TDB
            skip = skip (invoied before)
            del - deleted

            Flow
            - Load all people from tdb_people in this invoicing (meetings)
            - Loop true all people and get there eco_record
            - Set the $invocieActive to false (indicate that noth showed up yet, that need to be a new invoice.)
            - If it is the first Invoicing indicate all by inv (to be invoiced) 
              skip fee_type payment set action to payment same with prize_money set action  to priz
            - If not first call the _ecoCheck function for each eco record and pass the record as parameter
        
            */
        
        // $this->invoicingId = 1;
        $sql = "SELECT * FROM tdb_people WHERE tdb_invoicing_id = $this->invoicingId AND action='proc'";
        $people = $this->_GetList($sql);
        
        if (sizeof($people) > 0) {
            //for ($i=0; $i<1; $i++) {
            for ($i=0; $i<sizeof($people); $i++) {

                $invocieActive = $this->_ecoMatch($people[$i]['tdb_people_id'], $people[$i]['rnr']);

                $paramPeople = new stdClass();
                if ($invocieActive) {
                    $paramPeople->action = 'inv';
                } 
                else {
                    $paramPeople->action = 'skip';
                }
                $reply = $this->_Update('tdb_people', 'tdb_people_id', $people[$i]['tdb_people_id'], $paramPeople);
              
            }
        }
    }

    private function _ecoMatch($tdbPeopleId, $rnr) {

        $invocieActive = false;
        // Load current 
        $sql = "SELECT * FROM tdb_eco ";
        $sql .= "WHERE tdb_people_id = " . $tdbPeopleId . " AND action = 'proc'";
        $ecoCurrent = $this->_GetList($sql);

        // Load previous inv
        $sql = "SELECT * FROM tdb_eco ";
        $sql .= "WHERE rnr = $rnr AND event_id = $this->eventId AND ";
        $sql .= "action IN('inv') ";
        $sql .= "ORDER BY tdb_invoicing_id;";
        $ecoPrev = $this->_GetList($sql);

        // Set status pre (not find)
        if (sizeof($ecoCurrent) > 0 ) {
            for ($i=0; $i<sizeof($ecoCurrent); $i++) {
                $ecoCurrent[$i]['status'] = 'pre';
            }
        }
        // Set status pre (not find)
        if (sizeof($ecoPrev) > 0 ) {
            for ($i=0; $i<sizeof($ecoPrev); $i++) {
                $ecoPrev[$i]['status'] = 'pre';
            }
        }

        // check if the current already exist 
        if (sizeof($ecoCurrent) > 0 ) {
            for ($i=0; $i<sizeof($ecoCurrent); $i++) {
                if ($ecoCurrent[$i]['fee_type'] == 'payment') {
                    $ecoCurrent[$i]['action'] = 'paym';
                    $ecoCurrent[$i]['status'] = 'spec'; // special
                }
                else if ($ecoCurrent[$i]['fee_type'] == 'prize_money') {
                    $ecoCurrent[$i]['action'] = 'priz';
                    $ecoCurrent[$i]['status'] = 'spec'; // special
                }
                else if ($ecoCurrent[$i]['fee_type'] == 'extra') {
                    $ecoCurrent[$i]['action'] = 'extr';
                    $ecoCurrent[$i]['status'] = 'spec'; // special
                }
                else if (sizeof($ecoPrev) > 0 ) {
                    for ($j=0; $j<sizeof($ecoPrev); $j++) {
                        if  ($ecoCurrent[$i]['id'] == $ecoPrev[$j]['id'] &&
                            $ecoCurrent[$i]['fee_type'] == $ecoPrev[$j]['fee_type'] &&
                            $ecoCurrent[$i]['realrnr'] == $ecoPrev[$j]['realrnr'] &&
                            $ecoCurrent[$i]['total'] == $ecoPrev[$j]['total'] &&
                            $ecoCurrent[$i]['competition_no'] == $ecoPrev[$j]['competition_no'] &&
                            $ecoCurrent[$i]['horse_num'] == $ecoPrev[$j]['horse_num']) 
                        {
                            $ecoCurrent[$i]['status'] = 'exist';
                        }
                    }
                }
            }
        }

        //echo json_encode($ecoCurrent);

        if (sizeof($ecoPrev) > 0 ) {
            for ($i=0; $i<sizeof($ecoPrev); $i++) {
                if (sizeof($ecoCurrent) > 0 ) {
                    for ($j=0; $j<sizeof($ecoCurrent); $j++) {
                        if ($ecoCurrent[$j]['status'] != 'spec') { 
                            if  ($ecoPrev[$i]['id'] ==  $ecoCurrent[$j]['id'] &&
                                $ecoPrev[$i]['fee_type'] == $ecoCurrent[$j]['fee_type'] &&
                                $ecoPrev[$i]['realrnr'] == $ecoCurrent[$j]['realrnr'] &&
                                $ecoPrev[$i]['total'] == $ecoCurrent[$j]['total'] &&
                                $ecoPrev[$i]['competition_no'] == $ecoCurrent[$j]['competition_no'] &&
                                $ecoPrev[$i]['horse_num'] == $ecoCurrent[$j]['horse_num']) 
                            {
                                $ecoPrev[$i]['status'] = 'exist';
                            }
                        }
                    }
                }
            }
        }

        // if not exist before
        for ($i=0; $i<sizeof($ecoCurrent); $i++) {
            $param = new stdClass();
         
            if ($ecoCurrent[$i]['status'] == 'pre') {
                $param->action = 'inv';
                $invocieActive = true;
            }
            else if ($ecoCurrent[$i]['status'] == 'spec') {
                $param->action = $ecoCurrent[$i]['action'];
            } 
            else {
                $param->action = 'skip';
            }
            $this->_Update('tdb_eco', 'tdb_eco_id', $ecoCurrent[$i]['tdb_eco_id'], $param);
        }

        // If not exist in the new, so the previous has to be credit
        for ($i=0; $i<sizeof($ecoPrev); $i++) {
            if ($ecoPrev[$i]['status'] == 'pre') {  // FIX
                $param = new stdClass();
                $param->action = 'cre';
                $this->_Update('tdb_eco', 'tdb_eco_id', $ecoPrev[$i]['tdb_eco_id'], $param);
            }
        }

        return $invocieActive;

    }

    private function _peopleRemovedCredit() {
        //$invoicingIdPrev = 11;
        //$invoicingId = 12;

        $sql = "SELECT rnr FROM tdb_people WHERE tdb_invoicing_id = $this->invoicingIdPrev";
        $peoplePrev = $this->_GetList($sql);

        $sql = "SELECT rnr FROM tdb_people WHERE tdb_invoicing_id = $this->invoicingId";
        $peopleCurrent = $this->_GetList($sql);

        if (sizeof($peoplePrev) > 0 ) {
            for ($i=0; $i<sizeof($peoplePrev); $i++) {
                $peoplePrev[$i]['status'] = 'pre';
                if (sizeof($peopleCurrent) > 0 ) {
                    for ($j=0; $j<sizeof($peopleCurrent); $j++) {
                        if  ($peoplePrev[$i]['rnr'] ==  $peopleCurrent[$j]['rnr'] ) {
                            $peoplePrev[$i]['status'] = 'exist';
                        }
                    }
                }
            }
        }
        // Check if has status pre, the credit
        if (sizeof($peoplePrev) > 0 ) {
            for ($i=0; $i<sizeof($peoplePrev); $i++) {
                if ($peoplePrev[$i]['status'] == 'pre') {
                    $sql = "UPDATE tdb_eco SET action='cre' WHERE action='inv' AND rnr=" . $peoplePrev[$i]['rnr'];
        
                    $this->_query($sql);

                    // Load previous inv
                    /*
                    $sql = "SELECT * FROM tdb_eco ";
                    $sql .= "WHERE rnr = " . $peoplePrev[$i]['rnr']  . " AND ";
                    $sql .= "action IN('inv') ";
                    $sql .= "ORDER BY tdb_invoicing_id;";
                    $ecoPrev = $this->_GetList($sql);
                    */
                }
            }
        }
        
        // echo json_encode( $peoplePrev);
        
    }

    private function invoiceCreate() {
        $counter = 0;
        $sql = "SELECT * FROM tdb_people WHERE tdb_invoicing_id = $this->invoicingId AND action='inv'";
        $people = $this->_GetList($sql);
        if (sizeof($people) > 0) {
            for ($i=0; $i<sizeof($people); $i++) {
                $param = new stdClass();
                $param->invoice_event_id = $this->invoiceEventId;
                $itemCode = $this->_GUI();
                $param->invoice_event_item_code = $itemCode;
                $param->event_id = $this->eventId; 
                $param->people_name = $people[$i]['name'];
                $param->email = $people[$i]['epost'];
                $param->mobile = $people[$i]['mobil'];
                $param->referens = $this->eventRef;
                $param->invoice_event_item_status =  'p'; 
                $param->planed_date = date('Y-m-d'); 
                $param->tdb_item = 'y';
                    
                $reply = $this->_Insert("invoice_event_item", $param);
                $paramPeople = new stdClass();
                if ($reply['code'] == '1') {
                    //$paramPeople->active = 'c';
                    $paramPeople->item_code = $itemCode;
                    $counter++;
                } 
                else {
                    $paramPeople->active = 'e';
                }
                $reply = $this->_Update('tdb_people', 'tdb_people_id', $people[$i]['tdb_people_id'], $paramPeople);
            }
        }
        $this->invoiceCounter = $counter;
    }

    private function eventLastInvoiced() {
        $param = new stdClass();
		$param->tdb_last = date("Y-m-d H:i");
        $this->tdb_last = $param->tdb_last;
		$this->_Update('event_v4', 'event_id', $this->eventId, $param);
    }

    private function _nullFix($string) {
		if (is_null($string)) {
			return '';
		} 
		else {
			return  trim($string);
		}
	}
}