var URL = "/wa-lib4/service/";
var Form = {};
var Action = {};

var Confirm = {};
var Webform;

var Participant = new Array();

var ParticipantCurrentIndex = 0;
var TotalAmount = 0;


var message = {};
message['turtle'] =  "<br><br>Kontakta Turtle Pay för information,<br>08-806220 eller info@turtle-pay.com";


Confirm.checkForm = function () {
    
    Form.personal_id_number = $('#personal_id_number').val();
    // if (Webform['participant_on'] == 'y') {
        // Form.amount = $('#total_amount').val();
    //}
    //else {
        // -- FIX Form.amount = $('#amount').val();
    // }
    //Form.receipt_number = $('#receipt_number').val();
    Form.email = $('#email').val();
    Form.mobile = $('#mobile').val();
    Form.clearingno = $('#infotext-small-1').val();
    Form.bank_accountno = $('#infotext-1').val();

    Form.amount = $('#option-0').val();
    Form.term = $('#option-1').val();
    Form.repay_type = $('#option-2').val();

    if (Form.amount == '8E1C7E8F67D0') {
        $('#message-box-text').html('Välj lånebelopp!');
        $('#message-box').addClass('is-active');
        return ;
    }
    if (Form.term ==  '8E1C7E8F67D0') {
        $('#message-box-text').html('Välj löptid & räntesatts!');
        $('#message-box').addClass('is-active');
        return ;
    }
    if (Form.repay_type ==  '8E1C7E8F67D0') {
        $('#message-box-text').html('Välj betalning av ränta!');
        $('#message-box').addClass('is-active');
        return ;
    }

    if (Tool.isValidSwedishSSN(Form.personal_id_number) == false) {
        $('#message-box-text').html('Personnummer är inte giltigt!');
        $('#message-box').addClass('is-active');
        return;
    }
    if (isNaN(Form.personal_id_number)) {
        $('#message-box-text').html('Personnummer är inte giltigt!');
        $('#message-box').addClass('is-active');
    }

    if (Form.email.length < 5) {
        $('#message-box-text').html('E-postaddress är inte giltigt');
        $('#message-box').addClass('is-active');
        return ;
    }
    if (validateEmail(Form.email) == false) {
        $('#message-box-text').html('E-postaddress är inte giltigt');
        $('#message-box').addClass('is-active');
        return;
    }

    if (Form.clearingno.length < 3) {
        $('#message-box-text').html('Clearingnummer måste var minst 3 siffror!');
        $('#message-box').addClass('is-active');
        return ;
    }

    if (Form.bank_accountno.length < 7) {
        $('#message-box-text').html('Bankkonto måste var minst 7 siffror!');
        $('#message-box').addClass('is-active');
        return ;
    }
        
    Confirm.initOffer();
}

Confirm.initOffer = function() {

    var param = {};
    param._action = "InitOffer";
    param.personal_id_number = Form.personal_id_number;
    param.amount = Form.amount;
    param.email = Form.email;
    param.mobile = Form.mobile;
    
    param.id = COMPANY_ID;
    param._invoice_event_id = INVOICE_EVENT_ID; 
    param._invoice_event_item_id = INVOICE_EVENT_ITEM_ID; 
    param.event_id = EVENT_ID;
    param.bank_accountno = Form.bank_accountno;
    param.clearingno = Form.clearingno;
    param.term = Form.term;
    param.repay_type = Form.repay_type;

    $.ajax({ type: "POST", url: URL, data: JSON.stringify(param), contentType : 'application/json',
        success: function(result) {
            
            var data = jQuery.parseJSON(result);
           
            if (data.code == '1') {   
                Confirm.goProgress(data);  
            }
            else if (data.code == '7') {
                $('#message-box-text').html('BankID är upptagen, försök igen om en stund!');
                $('#message-box').addClass('is-active');
                return;
            }
            else {
                
                //if (INVOICE_EVENT_ITEM_ID == '0') {
                    //window.location.href = SITE_URL + '?m=denied';
                //}
                //else {
                   // window.location.href = SITE_URL + '?m=denied&id=' + INVOICE_EVENT_ITEM_ID;
                //}
                
                $('#message-box-text').html('Okänt fel' + message['turtle']);
                $('#message-box').addClass('is-active');
                return;
            }
           
        },
        error: function(result) {
            $('#message-box-text').html('Något fel har inträffat försök igen!');
            $('#message-box').addClass('is-active');
            return;
        }
    });
}

