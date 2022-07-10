<?php

/*
ALTER TABLE `company` 
    ADD `tdb_on` CHAR(1) NOT NULL DEFAULT 'n' AFTER `sie_start_date`, 
    ADD `tdb_apikey` VARCHAR(60) NULL DEFAULT NULL AFTER `tdb_on`, 
    ADD `tdb_orgno` VARCHAR(8) NULL DEFAULT NULL AFTER `tdb_apikey`; 
*/
class TdbBaseClass extends BaseClass {

    public function TdbSettingGet($userId) {
        $sql = "SELECT tdb_apikey, tdb_orgno FROM company WHERE company_id=$userId AND tdb_on = 'y'";
        $reply = $this->_Get($sql);
        return $reply;
	}

    public function _RestApiTdb($param, $apiKey) {
		
		$apiKeyName = 'X-API-KEY';
		$tdbUrl = 'https://app.equipe.com/';

		// echo $tdbUrl . $param; die('');

		$curl = curl_init($tdbUrl . $param);
		curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($curl,CURLOPT_SSL_VERIFYPEER, false);
		curl_setopt($curl, CURLOPT_HTTPHEADER, array(
			"$apiKeyName : $apiKey"
		));
		$result = curl_exec($curl);
		if (curl_errno($curl)) {
			$error_msg = curl_error($curl);
			print_r($error_msg);
			die('stop');
		}
		
		curl_close($curl);
		return json_decode($result);
	}
}
