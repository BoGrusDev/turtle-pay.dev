<?php
 /*
    {
        "_group" : "People",
        "_action : "RoaringCheck",
        "_people_id" : "1",
        "_personal_id_number" : ""
    }

    Sandbox:
        Client id:      bMII6kRVrpxfLLwdh11bqUa5KyMa
        Client secret:  NJng2eX5hgjuwzidwyL8ID84GlIa
    Production:
        Client id:     jjvvmeOspMvQ4SaLclmcN2JfqDAa
        Client secret:  kWdYUvHFj7mHnx_vrwHTAChOf9Ua
*/


ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

class RoaringCheckClass extends BaseClass {

    private $peopleId;
    private $personalIdNumber;
    private $reply;

    public function _($data) {     
        $this->reply = new stdClass();
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denied_code"=>"parameter-fail");
        }        

		// Sandbox
		$this->clientId = 'bMII6kRVrpxfLLwdh11bqUa5KyMa';
		$this->clientSecret =  'NJng2eX5hgjuwzidwyL8ID84GlIa';
		

		// Production
		// $this->clientId = 'jjvvmeOspMvQ4SaLclmcN2JfqDAa';
		// $this->clientSecret =  'kWdYUvHFj7mHnx_vrwHTAChOf9Ua';

		// print_r($this->personalIdNumber); die('');

		if ($this->tokenGet() == false) {
            return array("code"=>"0", "denied_code"=>"cant-access-roaring");
        }  

		$this->personalIdNumber = '197109259288'; // Pep
		// $this->personalIdNumber = '196501133372'; // Rca
		//$this->bearer = '3af7b47c-bf9a-3aa7-97ec-25ecce400fee';
		if ($this->roaringCall() == false) {
            return array("code"=>"0", "denied_code"=>"people-not-exist");
        } 
		
		$this->peopleUpdate();

		return $this->reply; 


    }

    private function parameterCheck($data) {
		
        if (isset($data->_people_id)) {
			$this->peopleId = trim($data->_people_id);
		}
		else {
			return false;
		}        
        if (isset($data->_personal_id_number)) {
			$this->personalIdNumber = trim($data->_personal_id_number);
		}
		else {
            return false;
		}    
		return true;
	}

    private function tokenGet() {
		// echo $this->clientId . ":" . $this->clientSecret; die('');
		// $authorization = "Authorization: Basic Base64($this->clientId:$this->clientSecret)";

		$curl = curl_init();
		curl_setopt( $curl, CURLOPT_URL, 'https://api.roaring.io/token');
		// curl_setopt($curl, CURLOPT_HTTPHEADER, array('Content-Type: application/json'));
		curl_setopt($curl, CURLOPT_HTTPHEADER, array('Content-Type: application/x-www-form-urlencoded'));
		curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
		curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_setopt($curl, CURLOPT_USERPWD, $this->clientId . ":" . $this->clientSecret);
		curl_setopt($curl, CURLOPT_POSTFIELDS, 'grant_type=client_credentials');
		//curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false);
	
		$result = curl_exec($curl);
		if (curl_errno($curl)) {
			return false;	
			// $error_msg = curl_error($curl);
			// print_r($error_msg);
		}	

		//print_r($result);


		curl_close($curl);
		$res = json_decode($result);
		$this->accessToken = $res->access_token;
		return true;
		
		/*
			{
				"access_token": "640c3f00-f82a-353c-a8e9-d11c2c6cd6a3",
				"scope": "am_application_scope default",
				"token_type": "Bearer",
				"expires_in": 3600
			}	
		*/
    }

    private function roaringCall() {
    
		//$authorization = "Authorization: Bearer 445cdda2-bacc-37a0-969e-a2e90f1ff04b";
		// $authorization = "Authorization: Bearer c0b049ef-57af-37c7-a7f6-5c8ebeab1245";
		$authorization = 'Authorization: Bearer ' . $this->accessToken;
		$url = 'https://api.roaring.io/nordic/pep/1.0/search?countryCode=se&personalNumber=' . $this->personalIdNumber; 
	
		$curl = curl_init();
		curl_setopt( $curl, CURLOPT_URL, $url);
		curl_setopt($curl, CURLOPT_HTTPHEADER, array('Content-Type: application/json' , $authorization ));
		curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
		
		// Execute
		$result = curl_exec($curl);
		// Closing
		curl_close($curl);

		// Will dump a beauty json :3
		$this->result = json_decode($result);

		// print_r($result);

		if (isset($this->result->hitCount)) {
			return true;
		}		
		else {
			return false;
		}
	}

	private function peopleUpdate() {

		if ($this->result->hitCount > '0') {
			$param = new stdClass();
			if ($this->result->hits[0]->pep) {
				$param->pep = 'y';
			}
			else {
				$param->pep = 'n';
			}
			if ($this->result->hits[0]->rca) {
				$param->rca = 'y';
			}
			else {
				$param->rca = 'n';
			}
		}
		else {
			$param->pep = 'n';
			$param->rca = 'y';
		}
		$param->pep_date = date('Y-m-d');
		$this->_Update('people', 'people_id', $this->peopleId, $param);
		$this->reply->pep = $param->pep;
		$this->reply->rca = $param->rca;
		$this->reply->code = '1';
    }
}
