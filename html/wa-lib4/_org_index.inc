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


$browserCheck = $_SERVER['HTTP_USER_AGENT'];
$isDuckAndGo = 'n';
if (strpos($browserCheck, 'DuckDuckGo') > 0)  {
		//echo '<h1>is DUCK AND GO</h1>';
		$isDuckAndGo = 'y';
 }

// --
// -- From index.php comming
// -- $Param 
// .. SITE_URL
// --

require_once '.env/env.inc';
require_once '.env/' . ENV_TYPE . '/db.config.inc';

if (ERROR_REPORTING) {
    require_once '.env/error-reporting.inc';
}
if ( $Param['param'] == 'djrk') {
    if (isset($Param['f']) || isset($Param['m']) || isset($Param['p']) || isset($Param['e'])) {
        // Skip
    }
    else {
        $Param['e'] = 'djrk'; 
    }
}

if ( $Param['param'] == 'vemdalsskalet') {
    if (isset($Param['f']) || isset($Param['m']) || isset($Param['p']) || isset($Param['e'])) {
        // Skip
    }
    else {
        $Param['e'] = 'vemdalsskalet'; 
    }
}

if ( $Param['param'] == 'captains') {
    if (isset($Param['f']) || isset($Param['m']) || isset($Param['p']) || isset($Param['e'])) {
        // Skip
    }
    else {
        $Param['e'] = 'captains'; 
    }
}

if ( $Param['param'] == 'mattlangett') {
    if (isset($Param['f']) || isset($Param['m']) || isset($Param['p']) || isset($Param['e'])) {
        // Skip
    }
    else {
        $Param['e'] = 'mattlangett'; 
    }
}

if ( $Param['param'] == 'hairbar') {
    if (isset($Param['f']) || isset($Param['m']) || isset($Param['p'])) {
        // Skip
    }
    else {
        $Param['e'] = 'hairbar'; 
    }
}

define ('LIB', "wa-lib4");

// Check if paramers is allowed, if mno set to 'm';
if (isset($Param['e']) || isset($Param['f']) || isset($Param['a']) || isset($Param['m']) || isset($Param['p']) || isset($Param['o']) || isset($Param['q'])) {
    if (isset($Param['test'])) {
        define ('PREVIEW', TRUE);
    }
    else {
        define ('PREVIEW', FALSE);
    }
}

// --
// -- Create the Action Class
// --
require_once LIB . "/inc/text.inc";
// require_once LIB . "/class/Config.inc";
require_once LIB . "/class/ActionWa.class";
require_once LIB . "/class/Action.class";
$Action = new ActionClass(DB_HOST, DB_NAME, DB_USER, DB_PASS);

// -- 
// -- Add company id set inte the call to Action
// --
$Action->companyId = $CompanyId; 
$Action->inheritEventItemId = '0'; // This is the EventId for inherit
//
// -- Add the Ur param to the Param
//
$Action->companyUrl = $Param['param'];

// Used for forms that are inherit
$Action->inheritOn = 'n';
// print_r($Param);

// die('');
//
// -- Load the Company Information from the class Acron.class and store in  $Action->companyInfo
//
$Action->getCompanyInfo();

// --
// -- ENTRY POINT
//

// -- Fix for Safari

if (isset($Param['e']) && isset($_COOKIE['tpsafari'])) { 
	$Param['p'] = $_COOKIE['tpsafari'];
	unset($Param['e']); 
}

if (isset($Param['f']) && isset($_COOKIE['tpsafari'])) { 
	$Param['p'] = $_COOKIE['tpsafari'];
	unset($Param['f']); 
}



if (isset($Param['o'])) {
   
    if ($Action->loadEventByInvoiceEvent($Param['o'])) {
        $Action->invoiceEventId = $Action->invoiceEvent['invoice_event_id'];
        $Action->invoiceEventItemId = $Action->invoiceEvent['invoice_event_item_id'];
        $Action->eventId = $Action->invoiceEvent['event_id'];
        if ($Action->loadEventByEventId()) {
            $Action->view = "offer";
        }  
        else {
            $DeniedText = "Det finns inget att hämta på länken!";
            $DeniedHtml = $Message['more-info'];
            $Action->view = 'message';
        }   
    }
    else {
        $DeniedText = "Det finns inget att hämta på angiven länk!";
        $DeniedHtml = $Message['more-info'];
        $Action->view = "message";  
    }
}

