<?php
class WebAppTdbBaseClass extends BaseClass {

	protected $webAppTdbLogId;
	protected $webAppTdbLoggAction;

    public function _WebWebAppTdbLog($param) {
		$param->web_app_tdb_log_id = $this->webAppTdbLogId;
		$param->action = $this->webAppTdbLoggAction;
		$timeStamp = date("Y-m-d h:i:s");
		$param->update_time = $timeStamp;
		$reply = $this->_Insert('web_app_tdb_log_item', $param);
	}
}
