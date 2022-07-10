var URL = "/wa-lib4/service/";
//var URL = "https://turtle-pay.com/wa-lib4/service/";
var Form = {};
var Action = {};
Action.eventSpecOn = 'n';

var Confirm = {};
var Webform;
var message = {};
message['turtle'] =  "<br><br>Kontakta Turtle Pay för information,<br>08-806220 eller info@turtle-pay.com";
//message['exist'] = "<strong>EN FAKTURA MED SAMMA BELOPP OCH REFERNS FINNS REDAN!</strong><br/>" + messageTurtle;
//message['klart'] = '<strong>KLART</strong><br/>';
//message['klart'] += 'Fakturan har skickats till din angivna e-postadress.<br/>';
//message['klart'] += 'Om du inte fått fakturan inom några minuter, kontakta Turtle Pay AB på info@turtle-pay.com eller tel. 08-806220.<br/>';


var Participant = new Array();

var ParticipantCurrentIndex = 0;
var TotalAmount = 0;

$(document).on('change', '.select-option', function(event) {
    saveParticipant(ParticipantCurrentIndex);
    calculateTotal();
});

$(document).on('click', '.participant-tab', function(event) {
    event.preventDefault();
    saveParticipant(ParticipantCurrentIndex);
    $('.participant-tab').removeClass('is-active');
    ParticipantCurrentIndex = $(this).attr('index');
    $(this).addClass('is-active');
    $('#first-name').val(Participant[ParticipantCurrentIndex].first_name);  
    $('#last-name').val(Participant[ParticipantCurrentIndex].last_name); 
    if (Webform.participant_address_on == 'y') {
        $('#part-address').val(Participant[ParticipantCurrentIndex].address);
        $('#part-postcode').val(Participant[ParticipantCurrentIndex].postcode); 
        $('#part-city').val(Participant[ParticipantCurrentIndex].city);
        $('#part-mobile').val(Participant[ParticipantCurrentIndex].mobile);  
        $('#part-email').val( Participant[ParticipantCurrentIndex].email);
    }
    if (Webform.note_on == 'y') {
        $('#note').val(Participant[ParticipantCurrentIndex].note);
    }

    if (Webform.date_of_birth_on == 'y') {
        $('#date_of_birth').val(Participant[ParticipantCurrentIndex].date_of_birth);
    }

    if (Webform.collect_spar_on == 'y') {
        $('#part-personal-id').val(Participant[ParticipantCurrentIndex].personal_id_number); 
        if (Webform.participant_address_on == 'n') {
            $('#part-address').val(Participant[ParticipantCurrentIndex].address);
            $('#part-postcode').val(Participant[ParticipantCurrentIndex].postcode); 
            $('#part-city').val(Participant[ParticipantCurrentIndex].city);
        }
    }

    for (var i=0; i < OptionCounts; i++) {
        setSelectedByText('option-' + i, Participant[ParticipantCurrentIndex].option[i].text);
    }
});

$(document).on('click', '#eAddTab', function(event) {
    event.preventDefault();

    if (Webform.participant_apply_limit_on == 'n') {
        // continue
    }
    else {
        if (Participant.length < Webform.participant_apply_max) {
            // contunue
        }
        else {
            $('#message-box-text').html('Max antal deltagare på denna anmälan är  ' + Webform.participant_apply_max);
            $('#message-box').addClass('is-active');
            return;
        }
    }

    saveParticipant(ParticipantCurrentIndex);
    $('.participant-tab').removeClass('is-active');
    ParticipantCurrentIndex = Participant.length;
    $('#eAddTab').before('<li class="is-active participant-tab" index="' + ParticipantCurrentIndex + '" style="font-size:13px"><a>' + Webform.participant_title + '</a></li>');
    Participant[ParticipantCurrentIndex] = {};
    Participant[ParticipantCurrentIndex].status = "a";
    Participant[ParticipantCurrentIndex].option = new Array();
    for (var i=0; i < OptionCounts; i++) {
        Participant[ParticipantCurrentIndex].option[i] = {};
        $('#option-' + i).val('8E1C7E8F67D0');
    }
    $('#first-name').val('');  
    $('#last-name').val(''); 
    if (Webform.participant_address_on == 'y') {
        $('#part-address').val('');  
        $('#part-postcode').val(''); 
        $('#part-city').val('');  
        $('#part-mobile').val(''); 
        $('#part-email').val(''); 
    }
    if (Webform.note_on == 'y') {
        $('#note').val('');  
    }

    if (Webform.date_of_birth_on == 'y') {
        $('#date_of_birth').val('');  
    }

    
    if (Webform.collect_spar_on == 'y') {
        $('#part-personal-id').val(''); 
        if (Webform.participant_address_on == 'n') {
            $('#part-address').val('');  
            $('#part-postcode').val(''); 
            $('#part-city').val('');  
        }
    }
});