// --
// Public with a evnet URL
//
else if (isset($Param['e'])) {
    $Action->eventUrl = $Param['e'];
    $Action->invoiceEventId = '0';
    $Action->invoiceEventItemId = '0';
    if ($Action->loadEventByUrl()) {
        if ($Action->event['event_type'] == 'o') {
            $Action->view = "offer";
        }
        else {
            $Action->view = "form";
        }
    }
    else {
        $Action->view = "message";  
        $DeniedText = "Det finns inget event på angiven länk!";
        $DeniedHtml = $Message['more-info'];
		$Action->event['event_create_type'] = 'x'; // Means not exist
    }

    if ($Action->event['event_create_type'] == 'b' || $Action->event['event_create_type'] == 'g') {
        $reply = $Action->checkMax($Action->eventId);
        if ($reply->participant_limit_on == 'y' && $reply->event_full == 'y') {
            $Action->view = "message";  
            $DeniedText = "Aktiviteten är fullbokad!";
            $DeniedHtml = 'För information kontakta ' . $Action->event['header_title'] . '.';   
        }
    }
}

// --
// -- Load for with a invoice Faktura 
//

else if (isset($Param['f'])) {
  
    // -- 
    // Check if event is inherit (kedjan)
    //

    if ($Action->loadEventByInvoiceEvent($Param['f'])) {
        $Action->invoiceEventId = $Action->invoiceEvent['invoice_event_id'];
        $Action->invoiceEventItemId = $Action->invoiceEvent['invoice_event_item_id'];
        $Action->eventId = $Action->invoiceEvent['event_id'];
        if ($Action->loadEventByEventId()) {
            if ($Action->event['event_create_type'] == 'b' || $Action->event['event_create_type'] == 'g') {
                $reply = $Action->checkMax($Action->eventId);
                if ($reply->participant_limit_on == 'y' && $reply->event_full == 'y') {
                    $Action->view = "message";  
                    $DeniedText = "Aktiviteten är fullbokad!";
                    $DeniedHtml = 'För information kontakta ' . $Action->event['header_title'] . '.';   
                }
                else {
                    $Action->view = "form";
                }
            }
			else {
                $Action->loadParentEventItem();
                // -- Add for Imherit 2021-07-09
                if ($Action->parentEventItem['participant_number'] > 0) {
					if ($Action->event['event_create_type'] == 'i' && $Action->event['tdb_on'] == 'y') {
                        $Action->selectionValidate();
                    }
                    $Action->inheritOn = 'y';
                    $Action->view = "form";
                }
                else {
                    $DeniedText = "Det finns inget att hämta på angiven länk!";
                    $DeniedHtml = $Message['more-info'];
                    $Action->view = "message";  
                }    
                // --            
            }
			/*
            else {
                $Action->loadParentEventItem();
                $Action->inheritOn = 'y';
                $Action->view = "form";
            }
			*/
        }  
        else {
            $DeniedText = "Det finns inget att hämta på angiven länk!";
            $DeniedHtml = $Message['more-info'];
            $Action->view = 'message';
        }   
    }
    else {
        $DeniedText = "Det finns inget att hämta på angiven länk!";
        $DeniedHtml = $Message['more-info'];
        $Action->view = "message";  
    }

        /*
            echo $Action->view;
            die('');
            echo '<pre>';
            print_r($Action);
            die('');
        */
}


// --
// -- Process form
//
else if (isset($Param['p'])) {
    // Get the process form the log
    if ($Action->getEventFromWaLog($Param['p'])) {
        $Action->loadEventByEventId();
        //$Action->eventId = $Action->event['event_id'];
        $Action->view = "progress";
    }
    else {
        $DeniedText = "Inget pågånde köp för närvarande";
        $DeniedHtml = $Message['more-info'];
        $Action->view = 'message';
    }   
}

