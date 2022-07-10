<?php
/*
    Intermal - API

    Hanling funktionalitet that is global and used by the other API:s
    This API can only be reacg fromn localhost

*/
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
    
    if (file_exists('Group/' . $data->_group . '/' . $data->_action . '.inc')) {
        $class = $data->_action . 'Class';
        require_once "InternalBaseClass.inc";
        require_once 'Group/' . $data->_group . '/' . $data->_action . '.inc';

        header("Content-Type: application/json;charset=utf-8");
        $api = new $class(DB_HOST, DB_NAME, DB_USER, DB_PASS);
        header("Content-Type: application/json;charset=utf-8");
        echo json_encode($api->_($data));
    }
    else {
       die('');
    }
   
    
}
else {
    die('' );
}
?>
