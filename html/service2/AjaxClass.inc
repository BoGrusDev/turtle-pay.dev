<?php

class AjaxClass {


	protected $url;

	public function __construct($URL) {
		$this->Url = $URL;
	}

	function _RestApiCall($param, $api = KAPI_URL) {
		$json = json_encode($param);
		$curl = curl_init($api);
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

	
	protected function _TokenCheck($token, $userId) {
		$reply = new stdClass();
        $res = $this->_TokenCheckCall($token, $userId);
        if ($res->code == '1') {
			$reply->code = '1';
			$reply->priv = $res->priv;
			$reply->operatorId = $res->operator_id;
        }
        else {
			$reply->code = '0';
        }
		return $reply;
    }
	

	protected function _TokenCheckCall($token, $userId) {
		// 2022-02-01
		$param = new stdClass();
		$param->_group = 'Priv';
        $param->_action= 'TokenCheck';
        $param->_token = $token;
        $param->_user_id = $userId;
		return $this->_RestApiCall($param);
	}

}
