<script> 

class FormsController  {
	
	init() {
        Current.eventId = EVENT_ID;
        Current.inherit =  INHERIT;
        Current.Participant = [];
        Current.ParticipantCurrentIndex = 0;
        Current.TotalAmount = 0;
        Current.Form = {};
        Current.optionMaxOn = 'n';
		Current.waId;
        Current.inProgress = false;
        View.init(); 
    }

	load() {
        let param = {};
        param._action = "LoadEvent";
        param._event_id = Current.eventId;
        Model.service(param)
		.then(response => response.json())
		.then(function(data) {   
            Current.Webform = data;
            Current.Webform.company_address_on = data.company_address_on;
            if (Current.Webform.event_create_type == 'i') {
                Current.maxOn = 'n';
            }
            else {
                Current.maxOn = Current.Webform.participant_limit_on;
            }
          
            if (Current.Webform.participant_on == 'y') {
                Current.OptionCounts = Current.Webform.selection.length;
                if (Current.inherit == '0') {
                    Current.Participant[0] = {};
                    Current.Participant[0].status = "a";
                    Current.Participant[0].option = new Array();
                    for (let i=0; i <  Current.OptionCounts; i++) {
                        Current.Participant[0].option[i] = {};
                    }
                   Current.total = '0.00';
				    View.load();
                }
                else {
                    let param = {};
                    param._action = "LoadInheritParticipant";
                    param._parent_event_item_id = Current.inherit;
                    param._event_id = Current.eventId;
                    Model.service(param)
                    .then(response => response.json())
                    .then(function(data) {   
                        for (var i=0; i<data.length; i++) {
                            Current.Participant[i] = {};
                            Current.Participant[i].first_name = data[i].first_name;
                            Current.Participant[i].last_name =  data[i].last_name;
                            Current.Participant[i].base_participant_id = data[i].event_participant_id;    
                            Current.Participant[i].base_participant_id = data[i].base_participant_id;
                            Current.Participant[i].status = "a";
                            Current.Participant[i].option = new Array();
						   for (var j=0; j < Current.OptionCounts; j++) {
								Current.Participant[i].option[j] = {};
								Current.Participant[i].option[j].text = '--- Välj ---';
								Current.Participant[i].option[j].event_option_setting_id = 0;
                            }
                            for (var j=0; j < data[i].parents.length; j++) {
                                Current.Participant[i].option[j] = {}; 
                                Current.Participant[i].option[j].value = data[i].parents[j].value;
                                Current.Participant[i].option[j].text = data[i].parents[j].text;
                                Current.Participant[i].option[j].event_option_setting_id = data[i].parents[j].event_option_setting_id;
                                //if (i==0 && data[i].parents[j].value != '8E1C7E8F67D0') { 
                                // Changed 2021-07-30
                                if (Current.Webform.event_create_type == 'i' && Current.Webform.tdb_on == 'y') {
                                   
                                    if (data[i].parents[j].value != '8E1C7E8F67DD') {
                                        View.setSelectedByText('option-' + j, Current.Participant[0].option[j].text);
                                        $('#option-' + j).prop( "disabled", true);
                                        if (Current.Participant[0].option[j].text == 'Rabatt') {
                                            //alert('Rabatt');
                                            //$('#option-' + j).text('Test');
                                        }
                                    }
                                }
                                else if (i==0 && data[i].parents[j].value != '8E1C7E8F67D0' ) { 
                                    View.setSelectedByText('option-' + j, Current.Participant[0].option[j].text);
                                    $('#option-' + j).prop( "disabled", true);
                                }
                               
                            }
                            if (Current.Webform.event_create_type == 'i' && Current.Webform.tdb_on == 'y') {  
                                $('#note').val(data[0].note);
                                $('#note').prop( "disabled", true);
                            }
                        }
						View.load();
						Model.calculateTotal();
                        View.total();
                    })
                }
               

                // Create option index
                Current.optionCheck = [];
                for (let i=0; i<Current.Webform.selection.length; i++) {
                    for (let j=0; j<Current.Webform.selection[i].option.length; j++) {
                        if (Current.Webform.selection[i].option[j].max_on == 'y') {
                            Current.optionMaxOn = 'y';
                            let record = {};
                            record.selection_text = Current.Webform.selection[i].text;
                            record.option_text = Current.Webform.selection[i].option[j].text;
                            record.event_option_setting_id = Current.Webform.selection[i].option[j].event_option_setting_id
                            record.base_event_option_setting_id = Current.Webform.selection[i].option[j].base_event_option_setting_id;
                            record.current_number = 0;
                            Current.optionCheck.push(record);
                        }
                    }
                }
            }
        })
	}