$(document).on('click', '#eRemoveTab', function(event) {
    event.preventDefault();
    var active = 0;
    for (var i = 0; i < Participant.length; i++) {
        if (Participant[i].status == 'a') {
            active++;
        }
    }
   
    if (active == 1) {
        $('#message-box-text').html('Kan inte ta bort alla ' + WEBFORM_PARTICIPANT_LABEL);
        $('#message-box').addClass('is-active');
        return;
    }
    
    Participant[ParticipantCurrentIndex].status = "x";
    var element = ".participant-tab[index='" + ParticipantCurrentIndex + "']";
    $(element).hide();
    var firstActive = -1;
    for (var i = 0; i < Participant.length; i++) {
        if (Participant[i].status == 'a' && firstActive == -1) {
            firstActive = i;
        }
    }
    ParticipantCurrentIndex = firstActive;
 
    element = ".participant-tab[index='" + ParticipantCurrentIndex + "']";
    
    $(element).addClass('is-active');
    $('#first-name').val(Participant[ParticipantCurrentIndex].first_name);  
    $('#last-name').val(Participant[ParticipantCurrentIndex].last_name); 
    for (var i=0; i < OptionCounts; i++) {
        setSelectedByText('option-' + i, Participant[ParticipantCurrentIndex].option[i].text);
    }

    saveParticipant(ParticipantCurrentIndex);
    calculateTotal();

});

function saveParticipant(index) {
    //alert(index);
    Participant[index].first_name = $('#first-name').val();  
    Participant[index].last_name = $('#last-name').val(); 

    if (Webform.participant_address_on == 'y') {
        Participant[index].address = $('#part-address').val();  
        Participant[index].postcode = $('#part-postcode').val(); 
        Participant[index].city = $('#part-city').val();  
        Participant[index].mobile = $('#part-mobile').val(); 
        Participant[index].email = $('#part-email').val(); 
    }
    if (Webform.note_on == 'y') {
        Participant[index].note = $('#note').val(); 
    }

    if (Webform.date_of_birth_on == 'y') {
        Participant[index].date_of_birth = $('#date_of_birth').val(); 
    }
    
    if (Webform.collect_spar_on == 'y') {
        Participant[index].personal_id_number = $('#part-personal-id').val(); 
        if (Webform.participant_address_on == 'n') {
            Participant[index].address = $('#part-address').val();  
            Participant[index].postcode = $('#part-postcode').val(); 
            Participant[index].city = $('#part-city').val();  
        }
    }

    for (var i=0; i < OptionCounts; i++) {
       
        var value = $('#option-' + i).val();
        if(Webform.selection[i].calculate_on == 'y') {
            Participant[index].option[i].value = value;
        }
        else {
            Participant[index].option[i].value
        }

        //Participant[index].option[i].value

        var text = $('#option-' + i + ' option:selected').text(); 
        Participant[index].option[i].text = text;
        Participant[index].option[i].event_option_setting_id = getOptionId(i, text);
        //alert(Participant[index].option[i].event_option_setting_id );
    } 
}

