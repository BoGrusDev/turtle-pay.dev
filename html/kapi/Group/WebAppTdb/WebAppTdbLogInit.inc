<?php
/*
    IInit the WebAppLogTdb
    
   {
		"_group" : "WebAppTdb",
		"_action" : "Init",
        "item_code" : "72BB2A19FBB35E0D318E45B9CA3BEC65"
	}	
*/
require_once 'Group/WebAppTdb/WebAppTdbBase.inc';

class WebAppTdbLogInitClass extends WebAppTdbBaseClass {

    private $reply;

    public function _($data) {
        $this->reply = new stdClass();
        $this->init($data);
        return $this->reply;
    }

    private function init($data){
        $param = new stdClass();
        $timeStamp = date("Y-m-d h:i:s");
		$param->init_time = $timeStamp;
        if (isset($data->item_code)) {
            $param->item_code = $data->item_code;
        }
        else {
            $param->item_code = 'No code';
        }
        $reply = $this->_Insert('web_app_tdb_log', $param);
        if ($reply['code'] == '1') {
            $this->reply->web_app_tdb_log_id = $reply['id'];
            return true;
        }
        else {
            return false;
        }
    }
}