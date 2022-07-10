<?php

class AjaxClass {


	protected $url;

	public function __construct($URL) {
		$this->Url = $URL;
	}

	function _RestApiCall($param, $url = 'default') {
		// 2022-02-01
		
		if ($url == 'default') {
			$url = $this->Url;
		}
		$json = json_encode($param); 
		// $curl = curl_init($this->Url);
		$curl = curl_init($url);
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

		if (curl_errno($curl)) {
			echo curl_error($curl);
		}
		curl_close($curl);
		return json_decode($result);
	}

	protected function _TokenCheckCall($token, $userId) {
		// 2022-02-01
		$param = new stdClass();
		$param->_group = 'Priv';
        $param->_action= 'TokenCheck';
        $param->_token = $token;
        $param->_user_id = $userId;
		return  $this->_RestApiCall($param);
	}

}
