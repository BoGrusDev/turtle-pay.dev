var URL = "/wa-lib4/service/";

var Action = {};
var Confirm = {};

var Webform;
//var Selections

var Progress = {};

Progress.start = function() {
    var param = {};
    param._action = "Qprogress";
    param._log_id = QLOG_ID;
   
    //alert(URL);

    $.ajax({ type: "POST", url: URL, data: JSON.stringify(param), contentType : 'application/json',
        success: function(result) {
            var data = jQuery.parseJSON(result);
            if (data.code == '1') {
                $('#status-text').html(message['klart']);
                /*
                if (data.uc == 'y') {
                    alert('UC');
                }
                */
            } 
            else {
                //alert(data.denied_code);
                if (data.denied_code == 'No such order') {
                    $('#status-text').html(message['not-in-progress']);
                }
                else  if (data.denied_code == 'userCancel' || data.denied_code == 'expiredTransaction') {
                    $('#status-text').html(message['bankid-cancel']);
                }
                else  if (data.denied_code == 'not-in-progress') {
                    $('#status-text').html(message['not-in-progress']);
                }
                else  if (data.denied_code == 'complete-rejected') {
                    $('#status-text').html(message['complete-rejected'] + message['turtle']);
                }
                
               else {
                $('#status-text').html(message['not-in-progress']);
               }
            }
        },
        error: function(result){
            console.log(result);
            $('#status-text').html(message['not']);
        }
    });
}

$(document).on('click', '#eMessageBoxClose', function(event) {
    event.preventDefault();
    $('#message-box').removeClass( 'is-active');
});

$(document ).ready(function() {
    //alert('ready to start: ' + QLOG_ID);
    Progress.start();
});

var messageTurtle =  "<br>För information kontakta Turtle Pay AB på info@turtle-pay.com eller tel. 08-806220.";
var message = {};
message['klart'] = '<strong>KLART!</strong><br/>';
message['klart'] += 'Skuldebrev och inbetalningsavi har skickats till din angivna e-postadress.<br/>';
message['klart'] += 'Om du inte fått skuldebrevet och inbetalningsavin inom några minuter, kontakta Turtle Pay AB på info@turtle-pay.com eller tel. 08-806220.<br/>';
message['not-in-progress'] = "<strong>INGET ERBJUDANDE PÅGÅR FÖR TILLFÄLLET!</strong><br/>" + messageTurtle; 
message['not'] = "<strong>EJBJUDANDET  GICK INTE ATT GENOMFÖRA!</strong><br/>" + messageTurtle;
message['bankid-cancel'] = "<strong>SIGNERING MED BANKID GICK EJ ATT GENOMFÖRA!</strong><br/>" + messageTurtle;

message['turtle'] =  "<br><br>Kontakta Turtle Pay för information,<br>08-806220 eller info@turtle-pay.com";
message['complete-rejected'] = "<strong>MEDGES EJ!</strong>"
