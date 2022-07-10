<?php

date_default_timezone_set("Europe/Stockholm");

require_once '../../.env/env.inc';
require_once '../../.env/' . ENV_TYPE . '/site.config.inc';
if (ERROR_REPORTING) {
    require_once '../../.env/error-reporting.inc';
}

define("DAYS","25");

$method = $_SERVER['REQUEST_METHOD'];

if ($method == 'POST') {
    $json = file_get_contents('php://input');
    $data =  json_decode($json);

    if (!$data) {
        $reply = new StdClass();
        $reply->code = "0";
        $reply->denid = "no-valid-json";
        echo json_encode($reply);
        die('');
    }

    $webApi  = new WebApi(CAPI_URL);

    echo $webApi->Run($data);
}
else {
    die('NOT ALLOWED METHOD');
}

class WebApi {

    //protected url;

    public function __construct($url) {
		$this->url = $url;
	}

    public function Run($data) {
        $actionMethod = 'action' . $data->_action;
        echo $this->$actionMethod($data);
    }

    // --
    // -- FORM
    // --

    public function actionLoadEvent($data) {

        $param = new StdClass();
        $param->_group = "WebAppV4";
        $param->_action = "LoadEvent";
        $param->_event_id = $data->_event_id;

        $resultJson =  $this->_RestApiCall(json_encode($param));
        return $resultJson;
    }

    	// ADD 2020-08-06
	public function actionLoadInheritParticipant($data) {
        $param = new StdClass();
        $param->_group = "WebAppV4";
        $param->_action = "LoadInheritParticipant";
        $param->_parent_event_item_id = $data->_parent_event_item_id;
        $param->_event_id = $data->_event_id;
        $resultJson =  $this->_RestApiCall(json_encode($param));
        return $resultJson;
    }

    private function actionCheckDoubleInvoice($data) {

        $param = new StdClass();
        $param->_group = "Check";
        $param->_action = "DoubleInvoice";

        $param->_personal_id_number = $data->_personal_id_number;
        $param->_amount = $data->_amount;
        $param->_receipt_number = $data->_receipt_number;
        $param->_days = DAYS;
        $param->_company_id = $data->_id;
        //$param->_company_id = COMPANY_ID;
        $resultJson =  $this->_RestApiCall(json_encode($param));

        return $resultJson;
    }

    private function actionOverdueCheck($data) {

        $param = new StdClass();
        $param->_group = "WebAppV4";
        $param->_action = "OverdueCheck";
        $param->_personal_id_number = $data->_personal_id_number;
        $resultJson =  $this->_RestApiCall(json_encode($param));
        return $resultJson;
    }

    private function actionMaxCheck($data) {

        //$param = new StdClass();
        //$param->_group = "WebAppV4";
        //$param->_action = "MaxCheck";
        //$param->_event_id = $data->_event_id;
        $data->_group = "WebAppV4";
        $resultJson =  $this->_RestApiCall(json_encode($data));
        return $resultJson;
    }