    eParticipantTab(event) {
        View.participantSave(Current.ParticipantCurrentIndex);
        View.eParticipantTab(event);
    }

    eParticipantTabAdd() {
        // Check max in application
        if (Current.Webform.participant_apply_limit_on == 'y' && Current.Participant.length >= Current.Webform.participant_apply_max) {
            View.message('Max antal deltagare på denna anmälan är  ' + Current.Webform.participant_apply_max);
            return;
        }
        View.participantSave(Current.ParticipantCurrentIndex);
        View.eParticipantTabAdd(event);
    }

    eParticipantTabRemove() {
        View.eParticipantTabRemove();
        View.participantSave(Current.ParticipantCurrentIndex);
        Model.calculateTotal();
        View.total();
    }

    eOptionChange(index) {
        View.participantSave(Current.ParticipantCurrentIndex);
        Model.calculateTotal();
        View.total();
    }

    eGetFromSpar(peopleIdNumber) { 
        var param = {};
        param._action = "Spar";
        param._personal_id_number = peopleIdNumber
        Model.service(param)
        .then(response => response.json())
        .then(function(data) {   
            if (data.status == '1') {
                View.sparShowPeople(data); 
            }  
            else {
                View.message('Kontrollera personnummer!');
                return;
            }
        })
    }     

    eUcBoxContinue() {
        $('#uc-box').removeClass( 'is-active');
    
        // -- Ny del
        var param = {};
        param._action = "UcInit";
        // param._action = "Request";
        param.personal_id_number = Current.Form.personal_id_number;
        param.amount = Current.Form.amount;
        param.receipt_number = Current.Form.receipt_number;
        param.email = Current.Form.email;
        
        if (Current.Webform.mobile_on == 'y') {
            param.mobile = $('#mobile').val(); 
        }
    
        param.id = COMPANY_ID;
        param._invoice_event_id = INVOICE_EVENT_ID; 
        param._invoice_event_item_id = INVOICE_EVENT_ITEM_ID; 
    
        param.event_id = EVENT_ID;
        param.participant_on = Current.Webform.participant_on;
        if ( Current.Webform.participant_on == 'y') {
            param.participant = Current.Participant;
        }
        param.infobox_1_on =  Current.Webform.other_info_on;
        if ( Current.Webform.infobox_1_on == 'y') {
            param.infobox_1 = $('#infobox_1').val();
        }
        if ( Current.Webform.infobox_2_on == 'y') {
            param.infobox_2 = $('#infobox_2').val();
        
        }
        param.people_company_on = 'n';
        if (Current.Webform.tdb_on == 'y' || Current.Webform.company_address_on == 'y') {
            // Check if company address is on
            var element = document.getElementById("people_company_on");
            if (element.checked) {
                param.people_company_on = 'y';
                param.people_company = $('#people_company').val();
                param.people_company_address = $('#people_company_address').val();
                param.people_company_postcode = $('#people_company_postcode').val();
                param.people_company_city  = $('#people_company_city').val();
            } 
            else {
                param.people_company_on = 'n';
            }
        }
        param._people_id = Current.Form._people_id;

        param._visitor = Current.visitor;
        // -- Del 

        // console.log();
        // param.personal_id_number = '197811107338';
        // console.log(param);
        Model.service(param)
        .then(response => response.json())
        .then(function(data) {      
            //console.log(data);
            Controller.goProgress(data); // Changed
        })
        
    }

    checkOption() {

        for (let i=0; i<Current.optionCheck.length; i++) {
            Current.optionCheck[i].current_number = 0;
            for (let j=0; j<Current.Participant.length; j++) {
                for (let k=0; k<Current.Participant[j].option.length; k++) {
                    if (Current.optionCheck[i].event_option_setting_id == Current.Participant[j].option[k].event_option_setting_id) {
                        Current.optionCheck[i].current_number++;
                    }
                }
            }
        }
        let param = {};

        console.log(Current.optionCheck);
    }

