<?php
/*
	Tolls that is used in index.php
*/

$PageUrl = array (
	// -- Public
	'om-oss'=>'about-us',
	'vanliga-fragor-och-svar'=>'faq',
	'kontakt'=>'contact-us',
	'turtlepay-integritetspolicy'=>'integr',
	'logga-in'=>'login',
	// -- User
	'mina-delajer'=>'details-user',
   	'transaktioner'=>'trans-user',
    'fakturor'=>'invoices-user',
    'hushallsbudget'=>'budget',
    'kyc'=>'kyc',
	'konto'=>'',
	// -- Company
	'foretagsdetaljer'=>'details-company',
	'event'=>'event',
	'webbformular'=>'webform',
	'utskick'=>'invoice-mailings',
	'transaktioner'=>'trans-company',
	'bokforingsorder'=>'accounting-order'
);

function IsWebApp($Param) {
	/*
		Is iused for check if the URL is a actibver Webb App,
		if so return Company else return false
	*/
	if (isset($Param['param'])) {
		$url = $Param['param'];
	}
	else {
		return false;
	}
	// -- Remove / in end if provided
	if (substr($url, -1) == '/') {
		$url = substr_replace($url , '', -1);
		$Param['param'] = $url;
	}

	$param = new stdClass();
	$param->_group = "Company";
	$param->_action = "WebAppInfo";
	$param->_wa_url = $url;
	$result = KapiRest($param);

	if ($result->code == '1') {
		return $result;
	}
	else {
		return false;
	}
}
    
function isLogedIn() {
	// echo $_COOKIE['turtlepaykp']; die('');
	if(isset($_COOKIE['turtlepaykp'])){
		$Token = $_COOKIE['turtlepaykp'];
		if (isset($_COOKIE['turtlepayid'])) {
			$UserId = $_COOKIE['turtlepayid']; 
			if (is_numeric($UserId) == false ) {
				$UserId = '0';
			}
		}
		else {
			$UserId = '0';
		}
		$param = new stdClass();
		$param->_group = "Priv";
		$param->_action = "PersonCheck";
		$param->_token = $Token;
		$param->_user_id = $UserId;
		return KapiRest($param);
	}
	else {
		$reply = new stdClass();
		$reply->code = '0';
		return $reply;
	}
}

function KapiRest($param) {
	$json = json_encode($param);
	$curl = curl_init(KAPI_URL);
	curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
	curl_setopt($curl, CURLOPT_POSTFIELDS, $json);
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
	curl_setopt($curl, CURLOPT_HTTPHEADER, array(
		'Content-Type: application/json',
		'Content-Length: ' . strlen($json))
	);
    if (ENV_TYPE != 'prod') {	
		curl_setopt($curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, 0);
	}

	$result = curl_exec($curl);
	if (curl_error($curl)) {
		echo curl_error($url);
	}
	
	curl_close($curl);
	return json_decode($result);
}