    private function actionRequest($data) {

        /*
            Request and init the Bankid

            Return order_ref and aprroved_code
        */

        // ---
        // --- Get the company param
        // ---
        $companyInfo = $this->getCompanyInfo($data->id);

        $data->store_id = $companyInfo->wa_store_id;
        $data->sales_person_people_id = $companyInfo->wa_sp_id;
        $data->uc_confirm = "n";

        $resultObj = $this->doInvoiceRequest($data);

        if ($resultObj->code == "1") {
            $bankIdText = str_replace('_ReceiptNumber_' ,$data->receipt_number, $resultObj->bankid_text);
            $resultBankIDObj = $this->bankIDSignInt($data->personal_id_number, $bankIdText);
            if ($resultBankIDObj->code == '1') {
                // --
                // -- Add Ivent Item
                $replyEvent = $this->eventItemAdd($data, $resultObj->approved_code);

                //print_r($replyEvent); die('');

                // --
                // -- Create a log
                // --
                $param = new stdClass();
                $param->order_ref = $resultBankIDObj->order_ref;
                $param->receipt_number = $data->receipt_number;
                $param->email = $data->email;
                $param->amount = $data->amount;
                $param->approved_code = $resultObj->approved_code;
                $param->event_id = $data->event_id;
                $param->invoice_event_item_id = $data->_invoice_event_item_id;
                $param->event_item_id = $replyEvent->id;

                $param->company_id = $data->id;
                $param->personal_id_number = $data->personal_id_number;
                // --
                // -- Invoice Invoice EventParticipant
                // --
                // -- if ($data->invoice_event == 'y') {
                // --    $paramProgress->invoice_event = 'y';
                // --    $paramProgress->invoice_event_item_id = $data->invoice_event_item_id;
                // --}

                $param->uc = 'n'; // Indikate no UC needed
                $resultWaApp = $this->writeToLog($param);
				
				// New 20210817
                $this->writeVisitorLog($resultWaApp->id, $data->_visitor);
				
                $resultWaApp->auto = $resultBankIDObj->auto_start_token;
                //$resultWaApp->waid = $resultObj->approved_code;
                $resultWaApp->waid = $resultBankIDObj->order_ref;
                echo json_encode($resultWaApp);

                die('');
            }
            else {
                // --
                // problem Bankin int sign, like Banik has a ongoing progcess
                //
                $replyObj = new StdClass();
                $resultBankIDObj->code = "7";
                echo json_encode($resultBankIDObj);
                die('');
            }

        }
        else if ($resultObj->code == '8') {
            // --
            // -- Check for a UC
            // --
            $replyObj = new StdClass();
            $replyObj->people_id = $resultObj->people_id;
            $replyObj->code = "8";
            $replyObj->denied_code = "ask-for-uc";
            echo json_encode($replyObj);
            die('');
        } else {
            $replyObj = new StdClass();
            $replyObj->code = "0";
            $replyObj->denied_code = $resultObj->denied_code;
            echo json_encode($replyObj);
            die('');
        }

    }

