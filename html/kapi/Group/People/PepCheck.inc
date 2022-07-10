<?php
 /*
    {
        "_group" : "People",
        "_action : "PepCheck",
        "_personal_id_number" : "198102156521"
    }
    Reply 
    {
        "kyc_need": "n",
        "pep": "n",
        "rca": "n",
        "code": "1"
    }
    {
        "kyc_need": "y",
        "pep": "y",
        "rca": "y",
        "code": "1"
    }

        Sandbox:
            Client id:      bMII6kRVrpxfLLwdh11bqUa5KyMa
            Client secret:  NJng2eX5hgjuwzidwyL8ID84GlIa
        Production:
            Client id:     jjvvmeOspMvQ4SaLclmcN2JfqDAa
            Client secret:  kWdYUvHFj7mHnx_vrwHTAChOf9Ua

    Roaring
        Not Pep och Rca
        {
            "hitCount": 0,
            "responseInfo": {
                "requestCount": 1,
                "hitCount": 0
            },
            "hits": []
        }
        Is Rca
        {
            "hitCount": 1,
            "responseInfo": {
                "requestCount": 1,
                "hitCount": 1
            },
            "hits": [
                {
                    "pep": false,
                    "rca": true,
                    "ssns": [
                        {
                            "ssnTypeId": 1,
                            "ssnType": "SwePersonalNumber",
                            "currentSsn": "197109259288"
                        }
                    ],
                    "gender": "Female",
                    "birthDate": "1971-09-25",
                    "pepCountries": [
                        "Sweden"
                    ],
                    "names": [
                        {
                            "firstName": "Lena",
                            "lastName": "Bananberg",
                            "nameTypeId": "3",
                            "nameType": "Primary name"
                        },
                        {
                            "firstName": "Lena",
                            "lastName": "Bananberg",
                            "nameTypeId": "4",
                            "nameType": "National registry name"
                        }
                    ],
                    "relations": [
                        {
                            "relationPersonId": 55001,
                            "relationTypeId": 5,
                            "relationType": "Mother-in-law"
                        },
                        {
                            "relationPersonId": 55000,
                            "relationTypeId": 1,
                            "relationType": "Father-in-law"
                        },
                        {
                            "relationPersonId": 55003,
                            "relationTypeId": 6,
                            "relationType": "Partner"
                        }
                    ],
                    "personId": 55002
                }
            ]
        }

*/

ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

class PepCheckClass extends BaseClass {

    private $peopleId;
    private $personalIdNumber;
    private $reply;
    private $pepNeed;

    public function _($data) {         
        $this->pepNeed = false;
        $prodOn = true;
        $this->reply = new stdClass();
        $this->reply->kyc_need = 'n';

        if ($this->parameterCheck($data) == false) {
            return array("code"=>"0", "denied_code"=>"parameter-fail");
        }        

        if ($prodOn) {
            $this->clientId = 'jjvvmeOspMvQ4SaLclmcN2JfqDAa';
            $this->clientSecret = 'kWdYUvHFj7mHnx_vrwHTAChOf9Ua';
        }
        else {
            $this->clientId = 'bMII6kRVrpxfLLwdh11bqUa5KyMa';
            $this->clientSecret = 'NJng2eX5hgjuwzidwyL8ID84GlIa';
            //$this->personalIdNumber = '197109259288'; // Rca
		    // $this->personalIdNumber = '196501133372'; // Rca
        }
        if ($this->peopleExist() == false) {
            if ($this->peopleSparCollect() == false) {
                return array("code"=>"0", "denied_code"=>"people_not_exist");
            }
        } 
        
        if ($prodOn == false) {
            //$this->personalIdNumber = '192908187541'; // Pep
            // $this->personalIdNumber = '196501133372'; // Rca
        }

        //echo $this->personalIdNumber; 
        //echo $this->pepNeed;
        //die('');
        
        if ($this->pepNeed) {
            if ($this->tokenGet() == false) {
                return array("code"=>"0", "denied_code"=>"cant-access-roaring");
            }  
            $this->roaringCall(); 
        }
        

        $this->reply->code = '1';
        return $this->reply; 
    }

