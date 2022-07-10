<?php
/*
    SelectionsLoadLoadClass 
    {
        "_group": "Tdb",
        "_action": "Request",
        "_web_app_tdb_log_id" : "1",
        "personal_id_number": "195711040054",
        "amount": 1188,
        "receipt_number": "TDB - Betalning",
        "email": "bo.grus@yahoo.com",
        "mobile": "0729427977",
        "participant_on": "y",
        "participant": [{
            "first_name": "Amanda Filippa",
            "last_name": "A Deild",
            "horse_name": "Jevory W",
            "option": [{
                "event_option_setting_id": "5505",
                "text": "5 - WE Lätt B:1",
                "value": "350",
                "status": "a"
            }, {
                "event_option_setting_id": "5506",
                "text": "4 - WE Lätt B:2",
                "value": "250",
                "status": "a"
            }, {
                "event_option_setting_id": "5509",
                "text": "1 - WAWE Svår Kür",
                "value": "350",
                "status": "a"
            }, {
                "event_option_setting_id": "-1",
                "text": "Anmälningsavgift, Veterinär",
                "value": "150",
                "status": "a"
            }, {
                "event_option_setting_id": "-1",
                "text": "Meetingavgift, Veterinäravgift",
                "value": "88",
                "status": "a"
            }]
        }],
        "people_company_on": "y",
        "people_company": "Snabb data AB",
        "people_company_address": "Box 9811",
        "people_company_postcode": "11220",
        "people_company_city": "Stockholm",
        "company_id": "69",
        "_invoice_event_id": "337",
        "_invoice_event_item_id": "14429",
        "event_id": "636",
        "_visitor": ""
    }
            
*/

require_once 'Group/WebAppTdb/WebAppTdbBase.inc';

class RequestClass extends WebAppTdbBaseClass {

    private $reply;
    private $personalIdNumber;
	private $amount;
	private $receiptNumber;
	private $email;
	private $mobile;
	private $participantOn;
	private $participant;
	private $peopleCompanyOn;
	private $peopleCompany;
	private $peopleCompanyAddress;
	private $peopleCompanyPostcode;
	private $peopleCompanyCity;
	private $companyId;
	private $invoiceEventId;
	private $invoiceEventItemId;
	private $eventId;
	// "_visitor": ""
    private $invoiceRequest;
    private $eventItemId;
    private $paramError;
	
    public function _($data) {

        $this->webAppTdbLoggAction = "Request";

		if ($this->parameterCheck($data) == false) {
            $this->_WebWebAppTdbLog((object) ['part'=>'paramCheck', 'step'=>"fail",'step_ref'=>$this->paramError]);
			return array("code"=>"0", "denied_code"=>"parameter-fail",'param'=>$this->paramError );
		}

        $replyPep = $this->pepCheck($this->personalIdNumber);
        if ( $replyPep->code == '6') {
            return $replyPep;
        }

        // Get the store_id and sales person
        if ($this->companyInfo() == false) {
            return array('code'=>'0', 'denide_code'=>'company-info-fail');
		}
        
        // Do the standard invopice requst
       if ($this->invoiceRequestCall() == false) {
           return $this->invoiceRequest;
       }
       
        $this->reply = new stdClass();
        if ($this->signInit()== false) {
            return $this->reply;
        }
        
        // Add event items, like options
        if ($this->eventItemAdd() == false) {
            return array('code'=>'0', 'denide_code'=>'item-add-fail');
        }
        
        // Write all the the log (need it, when process)
        if ($this-> logWrite() == false) {
            return array('code'=>'0', 'denide_code'=>'log-write-fail');
        }
        
        $this->reply->order_ref = $this->orderRef;
        $this->reply->approved_code = $this->invoiceRequest->approved_code;
        $this->reply->auto_start_token = $this->autoStartToken;
        $this->reply->code = '1';
        return $this->reply;
    }