    eConfirm() {
       
        if (Current.Webform.participant_on == 'y') {
            View.participantSave(Current.ParticipantCurrentIndex);
            Model.calculateTotal();
            View.total();
        }

        if (Controller.checkForm() == false) {
            return false;
        }
       
        let param = {};
        param._action = "OverdueCheck";
        param._personal_id_number = Current.Form.personal_id_number;
        Model.service(param)
		.then(response => response.json())
		.then(function(data) {           
            if (data.code == '1') {
                if (data.people_status == 'b' || data.overdue > 0) {
                    if (INVOICE_EVENT_ITEM_ID == '0') {
                        window.location.href = SITE_URL + '?m=denied';
                    }
                    else {
                        window.location.href = SITE_URL + '?m=denied&id=' + INVOICE_EVENT_ITEM_ID;
                    }
                    return;
                }
                else {
                    Controller.maxCheck();
                    //Controller.request();
                }
            }
            else {
                Controller.maxCheck(); 
                //Controller.request();
            }
        })
        // {"code":"7","denied_code":"alreadyInProgress"}
        // .catch(error => alert(error));
        .catch(error => View.message('Ett fel har inträffat, kontakta Turtle Pay AB, för mer information!'))         
    }

    checkForm() {
        Current.Form.personal_id_number = $('#personal_id_number').val();
        if (Current.Webform['participant_on'] == 'y') {
            Current.Form.amount = $('#total_amount').val();
            if (Current.Form.amount < 0 ) {
                View.message('Avisad - negativt belopp!');
                return false;
            }
        }
        else {
            Current.Form.amount = $('#amount').val();
        }
		/*
        if( $('#date_of_birth').length )  {
            var dateOfBirth = $('#date_of_birth').val();
            if (dateOfBirth.length < 6) {
                View.message('Födelsdatum måste vara 6 siffror!');
                return false;
            }
        }
		*/
        Current.Form.receipt_number = $('#receipt_number').val();
        Current.Form.email = $('#email').val();
        if (View.isValidSwedishSSN(Current.Form.personal_id_number) == false) {
            View.message('Personnummer är inte giltigt!');
            return false;
        }
        if (isNaN(Current.Form.personal_id_number)) {
            View.message('Personnummer är inte giltigt!');
            return false;
        }
        if (Current.Form.email.length < 5) {
            View.message('E-postaddress är inte giltigt');
            return false;
        }
        if (View.validateEmail(Current.Form.email) == false) {
            View.message('E-postaddress är inte giltigt');
            return false;
        }
        if (Current.Form.receipt_number.length < 1) {
            View.message('Ange referens');
            return false;
        }
        if (Current.Webform.amount_on == 'y') {
            if (isNaN(Current.Form.amount)) {
                View.message('Felaktigt belopp');
                return false;
            }
        }
        if (Current.Webform.participant_on == 'y') {
            var formComplete = true;
            for (var i = 0; i < Current.Participant.length; i++) {
                if (Current.Participant[i].status == 'a') { 
                    if (Current.Participant[i].first_name.length < 1) {
                        formComplete = false;
                    }
                    if (Current.Participant[i].last_name.length < 1) {
                        formComplete = false;
                    }
                    for (let j = 0; j < Current.Participant[i].option.length; j++) {
                        if (Current.Participant[i].option[j].value == '8E1C7E8F67D0' && Current.Webform.selection[j].required_on == 'y') {
                            formComplete = false;
                        }
                    }
                }
            } 
            if (formComplete == false) {
                View.message(Current.Webform.participant_title + ' information är inte komplett');
                return false;
            }
        }
        return true;             
    }