Confirm.goProgress = function(data) {

    element = document.getElementById("BankIDCheckBox");
    if (element.checked) {
        internalBankID = true;
    } 
    else {
        internalBankID = false;
    }
    if (IS_MOBILE == 'yes') {   
        if (internalBankID == true) {
            //alert('Internal');
            var url = "";
            if (Browser == "Safari") {
                //var redirect =  SITE_URL + '?p=' + data.waid + '&id=' + EVENT_ID;
                var redirect =  SITE_URL + '?q=' + data.waid;
                
                url = "bankid:///?autostarttoken=" + data.auto + "&redirect=" + redirect;
                //url = "bankid:///?autostarttoken=" + data.auto + "&redirect=";
            }
            else if (Browser == "Chrome") {
                var redirect =  SITE_URL + '?q=' + data.waid;
                //url = "bankid:///?autostarttoken=" + data.auto + "&redirect=googlechrome:///";
                url = "bankid:///?autostarttoken=" + data.auto + "&redirect=googlechrome:///";
            }
            else if (Browser == "Firefox") {
                url = "bankid:///?autostarttoken=" + data.auto + "&redirect=firefox:///";
            }
            else {
                url = "bankid:///?autostarttoken=" + data.auto;
            }
           //alert(data.waid);
            $('.view-1').hide();
            $('#status-text').html('');
            $('#MobilePanel').show();
            $('.view-2').show();
            WaId = data.waid;
            window.location.href = url;
           return;
        } 
        else {
            // Mobile and not BankID on Mobile
            $('.view-1').hide();
            $('#status-text').html('');
            $('#MobilePanel').show();
            $('.view-2').show();

            WaId = data.waid;
            return;
        }
    }
    
    if (internalBankID == true) {
        var redirect =  SITE_URL + '?q=' + data.waid;
        $('.view-1').hide();
        $('#status-text').html('');
        $('#MobilePanel').show();
        
        $('.view-2').show();
        WaId = data.waid;
       
        if (Browser == "Chrome") {
            url = "bankid:///?autostarttoken=" + data.auto + "&redirect=googlechrome:///";
        }
        else if (Browser == "Firefox") {
            url = "bankid:///?autostarttoken=" + data.auto + "&redirect=firefox:///";
        }
        else if (Browser == "Internet Explorer") {
            url = "bankid:///?autostarttoken=" + data.auto + "&redirect=iexplore:///";
        } 
        else if (Browser == "edge") {
            url = "bankid:///?autostarttoken=" + data.auto + "&redirect=edge:///";
        } 
        else if (Browser == "Safari") {
            var redirect =  SITE_URL + '?p=' + data.waid;
            url = "bankid:///?autostarttoken=" + data.auto + "&redirect=" + redirect;
        }
        else {
            url = "bankid:///?autostarttoken=" + data.auto + "&redirect=";
        }
            
        window.location.href = url;
        return;
    }
    window.location.href = SITE_URL + '?q=' + data.waid;
    return;
}


/*
amount: "50000"
​
bank_accountno: "01045454"
​
clearingno: "254"
​
email: "bo.grus@icloud.com"
​
mobile: "05787822"
​
personal_id_number: "195711040054"
​
repay_type: "1"
​
terms_type: "12"
*/

$(document).on('click', '#eConfirm', function(event) {
    event.preventDefault();
    if (Webform.participant_on == 'y') {
        // --FIX saveParticipant(ParticipantCurrentIndex); // NEED TO BE FIXED
        // --FIX calculateTotal();  // NEED TO BE FIXED
    }
    Confirm.checkForm();
  
});

$(document ).ready(function() {
  
    var param = {};
    param._action = "LoadEvent";
    param._event_id = EVENT_ID;
    $.ajax({ type: "POST", url: URL, data: JSON.stringify(param), contentType : 'application/json', 
        success: function(result) {
            //alert(result)
            Webform = jQuery.parseJSON(result);
           
            OptionCounts = Webform.selection.length;
            Participant[0] = {};
            Participant[0].status = "a";
            Participant[0].option = new Array();
            for (var i=0; i <  OptionCounts; i++) {
                Participant[0].option[i] = {};
            }
            $('#total_amount').prop("disabled", true);
            
            var ccsStyle = ".webform-text-color {color: " + Webform.text_color + ";}";
            $("<style>")
            .prop("type", "text/css").html(ccsStyle).appendTo("head");
            
        }
    });
});


$(document).on('click', '#eMessageBoxClose', function(event) {
    event.preventDefault();
    $('#message-box').removeClass( 'is-active');
});

var Tool = {};

Tool.isValidSwedishSSN = function (ssnInput) {

    if (ssnInput.length !=12) {
        return false;
    }
    let century = ssnInput.substring(0, 2);
    if (century == "19" || century =="20") {
    //if (century.includes("19") || century.includes("20")) {
        ssnInput = ssnInput.substring(2);
    } else {
        return false;
    }
    let ssn = ssnInput
        .replace(/\D/g, "")     // strip out all but digits
        .split("")              // convert string to array
        .reverse()              // reverse order for Luhn
        .slice(0, 10);          // keep only 10 digits (i.e. 1977 becomes 77)
     // verify we got 10 digits, otherwise it is invalid
    if (ssn.length != 10) {
        return false;
    }

    let sum = ssn
    // convert to number
    .map(function(n) {
        return Number(n);
    })
    // perform arithmetic and return sum
    .reduce(function(previous, current, index) {
        // multiply every other number with two
        if (index % 2) current *= 2;
        // if larger than 10 get sum of individual digits (also n-9)
        if (current > 9) current -= 9;
        // sum it up
        return previous + current;
    });

    // sum must be divisible by 10
    return 0 === sum % 10;
}

function validateEmail (mail) {
    if (/^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/.test(mail)) {
        return true;
    }
    else {
        return false;
    }
}

$(document).on('keypress', '.only-numeric', function (e) {
	var keyCode = e.which ? e.which : e.keyCode     
	if (!(keyCode >= 48 && keyCode <= 57)) {
		return false;
	}
});
