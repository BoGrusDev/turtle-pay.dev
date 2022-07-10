<?php
date_default_timezone_set("Europe/Stockholm");

$method = $_SERVER['REQUEST_METHOD'];
if ($method == 'POST') {
    $json = file_get_contents('php://input');
    $data =  json_decode($json);
   
    require_once '../.env/env.inc';
    require_once '../.env/' . ENV_TYPE . '/db.config.inc';
    require_once '../.env/' . ENV_TYPE . '/site.config.inc';
    require_once '../.env/' . ENV_TYPE . '/upload.config.inc';
    if (ERROR_REPORTING) {
        require_once '../.env/error-reporting.inc';
    }
    
    //echo 'Group/' . $data->_group . '/' . $data->_action . '.inc'; die('');

    if (file_exists('Group/' . $data->_group . '/' . $data->_action . '.inc')) {
		//echo '{"code":"99"}'; 
        $class = $data->_action . 'Class';
        require_once "BaseClass.inc";
        require_once 'Group/' . $data->_group . '/' . $data->_action . '.inc';

        header("Content-Type: application/json;charset=utf-8");
		//echo json_encode($data);
        $api = new $class(DB_HOST, DB_NAME, DB_USER, DB_PASS);
        header("Content-Type: application/json;charset=utf-8");
        echo json_encode($api->_($data));
    }
    else {
        $class = $data->_group . 'Class';
        require_once "ActionPortal.class";
        require_once 'class/' . $data->_group . '.class';
        $api = new $class(DB_HOST, DB_NAME, DB_USER, DB_PASS);
        echo $api->Run($data);
    }
   
    
}
else {
    die('NOT ALLOWED METHOD: ' );
}
?>