    private function actionUcInit($data) {

        // ---
        // --- Get the company param
        // ---
        // -- Init the process for BankId sign
        // -- Create the Text for the BankId
        // --

        // ---
        // --- Get the company param
        // ---
        $companyInfo = $this->getCompanyInfo($data->id);

        // --
        // -- Load steetings
        // --
        $param = new stdClass();
        $param->_group = "WebAppV4";
        $param->_action = 'SetSettings';
        $param->_company_id = $data->id;
        $Setting = (object) json_decode($this->_RestApiCall(json_encode($param)));
        $this->_Settings($data->id, $data->_people_id); // Should add the People id

        // --
        // -- Calculate montly payment (same as in Invoice Request)
        // --
        $param = new stdClass();
        $param->_group = "WebAppV4";
        $param->_action = 'MonthlyPayment2';
        $param->amount = $data->amount;
        $param->first_invoice_fee = $this->Setting->first_invoice_fee;
        $param->first_invoice_start_fee = $this->Setting->first_invoice_start_fee;
        $param->customerInterest = $this->Setting->customerInterest;
        $param->repayment_term = $this->Setting->repayment_term;
        $param->monthly_invoice_fee = $this->Setting->monthly_invoice_fee;
        $param->administration_fee = $this->Setting->administration_fee;
        $param->credit_interest_grace_days = $this->Setting->credit_interest_grace_days;
        $reply = json_decode($this->_RestApiCall(json_encode($param)));
        $monthlyPaymentTotal = $reply->monthly_payment_total;

        // --
        // -- Create the Bankid Sign Text
        // --
        $bankidText = "\rFAKTURA\r\r<Companyname>\r<Storename>\rKöpesumma <RequestAmount> kr\r\rRäntefritt " . $this->Setting->credit_interest_grace_days . " dagar";
		if ($this->Setting->first_invoice_start_fee > 0 ) {
			$bankidText .= "\rUppläggningsavgift " . $this->Setting->first_invoice_start_fee  . " kr"; // Fix for naming
		}
		$bankidText .= "\rAviavgift <AdminFee> kr\r\rKvittoreferens _ReceiptNumber_\r \rMöjlig delbetalning\rLägsta månadsbelopp\r" . $this->Setting->repayment_term . " mån - ca <MonthlyPayment> kronor";
		$bankidText = str_replace('<RequestAmount>' , number_format($data->amount, 2), $bankidText);
   		$bankidText = str_replace('<Companyname>' , $companyInfo->company_name, $bankidText);
        $bankidText = str_replace('<Storename>' , $companyInfo->store_name, $bankidText);
        $bankidText = str_replace('_ReceiptNumber_' ,$data->receipt_number, $bankidText);
   		//$bankidText = str_replace('<FirstFee>' , $this->Setting->first_invoice_fee, $bankidText);
   		$bankidText = str_replace('<AdminFee>' , $this->Setting->first_invoice_fee, $bankidText);
   		$bankidText = str_replace('<MonthlyPayment>' ,$monthlyPaymentTotal, $bankidText);
   		$bankidText = $bankidText . "\r(Årsränta " . $this->Setting->customerInterest . '%, aviavg. 29 kr';
		if ($this->Setting->administration_fee > 0) {
			$bankidText .= ", adm.avg " . $this->Setting->administration_fee . " kr/mån";
		}
        $bankidText .= ")";
        $bankidText .= "\r\rJag godkänner Turtle Pays villkor och integritetspolicy samt att kreditupplysning inhämtas.";

        // --
        // -- Init the Bank ID
        // --
        $resultBankIDObj = $this->bankIDSignInt($data->personal_id_number, $bankidText);

        if ($resultBankIDObj->code == '1') {

            $replyEvent = $this->eventItemAdd($data, '');
            // --
            // Createte log, for a new request
            //

            $param = new stdClass();
            $param->order_ref = $resultBankIDObj->order_ref;
            $param->receipt_number = $data->receipt_number;
            $param->email = $data->email;
            $param->amount = $data->amount;
            $param->approved_code = ''; // $resultObj->approved_code;
            $param->event_id = $data->event_id;
            $param->invoice_event_item_id = $data->_invoice_event_item_id;
            $param->event_item_id = $replyEvent->id; // Need to send to request
            $param->uc = 'y';
            $param->company_id = $data->id;
            $param->personal_id_number = $data->personal_id_number;
            $resultWaApp = $this->writeToLog($param);
			
			// New 20210817
            $this->writeVisitorLog($resultWaApp->id, $data->_visitor);

            $resultWaApp->auto = $resultBankIDObj->auto_start_token;
            $resultWaApp->waid = $resultBankIDObj->order_ref;

			$resultWaApp->people_company_on = $data->people_company_on;
            if ($data->people_company_on == 'y') {
                $resultWaApp->people_company = $data->people_company;
                $resultWaApp->people_company_address = $data->people_company_address;
                $resultWaApp->people_company_postcode = $data->people_company_postcode;
                $resultWaApp->people_company_city = $data->people_company_city;
            }

            echo json_encode($resultWaApp);
            die('');
        }
        else {
            // --
            // problem Bankin int sign, like Banik has a ongoing progcess
            //
            $replyObj = new StdClass();
            $resultBankIDObj->code = "7";
            echo json_encode($resultBankIDObj);
            die('');
        }
        return json_encode($resultBankIDObj);
    }

    // --
    // -- PROGRESS
    // --

