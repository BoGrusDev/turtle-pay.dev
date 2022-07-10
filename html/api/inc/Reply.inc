<?php
class Reply {
	function _($code, $denied_code) {
		$reply = new StdClass();
		$reply->code = $code;
		$reply->denied_code = $denied_code;
		return json_encode($reply);
	}
}