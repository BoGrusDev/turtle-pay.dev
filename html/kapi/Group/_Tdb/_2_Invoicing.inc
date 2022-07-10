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
        "_event_id" : "636",
		"_user_id" : "69",
        "_operator_id" : "1"
	}	

*/
require_once 'Group/Tdb/TdbBase.inc';

class InvoicingClass extends TdbBaseClass {

    private $userId;
	private $operatorId;
    private $eventId; 
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
  
    public function _($data) {

		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0");
		}

        if ($this->eventGet() == false) {
            return array("code"=>"0");
        }

        $this->invoicingIdPrevGet();
        
       
            // Firtt time with test
            // $this->tdbInvoicingIdPrev = 0;

            //$this->tdbInvoicingId = 2;
            //$this->ecoProcess();

            // die(' stop 55 ');
        

		/*
        // TEST
       
        $this->tdbInvoicingIdPrev = 2;
        
        $this->eventName = 'TDB Lindköping Race';

        $this->ecoProcess();
        $this->invoiceCreate();
        die('complete');
        */
        /*
        $this->ecoProcess();
        $this->invoiceCreate();

        $reply = new stdClass();
        $reply->counter = $this->invoiceCounter;
        $reply->code = '1';
        return $reply;
        die('');
        */

        $this->matchIndexCreate();
 
        // $this->list = json_decode(file_get_contents("Group/Tdb/list-564-1.json")); 
        $this->list = json_decode(file_get_contents("Group/Tdb/people-41991.json")); 


        if (is_array($this->list) == false) {
            return array("code"=>"0");
        }

        $this->nameIndexCreate();

        if ($this->tdbInvoicingCreate() == false) {
			return array("code"=>"0");
		}

        $this->fileProcess();

        $this->ecoProcess();

        $this->invoiceCreate();

        $reply = new stdClass();
        $reply->processed = sizeof($this->list);
        $reply->invoiced = $this->invoiceCounter;
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
        