function calculateTotal() {
    var total = 0;
    for (var i = 0; i < Participant.length; i++) {
        if (Participant[i].status == "a") {
            for (var j = 0; j < Webform.selection.length; j++) {
                if(isNaN(Participant[i].option[j].value)) {
                    // do nothing
                }
                else {
                    if(Webform.selection[j].calculate_on == 'y') {
                        total = total + Number(Participant[i].option[j].value);
                    }
                }  
            }
        }
    }
    if (Webform.amount_on == 'y') {
        var amount = $('#amount').val();
        if (Number(amount) == false || Number(amount) == NaN) {
            // Skip no value
        }
        else {
            total = total + Number(amount);
        }
    } 
    $('#total_amount').val(total); // Total
}

function optionCheck() {
    var checkOK = true;
    for (var i = 0; i < Participant.length; i++) {
        for (var j=0; j < OptionCounts; j++) {
            //alert(Participant[index].option[i].value);
            //Participant[index].option[i].webform_option_id = Selections[i].option[i].webform_option_id;
            //if ($('#option-' + j).val() == '8E1C7E8F67D0') {
                //checkOK = false;
            //}
        }
    }

    return checkOK;
}

function setSelectedByText(eID, text) {
    // console.log('Text: ' + text + ' eID: ' + eID);
    var ele=document.getElementById(eID);
    for(var ii=0; ii<ele.length; ii++)
        if(ele.options[ii].text==text) { //Found!
            // console.log('Found ');
            ele.options[ii].selected=true;
            return true;
        }
    return false;
}

function getOptionId(selectionIndex, text) {

    //alert("Option id: " + selectionIndex + " " + text);
    var optionId = 0;
    
    for (i=0; i<Webform.selection[selectionIndex].option.length; i++) {
        //alert(Webform.selection[selectionIndex].option[i].text);
        if (Webform.selection[selectionIndex].option[i].text == text) {
           
            //alert(Webform.selection[selectionIndex].option[i].event_option_setting_id);
            optionId = Webform.selection[selectionIndex].option[i].event_option_setting_id;
        }
    }
    //alert(optionId);
    return optionId;
}
// -- End spec

$(document).on('click', '#eGetFromSpar', function(event) {
    event.preventDefault();
    var peopleIdNumber = $('#part-personal-id').val();
    var param = {};
    param._action = "Spar";
    param._personal_id_number = peopleIdNumber;
    $.ajax({ type: "POST", url: URL, data: JSON.stringify(param), contentType : 'application/json', 
        success: function(result) {
           
            var data  = jQuery.parseJSON(result);
            
            if (data.status == '1') {
                $('#first-name').val(data.people.first_name);  
                $('#last-name').val(data.people.last_name); 
                $('#part-address').val(data.people.address);  
                $('#part-postcode').val(data.people.postcode); 
                $('#part-city').val(data.people.city);  
                    /*
                        { "people":{"personal_id_number":"195711040054","first_name":"Bo Erik",
                        "last_name":"Grusell","address":"DUVEDSV\u00c4GEN 15 LGH 1202","postcode":"16265",
                        "city":"V\u00c4LLINGBY"},"status":"1"}
                    }
                    */
            }  
            else {
             
                $('#message-box-text').html('Kontrollera personnummer!');
                $('#message-box').addClass('is-active');
            }
        }     
    });
   
});

$(document).on('click', '#eConfirm', function(event) {
    event.preventDefault();
    if (Webform.participant_on == 'y') {
        saveParticipant(ParticipantCurrentIndex);
        calculateTotal();
    }
    Confirm.checkForm();
});

