<?php
/*
    CollectClass
    
    Get personal informationn from SPAR
    
    External need SSL:  spar-cert.pem

	{
		"_group" : "Spar",
		"_action" : "Collect",
        "_personal_id_number" : ""
	}	

    {
    "people": {
        "personal_id_number": "195711040054",
        "first_name": "Bo Erik",
        "last_name": "Grusell",
        "address": "DUVEDSVÄGEN 15 LGH 1202",
        "postcode": "16265",
        "city": "VÄLLINGBY"
    },
    "code": "1"
}


*/

class CollectClass {

    private $personalIdNumber;
    private $peopleInfofromSpar;
    
    public function _($data) {
        // Check if all demand paramer exist
        if ($this->parameterCheck($data) == false) {
            return array("code"=>"2");
        }

        $this->peopleInfoFromSparGet();

        return $this->peopleInfoFromSpar;
    }

	private function parameterCheck($data) {
		/*
			Check and set all parameter.
			If not exist and mandaty return false
		*/
		// Check API paramer
		if (isset($data->_personal_id_number)) {
			$this->personalIdNumber = trim($data->_personal_id_number);
		}
		else {
			return false;
		}
		return true;
	}

    private function peopleInfoFromSparGet() {

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
        $xml_post_string  .= '<FysiskPersonId>' . $this->personalIdNumber . '</FysiskPersonId>';
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
        curl_setopt($ch, CURLOPT_SSLCERT, 'cert/spar-cert.pem');
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
            $result->code = "0";
            $this->peopleInfoFromSpar = $result;
        }
        else if (!isset($doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Efternamn')->item(0)->nodeValue)) {
            $result->text = 'Sekretessmarkering'; // Person not exist
            $result->code = "0";
            $this->peopleInfoFromSpar = $result;
        }
        else {
            $protected  = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Sekretessmarkering')->item(0)->nodeValue;
            //
            // Handling ptotected
            //
            if ($protected == "J") {
                $result->text = 'Sekretessmarkering';
                $result->code = "0";
                return $this->peopleInfoFromSpar = $result;
            }

            $result->people->personal_id_number  = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'FysiskPersonId')->item(0)->nodeValue;
            $result->people->first_name = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Fornamn')->item(0)->nodeValue;
            $result->people->last_name = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Efternamn')->item(0)->nodeValue;
            $result->people->address = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Utdelningsadress2')->item(0)->nodeValue;
            $result->people->postcode = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'PostNr')->item(0)->nodeValue;
            // CareOf
            $result->people->city = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Postort')->item(0)->nodeValue;

            /*
            if (isset($doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'AvregistreringsorsakKod')->item(0)->nodeValue)) {
                //$result->people->avreg_code = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'AvregistreringsorsakKod')->item(0)->nodeValue;
                //$result->people->avreg_date = $doc->getElementsByTagNameNS('http://skatteverket.se/spar/komponent/1.0', 'Avregistreringsdatum')->item(0)->nodeValue;
                $result->status = "0";
            } else {
                $result->status = "1";
            }
            */
            $result->code = "1";
            return $this->peopleInfoFromSpar = $result;
        }
    }
}