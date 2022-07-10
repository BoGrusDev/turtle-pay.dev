<?php
    /*
        Basic index.inc - for WebApp - TDB
*/        

require_once '.env/env.inc';
require_once '.env/' . ENV_TYPE . '/webapp-tdb.config.inc';

if (ERROR_REPORTING) {
    require_once '.env/error-reporting.inc';
}

require_once LIB . "/inc/webapp-tools.inc";

// require_once LIB . "/inc/text.inc";

$Current = new stdClass();

/*
    Handling Safari Mobile and BankID
*/
if (isset($Param['t']) && isset($_COOKIE['tpsafari'])) { 
    $Param['tp'] = $_COOKIE['tpsafari'];
    unset($Param['t']); 
}

if (isset($Param['tp'])) {
    // $Current->approvedCode = $Param['tp'];
    $Current->view = 'tdb-payment';
}

else if (isset($Param['t'])) {
    // Init Log
    $paramLog = new stdClass();
    $paramLog->_group = 'Tdb';
    $paramLog->_action = 'WebAppTdbLogInit';
    $paramLog->item_code = $Param['t'];
    $resLog = WebAppService($paramLog);
    $Current->webAppTdbLogId = $resLog->web_app_tdb_log_id;
    $param = new stdClass();
    $param->_group = 'Tdb';
    $param->_action = 'ItemsLoad';
    $param->_item_code = $Param['t'];
    $param->_web_app_tdb_log_id = $Current->webAppTdbLogId;
    $param->_log = 'init';
    $Current->items = WebAppService($param);
    if ($Current->items->code == '1') {
        $Current->view = 'tdb';
    }
    else {
        $Current->deniedText = "Det finns inget att hämta på angiven länk!";
        $Current->view = "message";  
    }
    
}
else {
    $Current->deniedText = "Det finns inget att hämta på angiven länk!";
    // $DeniedHtml = $Message['more-info'];
    $Current->view = "message";  
   
}

if ($Current->view == 'message') {
    $SiteTitle = 'Turtle Pay'; // SITE_TITLE;
}
else {
    // $SiteTitle =  $Action->event['event_name'];
}

require_once LIB . "/inc/mobile-detect.php";
$detect = new Mobile_Detect;
if ($detect->isMobile() ) {
    $Current->isMobile = 'yes';
}
else {
    $Current->isMobile = 'no';
}
$browserCheck = $_SERVER['HTTP_USER_AGENT'];
$Current->isDuckAndGo = 'n';
if (strpos($browserCheck, 'DuckDuckGo') > 0)  {
		$Current->isDuckAndGo = 'y';
 }

// require_once LIB . "/inc/html.inc";
?>

<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>Turtle Pay</title>
    <link rel="icon" type="image/png" href="/images/favicon.png">
    <?php /*
        <link rel="stylesheet" href="css/style.css?<? php echo uniqid(); ? >">
    */ ?>
   
	<link rel="stylesheet" href="<?php echo SITE_URL . '/' . LIB . '/css/style.css?'; ?><?php echo uniqid(); ?>">
    <script type="text/javascript" src="<?php echo  SITE_URL . '/' . LIB . '/js/jquery-3.2.1.min.js'?>"></script>
    <script type="text/javascript" src="<?php echo SITE_URL . '/' . LIB . '/js/bowser.min.js'?>"></script>
  

    <script>    
		document.cookie = 'tpsafari=; expires=Thu, 01 Jan 1970 00:00:00 UTC;sameSite=lax;path=/';
        const SITE_URL = '<?php echo SITE_URL ?>'; //  $Current->waUrl;
        const IS_MOBILE = '<?php echo $Current->isMobile; ?>';
        const BROWSER = bowser;
        const IS_DUCK_AND_GO = '<?php echo $Current->isDuckAndGo; ?>';

        <?php if ($Current->view == "tdb") { ?>
            const ITEM_CODE = '<?php echo $Param['t']; ?>';
            const WEB_APP_TDB_LOG_ID = '<?php echo $Current->webAppTdbLogId; ?>';
        <?php } ?>
        <?php if ($Current->view == "tdb-payment") { ?>
            const APPROVED_CODE = '<?php echo $Param['tp']; ?>';
        <?php } ?>
    </script>

    <?php 
        if ($Current->view == "tdb") {
            require_once 'base-lib/ViewBaseClass.js.inc';
            require_once 'base-lib/ModelBaseClass.js.inc';
            require_once 'base-lib/VisitorClass.js.inc';
            require_once 'base-lib/BankIdClass.js.inc';
            require_once LIB . '/mvc/' .  $Current->view . '/' .  $Current->view . '.js.inc';
        }
        else if ($Current->view == "tdb-payment") {
            require_once 'base-lib/ViewBaseClass.js.inc';
            require_once 'base-lib/ModelBaseClass.js.inc';
            require_once 'base-lib/VisitorClass.js.inc';
            require_once 'base-lib/BankIdClass.js.inc';
            require_once LIB . '/mvc/' .  $Current->view . '/' .  $Current->view . '.js.inc';
        }
        
    ?>
       
</head>

<body>
    <?php 
        require_once LIB . '/mvc/' . $Current->view . '/' .  $Current->view . '.inc';
        require_once 'base-lib/MessageBox.inc';
        require_once 'base-lib/BankIdBox.inc';
    /*
            // -- Create Main section 
            echo htmlSection($Action->isMobile);

        
            require_once "view/view-$Action->view.inc";

            
            
            echo htmlDivEnd(); // Container
            echo htmlSectionEnd(); // Main section

            // -- Create MessageBox - Modal
            echo htmlMessageBoxCreate();

            // -- Create UCBox - Modal
            echo htmlUcBoxCreate();
        */
    ?>

</body>
</html>
