<?php
    /*
        Basic index.inc - for Turtle Pay Web App
        
        Entry points for a user:
            * No paramers in URL), show a empty form
            * p - Progress GUID as a paramer: ?p=050DBDB3-4738-00BA-57CE-031C622A8904
            * m - Message MessageId as a paramer ?m=exist
            * f - Faktura
            * e - Event

        Setting for Prod vs. Dev 
        Define "PROD"  index.inc and serice.php 
        config.inc for database
       
        Version 4 the file is divded in 3 part,
            * Form
                - None paramter when a company has a default wa:ebent_id in the company table
                - (e) Event adress to the event /?e=event-name
                - (f) Faktura med ett referns nummer där
            * Progress
                - (p) Process the 
            * Message 
                - A message when no action will be happend
    */

// --
// -- Set app to produ or dev 
// --
define("PROD", FALSE);

// --
// -- Check the SSL and redirect if some tricky thing is done
// --
if (PROD) {
    if($_SERVER["HTTP_HOST"] == "176.57.88.50") {
        header("Location: https://www.turtle-pay.com" . $_SERVER["REQUEST_URI"], true, 301);
        exit;
    }
    $Host = "https://www.turtle-pay.com/";
    $Lib = "wa-lib4";
}
else {
    $Host = "http://localhost/";
    $Lib = "wa-lib4";
}

// --
// -- Get the URL paramter
// --
parse_str($_SERVER['QUERY_STRING'], $Param);

// Check if paramers is allowed, if mno set to 'm';
if (isset($Param['o']) || isset($Param['m']) || isset($Param['p']) || empty($Param)) {
}
else {
    $Param['m'] = "no-valid-parameter";
}
// --
// -- Create the Action Class
// --
// +-- require_once "../$Lib/inc/text.inc";
// +-- require_once "../$Lib/class/Config.inc";
// +-- require_once "../$Lib/class/ActionWa.class";
// +-- require_once "../$Lib/class/Action.class";
// +-- $Action = new ActionClass(DB_HOST, DB_NAME, DB_USER, DB_PASS);

// -- 
// -- Add company id set inte the call to Action
// --
// +-- $Action->companyId = $CompanyId; 

//
// -- Add the Ur param to the Param
//
// +-- $Action->urlParam = $Param;

//
// -- Load the Company Information from the class Acron.class and store in  $Action->companyInfo
//
// +-- $Action->getCompanyInfo();

// --
// -- DECIDE WHAT VIEW GOUNFG TO BE USe
//

// --
// No Paramter
// --
 if (empty($Action->urlParam)) {
        // --
        // No default set for the company (wa_event_id = 0) 
    if ($Action->eventId == '0') {
        $Action->view = 'message';
        $DeniedText = "Inget finns på denna länk, kontrollera eller kontakta Turtle-Pay ";
        $DeniedHtml = $Message['more-info'];
    }
    else {
        //-- Lad default event and its webform
        $Action->loadEvent();
        $Action->loadWebform();
        $Action->setSettings();
        $Action->view = "form";
    }
}

// --
// -- Load for with a invoice Faktura 
//
else if (isset($Action->urlParam['e'])) {
    die('Ladda erbjudande');
}

// --
// -- Process form
//
else if (isset($Action->urlParam['p'])) {
    // Get the process form the log
    if ($Action->getEventFromWaLog($Action->urlParam['p'])) {
        $Action->loadEvent();
        $Action->loadWebform();
        $Action->view = "progress";
    }
    else {
        $DeniedText = "Ingen pågånde transaktion för närvarande";
        $DeniedHtml = $Message['more-info'];
        $Action->view = 'message';
    }   
}

// --
// -- Show a message, this collect all message
//)
if (isset($Action->urlParam['m'])) {

    $indexMessage = $Action->urlParam['m'];
    if (array_key_exists($indexMessage, $Message)) { 
        $DeniedText = $Message[$indexMessage];
        $DeniedHtml = $Message['more-info'];
    }
    else {
        $DeniedText = "Ett okänd åtgärd har skett";
        $DeniedHtml = $Message['more-info'];
    }
    $Action->view = 'message';
}