    private function actionProgress($data) {

        /*
        - Paramter in is the wa_log_id

       - The wa_log_v4 is holdning the order fref and other informationGet
       the reply code from the BANKID the orderRef needed is now stored in the variable $order_ref

       $dataParam is the result of the result from the wa_log_v4
       */

        // --
        // -- Get ongoing progress by ids wa_log_id
        // --
        $param = new StdClass();
        $param->_group = "WebAppV4";
        $param->_action = "GetWaLog";
        $param->_log_id = $data->_log_id;
        $resWaLog =  $this->_RestApiCall(json_encode($param));
        // --
        // -- $dataParam include all paramaters from the request
        /*
            [wa_log_id] => 6
            [event_id] => 101
            [approved_code] => 615F1C1A-C90B-BD64-C521-D025E70FB234
            [order_ref] => 066b6d49-32c4-45a5-bea4-380f5c1977be
            [receipt_number] => Medlemsavgift 2020
            [email] => bo.grus@yahoo.com
            [invoice_event] => n
            [invoice_event_item_id] => 0
            [uc] => n
            [spec] =>
            [event_item_id] => 7
            [code] => 1
        */
        $dataParam = json_decode($resWaLog);

        if ($dataParam->code == "1") {
           // OK and continue $invoiceItemId = $dataParam->invoice_event_item_id;
        }
        else {
            $replyObj = new StdClass();
            $replyObj->code = "0";
            $replyObj->denied_code = 'not-in-progress';
            echo json_encode($replyObj);
            die('');
        }

        // --
        // -- Collect the BankID
        // --
        $paramComplete = new StdClass();
        $bankIdReply = false;
        $paramCollect = new StdClass();
        $paramCollect->_group = "BankID";
        $paramCollect->_action = "SignCollect";
        $paramCollect->_order_ref = $dataParam->order_ref;

        sleep(5);
        while ($bankIdReply == false) {
            $resultJson =  $this->_RestApiCall(json_encode($paramCollect));
               // {"code":"2","denied_code":"Pending"}
               // {"code":"0","denied_code":"userCancel"}
               // {"status":0,"denied_code":"No such order"} after cancel
               // {"code":"0","denied_code":"expiredTransaction"}
            if (json_decode($resultJson)) {
               $result = json_decode($resultJson);
              // print_r( $result);
                if ($result->code == "1") {
                   // Complete
                   $paramComplete->signature = $result->signature;
                   $paramComplete->ocspResponse = $result->ocspResponse;
                   $Signature = $result->signature;
                   $OcspResponse = $result->ocspResponse;
                   $bankIdReply = true;
                }
                else if ($result->code == "2") {
                   // Pending (continue)
                   //echo "pending";
                   sleep(5);
                }
                else {
                    $replyObj = new StdClass();
                    $replyObj->code = "0";
                    $replyObj->denied_code = $result->denied_code;
                    echo json_encode($replyObj);
                    $bankIdReply = false;
                    die('');
                }
            }
            else {
                // Fail call BankID collect
                $replyObj = new StdClass();
                $replyObj->code = "0";
                if (isset($result->denied_code)) {
                    $replyObj->denied_code;
                } else {
                   $replyObj->denied_code = "bankid-collect-fail";
                }
                echo json_encode($replyObj);
                $bankIdReply = false;
                die('');
            }
        } // While loop ended

        // --
        // Normal and all confirmed,
        //
        if ($dataParam->uc == 'n') {
            $paramComplete->_group = "InvoiceRequestConfirm";
            $paramComplete->_action = "Complete";
            $paramComplete->receipt_number = $dataParam->receipt_number;
            $paramComplete->cr_id = '1';
            $paramComplete->_approved_code = $dataParam->approved_code;
            // SPEC
            //$paramComplete->spec = $dataParam->spec;
            $result =  $this->_RestApiCall(json_encode($paramComplete));
            //print_r( $resultJson);
            if (json_decode($resultJson)) {

                if (json_decode($result)) {
                    return $this->completeAll($result, $dataParam->event_item_id, $dataParam->email, $resWaLog);
                }

                $resultObj = json_decode($resultJson);

            }
            else {
                $replyObj = new StdClass();
                $replyObj->code = "0";
                $replyObj->denied_code = "complete-rejected";
                echo json_encode($replyObj);
                die('');
            }
        }
        else {

            $param = new StdClass();
            $param->_group = "InvoiceRequest";
            $param->_action = "Start";
            $param->company_id = $dataParam->company_id;
            $companyInfo = $this->getCompanyInfo($dataParam->company_id);  // Where comes th company id from
            $param->store_id = $companyInfo->wa_store_id;
            $param->sales_person_people_id = $companyInfo->wa_sp_id;

            $param->_uc_confirm = 'y';
            $param->personal_id_number = $dataParam->personal_id_number; // Missing
            $param->amount = $dataParam->amount;
            $param->source = "wa";
            $param->device = "web";
            //$param->approved_code = $dataParam->approved_code;
            $param->_receipt_number = $dataParam->receipt_number;
            //$param->_email = $dataParam->email;
            $param->_signature = $Signature;
            $param->_ocspResponse = $OcspResponse;

            $param->_event_item_id = $dataParam->event_item_id; // Need for update the spec
            //print_r($param);

            $result = $this->_RestApiCall(json_encode($param));

            // All OK
            if (json_decode($result)) {
                return $this->completeAll($result, $dataParam->event_item_id, $dataParam->email, $resWaLog);
            }
            else {
                $replyObj = new StdClass();
                $replyObj->code = "0";
                $replyObj->denied_code = "complete-rejected";
                echo json_encode($replyObj);
                die('');
            }

        }
    }