    maxCheck() {
        if (Current.maxOn == 'y' || Current.optionMaxOn == 'y') {
            let param = {};
            //param._group = 'WebAppV4';
            param._action = "MaxCheck";
            param._event_id = Current.eventId;
            if (Current.optionMaxOn == 'y') {
                // Check selction and counter in this form
                for (let i=0; i<Current.optionCheck.length; i++) {
                    Current.optionCheck[i].current_number = 0;
                    for (let j=0; j<Current.Participant.length; j++) {
                        if (Current.Participant[j].status == 'a') {
                            for (let k=0; k<Current.Participant[j].option.length; k++) {
                                if (Current.optionCheck[i].event_option_setting_id == Current.Participant[j].option[k].event_option_setting_id) {
                                    Current.optionCheck[i].current_number++;
                                }
                            }
                        }
                    }
                }
                param._option = Current.optionCheck;
                param._option_on = 'y';
            }
            else {
                param._option_on = 'n';
            }
            if (Current.maxOn == 'y') {
                param._max_on = 'y';
            }
            else {
                param._max_on = 'n';
            }
            Model.service(param)
            .then(response => response.json())
            .then(function(data) {         
                if (data.code == '1') {
                    var counter = 0;
                    for (let i=0; i<Current.Participant.length; i++) {
                        if (Current.Participant[i].status == 'a') {
                            counter++;
                        }
                    }
                    if (counter > data.place_left) {
                        let text = '';
                        if (data.place_left == 1) {
                            text = 'Aktiviteten har ' + data.place_left + ' plats kvar!';
                        }
                        else {
                            text = 'Aktiviteten har ' + data.place_left + ' platser kvar!';
                        }
                        View.message(text);
                        return;
                    }
                    if (Current.optionMaxOn == 'y') {
                        let optionOK = true;
                        let mesOption = '<div style="margin-top: -12px; margin-bottom: 22px">Det finns inte tillräckligt många platser kvar.</div>';
                        mesOption += '<table style="width:94%">';
                        for (let i=0; i<data.option.length; i++) {
                            if (data.option[i].current_number > 0) {
                                if (data.option[i].code == '0') {
                                    optionOK = false;
                                    mesOption += '<tr>';
                                    mesOption += '<td>' + data.option[i].selection_text + ' : ' + data.option[i].option_text + '</td>'; 
                                    if (data.option[i].place_left == '1') {
                                        mesOption += '<td>' + data.option[i].place_left + ' plats kvar' + '</td>';
                                    }
                                    else {
                                        mesOption += '<td>' + data.option[i].place_left + ' platser kvar' + '</td>';
                                    }
                                    mesOption += '</tr>';
                                }
                            }
                        }
                        mesOption += '</table>';
                        if (optionOK == false) {
                            View.message(mesOption);
                            return;
                        }    
                    } 
                   
                    Controller.request(); 
                }
                else {
					View.message('Eventet är fullt');
                    //location.reload();
                    return;
                }
            });
        }
        else {
            //console.log('No check');
            Controller.request(); 
        }
    }

    request() {
        let param = {};
        param._action = "Request";
        param.personal_id_number = Current.Form.personal_id_number;
        param.amount = Current.Form.amount;
        param.receipt_number = Current.Form.receipt_number;
        param.email = Current.Form.email;
        if (Current.Webform.mobile_on == 'y') {
            param.mobile = $('#mobile').val(); 
        }
        param.id = COMPANY_ID;
        param._invoice_event_id = INVOICE_EVENT_ID; 
        param._invoice_event_item_id = INVOICE_EVENT_ITEM_ID; 
        param.event_id = EVENT_ID;
        param.participant_on = Current.Webform.participant_on;
        if (Current.Webform.participant_on == 'y') {
            if (INHERIT == '0') {
                for (var i=0; i<Current.Participant.length; i++) {
                    Current.Participant[i].base_participant_id = '0';
                }
            }
            param.participant = Current.Participant;
        }
        if (Current.Webform.infobox_1_on == 'y') {
            param.infobox_1 = $('#infobox_1').val();
        }
        if (Current.Webform.infobox_2_on == 'y') {
            param.infobox_2 = $('#infobox_2').val();
        }
        param.people_company_on = 'n';
    
        if (Current.Webform.company_address_on == 'y') {
            // Check if company address is on
            var element = document.getElementById("people_company_on");
            if (element.checked) {
                param.people_company_on = 'y';
                param.people_company = $('#people_company').val();
                param.people_company_address = $('#people_company_address').val();
                param.people_company_postcode = $('#people_company_postcode').val();
                param.people_company_city  = $('#people_company_city').val();
            } 
            else {
                param.people_company_on = 'n';
            }
        }
        param._visitor = Current.visitor;
        
        Model.service(param)
		.then(response => response.json())
		.then(function(data) {   
            if (data.code == '1') {   
                Controller.goProgress(data);  
            }
            else if (data.code == '6') {
                KycController.load(data.people_id, Current.Form.personal_id_number, true, 'y'); 
                $('#kyc-box').addClass('is-active');
                return;
            }
            else if (data.code == '8') {
                Current.Form._people_id = data.people_id;
                $('#uc-box').addClass('is-active');
            }
            else if (data.code == '7') {
                View.message('BankID är upptagen, försök igen om en stund!');
                return;
            }
			 else if (data.code == '0' && data.denied_code == 'age_under_18') {
                View.message('Fakturamottagare får ej vara minderårig!');
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
                View.message('Ett BankID fel har inträttats, försök igen om en stund!');
                return;
            }
        });

    }