$(document).on('click', '#eUcBoxContinue', function(event) {
    event.preventDefault();
    $('#uc-box').removeClass( 'is-active');
   
    // -- Ny del
    var param = {};
    param._action = "UcInit";
    // param._action = "Request";
    param.personal_id_number = Form.personal_id_number;
    param.amount = Form.amount;
    param.receipt_number = Form.receipt_number;
    param.email = Form.email;
    
    if (Webform.mobile_on == 'y') {
        param.mobile = $('#mobile').val(); 
    }
   
    param.id = COMPANY_ID;
    param._invoice_event_id = INVOICE_EVENT_ID; 
    param._invoice_event_item_id = INVOICE_EVENT_ITEM_ID; 
   
    param.event_id = EVENT_ID;
    param.participant_on = Webform.participant_on;
    if (Webform.participant_on == 'y') {
        param.participant = Participant;
    }
    param.infobox_1_on = Webform.other_info_on;
    if (Webform.infobox_1_on == 'y') {
        param.infobox_1 = $('#infobox_1').val();
    }
    if (Webform.infobox_2_on == 'y') {
        param.infobox_2 = $('#infobox_2').val();
       
    }

    param._people_id = Form._people_id;
    // -- Del 

    $.ajax({ type: "POST", url: URL, data: JSON.stringify(param), contentType : 'application/json',
        success: function(result) {
            //alert(result);

            var data = jQuery.parseJSON(result);
            Confirm.goProgress(data);

            /*
            if (IS_MOBILE == 'y') {
                alert('mobile');
            }
            else {
                //Confirm.goProgress(data);
                Confirm.progressUc(data.order_ref);
            }
            */
        }
    });
});

$(document).on('click', '#eUcBoxCancel', function(event) {
    event.preventDefault();
    $('#uc-box').removeClass( 'is-active');
});

Confirm.checkForm = function () {
    
    Form.personal_id_number = $('#personal_id_number').val();
    if (Webform['participant_on'] == 'y') {
        Form.amount = $('#total_amount').val();

        if (Form.amount < 0 ) {
            $('#message-box-text').html('Avisad - negativt belopp!');
            $('#message-box').addClass('is-active');
            return;
        }
    }
    else {
        Form.amount = $('#amount').val();
    }

    if( $('#date_of_birth').length )  {
        var dateOfBirth = $('#date_of_birth').val();
        if (dateOfBirth.length < 6) {
            $('#message-box-text').html('Födelsdatum måste vara 6 siffror!');
            $('#message-box').addClass('is-active');
            return;
        }
    }

    Form.receipt_number = $('#receipt_number').val();
    Form.email = $('#email').val();

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

    if (Form.receipt_number.length < 1) {
        $('#message-box-text').html('Ange referens');
        $('#message-box').addClass('is-active');
        return;
    }
    if (Webform.amount_on == 'y') {
        /* TEMP
        if (Form.amount.length < 3) {
            $('#message-box-text').html('Felaktigt belopp');
            $('#message-box').addClass('is-active');
            return;
        }
        */
        if (isNaN(Form.amount)) {
            $('#message-box-text').html('Felaktigt belopp');
            $('#message-box').addClass('is-active');
            return;
        }
    }

    if (Webform.participant_on == 'y') {
        
        var formComplete = true;
        for (var i = 0; i < Participant.length; i++) {
            if (Participant[i].first_name.length < 1) {
                formComplete = false;
            }
            if (Participant[i].last_name.length < 1) {
                formComplete = false;
            }
            for (j = 0; j < Participant[i].option.length; j++) {
                if (Participant[i].option[j].value == '8E1C7E8F67D0') {
                    formComplete = false;
                }
            }
        } 
       
        if (formComplete == false) {
            $('#message-box-text').html(Webform.participant_title + ' information är inte komplett');
            $('#message-box').addClass('is-active');
            return;
        }
    }
    
    // alert('415 OK');

    Confirm.checkDoubleInvoice();                         
}

