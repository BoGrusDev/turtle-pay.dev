<?php
/*
    Front-end Company

*/
?>
<script>

class TdbPaymentView extends ViewBaseClass{
 
    init() {
        if (Current.isMobile == 'yes') {
            View.paymentStatus('process-mobile'); 
        }
        else {
            View.paymentStatus('process-computer'); 
        }
	}

    paymentStatus(status)  {
        let messageTurtle =  '<br>För information kontakta Turtle Pay AB på info@turtle-pay.com eller tel. 08-806220.';
        let html = '';
        switch(status) {

            case 'process-computer' :
                html += '<strong>ÖPPNA DITT BANKID OCH SIGNERA!</strong> <br/>';
                html += '<strong>VAR GOD VÄNTA! </strong> <br/>';
                break;
            case 'process-mobile' :
                html += '<strong>VAR GOD VÄNTA! </strong> <br/>';
                html += 'Fakturan skickas nu till angiven e-postadress.</br>';
                html += '<i>Lämna inte denna sida medan fakturan skickas.';        
                // html += '<strong>ÖPPNA DITT BANKID OCH SIGNERA!</strong> <br/>';
                break;
            case 'complete':
                html += '<strong>KLART!</strong><br/>';
                html += 'Fakturan har skickats till din angivna e-postadress.<br/>';
                html += 'Om du inte fått fakturan inom några minuter, kontakta Turtle Pay AB på info@turtle-pay.com eller tel. 08-806220.<br/>';
                break;
            case 'no-process':
                html += '<strong>INGET FAKTURAKÖP PÅGÅR FÖR TILLFÄLLET!</strong><br/>' + messageTurtle; 
                break;
            case 'rejected':
                html += '<strong>MEDGES EJ!</strong>' + messageTurtle; 
                break;
            case 'bankid-cancel':
                html += '<strong>SIGNERING MED BANKID GICK EJ ATT GENOMFÖRA!</strong><br/>' + messageTurtle; 
                break;
            case 'error' :
                html += '<strong>FAKTURAKÖPET GICK INTE ATT GENOMFÖRA!</strong><br/>' + messageTurtle;
                break;
            case 'no-such-order' :
                html += '<strong>INGET FAKTURAKÖP PÅGÅR FÖR TILLFÄLLET!</strong><br/>' + messageTurtle;
                break;
            case 'usercancel' :
                html += '<strong>SIGNERING MED BANKID GICK EJ ATT GENOMFÖRA!</strong><br/>' + messageTurtle;
                break;
            case 'complete-rejected' :
                html += '<strong>MEDGES EJ!</strong><br/>' + messageTurtle;
                break;
            case 'expiredtransaction' :
                html += '<strong>SIGNERING MED BANKID GICK EJ ATT GENOMFÖRA!</strong><br/>' + messageTurtle;
                break;
            default :
                html += '<strong>FAKTURAKÖPET GICK INTE ATT GENOMFÖRA!</strong><br/>' + messageTurtle;
                break;
        }
        View.html('payment-status-text', html);
    }
}

class TdbPaymentModel extends ModelBaseClass {}

class TdbPaymentController  {
	
	init() {
        //Current.visitor = Visitor.info(Current.browser, Current.isDuckAndGo);
        //console.log(Current.visitor);
        View.init();
        Controller.process();
	}  
    process() {
        let param = {};
        param._group = 'Tdb';
        param._action = "Process";
        param._approved_code = Current.approvedCode;
        param._web_app_tdb_log_id = '999';
        //alert(JSON.stringify(param)); 
       


        $.ajax({ type: "POST", url: '/webapp-service/', data : JSON.stringify(param), contentType : 'application/json',
		    success: function(result) {
                let data = result;
                //console.log(data);
                if (data.code == '1') {
                    View.paymentStatus('complete');
                } 
                else {
                    View.paymentStatus(data.denied_code);
                }
            },
            error: function(result){
                // console.log(result);
                View.paymentStatus('error');
            }
        });
    }
}

var Current = {};
Current.siteUrl = SITE_URL;
Current.approvedCode = APPROVED_CODE;
Current.isMobile = IS_MOBILE;
Current.browser = BROWSER;
Current.isDuckAndGo = IS_DUCK_AND_GO;

const View = new TdbPaymentView();
const Model = new TdbPaymentModel();
const Controller = new TdbPaymentController();

document.addEventListener('DOMContentLoaded', function() {
    Controller.init();
});

</script>