    private function parameterCheck($data) {
        if (isset($data->_personal_id_number)) {
			$this->personalIdNumber = trim($data->_personal_id_number);
		}
		else {
            return false;
		}    
		return true;
	}

    private function peopleExist() {
        $sql = "SELECT people_id, pep, rca, pep_date, is_sanction_list, kyc_need FROM people ";
        $sql .= "WHERE personal_id_number = '$this->personalIdNumber'";
        $res = $this->_Get($sql); 
        if ($res['code'] == '1') {
            if ($res['kyc_need'] == 'y') {
                $this->reply->kyc_need = 'y';
            }
            $this->reply->people_id = $res['people_id'];
            return true;
        }
        else {
            // New people
            return false; 
        }
    }

    private function peopleSparCollect() {
        /*
            Get people form SPAR
            If exist insert to Turle Pay database and 
            set $this->peopleId and return true else false
        */
        $param = new stdClass();
        $param->_group = "Spar";
        $param->_action = "Collect";
        $param->_personal_id_number = $this->personalIdNumber;
        $res = $this->_RestApiCall($param, INTERNAL_API);
        if($res->code == "0") {
            return false;
		} 
        else {
            // -- Insert into Turtle Pay
            $res->people->people_status = 'p';
            $res->people->ocrno = $this->_ocrnoCreate($this->personalIdNumber);
            //$res->people->kyc_need = 'y'; // If all new need
            $reply = $this->_Insert('people', $res->people);
            if ($reply['code'] == "1") {
                $this->peopleId = $reply['id'];
                $this->reply->people_id = $reply['id'];
                $this->pepNeed = true;
                // $this->reply->kyc_need = 'y';  // If all new need
                return true;
            } 
            else {
                return false;
            }
        }
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
		$authorization = 'Authorization: Bearer ' . $this->accessToken;
		$url = 'https://api.roaring.io/nordic/pep/1.0/search?countryCode=se&personalNumber=' . $this->personalIdNumber; 
	
		$curl = curl_init();
		curl_setopt( $curl, CURLOPT_URL, $url);
		curl_setopt($curl, CURLOPT_HTTPHEADER, array('Content-Type: application/json' , $authorization ));
		curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);		
		$result = curl_exec($curl);
        //print_r($result);
        //die('');
		curl_close($curl);
		$this->result = json_decode($result);
        $param = new stdClass();
		if (isset($this->result->hitCount)) {
            if($this->result->hitCount > '0') {
                if ($this->result->hits[0]->pep) {
                    $param->pep = 'y';
                    $param->kyc_need = 'y';
                    $this->reply->kyc_need = 'y';
                }
                else {
                    $param->pep = 'n';
                }
                if ($this->result->hits[0]->rca) {
                    $param->rca = 'y';
                    $param->kyc_need = 'y';
                    $this->reply->kyc_need = 'y';
                }
                else {
                    $param->rca = 'n';
                }
            }
            else { // if (isset($this->result->hitCount) {
                $param->pep = 'n';
                $param->rca = 'n';
		    }
            $param->pep_date = date('Y-m-d');
            $this->_Update('people', 'people_id', $this->peopleId, $param);
            $this->reply->pep = $param->pep;
            $this->reply->rca = $param->rca;
            $this->reply->code = '1';
	    }
    }

    private function _ocrnoCreate($peopleIdNumber) {
        $ocrno = '2' . substr($peopleIdNumber, 2, 6) . mt_rand(1000, 9999);
		$sum = 0;
		for ($i=0; $i < strlen($ocrno); $i++) {
			if ($i % 2 == 0) {
				$res = $ocrno[$i] * 2;
			} else {
				$res = $ocrno[$i];
			}
			if ($res > 9) {
				$res = $res -9;
			}
			$sum = $sum + $res;
		}
		$nerast10 = ceil($sum / 10) * 10;
		$checksum =  $nerast10 - $sum;
		$ocr_number = $ocrno . $checksum; // 11
		return $ocr_number;
	}

    /*
        private function peopleUpdate() {
            $param = new stdClass();
            if ($this->result->hitCount > '0') {
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
    */
}
