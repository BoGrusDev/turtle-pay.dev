<?php
/*
	index.php - Email
*/

date_default_timezone_set("Europe/Stockholm");
require_once '../../.env/env.inc';
require_once '../../.env/' . ENV_TYPE . '/db.config.inc';
require_once '../../.env/' . ENV_TYPE . '/site.config.inc';
if (ERROR_REPORTING) {
	require_once '../../.env/error-reporting.inc';
}

require_once "ActionPublic.class";

$method = $_SERVER['REQUEST_METHOD'];
if ($method == 'POST') {
	$json = file_get_contents('php://input');
	$data =  json_decode($json);

	// $data = (object) $_POST;
	//print_r($_POST); die('stop');

	$class = $data->_group . 'Class';

	require_once 'class/' . $data->_group . '.class';
	
	$api = new $class(DB_HOST, DB_NAME, DB_USER, DB_PASS, KAPI_URL);
	
	echo $api->Run($data);

}
else {
    die('NOT ALLOWED METHOD');
}