else if (isset($Param['q'])) {
    // Get the process form the log
    if ($Action-> getOfferFromLog($Param['q'])) {
        //$Action->loadEventByEventId();
        //$Action->eventId = $Action->event['event_id'];
        $Action->view = "qprogress";
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
else if (isset($Param['m'])) {

    $indexMessage = $Param['m'];
    if (array_key_exists($indexMessage, $Message)) { 
        $DeniedText = $Message[$indexMessage];
        $DeniedHtml = $Message['more-info'];
        if ($indexMessage = 'denied' && isset($Param['id'])) {
            // ?m=denied&id=93
            $invoiceEventItemId = $Param['id'];
            //$Action->setDenied($eventId);
            //$Action->setDenied($invoiceEventItemId);
        }
    }
    else {
        $DeniedText = "Ett okänd åtgärd har skett";
        $DeniedHtml = $Message['more-info'];
    }
    $Action->view = 'message';
    
}

// 
// Empty and menu
// 
else {
    $LogoOn = true;
    $Action->loadPublicEvent();
    $Action->view = 'message';
    $DeniedText = '';
    if (sizeof($Action->publicEvent) > 0) {
        $DeniedHtml = '<table class="table" style="border: 1px solid #dbdbdb; border-width: 0 0 1px 0; padding: 0.5em 0.75em; vertical-align: top;">';
        for ($i=0; $i<sizeof($Action->publicEvent); $i++) {   

            if ($Action->publicEvent[$i]['event_create_type'] == 'b') {
                $eventName =  $Action->publicEvent[$i]['event_name'];
            }
            else {
                $eventName =  $Action->publicEvent[$i]['event_name'] . ' - ' . $Action->publicEvent[$i]['ref'];
            }

            if ($Action->publicEvent[$i]['max_on'] == 'y') {
                if ($Action->publicEvent[$i]['event_full'] == 'n') {
                    $DeniedHtml .= '<tr style="font-size:16px">';
                        $DeniedHtml .= '<td><a style="color: #444444" href="' . SITE_URL . $Action->publicEvent[$i]['wa_url'] . '/?e=' . $Action->publicEvent[$i]['event_url'] . '">' . $eventName . '</a></td>';
                        if ( $Action->publicEvent[$i]['place_left'] == '1') {
                            $DeniedHtml .= '<td><i>' . $Action->publicEvent[$i]['place_left'] . ' plats kvar' . '</i></td>';
                        }
                        else {
                            $DeniedHtml .= '<td><i>' . $Action->publicEvent[$i]['place_left'] . ' platser kvar' . '</i></td>';
                        }
                    $DeniedHtml .= '</tr>';
                }
                else {
                    $DeniedHtml .= '<tr style="font-size:16px">';
                        $DeniedHtml .= '<td><a style="color: #888888" href="">' . $eventName . '</a></td>';
                        $DeniedHtml .= '<td style="color: #888888"><i>' . 'Fullt' . '</i></td>';
                    $DeniedHtml .= '</tr>';
                }
            }
            else {
                $DeniedHtml .= '<tr style="font-size:16px"><td><a style="color: #444444" href="' . SITE_URL . $Action->publicEvent[$i]['wa_url'] . '/?e=' . $Action->publicEvent[$i]['event_url'] . '">' . $eventName. '</a></td><td></td></tr>';
            }
        }
        $DeniedHtml .= '</table>'; 
    }
    else {
        $DeniedHtml = '<h3 class="title is-5">Inga öppna event pågår!</h3>' ;
    }
}


if ($Action->view == 'message') {
    $SiteTitle = "Turtle Pay";
}
else {
    $SiteTitle =  $Action->event['event_name'];
}

// --
// -- Check if Max on is set on Selections
// --
if ($Action->view == "form") {
    $Action->chekAndGetSelections();
    //die('');
}

// --
// -- Detect if mobile
// -- Any mobile device (phones or tablets).
// --
require_once LIB . "/inc/mobile-detect.php";
$detect = new Mobile_Detect;
if ($detect->isMobile() ) {
    $Action->isMobile = 'yes';
}
else {
    $Action->isMobile = 'no';
}

/*
echo '<pre>';
print_r($Action); 
echo '</pre>'; 
die('');
*/

//$Action->isMobile = 'yes';

// --
// -- html.inc is a help library for create HTML inPHP and are customized for this site
//
require_once LIB . "/inc/html.inc";
?>

<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">

    <title><?php echo $SiteTitle; ?></title>
    <link rel="icon" type="image/png" href="/images/favicon.png">
    <?php /*
        <link rel="stylesheet" href="css/style.css?<? php echo uniqid(); ? >">
    */ ?>
   
	<link rel="stylesheet" href="<?php echo SITE_URL . '/' . LIB . '/css/style.css?'; ?><?php echo uniqid(); ?>">
    <script type="text/javascript" src="<?php echo  SITE_URL . '/' . LIB . '/js/jquery-3.2.1.min.js'?>"></script>
    <script type="text/javascript" src="<?php echo SITE_URL . '/' . LIB . '/js/bowser.min.js'?>"></script>
  

    <script>    
		document.cookie = 'tpsafari=; expires=Thu, 01 Jan 1970 00:00:00 UTC;sameSite=lax;path=/';
        const SITE_URL = '<?php echo SITE_URL . $Action->waUrl; ?>';
        const VIEW = '<?php echo $Action->view; ?>';
        const IS_MOBILE = '<?php echo $Action->isMobile; ?>';

        <?php 
         if ($Action->view == "form" || $Action->view == "offer") { ?>             
            const COMPANY_ID = '<?php echo $CompanyId; ?>';
            var Browser = bowser.name;
            const EVENT_ID = '<?php echo $Action->eventId; ?>';
            const INVOICE_EVENT_ID = '<?php echo $Action->invoiceEventId; ?>';
            const INVOICE_EVENT_ITEM_ID = '<?php echo $Action->invoiceEventItemId; ?>';
            const INHERIT = '<?php echo $Action->inheritEventItemId; ?>';
        <?php } ?>
        
        <?php 
        //
        //-- progress (constat need to be transfered to JavaScript)
        //
        if ($Action->view == "progress") { ?>
            const LOG_ID = '<?php echo $Action->logId; ?>';
        <?php } ?>
        
        <?php 
        if ($Action->view == "qprogress") { ?>
            const QLOG_ID = '<?php echo $Action->logOfferId; ?>';
        <?php } ?>

    </script>

	<script>
		
		function checkCookie() {
			var cookieEnabled = navigator.cookieEnabled;
			if (!cookieEnabled){ 
				document.cookie = "testcookie";
				cookieEnabled = document.cookie.indexOf("testcookie")!=-1;
			}
			if ( cookieEnabled) {
				 return 'y';
			}
			else {		
				return 'n';
			}
		}
				
	</script>


    <?php 
    // --
    // -- Script for form
    // 
    if ($Action->view == "form") {
        // echo LIB . '/mvc/forms/forms-controller.js.inc';  die( ''); 
        require_once LIB . '/mvc/forms/forms-view.js.inc';
        require_once LIB . '/mvc/forms/forms-model.js.inc';
        require_once LIB . '/mvc/forms/forms-controller.js.inc';
    ?>
        <script>    
            var Current = {};
            const Model = new FormsModel();
            const View = new FormsView();
            const Controller = new FormsController();
			
			//alert(JSON.stringify( Current.visitor));
			
            $(document ).ready(function() {
				Current.visitor = {};
                Current.visitor.browser = bowser.name;
                Current.visitor.version = bowser.version;
                Current.visitor.osname = bowser.osname;
                Current.visitor.osversion = bowser.osversion;
              
				Current.visitor.cookie_on = checkCookie(); 
				Current.visitor.dg = '<?php echo $isDuckAndGo; ?>';
				
				 
                Controller.init();
                Controller.load();
				
            });
            
        </script>
    <?php } ?>

    <?php
    // --
    // -- Script for progress
    // 
     if ($Action->view == "progress") { ?>
         <script type="text/javascript" src="<?php echo SITE_URL . '/' . LIB . '/script/progress.js?' . uniqid(); ?>"></script>
    <?php } ?>

    <?php
    // --
    // -- Script for offer
    // 
     if ($Action->view == "offer") { ?>
         <script type="text/javascript" src="<?php echo SITE_URL . '/' . LIB . '/script/offer.js?' . uniqid(); ?>"></script>
    <?php } ?>

    <?php
    // --
    // -- Script for qprogress
    // 
     if ($Action->view == "qprogress") { ?>
         <script type="text/javascript" src="<?php echo SITE_URL . '/' . LIB . '/script/qprogress.js?' . uniqid(); ?>"></script>
    <?php } ?>


</head>

<body>
<?php 
  
    // -- Create Main section 
    echo htmlSection($Action->isMobile);

   
    require_once "view/view-$Action->view.inc";

    
    
    echo htmlDivEnd(); // Container
    echo htmlSectionEnd(); // Main section

    // -- Create MessageBox - Modal
    echo htmlMessageBoxCreate();

     // -- Create UCBox - Modal
    echo htmlUcBoxCreate();

?>
    </body>
</html>