// Need to ne set right
$Action->invoiceEventId = '0';

// --
// -- Detect if mobile
// -- Any mobile device (phones or tablets).
// --
require_once "../$Lib/inc/Mobile_Detect.php";
$detect = new Mobile_Detect;
if ($detect->isMobile() ) {
    $Action->isMobile = 'yes';
}
else {
    $Action->isMobile = 'no';
}

// --
// -- html.inc is a help library for create HTML inPHP and are customized for this site
//
require_once "../$Lib/inc/html.inc";
?>

<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">

    <title><?php echo $Action->event['event_name'] ?></title>
    <link rel="icon" type="image/png" href="<?php echo $Host . $Lib; ?>/images/favicon.png">
    <link rel="stylesheet" href="<?php echo $Host . $Lib; ?>/css/style.css?<?php echo uniqid(); ?>">

    <script type="text/javascript" src="<?php echo $Host . $Lib; ?>/js/jquery-3.2.1.min.js"></script>
    <script type="text/javascript" src="<?php echo $Host . $Lib; ?>/js/bowser.min.js"></script>
  

    <script>        
        const SITE_URL = '<?php echo $Host . $Action->waUrl; ?>';
        const VIEW = '<?php echo $Action->view; ?>';
        const IS_MOBILE = '<?php echo $Action->isMobile; ?>';

        <?php 
         //
        //-- form (constat need to be transfered to JavaScript)
        //
        if ($Action->view == "form") { ?>
            const WEBFORM_ID = '<?php echo $Action->event['webform_id']; ?>';
            const WEBFORM_PARTICIPANT_ON = '<?php echo $Action->webform['participant_on']; ?>';
            const COMPANY_ID = '<?php echo $CompanyId; ?>';
            const BOWSER = bowser.name;   // Safari // FireFox // Chrome
            const EVENT_ID = '<?php echo $Action->eventId; ?>';
            const INVOICE_EVENT_ID = '<?php echo $Action->invoiceEventId; ?>';
            const ALLOWED_EDIT = 'y'; 
        <?php } ?>
        
        <?php 
        //
        //-- progress (constat need to be transfered to JavaScript)
        //
        if ($Action->view == "progress") { ?>
            const LOG_ID = '<?php echo $Action->logId; ?>';
        <?php } ?>

    </script>

    <?php 
    // --
    // -- Script for form
    // 
    if ($Action->view == "form") { ?>
        <script src="<?php echo $Host . $Lib; ?>/script/form.js?<?php echo uniqid(); ?>"></script>
    <?php } ?>

    <?php
    // --
    // -- Script for progress
    // 
     if ($Action->view == "progress") { ?>
        <script src="<?php echo $Host . $Lib; ?>/script/progress.js?<?php echo uniqid(); ?>"></script>
    <?php } ?>

</head>

<body>
<?php 
  
    // -- Create Main section 
    echo htmlSection($Action->isMobile);

    // -- Set navigation header 
    echo htmlNavbar($Action->headerImageOn, $Host . 'logo/' . $Action->companyLogo, $Action->headerName, $Action->headerBcolor, $Action->headerTcolor);
    
    // -- Event namn
    // -- echo htmlRowText($Action->event['event_name'], 'view-1 bold');
    
    require_once "view/view-$Action->view.inc";

    // -- Descript for the Event
    
    
    echo htmlDivEnd(); // Container
    echo htmlSectionEnd(); // Main section

    // -- Create MessageBox - Modal
    echo htmlMessageBoxCreate();

     // -- Create UCBox - Modal
    echo htmlUcBoxCreate();

?>
    </body>
</html>

<?php
/*

Script flow

## #eConfirm Button Click

* Confirm.checkForm();
* Confirm.checkDoubleInvoice
* Confirm.checkOverdue 
* Confirm.request
  *  actionRequest (service.php)
    * CompanyInfo (WebAppV4)
    * start (InvoiceRequest)  
      if (code == 1)
        - EventAdd (WebAppV4)
        - SignInit (BankID)
          - ok
            - ProgressInit (WebAppV4) (write the wa_log_v4)
          - check or uc
          - denid


*/