    private function parameterCheck($data) {

        if (isset($data->_web_app_tdb_log_id)) {
			$this->webAppTdbLogId = trim($data->_web_app_tdb_log_id);
            $this->_WebWebAppTdbLog((object) ['part'=>'Enter']);
		}
		else {
            $this->paramError = '_web_app_tdb_log_id';
			return false;
		}
        if (isset($data->personal_id_number)) {
			$this->personalIdNumber = trim($data->personal_id_number);
		}
		else {
            $this->paramError = 'personal_id_number';
			return false;
		}
        if (isset($data->amount)) {
            $this->amount = trim($data->amount);
		}
		else {
            $this->paramError = 'amount';
			return false;
		}
        if (isset($data->receipt_number)) {
            $this->receiptNumber = trim($data->receipt_number);
		}
		else {
            $this->paramError = 'receipt_number';
			return false;
		}
        if (isset($data->email)) {
            $this->paramError = 'email';
            $this->email = trim($data->email);
		}
		else {
			return false;
		}
        if (isset($data->mobile)) {
            $this->mobile = trim($data->mobile);
		}
		else {
            $this->paramError = 'mobile';
			return false;
		}
        if (isset($data->participant_on)) {
            $this->participantOn = trim($data->participant_on);
		}
		else {
			return false;
		}
        if (isset($data->participant)) {
            $this->participant = $data->participant;
		}
		else {
			return false;
		}
        
        if (isset($data->people_company_on)) {
            $this->peopleCompanyOn = trim($data->people_company_on);
		}
		else {
			return false;
		}

        if ($this->peopleCompanyOn == 'y') {
            if (isset($data->people_company)) {
                $this->peopleCompany = trim($data->people_company);
            }
            else {
                return false;
            }
            
            if (isset($data->people_company_address)) {
                $this->peopleCompanyAddress = trim($data->people_company_address);
            }
            else {
                return false;
            }
            if (isset($data->people_company_postcode)) {
                $this->peopleCompanyPostcode = trim($data->people_company_postcode);
            }
            else {
                return false;
            }
            if (isset($data->people_company_city)) {
                $this->peopleCompanyCity = trim($data->people_company_city);
            }
            else {
                return false;
            }
        }
        if (isset($data->company_id)) {
            $this->companyId = trim($data->company_id);
		}
		else {
			return false;
		}
        if (isset($data->_invoice_event_id)) {
            $this->invoiceEventId = trim($data->_invoice_event_id);
		}
		else {
			return false;
		}
        if (isset($data->_invoice_event_item_id)) {
            $this->invoiceEventItemId = trim($data->_invoice_event_item_id);
		}
		else {
			return false;
		}
        if (isset($data->event_id)) {
            $this->eventId = trim($data->event_id);
		}
		else {
			return false;
		}
        
        if (isset($data->infobox_1)) {
            $this->infobox_1 = $data->infobox_1;
        }
        if (isset($data->infobox_2)) {
            $this->infobox_2 = $data->infobox_2;
        }


		return true;
	}

    private function companyInfo() {
        $sql = "SELECT c.wa_store_id, c.wa_sp_id, s.store_name, c.known_as AS company_name ";
        $sql .= "FROM company c, store s ";
        $sql .= "WHERE c.company_id = $this->companyId AND c.wa_store_id = s.store_id";
        $result = $this->_Get($sql);
        if ($result['code'] == '1') {
            $this->storeId = $result['wa_store_id'];
            $this->spId = $result['wa_sp_id'];
            $this->storeName = $result['store_name'];
            $this->companyName = $result['company_name'];
            return true;
        }
        else {
            $this->_WebWebAppTdbLog((object) ['part'=>'companyInfo', 'step'=>"Select Fail", 'step_ref'=>$this->companyInfo]);
            return false;
        }
    }

    private function invoiceRequestCall() {
        $param = new StdClass();
        $param->_group = "InvoiceRequest";
        $param->_action = "Start";

        $param->company_id = $this->companyId;
        $param->store_id = $this->storeId;
        $param->sales_person_people_id = $this->spId;

        //$param->cr_id = '1';
        $param->_uc_confirm = 'n'; // $this->uc_confirm;
        $param->personal_id_number = $this->personalIdNumber;
        $param->amount = $this->amount;
        $param->source = "TB";
        $param->device = "web";
        $this->invoiceRequest = $this->_RestApiCall($param, CAPI_URL);
        if ($this->invoiceRequest->code == '1') {
            // echo json_encode($this->invoiceRequest); die('');
            $this->_WebWebAppTdbLog((object) ['part'=>'invoiceRequestCall', 'step'=>"Call OK",'step_ref'=>$this->invoiceRequest->approved_code]);
            return true;
        }
        else {
            $this->_WebWebAppTdbLog((object) ['part'=>'invoiceRequestCall', 'step'=>"Call Fail", 'step_ref'=>$this->invoiceRequest->denied_code]);
            return false;
        }
    }
    
    private function signInit() {
        $bankIdText = str_replace('_ReceiptNumber_' ,$this->receiptNumber, $this->invoiceRequest->bankid_text);
        $param = new StdClass();
        $param->_group  = "BankId";
        $param->_action = "SignInit";
        $param->_personal_id_number = $this->personalIdNumber;
        $param->_bankid_text = $bankIdText;
        //echo json_encode($param);
        //return false;
        $reply = $this->_RestApiCall($param, INTERNAL_API);
        if ($reply->code == '1') {
            $this->_WebWebAppTdbLog((object) ['part'=>'SignInit', 'step'=>"OK",'step_ref'=>$reply->order_ref]);
            $this->orderRef = $reply->order_ref;
            $this->autoStartToken = $reply->auto_start_token;
            return true;
        }
        else {
            $this->_WebWebAppTdbLog((object) ['part'=>'SignInit', 'step'=>"Fail", 'step_ref'=>$reply->denied_code]);
            $this->reply->code = $reply->code;
            $this->reply->denied_code = $reply->denied_code;
            return false;
        }
        // return json_decode($this->_RestApiCall(json_encode($param)));
    }
    