Confirm.checkDoubleInvoice = function () {
   
    var param = {};
    param._action = "CheckDoubleInvoice";
    param._personal_id_number = Form.personal_id_number;
    param._amount = Form.amount;
    param._receipt_number = Form.receipt_number;
    param._id = COMPANY_ID;
    $.ajax({ type: "POST", url: URL, data: JSON.stringify(param), contentType : 'application/json',
        success: function(result) {
            var data = jQuery.parseJSON(result);
            //if (data.code == '1' && data.exist == '1') // TEMP REMOVE
            if (1 == 0) { // Never happend (TEMP)
                //window.location.href = SITE_URL + '?m=exist&id=' + EVENT_ID;
                $('#message-box-text').html('En faktura med samma referens och belopp finns redan!');
                $('#message-box').addClass('is-active');
                return;
            }
            else {
                Confirm.checkOverdue();
                return false;
            }
        },
        error: function(result) {
            //Check();
            alert('Call error');
            return false;
        }
    });
}

Confirm.checkOverdue = function() {
    var param = {};
    param._action = "OverdueCheck";
    param._personal_id_number = Form.personal_id_number;
    
    $.ajax({ type: "POST", url: URL, data: JSON.stringify(param), contentType : 'application/json',
        success: function(result) {
            var data = jQuery.parseJSON(result);
            if (data.code == '1') {
                if (data.people_status == 'b' || data.overdue > 0) {
                    if (INVOICE_EVENT_ITEM_ID == '0') {
                        window.location.href = SITE_URL + '?m=denied';
                    }
                    else {
                        window.location.href = SITE_URL + '?m=denied&id=' + INVOICE_EVENT_ITEM_ID;
                    }
                    // $('#message-box-text').html('Medges ej!' + message['turtle']);
                    // $('#message-box').addClass('is-active');
                    return;
                }
                else {
                    Confirm.request();
                }
            }
           
            else {
                Confirm.request();          }
        },
        error: function(result) {
            $('#message-box-text').html('Ett fel har inträffat, kontakta Turtle Pay AB, för mer information!');
            $('#message-box').addClass('is-active');
            return;
        }
    });
}