    // --
    // -- Commun function
    // --

    private function getCompanyInfo($companyId) {
        $param = new stdClass();
        $param->_group = "WebAppV4";
        $param->_action = 'CompanyInfo';
        $param->_company_id = $companyId;
        return json_decode($this->_RestApiCall(json_encode($param)));
    }

    private function doInvoiceRequest($data) {
        $param = new StdClass();
        $param->_group = "InvoiceRequest";
        $param->_action = "Start";

        $param->company_id = $data->id;
        $param->store_id = $data->store_id;
        $param->sales_person_people_id = $data->sales_person_people_id;

        //$param->cr_id = '1';
        $param->_uc_confirm = $data->uc_confirm;
        $param->personal_id_number = $data->personal_id_number;
        $param->amount = $data->amount;
        $param->source = "wa";
        $param->device = "web";

        /*
        {
            "_action": "Start",
            "_group": "InvoiceRequest",
            "_uc_confirm": "n",
            "amount": "2500",
            "company_id": "69",
            "device": "web",
            "personal_id_number": "195711040054",
            "sales_person_people_id": "34",
            "source": "wa",
            "store_id": "67"
        }
        */

        return json_decode($this->_RestApiCall(json_encode($param)));

    }

    private function bankIDSignInt($personalIdNumber, $bankIdText) {
        $param = new StdClass();
        $param->_group  = "BankID";
        $param->_action = "SignInit";
        $param->_bankid_personal_id_number = $personalIdNumber;
        $param->_bankid_text = $bankIdText;
        return json_decode($this->_RestApiCall(json_encode($param)));
    }

    private function _RestApiCall($json) {

        $curl = curl_init($this->url);
        curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_setopt($curl, CURLOPT_POSTFIELDS, $json);
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($curl, CURLOPT_HTTPHEADER, array(
            'Content-Type: application/json',
            'Content-Length: ' . strlen($json))
        );
        
        // Local and SSL
		curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, false);

        $result = curl_exec($curl);
        /*
        print_r($result);
        if(curl_errno($curl)){
            echo curl_error($curl);
        }
        */

