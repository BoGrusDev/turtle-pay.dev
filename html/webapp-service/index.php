<?php
/*
	webapp-service2 - gateway to KAPI
*/

date_default_timezone_set("Europe/Stockholm");
require_once '../.env/env.inc';
require_once '../.env/' . ENV_TYPE . '/site.config.inc';
if (ERROR_REPORTING) {
    require_once '../.env/error-reporting.inc';
}

$method = $_SERVER['REQUEST_METHOD'];
if ($method == 'POST') {
	if (sizeof($_POST) > 0) {
		$data = (object) $_POST;
	}
	else {
		$json = file_get_contents('php://input');
		$data =  json_decode($json);
	}
	// -- New part
	if (file_exists('Group/' . $data->_group . '/' . $data->_action . '.inc')) {
        $class = $data->_action . 'Class';
        require_once "AjaxClass.inc";
        require_once 'Group/' . $data->_group . '/' . $data->_action . '.inc';
        header("Content-Type: application/json;charset=utf-8");
        $api = new $class(KAPI_URL);
        header("Content-Type: application/json;charset=utf-8");
        echo json_encode($api->_($data));
    }
    else {
        die('NOT EXIST');
    }
}
else {
    die('NOT ALLOWED METHOD');
}