Confirm.request = function() {

    var param = {};
    param._action = "Request";
    param.personal_id_number = Form.personal_id_number;
    param.amount = Form.amount;
    param.receipt_number = Form.receipt_number;
    param.email = Form.email;
    if (Webform.mobile_on == 'y') {
        param.mobile = $('#mobile').val(); 
    }
   
    param.id = COMPANY_ID;
    param._invoice_event_id = INVOICE_EVENT_ID; 
    param._invoice_event_item_id = INVOICE_EVENT_ITEM_ID; 
   
    param.event_id = EVENT_ID;
    param.participant_on = Webform.participant_on;
    if (Webform.participant_on == 'y') {

        if (INHERIT == '0') {
            for (var i=0; i<Participant.length; i++) {
                Participant[i].base_participant_id = '0';
            }
        }
        param.participant = Participant;
    }
    if (Webform.infobox_1_on == 'y') {
        param.infobox_1 = $('#infobox_1').val();
    }
    if (Webform.infobox_2_on == 'y') {
        param.infobox_2 = $('#infobox_2').val();
    }
  

    $.ajax({ type: "POST", url: URL, data: JSON.stringify(param), contentType : 'application/json',
        success: function(result) {
           // alert(result);
            var data = jQuery.parseJSON(result);
           
            if (data.code == '1') {   
                Confirm.goProgress(data);  
            }
            else if (data.code == '8') {
                Form._people_id = data.people_id;
                $('#uc-box').addClass('is-active');
            }
            else if (data.code == '7') {
                $('#message-box-text').html('BankID är upptagen, försök igen om en stund!');
                $('#message-box').addClass('is-active');
                return;
            }
            else if (data.code == '0') {
                if (data.denied_code == 'no_credit_limit') {
                    if (INVOICE_EVENT_ITEM_ID == '0') {
                        window.location.href = SITE_URL + '?m=denied';
                    }
                    else {
                        window.location.href = SITE_URL + '?m=denied&id=' + INVOICE_EVENT_ITEM_ID;
                    }
                    //$('#message-box-text').html('Medges ej!' + message['turtle']);
                    //$('#message-box').addClass('is-active');
                    return;

                }
                else {
                    if (INVOICE_EVENT_ITEM_ID == '0') {
                        window.location.href = SITE_URL + '?m=denied';
                    }
                    else {
                        window.location.href = SITE_URL + '?m=denied&id=' + INVOICE_EVENT_ITEM_ID;
                    }
                    // $('#message-box-text').html('Medges ej' + message['turtle']);
                    // $('#message-box').addClass('is-active');
                    return;
                }
            }
            else {
                $('#message-box-text').html('Ett BankID fel har inträttats, försök igen om en stund!');
                $('#message-box').addClass('is-active');
                return;
            }
        },
        error: function(result) {
            $('#message-box-text').html('En faktura med samma referens och belopp finns redan!');
            $('#message-box').addClass('is-active');
            return;
            //window.location.href = SITE_URL + '?m=not&id=' + EVENT_ID;
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
                var redirect =  SITE_URL + '?p=' + data.waid;
                
                url = "bankid:///?autostarttoken=" + data.auto + "&redirect=" + redirect;
                //url = "bankid:///?autostarttoken=" + data.auto + "&redirect=";
            }
            else if (Browser == "Chrome") {
                var redirect =  SITE_URL + '?p=' + data.waid;
                //url = "bankid:///?autostarttoken=" + data.auto + "&redirect=googlechrome:///";
                url = "bankid:///?autostarttoken=" + data.auto + "&redirect=googlechrome:///";
            }
            else if (Browser == "Firefox") {
                url = "bankid:///?autostarttoken=" + data.auto + "&redirect=firefox:///";
            }
            else {
                url = "bankid:///?autostarttoken=" + data.auto;
            }
			
			if (IS_MOBILE == "yes") {
				WaId = data.waid;
				$('#login-mobile-modal-text').html("Väntar på BankID signering");
				$('#eMobileLogin').show();
				$('#login-mobile-modal').addClass('is-active');
				
				if (document.getElementById("BankIDCheckBox").checked == true) {
					window.location.href = url;
				}
				return;
			}
			else {
			   //alert(data.waid);
				$('.view-1').hide();
				$('#status-text').html('');
				$('#MobilePanel').show();
				$('.view-2').show();
				
				WaId = data.waid;
				window.location.href = url;
			   return;
			}
           
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
    // This is no mobile

    if (internalBankID == true) {
        var redirect =  SITE_URL + '?p=' + data.waid;
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
            

    	WaId = data.waid;
		// window.location.href = SITE_URL + '?p=' + data.waid;
		// return;
        $('#login-mobile-modal-text').html("BankID signering klar");
        $('#eMobileLogin').show();
        $('#login-mobile-modal').addClass('is-active');
        
        if (document.getElementById("BankIDCheckBox").checked == true) {
            window.location.href = url;
        }
        return;

        //window.location.href = url;
        //return;
    }
    //alert(SITE_URL + '?p=' + data.waid);
    window.location.href = SITE_URL + '?p=' + data.waid;
    return;
}

// Use for Mobile login
$(document).on('click', '#eMobileLogin', function(event) {
    event.preventDefault();
    window.location.href = SITE_URL + '?p=' + WaId;
   
    // -- $('.view-1').hide();
    // -- $('#status-text').html('');
    // -- $('#MobilePanel').show();
    // -- $('.view-2').show();
    // -- WaId = data.waid;
});

// var Progress = {};

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

$(document ).ready(function() {
    
    var param = {};
    param._action = "LoadEvent";
    param._event_id = EVENT_ID;
    $.ajax({ type: "POST", url: URL, data: JSON.stringify(param), contentType : 'application/json', 
        success: function(result) {
            //alert(result)
            Webform = jQuery.parseJSON(result);
            if (Webform.participant_on == 'y') {
                OptionCounts = Webform.selection.length;
               
                // var INHERIT = '426'; // Need in the index.inc
                if (INHERIT == '0') {
                    Participant[0] = {};
                    Participant[0].status = "a";
                    Participant[0].option = new Array();
                    for (var i=0; i <  OptionCounts; i++) {
                        Participant[0].option[i] = {};
                    }
                }
                else {
                    var param = {};
                    param._action = "LoadInheritParticipant";
                    param._parent_event_item_id = INHERIT;
                    param._event_id = EVENT_ID;
                    $.ajax({ type: "POST", url: URL, data: JSON.stringify(param), contentType : 'application/json', 
                        success: function(result) {
                         
                            var data = jQuery.parseJSON(result);
                            for (var i=0; i<data.length; i++) {
                                Participant[i] = {};
                                Participant[i].first_name = data[i].first_name;
                                Participant[i].last_name =  data[i].last_name;
                                Participant[i].base_participant_id = data[i].event_participant_id;
                              
                                Participant[i].base_participant_id = data[i].base_participant_id;
                                
                                Participant[i].status = "a";

                                Participant[i].option = new Array();
                               
                                for (var j=0; j < data[i].parents.length; j++) {
                                    Participant[i].option[j] = {};
                                 
                                    Participant[i].option[j].value = data[i].parents[j].value;
                                    Participant[i].option[j].text = data[i].parents[j].text;
                                    Participant[i].option[j].event_option_setting_id = data[i].parents[j].event_option_setting_id;
                                    
                                    if (i==0 && data[i].parents[j].value != '8E1C7E8F67D0') { // } && j==0) {
                                        setSelectedByText('option-' + j, Participant[0].option[j].text);
                                        $('#option-' + j).prop( "disabled", true);
                                    }
                                }
                                calculateTotal();
                            }
                            $('#first-name').val(Participant[0].first_name);
                            $('#first-name').prop( "disabled", true);
                            $('#last-name').val(Participant[0].last_name);
                            $('#last-name').prop( "disabled", true);
                            if (Webform.participant_address_on == 'y') {
                              
                            }
                            if (Webform.note_on == 'y') {
                                // $('#note').val(Participant[0].note);
                            }
                            if (Webform.date_of_birth_on == 'y') {
                                // $('#date_of_birth').val(Participant[0].date_of_birth);
                            }
                            if (Webform.collect_spar_on == 'y') {
                                // $('#part-personal-id').val(Participant[0].personal_id_number);
                                // $('#part-personal-id').prop( "disabled", true);
                            }
                        }
                    });
                }
               
                $('#total_amount').prop("disabled", true);
            }
            /*
            if (Webform['ref'].length > 0) {
                $('#receipt_number').val(Webform['ref']);
                $('#receipt_number').prop("disabled", true);
            }
            if (Webform['amount'].length > 0) {
                var amount = Webform['amount'];
                if (Number(amount) == false || Number(amount) == NaN) {
                    // Skip no value
                }
                else {
                    $('#amount').val(Webform['amount']);
                    $('#amount').prop("disabled", true);
                }
            }
            */
            var ccsStyle = ".webform-text-color {color: " + Webform.text_color + ";}";
            $("<style>")
            .prop("type", "text/css").html(ccsStyle).appendTo("head");
            
            //alert(INVOICE_EVENT_ID);

           // $('#intro_text_edit').html(Webform.intro_text.split("\n").join("<br />"));
        }
    });
});

$(document).on('keypress', '.only-numeric', function (e) {
	var keyCode = e.which ? e.which : e.keyCode     
	if (!(keyCode >= 48 && keyCode <= 57)) {
		return false;
	}
});

$(document).on('keypress', '.only-numeric-point', function (e) {
    var keyCode = e.which ? e.which : e.keyCode     
	if (keyCode == 46) {
		// return true; - tecken
	} 
	else if (!(keyCode >= 48 && keyCode <= 57)) {
		return false;
	}
});

$(document).on('keypress', '.no-special', function (e) {
	var keyCode = e.which ? e.which : e.keyCode     
	if (!(keyCode == 34 || keyCode == 39)) {
		
	}
    else {
        return false;
    }
});