        curl_close($curl);
        return $result;

    }

    private function _Settings($company_id = null, $people_id = null) {
        $param = new stdClass();
        $param->_group = "WebAppV4";
        $param->_action = 'GetSettings';
        $param->_company_id = $company_id;
        $this->Setting = (object) json_decode($this->_RestApiCall(json_encode($param)));
    }

    private function eventItemAdd($data, $approvedCode = '') {
        //
        // -- AddEvent
        // --
        $param = new StdClass();
        $param->_group = "WebAppV4";
        $param->_action = "EventItemAdd";
        $param->event_id = $data->event_id; // -- missing
        $param->approved_code = $approvedCode;
        $param->event_item_status = 'p';
        $param->email = $data->email;
        if (isset($data->mobile)) {
            $param->mobile = $data->mobile;
        }
        $param->referens = $data->receipt_number;
        $param->amount = $data->amount;
        $param->_participant_on = $data->participant_on;
        if ( $data->participant_on == 'y') {
            $param->_participant = $data->participant;  //FIX FOR SPEC
        }
        //
        if (isset($data->infobox_1)) {
            $param->infobox_1 = $data->infobox_1;
        }
        if (isset($data->infobox_2)) {
            $param->infobox_2 = $data->infobox_2;
        }
        $param->invoice_event_item_id = $data->_invoice_event_item_id;

        if ($data->people_company_on == 'y') {
            $param->people_company_on = 'y';
            $param->people_company = $data->people_company;
            $param->people_company_address = $data->people_company_address;
            $param->people_company_postcode = $data->people_company_postcode;
            $param->people_company_city = $data->people_company_city;
        } 
        else {
            $param->people_company_on = 'n';
        }

        // echo '<pre>';
        // print_r($param);
        // echo '</pre>';
        $replyJson = $this->_RestApiCall(json_encode($param));
        return json_decode($replyJson); // -- NEW 20191030
    }

    private function writeToLog($param) {
        $param->_group = "WebAppV4";
        $param->_action = "WriteToLog";

        $resultWaApp = $this->_RestApiCall(json_encode($param));
        //echo $resultWaApp;
        return json_decode($resultWaApp);
    }

    private function completeAll($resultJson, $eventItemId, $email, $waLogResult) {
        $resultObj = json_decode($resultJson);
        if ($resultObj->code == "1") { // Should be 1
            //$resultJson = $this->setConfirmed($dataParam, $resultObj->credit_id);
            $param = new StdClass();
            $param->_group = "WebAppV4";
            $param->_action = "SetConfirmed";
            $param->_credit_id = $resultObj->credit_id;
            $param->_event_item_id = $eventItemId;
            //$param->_email = $dataParam->email;
            //$param->_invoice_event = $dataParam->invoice_event;
            //$param->_invoice_event_item_id = $dataParam->invoice_event;
            $this->_RestApiCall(json_encode($param));

            if (ENV_TYPE == 'prod') {
                $paramEmail = new StdClass();
                $paramEmail->_group = "Email";
                $paramEmail->_action = "FirstInvoice";
                $paramEmail->_invoice_filename = $resultObj->invoice_filename;
                $paramEmail->email = $email;
                $res = $this->_RestApiCall(json_encode($paramEmail));
                $replyObj = new StdClass();
                $replyObj->code = "1";
                $replyObj->denied_code = "mail-sent";
                return json_encode($replyObj);
                die('');
            }
            else {
                $replyObj = new StdClass();
                $replyObj->code = "1";
                $replyObj->denied_code = "ok";
                return json_encode($replyObj);
                die('');
            }
        }
        else {
            $replyObj = new StdClass();
            $replyObj->code = "0";
            $replyObj->denied_code = "complete-rejected";
            return json_encode($replyObj);
            die('');
        }
    }

    private function eventItemSet() {
        $param->_group = "WebAppV4";
        $param->_action = "EventItemSet";
        $result = $this->_RestApiCall(json_encode($param));
        return json_decode($result);
    }

	private function actionSpar($data) {

		$tidsstampel = date('Y-m-d') . 'T' . date('H:i:s') . ".000";
		$soapUrl = "https://ext-ws.statenspersonadressregister.se/spar-webservice/SPARPersonsokningService/20160213/";
		$xml_post_string  = "<?xml version='1.0' encoding='UTF-8'?>";
		$xml_post_string  .= '<Envelope xmlns="http://schemas.xmlsoap.org/soap/envelope/">xxx<Header />';
		$xml_post_string  .= '<Body>';
		$xml_post_string  .= '<SPARPersonsokningFraga xmlns="http://skatteverket.se/spar/instans/1.0">';
		$xml_post_string  .= '<IdentifieringsInformation xmlns="http://skatteverket.se/spar/komponent/1.0">';

		// Prod
		$xml_post_string  .= '<KundNrLeveransMottagare>513610</KundNrLeveransMottagare>';
		$xml_post_string  .= '<KundNrSlutkund>513610</KundNrSlutkund>';
		$xml_post_string  .= '<OrgNrSlutkund>5591016786</OrgNrSlutkund>';
		$xml_post_string  .= '<UppdragsId>27469</UppdragsId>';

		$xml_post_string  .= '<SlutAnvandarId>Turtle Pay Spar</SlutAnvandarId>';
		$xml_post_string  .= '<Tidsstampel>' . $tidsstampel . '</Tidsstampel>';
		$xml_post_string  .= '</IdentifieringsInformation>';
		$xml_post_string  .= '<PersonsokningFraga xmlns="http://skatteverket.se/spar/komponent/1.0">';
		$xml_post_string  .= '<PersonId>';
		$xml_post_string  .= '<FysiskPersonId>' . $data->_personal_id_number . '</FysiskPersonId>';
		$xml_post_string  .= '</PersonId>';
		$xml_post_string  .= '</PersonsokningFraga>';
		$xml_post_string  .= '</SPARPersonsokningFraga>';
		$xml_post_string  .= '</Body>';
		$xml_post_string  .= '</Envelope>';

		$headers = array(
			"Content-type: text/xml;charset=\"utf-8\"",
			"Accept: text/xml",
			"Cache-Control: no-cache",
			"Pragma: no-cache",
			"Content-length: ".strlen($xml_post_string),
		);

		$ch = curl_init();
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 1);
		curl_setopt($ch, CURLOPT_URL, $soapUrl);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		curl_setopt($ch, CURLOPT_TIMEOUT, 10);
		curl_setopt($ch, CURLOPT_POST, true);
		curl_setopt($ch, CURLOPT_POSTFIELDS, $xml_post_string); // the SOAP request
		curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);

		// Security settings

		// Prod
		curl_setopt($ch, CURLOPT_SSLCERT, 'spar-cert.pem');
		curl_setopt($ch, CURLOPT_SSLCERTPASSWD, 'Yap2018Rut');

		//curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
		//curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);


		$response = curl_exec($ch);
		//$httpcode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
		//print curl_error($ch);
		curl_close($ch);

		$result = new StdClass();
		$result->people = new StdClass();

		$doc = new DOMDocument;
		$doc->loadXML($response);

		$status = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Kod')->item(0);
		if (isset($status)) {

			//echo $status->nodeValue . '<br>';
			$result->text = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Beskrivning')->item(0)->nodeValue;
			$result->status = "0";
			return  json_encode($result);
		}

		if (!isset($doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Efternamn')->item(0)->nodeValue)) {
			$result->text = 'Sekretessmarkering'; // Person not exist
			$result->status = "0";
			return  json_encode($result);
        }

		$protected  = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Sekretessmarkering')->item(0)->nodeValue;
		//
		// Handling ptotected
		//
		if ($protected == "J") {
			$result->text = 'Sekretessmarkering';
			$result->status = "0";
			return  json_encode($result);
		}

		$result->people->personal_id_number  = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'FysiskPersonId')->item(0)->nodeValue;
		$result->people->first_name = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Fornamn')->item(0)->nodeValue;
		$result->people->last_name = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Efternamn')->item(0)->nodeValue;
		$result->people->address = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Utdelningsadress2')->item(0)->nodeValue;
		$result->people->postcode = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'PostNr')->item(0)->nodeValue;
		// CareOf
		$result->people->city = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Postort')->item(0)->nodeValue;

        $result->status = "1";
        return json_encode($result);
	}


    private function actionInitOffer($data) {

        $bankIdText = 'Jag godkänner Turtle Pays allmänna upplåningsvillkor & integritetspolicy.';

        $resultBankIDObj = $this->bankIDSignInt($data->personal_id_number, $bankIdText);

        if ($resultBankIDObj->code == '1') {
            $param = new stdClass();
            $param->_group = "WebAppOffer";
            $param->_action = "WriteToLog";
            $param->order_ref = $resultBankIDObj->order_ref;
            $param->email = $data->email;
            $param->amount = $data->amount;
            $param->company_id = $data->id;
            $param->personal_id_number = $data->personal_id_number;
            $param->mobile = $data->mobile;
            $param->bank_accountno = $data->bank_accountno;
            $param->clearingno = $data->clearingno;
            $param->repay_type = $data->repay_type;
            $param->term = $data->term;
            $param->event_id = $data->event_id;
            $param->invoice_event_item_id = $data->_invoice_event_item_id;
            $result = $this->_RestApiCall(json_encode($param));
            $reply = json_decode($result);
            //print_r($reply);
            $reply->auto = $resultBankIDObj->auto_start_token;
            $reply->waid = $resultBankIDObj->order_ref;

            //print_r($reply);

            echo json_encode($reply);
        }
        else {
            // --
            // problem Bankin int sign, like Banik has a ongoing progcess
            //
            $replyObj = new StdClass();
            $resultBankIDObj->code = "7";
            echo json_encode($resultBankIDObj);
            die('');
        }
    }

    private function actionQprogress($data) {

        // --
        // -- Get ongoing progress by ids wa_log_id
        // --
        $param = new StdClass();
        $param->_group = "WebAppOffer";
        $param->_action = "GetWaLog";
        $param->_log_id = $data->_log_id;
        $resultJson =  $this->_RestApiCall(json_encode($param));

        // print_r($resultJson); die('');

        $dataParam = json_decode( $resultJson);

        if ($dataParam->code == "1") {
           // OK and continue $invoiceItemId = $dataParam->invoice_event_item_id;
        }
        else {
            $replyObj = new StdClass();
            $replyObj->code = "0";
            $replyObj->denied_code = 'not-in-progress';
            echo json_encode($replyObj);
            die('');
        }

        // --
        // -- Collect the BankID
        // --
        $paramComplete = new StdClass();
        $bankIdReply = false;
        $paramCollect = new StdClass();
        $paramCollect->_group = "BankID";
        $paramCollect->_action = "SignCollect";
        $paramCollect->_order_ref = $dataParam->order_ref;

        sleep(5);
        while ($bankIdReply == false) {
            $resultJson =  $this->_RestApiCall(json_encode($paramCollect));
               // {"code":"2","denied_code":"Pending"}
               // {"code":"0","denied_code":"userCancel"}
               // {"status":0,"denied_code":"No such order"} after cancel
               // {"code":"0","denied_code":"expiredTransaction"}
            if (json_decode($resultJson)) {
               $result = json_decode($resultJson);
              // print_r( $result);
                if ($result->code == "1") {
                   // Complete
                   $paramComplete->signature = $result->signature;
                   $paramComplete->ocspResponse = $result->ocspResponse;
                   //$Signature = $result->signature;
                   //$OcspResponse = $result->ocspResponse;
                   $bankIdReply = true;
                }
                else if ($result->code == "2") {
                   // Pending (continue)
                   //echo "pending";
                   sleep(5);
                }
                else {
                    $replyObj = new StdClass();
                    $replyObj->code = "0";
                    $replyObj->denied_code = $result->denied_code;
                    echo json_encode($replyObj);
                    $bankIdReply = false;
                    die('');
                }
            }
            else {
                // Fail call BankID collect
                $replyObj = new StdClass();
                $replyObj->code = "0";
                if (isset($result->denied_code)) {
                    $replyObj->denied_code;
                } else {
                   $replyObj->denied_code = "bankid-collect-fail";
                }
                echo json_encode($replyObj);
                $bankIdReply = false;
                die('');
            }
        }
        /*
            {
                "_group" : "WebAppOffer",
                "_action" : "CompleteOffer",
                "_wa_log_offer_id" : "9",
                "signature" : "test-sign",
                "ocspResponse" : "test-oscp"

            }
        */
        $paramComplete->_group = "WebAppOffer";
        $paramComplete->_action = "CompleteOffer";
        $paramComplete->_wa_log_offer_id = $data->_log_id;

        $result =  $this->_RestApiCall(json_encode($paramComplete));

        if (json_decode($result)) {
            $replyObj = new StdClass();
            $replyObj->code = "1";
            echo json_encode($replyObj);
            die('');
        }
        else {
            $replyObj = new StdClass();
            $replyObj->code = "0";
            $replyObj->denied_code = "complete-rejected";
            echo json_encode($replyObj);
            die('');
        }

    }

	 // New 2021-08-17
     private function writeVisitorLog($waLogId, $visitor) {
        $param = new stdClass();
        $param->_group = "WebAppV4";
        $param->_action = "WriteToVisitorLog";
        $param->wa_log_id = $waLogId;
        $param->browser = $visitor->browser;
        $param->version = $visitor->version;
        $param->osname = $visitor->osname;
        $param->osversion = $visitor->osversion;
		$param->cookie_on = $visitor->cookie_on;
		$param->dg = $visitor->dg;
        $reply = $this->_RestApiCall(json_encode($param));
    }

}

?>
