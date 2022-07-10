<?php

function WebAppService($param) {
	$json = json_encode($param);
	$curl = curl_init(WEBAPP_API_URL);
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
