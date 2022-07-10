<?php
/*
	service2 - kapi
*/

date_default_timezone_set("Europe/Stockholm");
require_once '../.env/env.inc';
require_once '../.env/' . ENV_TYPE . '/db.config.inc';
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
		//echo json_encode($data); die('');
        require_once "AjaxClass.inc";
        require_once 'Group/' . $data->_group . '/' . $data->_action . '.inc';
        header("Content-Type: application/json;charset=utf-8");
        $api = new $class(KAPI_URL);
        header("Content-Type: application/json;charset=utf-8");
        echo json_encode($api->_($data));
		//echo '{"company_name":"Test Bolaget AB","known_as":"Test Bolaget","tdb_on":"y","company_status":"a","code":"1"}';
    }
	else {
		require_once "ActionPublic.class";
		$class = $data->_group . 'Class';
		require_once 'class/' . $data->_group . '.class';
		$api = new $class(DB_HOST, DB_NAME, DB_USER, DB_PASS, KAPI_URL);	
		echo $api->Run($data);
	}
}
else {
    die('NOT ALLOWED METHOD');
}
