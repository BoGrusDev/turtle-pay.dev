
<?php
    
    function CheckCompanyUrl($url, $apiUrl) {

        $param = new stdClass();
    	$param->_group = "WebApp";
        $param->_action = "CheckCompanyUrl";
        $param->_wa_url = $url;
        $json = json_encode($param);
        $curl = curl_init($apiUrl);
		curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_setopt($curl, CURLOPT_POSTFIELDS, $json);
		curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($curl, CURLOPT_HTTPHEADER, array(
			'Content-Type: application/json',
			'Content-Length: ' . strlen($json))
		);
        $result = curl_exec($curl);
        if (curl_error($curl)) {
            print_r($url);
        }
       
		curl_close($curl);
		return json_decode($result) ;
	}

    function UserApiCall($Token, $apiUrl) {

        $param = new stdClass();
    	$param->_group = "People";
        $param->_action = "CheckPr";
        $param->_token = $Token;
        $json = json_encode($param);
       
        //print_r($json);
        //echo $apiUrl;
        //die('');
        $curl = curl_init($apiUrl);
		curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_setopt($curl, CURLOPT_POSTFIELDS, $json);
		curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($curl, CURLOPT_HTTPHEADER, array(
			'Content-Type: application/json',
			'Content-Length: ' . strlen($json))
		);
		$result = curl_exec($curl);
        if (curl_error($curl)) {
            echo curl_error($url);
        }
		// print_r($curl);
		curl_close($curl);
		return json_decode($result) ;
	}

    /*
    function CheckCompanyUrl($url) {

        $param = new stdClass();
    	$param->_group = "WebApp";
        $param->_action = "CheckCompanyUrl";
        $param->_wa_url = $url;
        $json = json_encode($param);

        //$curl = curl_init('http://localhost/events/service/json.php');
        //$curl = curl_init('http://turtle-pay.prod/events/service/json.php');
        $curl = curl_init(SITE_URL . 'events/service/json.php');
		curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_setopt($curl, CURLOPT_POSTFIELDS, $json);
		curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($curl, CURLOPT_HTTPHEADER, array(
			'Content-Type: application/json',
			'Content-Length: ' . strlen($json))
		);
        $result = curl_exec($curl);
        if (curl_error($curl)) {
            print_r($url);
        }
		curl_close($curl);
		return json_decode($result) ;
	}

    function UserApiCall($Token) {

        $param = new stdClass();
    	$param->_group = "People";
        $param->_action = "CheckEventUser";
        $param->_token = $Token;

        $json = json_encode($param);

        $curl = curl_init(SITE_URL . 'events/service/json.php');
       
		curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
		curl_setopt($curl, CURLOPT_POSTFIELDS, $json);
		curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($curl, CURLOPT_HTTPHEADER, array(
			'Content-Type: application/json',
			'Content-Length: ' . strlen($json))
		);
		$result = curl_exec($curl);

        
        if (curl_error($curl)) {
            echo curl_error($url);
        }
        //echo $json;
        //echo SITE_URL . '/service2/json.php';
        //print($result); 
        //die();
        
		curl_close($curl);
		return json_decode($result) ;
	}
    */
?>