    private function eventItemAdd() {

        $param = new StdClass();
        $param->event_id = $this->eventId;
        $param->approved_code = $this->invoiceRequest->approved_code;
        $param->event_item_status = 'p';
        $param->email = $this->email;
        if (isset($this->mobile)) {
            $param->mobile = $this->mobile;
        }
        $param->referens = $this->receiptNumber;
        $param->amount = $this->amount;
        $param->_participant_on = 'y';
        $param->_participant = $this->participant;          
    
        if (isset($this->infobox_1)) {
            $param->infobox_1 = $this->infobox_1;
        }
        if (isset($this->infobox_2)) {
            $param->infobox_2 = $this->infobox_2;
        }
    
        $param->invoice_event_item_id = $this->invoiceEventItemId;
        if ($this->peopleCompanyOn == 'y') {
            $param->people_company_on = 'y';
            $param->people_company = $this->peopleCompany;
            $param->people_company_address = $this->peopleCompanyAddress;
            $param->people_company_postcode = $this->peopleCompanyPostcode;
            $param->people_company_city = $this->peopleCompanyCity;
        } 
        else {
            $param->people_company_on = 'n';
        }
        //print_r($param); 
        $reply = $this->_Insert('event_item_v4', $param);
        //print_r($reply);
        //die('');
        if ($reply['code'] == '1') {
            if ($this->participantOn == 'y' ) {
                for ($i=0; $i < sizeof($this->participant); $i++) {
                    $participant = new stdClass();
                    $participant->event_item_id = $reply['id'];
                    $participant->first_name = $this->participant[$i]->first_name;
                    $participant->last_name = $this->participant[$i]->last_name;
                   
                    // Added for notes
                    //if (isset($this->participant[$i]->note)) {
                        $participant->note = $this->participant[$i]->horse_name;
                    //}
                   
                    // $participant->base_participant_id = $data->_participant[$i]->base_participant_id;

                    $replyPart = $this->_Insert('event_participant', $participant);
                    
                    //if ($this->participant[$i]->base_participant_id == '0') {
                        $param = new stdClass();
                        $param->base_participant_id = $replyPart['id'];
                        $this->_Update('event_participant', 'event_participant_id', $replyPart['id'], $param);
                    //}

                    for ($j=0; $j < sizeof($this->participant[$i]->option); $j++) {
                        $option = new stdClass();
                        $option->event_participant_id = $replyPart['id'];

                        $option->event_option_setting_id = $this->participant[$i]->option[$j]->event_option_setting_id;
                        $option->value = $this->participant[$i]->option[$j]->value;
                        $option->value_text = $this->participant[$i]->option[$j]->text;
                        $replyOption = $this->_Insert('event_option', $option);
                    }
                }
            }
        }
        else {
           return false;
        }

        $this->eventItemId = $reply['id'];
        $this->_WebWebAppTdbLog((object) ['part'=>'eventItemAdd', 'step'=>"Call OK", 'step_ref'=>$this->eventItemId]);
        return true;
    }

    private function logWrite() {
        $param = new StdClass();
        $param->order_ref = $this->orderRef;
        $param->receipt_number = $this->receiptNumber;
        $param->email = $this->email;
        $param->amount = $this->amount;
        $param->approved_code = $this->invoiceRequest->approved_code;
        $param->event_id = $this->eventId;
        $param->invoice_event_item_id = $this->invoiceEventItemId;
        $param->event_item_id = $this->eventItemId;
        $param->company_id = $this->companyId;
        // $param->store_id = $this->storeId;
        // $param->sales_person_people_id = $this->spId;
        $param->personal_id_number = $this->personalIdNumber;
        $param->uc = 'n'; 
        $reply = $this->_Insert('wa_log_v4', $param);
        if ($reply['code'] == '1') {
            $this->_WebWebAppTdbLog((object) ['part'=>"logWrite", "step"=>"Insert OK", "step_ref"=>$reply['id']]);
            return true;
        }
        else {
            $this->_WebWebAppTdbLog((object) ['part'=>"logWrite", "step"=>"Insert Fail"]);
            return false;
        }    
    }
    
    private function pepCheck($personalIdNumber) {
        $param = new stdClass();
        $param->_group = "People";
        $param->_action = "PepCheck";
        $param->_personal_id_number = $personalIdNumber;

        //echo json_encode($param);
        //die('');

        $res = $this->_RestApiCall($param, KAPI_URL);
        $data = $res;

        $param = new stdClass();

        if (isset($data->code)) {
            if ($data->code == '1' && $data->kyc_need == 'y') {
                $data->code = '6';
                // $param->people_id = $data->people_id;
                // $param->denied_code = "kyc-need";
                // echo json_encode(array("code"=>"6", "denied_code"=>"kyc-need"));
                return $data;
            }
            else {
                $data->code == '0';
                return $data;
            }
        }
    }
    
}
       
        