		$reply= $this->TdbSettingGet($this->userId);
		if ($reply['code'] != '1') {
			return false;
		}
		$this->tdbApikey = $reply['tdb_apikey'];
		$this->tdbOrgno = $reply['tdb_orgno'];
		return true;
	}

    private function eventGet() {
        $sql = "SELECT event_name, ref, invoice_event_id FROM event_v4 WHERE event_id = $this->eventId ";
        $res = $this->_Get($sql);
        if ($res['code'] == '1') {
            $this->eventName = $res['event_name'];
            $this->invoiceEventId = $res['invoice_event_id'];
            $this->eventRef = $res['ref'];
            return true;
        }
        else {
            return false;
        }
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
            $this->matchIndex[$i]['external_id'] = trim($this->matchIndex[$i]['external_id']);
        }
    }

	private function fileProcess() {
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
                        $param2->fee_type = trim($this->list[$i]->eco->economies[$j]->fee_type);
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
                            $param2->competition_no = trim($this->list[$i]->eco->economies[$j]->competition_no);
                        }
                        if ($this->list[$i]->eco->economies[$j]->horse_name) {
                            $param2->horse_name = $this->list[$i]->eco->economies[$j]->horse_name;
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
        $competitionNo = trim($competitionNo);
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

        $sql = "SELECT * FROM tdb_people WHERE tdb_invoicing_id = $this->invoicingId AND active='p'";
        $people = $this->_GetList($sql);
        
        //print_r($people); die('');
       
        if (sizeof($people) > 0) {
            //for ($i=0; $i<1; $i++) {
            for ($i=0; $i<sizeof($people); $i++) {
                $sql = "SELECT tdb_eco_id, tdb_people_id, id, fee_type, rnr, realrnr, hnr, name, ";
                $sql .= "qty, description, vat, amount, total, tax_percent, competition_no, horse_name, ";
                $sql .= "horse_num, removable, text, event_option_setting_id, action ";
                $sql .= "FROM tdb_eco ";
                $sql .= "WHERE tdb_people_id = " . $people[$i]['tdb_people_id'] . " AND action = 'pro'";
                $eco = $this->_GetList($sql);

                //echo json_encode($eco);
                //die('');
                //return;
                $invocieActive = false;
                if (sizeof($eco) > 0) {

                    
                    // Check person exist
                    /*
                        $sql = "SELECT * ";
                        $sql .= "FROM tdb_people ";
                        $sql .= "WHERE rnr = " . $people[$i]['rnr'] . " AND ";
                        $sql .= "event_id = $this->eventId AND ";
                        $sql .= "tdb_invoicing_id <> $this->tdbInvoicingId ";
                        $person = $this->_GetList($sql);
                        print_r($person); die('');
                    */

                    for ($j=0; $j<sizeof($eco); $j++) {
                        if ( $this->invoicingIdPrev > 0) {
                            // If any previuce invocing exits
                            $reply = $this->_ecoCheck($eco[$j]);
                            // print_r($reply); die('');
                        } 
                        else {
                            // First invoicing
                            $reply = new stdClass();
                            $reply->action = 'inv';
                            $reply->actionPre = 'skip';
                        }
                        $param = new stdClass();
                        $param->action =  $reply->action;
                        $replyUpdate = $this->_Update('tdb_eco', 'tdb_eco_id', $eco[$j]['tdb_eco_id'], $param);
                        if ($reply->action == 'inv') {
                            // Om ny faktura ska skapas
                            $invocieActive = true;
                        }
                        if ($reply->actionPre == 'cre') {
                            // Om någon har ändratsm crediterinf
                            $paramCre = new stdClass();
                            $paramCre->action = 'cre'; 
                            $replyUpdate = $this->_Update('tdb_eco', 'tdb_eco_id', $reply->tdbEcoId, $paramCre);
                        }
                    }
                     
                }
                if ($this->invoicingIdPrev > 0) {
                    // Kollar om något blivir borraget is ssta, i såfall creditera tidgare
                    // $this->_ecoRemovedCheck();
                }

                $paramPeople = new stdClass();
                if  ($invocieActive) {
                    $paramPeople->active = 'i';
                } 
                else {
                    $paramPeople->active = 'n';
                }
                $reply = $this->_Update('tdb_people', 'tdb_people_id', $people[$i]['tdb_people_id'], $paramPeople);
                // die('');
            }

            

            /*
                $log = new stdClass();
                $log->people = $people[$i];
                $log->eco = $eco;
                echo json_encode($log);
                die('');
            */
        }
    }

    private function _ecoCheck($paramEco) {
        $eco = (object) $paramEco;
        $reply = new stdClass();
        $sql = "SELECT * FROM tdb_eco ";
        $sql .= "WHERE event_id = $this->eventId AND tdb_invoicing_id < $this->invoicingId AND ";
        $sql .= "rnr = $eco->rnr AND ";
        $sql .= "horse_num = $eco->horse_num AND ";
        if ($eco->fee_type == 'discount') {
            $sql .= "fee_type = 'discount' ";
        }
        else if ($eco->fee_type == 'meeting') {
            $sql .= "fee_type = 'meeting' ";
        }
        else {  
            $sql .= "id = $eco->id ";
        }
        $sql .= "ORDER BY tdb_invoicing_id";
        $ecoPrev = $this->_GetList($sql);
        //echo $sql;
        //print_r($ecoPrev);    
        if (sizeof($ecoPrev) > 0) {
            $index = sizeof($ecoPrev) -1; 
            if ($ecoPrev[$index]['action'] == 'noa' && $index > 0) {
                $found = false;
                while($found == false) {
                    $index--;
                    if ($ecoPrev[$index]['action'] != 'noa') {
                        $found = true;
                    }
                    else {
                        if ($index == 0) {
                            $index = sizeof($ecoPrev) -1; 
                            $found = true;
                        }
                    }
                }
            }
            
            if ($eco->fee_type == 'discount') {
                if ($eco->total != $ecoPrev[$index]['total']) {
                    $reply->action = 'inv'; // Credit
                    $reply->id = $eco->id;
                    $reply->actionPre = 'cre';
                    $reply->tdbEcoId = $ecoPrev[$index]['tdb_eco_id'];
               }
                else {
                    $reply->action = 'noa';
                    $reply->id = $eco->id;
                    $reply->actionPre = 'skip';
                }
            }
            else if ($eco->fee_type == ' meeting') {
                if ($eco->total != $ecoPrev[$index]['total']) {
                    $reply->action = 'inv'; // Credit
                    $reply->id = $eco->id;
                    $reply->actionPre = 'cre';
                    $reply->tdbEcoId = $ecoPrev[$index]['tdb_eco_id'];
                }
                else {
                    $reply->action = 'noa';
                    $reply->id = $eco->id;
                    $reply->actionPre = 'skip';
                }
            }
            else {
                if ($eco->total != $ecoPrev[$index]['total']) {
                    $reply->action = 'inv'; // Credit
                    $reply->id = $eco->id;
                    $reply->actionPre = 'cre';
                    $reply->tdbEcoId = $ecoPrev[$index]['tdb_eco_id'];
                }
                else if ($eco->horse_num != $ecoPrev[$index]['horse_num']) {
                    $reply->action = 'inv'; // Credit
                    $reply->id = $eco->id;
                    $reply->actionPre = 'cre';
                    $reply->tdbEcoId = $ecoPrev[$index]['tdb_eco_id'];
                }
                else if ($eco->competition_no != $ecoPrev[$index]['competition_no']) {
                    $reply->action = 'inv'; // Credit
                    $reply->id = $eco->id;
                    $reply->actionPre = 'cre';
                    $reply->tdbEcoId = $ecoPrev[$index]['tdb_eco_id'];
                }
            
                else if ($eco->realrnr != $ecoPrev[$index]['realrnr']) {
                    $reply->action = 'inv'; // Credit
                    // $reply->id = $eco->id;
                    $reply->actionPre = 'cre';
                    $reply->tdbEcoId = $ecoPrev[$index]['tdb_eco_id'];
                }
                else {
                    $reply->action = 'noa';
                    $reply->id = $eco->id;
                    $reply->actionPre = 'skip';
                }
            }
            /*
         
            */
        }
        else {
             // New 
             $reply->action = 'inv';
             $reply->id = $eco->id;
             $reply->actionPre = 'skip';
        }
        return $reply;
    } 

    private function _ecoRemovedCheck() {
        /*
            SELECT rnr, id, tdb_eco_id FROM tdb_eco pre 
            WHERE pre.tdb_invoicing_id = 2 AND NOT EXISTS 
            (SELECT * FROM tdb_eco WHERE tdb_invoicing_id = 3 AND pre.id = id AND rnr = pre.rnr)
            258, 6 14
        */

        $sql = "SELECT rnr, id, tdb_eco_id FROM tdb_eco pre  ";
        $sql .= "WHERE pre.tdb_invoicing_id = $this->invoicingIdPrev AND NOT EXISTS ";
        $sql .= "(SELECT * FROM tdb_eco WHERE tdb_invoicing_id = $this->invoicingId AND pre.id = id AND rnr = pre.rnr)";
        $list = $this->_GetList($sql);
        if (sizeof($list) > 0) {
            for ($i=0; $i<sizeof($list); $i++) {
                $sql = "SELECT tdb_eco_id FROM tdb_eco ";
                $sql .= "WHERE rnr = " . $list[$i]['rnr'] . " AND ";
                $sql .= "id = " . $list[$i]['id'] . " AND "; 
                $sql .= "action <> 'noa' AND ";
                $sql .= "event_id = $this->eventId " ;
                $sql .= "ORDER by tdb_invoicing_id LIMIT 1";
                $res = $this->_Get($sql);
                if ($res['code'] == '1') {
                    $paramCre = new stdClass();
                    $paramCre->action = 'cre'; 
                    $replyUpdate = $this->_Update('tdb_eco', 'tdb_eco_id', $res['tdb_eco_id'], $paramCre);
                }
            }
        }
    }
    
    private function invoiceCreate() {
        $counter = 0;
        $sql = "SELECT * FROM tdb_people WHERE tdb_invoicing_id = $this->invoicingId AND active='i'";
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
                    $paramPeople->active = 'c';
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

    /*
        private function actionEventCreate($data) {
            / *
                {
                    "_group": "InvoiceEvent",
                    "_action": "EventCreate",
                    "_token": "B0044A966CD85D29817AC36AA7C7BECF", 
                    "_user_id": "69", 
                    "_store_id": "67",
                    "invoice_event_name": "Ölfestival resa",
                    "event_id" : "114",
                    "_import": "y",
                    "_import_id": "48",
                    "_people_id" : "1",
                    "_company_id": "69"
                }

                SELECT amount, ref FROM event_v4 WHERE event_id = 114;

		* /
		/ *
		$sql = "SELECT amount, ref ";
		$sql .= "FROM event_v4 ";
		$sql .= "WHERE event_id = $data->event_id  ";
		$res = $this->_Get($sql);
		* /
	
		$data->company_id = $data->_company_id;
		$data->create_date =  date("Y-m-d");

		$result = $this->_Insert("invoice_event", $data);
		
		$sql = "SELECT child_on, inherit_event_id, ref FROM event_v4 WHERE event_id = $data->event_id"; 
		$event = $this->_Get($sql);

		if ($event['child_on'] == 'y') {
			// Import from inherit event;
			$sql = "SELECT * FROM event_item_v4 WHERE event_item_status = 'c' AND event_id  = " . $event['inherit_event_id'];
			$eventItem = $this->_GetList($sql);
			if (sizeof($eventItem) > 0) {
				for ($i = 0; $i < sizeof($eventItem); $i++) {
					$param = new stdClass();
					$param->invoice_event_id = $result['id'];
					$param->invoice_event_item_code = $this->_GUI();
					$param->event_id = $data->event_id; 
					$param->people_name = $eventItem[$i]['people_name'];
					$param->email = $eventItem[$i]['email'];
					$param->mobile = $eventItem[$i]['mobile'];
					$param->referens = $event['ref'];
					// $param->referens = $eventItem[$i]['referens'];
					$param->parent_event_item_id = $eventItem[$i]['event_item_id'];
					$param->invoice_event_item_status =  'p'; 
					
					$param->planed_date = date('Y-m-d'); 
						
					$reply = $this->_Insert("invoice_event_item", $param);
				}
			}
		}
		
		return json_encode($result);
    }
    */
    /*
    private function invoicedCheck() {
        $sql = "SELECT e.* ";
        $sql .= "FROM tdb_people p, tdb_eco e ";
        $sql .= "WHERE p.event_id = 624 AND ";
        $sql .= "p.rnr = 258 AND ";
        $sql .= "p.tdb_people_id = e.tdb_people_id AND ";
        $sql .= "e.competition_no = '60' AND ";
        $sql .= "e.total = '150' AND ";
        $sql .= "e.fee_type = 'entry' AND ";
        $sql .= "e.tdb_eco_status = 'n'"; 
        $res = $this->_GetList($sql);
        return 'i';
    }
    */

    /*
    private function process() {
        $sql = "SELECT * FROM tdb_people WHERE tdb_invoicing_id = 1";
        $peopleList = $this->_GetList($sql);

        // - Create Nameindex for Lookup Riders
        $nameIndex = array();
		for ($i=0; $i<sizeof($peopleList); $i++) {	
            $nameIndex[$peopleList[$i]['rnr']] = $peopleList[$i]['name'];
		}
        // Load all eco record and connect them to the person
        for ($i=0; $i<sizeof($peopleList); $i++) {	
            $sql = "SELECT * FROM tdb_eco WHERE tdb_people_id = " . $peopleList[$i]['tdb_people_id'] . ' ORDER BY rnr';
            $peopleList[$i]['eco'] = $this->_GetList($sql);
        }

        / *
        //for ($i=0; $i<sizeof($peopleList); $i++) {
        for ($i=0; $i<5; $i++) { 
            // Check if earlier
            if (sizeof($peopleList[$i]['eco']) > 0) {
                
                for ($j=0; $j<sizeof($peopleList[$i]['eco']); $j++) { 

                    print_r($peopleList[$i]);
                }
            }
        }
        * /

        print_r($peopleList);

    }
    */

    /*
        $people = array();
		$riderName = array();
		for ($i=0; $i<sizeof($list); $i++) {	
			$riderNameRecord = new stdClass();
			$riderNameRecord->rnr = $list[$i]->rnr;
			$riderNameRecord->first_name = $list[$i]->first_name; // Ryttare
			$riderNameRecord->last_name = $list[$i]->last_name; // Ryttare
			// array_push($riderName, $riderNameRiderRecord);
			$riderName[$list[$i]->rnr] = $riderNameRecord;
		}
    */


}