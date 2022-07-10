<?php

/*
    Upload

    2020-05-11

    Fix
    - Max length uploaded fil
    - remove file, if go wrong
    - Logo upload
 */
date_default_timezone_set("Europe/Stockholm");
require_once '../../.env/env.inc';

require_once '../../.env/env.inc';
require_once '../../.env/' . ENV_TYPE . '/site.config.inc';
require_once '../../.env/' . ENV_TYPE . '/upload.config.inc';
if (ERROR_REPORTING) {
    require_once '../../.env/error-reporting.inc';
}


//echo UPLOAD_IMAGE_DIR; die('');

require_once 'upload.class';

$reply = new stdClass();

$filename =  _CreateFilename();

// $folder = BASE_IMAGE_DIR . $domain . '/product/';
move_uploaded_file($_FILES['file']['tmp_name'], UPLOAD_IMAGE_DIR . $filename);

// Copy original
//$result  = copy(UPLOAD_IMAGE_DIR . $filename, BASE_IMAGE_DIR . $domain . '/images/' . $newFilename .  $newFileExt);

$reply->code = '1';
$reply->filename = $filename; //  $id . $_FILES['file']['name'];
echo json_encode($reply);

function _CreateFilename(){
    // Return 2F8672B9-1BB8-2FFA-C56D-C5F8E8946FEF
    if (function_exists('com_create_guid')){
        return com_create_guid();
    }
    else {
        mt_srand((double)microtime()*10000);//optional for php 4.2.0 and up.
        $charid = strtoupper(md5(uniqid(rand(), true)));
        return $charid . '.csv';

    }
}

?>
