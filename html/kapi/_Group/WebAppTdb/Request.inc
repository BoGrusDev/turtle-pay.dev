<?php
/*
    SelectionsLoadLoadClass 
    {
        "_group": "Tdb",
        "_action": "Request",
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

class RequestClass extends BaseClass {

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
	
    public function _($data) {

		if ($this->parameterCheck($data) == false) {
			return array("code"=>"0", "denied_code"=>"parameter-fail");
		}

        if ($this->companyInfo() == false) {
			return array("code"=>"0");
		}

        $this->reply = new StdClass();
        
       if ($this->invoiceRequestCall() == false) {
           return $this->invoiceRequest;
       }

       // $this->signInt();
       $this->orderRef = 'test-order-ref';

       if ($this->eventItemAdd() == false) {
            return array("code"=>"0");
        }
        if ($this-> logWrite() == false) {
            return array("code"=>"0");
        }
       
        //echo $this->eventItemId;
      
        $reply = '1';
        return $reply;
    }

    private function parameterCheck($data) {
        if (isset($data->personal_id_number)) {
			$this->personalIdNumber = trim($data->personal_id_number);
		}
		else {
			return false;
		}
        if (isset($data->amount)) {
            $this->amount = trim($data->amount);
		}
		else {
			return false;
		}
        if (isset($data->receipt_number)) {
            $this->receiptNumber = trim($data->receipt_number);
		}
		else {
			return false;
		}
        if (isset($data->email)) {
            $this->email = trim($data->email);
		}
		else {
			return false;
		}
        if (isset($data->mobile)) {
            $this->mobile = trim($data->mobile);
		}
		else {
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
          return true;
        }
        else {
            return false;
        }

        /*
            {
                "code": "1",
                "approved_code": "812D7021-D85F-F333-E293-760328CD432B",
                "personal_id_number": "195711040054",
                "name": "Bo Erik Grusell",
                "address": "DUVEDSVÄGEN 15 LGH 1202",
                "postaddress": "16265 VÄLLINGBY",
                "invoice_amount": "Köpesumma: 1,188.00 kr",
                "payment_terms": "Räntefritt 30 dagar",
                "start_fee": "",
                "adm_fee": "Aviavgift 0.00 kr",
                "possible_installment": "Lägsta månadsbelopp",
                "possible_installment2": "12 mån - ca 143 kronor",
                "interest_info": "(Årsränta 14.9%)",
                "bankid_text": "\rFAKTURA\r\rTest Bolaget\rTest Store\rKöpesumma 1,188.00 kr\r\rRäntefritt 30 dagar\rAviavgift 0.00 kr\r\rKvittoreferens _ReceiptNumber_\r \rMöjlig delbetalning\rLägsta månadsbelopp\r12 mån - ca 143 kronor\r(Årsränta 14.9%, aviavg. 29 kr)\r\rJag godkänner Turtle Pays villkor\roch integritetspolicy"
            }
        */

        // print_r($reply); 
    }
    
    private function signInt() {
        $bankIdText = str_replace('_ReceiptNumber_' ,$data->receipt_number, $resultObj->bankid_text);
        $param = new StdClass();
        $param->_group  = "BankID";
        $param->_action = "SignInit";
        $param->_bankid_personal_id_number = $personalIdNumber;
        $param->_bankid_text = $bankIdText;
        return json_decode($this->_RestApiCall(json_encode($param)));
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
        
        /*
            if (isset($data->infobox_1)) {
                $param->infobox_1 = $data->infobox_1;
            }
            if (isset($data->infobox_2)) {
                $param->infobox_2 = $data->infobox_2;
            }
        */

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
        $reply = $this->_Insert('event_item_v4', $param);
        if ($reply['code'] == '1') {
          
        if ($this->participantOn == 'y' ) {
            for ($i=0; $i < sizeof($this->participant); $i++) {
                //if ($this->participant[$i]->status == 'a') {
                    $participant = new stdClass();
                    $participant->event_item_id = $reply['id'];
                    $participant->first_name = $this->participant[$i]->first_name;
                    $participant->last_name = $this->participant[$i]->last_name;
                   
                    // Added for notes
                    if (isset($this->participant[$i]->note)) {
                        $participant->note = $this->participant[$i]->note;
                    }
                   
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
                        if ($this->participant[$i]->option[$j]->event_option_setting_id == '0' ) {
                            $option->value = 0;
                        }
                        else {
                            $option->value = $this->participant[$i]->option[$j]->value;
                        }
                        $replyOption = $this->_Insert('event_option', $option);
                    }
                //}
            }
        }
        




            $this->eventItemId = $reply['id'];
            return true;
        }
        else {
            return false;
        }
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
        $param->personal_id_number = $this->personalIdNumber;
        $param->uc = 'n'; 
        $reply = $this->_Insert('webapp_log', $param);
        if ($reply['code'] == '1') {
            return true;
        }
        else {
            return false;
        }    
    }
    
    
}
       
        