    goProgress(data) {
      
        //var Browser = Current.visitor.browser;
        var WaId = 0;
        var internalBankID = false;
        var element = document.getElementById("BankIDCheckBox");
        if (element.checked) {
            internalBankID = true;
        } 
        else {
            internalBankID = false;
        }
     
        if (IS_MOBILE == 'yes') {   
            if (internalBankID == true) {                
                var url = "";
                if (Browser == "Safari") { 
                   if (Current.visitor.dg == 'y') {
						var redirect =  SITE_URL + '?p=' + data.waid;
						url = "bankid:///?autostarttoken=" + data.auto + "&redirect=" + redirect;
					}
					else if (Current.visitor.cookie_on == 'y') {
						var redirect = window.location.href;
						url = "bankid:///?autostarttoken=" + data.auto + "&redirect=" + redirect;
					}
					else {
						var redirect =  SITE_URL + '?p=' + data.waid;
						url = "bankid:///?autostarttoken=" + data.auto + "&redirect=" + redirect;
					}
                }
                else if (Browser == "Chrome") {
                    var redirect =  SITE_URL + '?p=' + data.waid;
                    url = "bankid:///?autostarttoken=" + data.auto + "&redirect=googlechrome:///";
                }
                else if (Browser == "Firefox") {
                    url = "bankid:///?autostarttoken=" + data.auto + "&redirect=firefox:///";
                }
                else {
                    url = "bankid:///?autostarttoken=" + data.auto;
                }
				
                WaId = data.waid;
                Current.waId = data.waid;
				
				if (Browser == 'Safari' && Current.visitor.cookie_on == 'y') {
					var date = new Date();
					date.setTime(date.getTime()+(3*60*1000));
        			var expires = "; expires="+date.toGMTString();	
        			document.cookie = "tpsafari=" + data.waid + expires + ';sameSite=lax;path=/';
				}
				//alert(url);
				
                $('#login-mobile-modal-text').html("Väntar på BankID signering");
                $('#eMobileLogin').show();
                $('#login-mobile-modal').addClass('is-active');
                if (document.getElementById("BankIDCheckBox").checked == true) {
                    window.location.href = url;
                }
                return;
            } 
            else {
                // Mobile and not BankID on Mobile
               	WaId = data.waid;
				Current.waId = data.waid;
				$('#login-mobile-modal-text').html("Väntar på BankID signering");
				$('#eMobileLogin').show();
				$('#login-mobile-modal').addClass('is-active');  
                return;
            }
        }
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
            Current.waId = data.waid;
            $('#login-mobile-modal-text').html("Väntar på BankID signering");
            $('#eMobileLogin').show();
            $('#login-mobile-modal').addClass('is-active');
            window.location.href = url;
            return;
            //$('#login-mobile-modal-text').html("BankID signering klar");
            //$('#eMobileLogin').show();
            //$('#login-mobile-modal').addClass('is-active');
            
            if (document.getElementById("BankIDCheckBox").checked == true) {
                window.location.href = url;
            }
            return;
        }
     
        window.location.href = SITE_URL + '?p=' + data.waid;
        return;
    }
}
</script>