<script> 
class FormsView {
	init() {
        $(document).on('click', '.eParticipantTab', function(event) {
            event.preventDefault();
            Controller.eParticipantTab($(this).attr('index'));
        });
        $(document).on('click', '#eAddTab', function(event) {
            event.preventDefault();
            Controller.eParticipantTabAdd();
        });
        $(document).on('click', '#eRemoveTab', function(event) {
            event.preventDefault();
            Controller.eParticipantTabRemove();
        });
        $(document).on('change', '.select-option', function(event) {
            event.preventDefault();
            Controller.eOptionChange(event);
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

        $(document).on('click', '#eMessageBoxClose', function(event) {
            event.preventDefault();
            Current.inProgress = false;
            $('#message-box').removeClass( 'is-active');
        });

        $(document).on('click', '#eGetFromSpar', function(event) {
            event.preventDefault();
            Controller.eGetFromSpar($('#part-personal-id').val());    
        });
        $(document).on('click', '#eConfirm', function(event) {
            event.preventDefault();
            if (Current.inProgress) {
                return;
            }
            else {
                Current.inProgress = true;
                Controller.eConfirm();
            }
        });
		
		 $(document).on('click', '#eUcBoxContinue', function(event) {
            event.preventDefault();
            Controller.eUcBoxContinue();
        });
		
		 $(document).on('change', '#people_company_on', function(event) {
            event.preventDefault();
            //Controller.eOptionChange(event);
            if($(this).is(":checked")) {
                $('.people_company-panel').show();
               $('.people_company_address-panel').show();
               $('.people_company-panel-postaddress').show();
            }
            else {
               $('.people_company-panel').hide();
               $('.people_company_address-panel').hide();
               $('.people_company-panel-postaddress').hide();
            }
        });
		$('.people_company-panel').hide();
        $('.people_company_address-panel').hide();
        $('.people_company-panel-postaddress').hide();
        /*
        $(document).on('click', '#eUcBoxContinue', function(event) {
            event.preventDefault();
            Controller.eUcBoxContinue();
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

                   
                }
            });
        });
        */
        $(document).on('click', '#eUcBoxCancel', function(event) {
            event.preventDefault();
            $('#uc-box').removeClass( 'is-active');
        });


		 $(document).on('click', '#eMobileLogin', function(event) {
            event.preventDefault();
            window.location.href = SITE_URL + '?p=' + Current.waId;
   
        });

	}

	load() {

        if (Current.Webform.participant_on == 'y') {
            if (Current.inherit == '0') {
                // New event
                $('#total_amount').prop("disabled", true);
            }
            else {
                // Inherit

                $('#first-name').val(Current.Participant[0].first_name);
                $('#first-name').prop( "disabled", true);
                $('#last-name').val(Current.Participant[0].last_name);
                $('#last-name').prop( "disabled", true);
                $('#total_amount').prop("disabled", true);
            }
            
            $('#total_amount').val(Current.total); 
        }
        // let ccsStyle = ".webform-text-color {color: " + Current.Webform.text_color + ";}";
        // $("<style>").prop("type", "text/css").html(ccsStyle).appendTo("head");
	}
	
    eParticipantTab(index) {
        $('.eParticipantTab[index="' + Current.ParticipantCurrentIndex + '"]').removeClass('is-active');
        $('.eParticipantTab[index="' + index + '"]').addClass('is-active');
      
        // $(this).addClass('is-active'); // FIXAS
        // $('.myclass[reference="12345"]')
        $('#first-name').val(Current.Participant[index].first_name);  
        $('#last-name').val(Current.Participant[index].last_name); 
        if (Current.Webform.participant_address_on == 'y') {
            $('#part-address').val(Current.Participant[index].address);
            $('#part-postcode').val(Current.Participant[index].postcode); 
            $('#part-city').val(Current.Participant[index].city);
            $('#part-mobile').val(Current.Participant[index].mobile);  
            $('#part-email').val(Current.Participant[index].email);
        }
        if (Current.Webform.note_on == 'y') {
            $('#note').val(Current.Participant[index].note);
        }

        if (Current.Webform.date_of_birth_on == 'y') {
            $('#date_of_birth').val(Current.Participant[index].date_of_birth);
        }

        if (Current.Webform.collect_spar_on == 'y') {
            $('#part-personal-id').val(Current.Participant[index].personal_id_number); 
            if (Current.Webform.participant_address_on == 'n') {
                $('#part-address').val(Current.Participant[index].address);
                $('#part-postcode').val(Current.Participant[index].postcode); 
                $('#part-city').val(Current.Participant[index].city);
            }
        }
        for (var i=0; i < Current.OptionCounts; i++) {
            View.setSelectedByText('option-' + i, Current.Participant[index].option[i].text);
        }

        Current.ParticipantCurrentIndex = index;
    }

    eParticipantTabAdd() {
      
        $('.eParticipantTab[index="' + Current.ParticipantCurrentIndex + '"]').removeClass('is-active');

        Current.ParticipantCurrentIndex = Current.Participant.length;
        $('#eAddTab').before('<li class="is-active eParticipantTab" index="' + Current.ParticipantCurrentIndex + '" style="font-size:13px"><a>' +Current.Webform.participant_title + '</a></li>');
        Current.Participant[Current.ParticipantCurrentIndex] = {};
        Current.Participant[Current.ParticipantCurrentIndex].status = "a";
        Current.Participant[Current.ParticipantCurrentIndex].option = new Array();
        for (var i=0; i < Current.OptionCounts; i++) {
            Current.Participant[Current.ParticipantCurrentIndex].option[i] = {};
            $('#option-' + i).val('8E1C7E8F67D0');
        }
        $('#first-name').val('');  
        $('#last-name').val(''); 
        if (Current.Webform.participant_address_on == 'y') {
            $('#part-address').val('');  
            $('#part-postcode').val(''); 
            $('#part-city').val('');  
            $('#part-mobile').val(''); 
            $('#part-email').val(''); 
        }
        if (Current.Webform.note_on == 'y') {
            $('#note').val('');  
        }
        if (Current.Webform.date_of_birth_on == 'y') {
            $('#date_of_birth').val('');  
        }
        if (Current.Webform.collect_spar_on == 'y') {
            $('#part-personal-id').val(''); 
            if (Current.Webform.participant_address_on == 'n') {
                $('#part-address').val('');  
                $('#part-postcode').val(''); 
                $('#part-city').val('');  
            }
        }
    }

    eParticipantTabRemove() {
        var active = 0;
        for (var i = 0; i < Current.Participant.length; i++) {
            if (Current.Participant[i].status == 'a') {
                active++;
            }
        }
        if (active == 1) {
            View.message('Kan inte ta bort alla ' +  Current.participant_title);
            return false;
        }
        Current.Participant[Current.ParticipantCurrentIndex].status = "x";
        var element = ".eParticipantTab[index='" + Current.ParticipantCurrentIndex + "']";
        $(element).hide();
        var firstActive = -1;
        for (var i = 0; i < Current.Participant.length; i++) {
            if (Current.Participant[i].status == 'a' && firstActive == -1) {
                firstActive = i;
            }
        }
        Current.ParticipantCurrentIndex = firstActive;
        element = ".eParticipantTab[index='" + Current.ParticipantCurrentIndex + "']";    
        $(element).addClass('is-active');
        $('#first-name').val(Current.Participant[Current.ParticipantCurrentIndex].first_name);  
        $('#last-name').val(Current.Participant[Current.ParticipantCurrentIndex].last_name); 
        for (var i=0; i < Current.OptionCounts; i++) {
            View.setSelectedByText('option-' + i, Current.Participant[Current.ParticipantCurrentIndex].option[i].text);
        }
        return true;
    }

    participantSave(index) {

        Current.Participant[index].first_name = $('#first-name').val();  
        Current.Participant[index].last_name = $('#last-name').val(); 
        if (Current.Webform.participant_address_on == 'y') {
            Current.Participant[index].address = $('#part-address').val();  
            Current.Participant[index].postcode = $('#part-postcode').val(); 
            Current.Participant[index].city = $('#part-city').val();  
            Current.Participant[index].mobile = $('#part-mobile').val(); 
            Current.Participant[index].email = $('#part-email').val(); 
        }
        if (Current.Webform.note_on == 'y') {
            Current.Participant[index].note = $('#note').val(); 
        }
        if (Current.Webform.date_of_birth_on == 'y') {
            Current.Participant[index].date_of_birth = $('#date_of_birth').val(); 
        }
        if (Current.Webform.collect_spar_on == 'y') {
            Current.Participant[index].personal_id_number = $('#part-personal-id').val(); 
            if (Current.Webform.participant_address_on == 'n') {
                Current.Participant[index].address = $('#part-address').val();  
                Current.Participant[index].postcode = $('#part-postcode').val(); 
                Current.Participant[index].city = $('#part-city').val();  
            }
        }
		
		if (Current.Webform.tdb_on == 'y') {
            // do nontikn
        }
        else {
			for (var i=0; i < Current.OptionCounts; i++) {
				var value = $('#option-' + i).val();
				if(Current.Webform.selection[i].calculate_on == 'y') {
					Current.Participant[index].option[i].value = value;
				}
				else {
					Current.Participant[index].option[i].value
				}
				var text = $('#option-' + i + ' option:selected').text(); 
				Current.Participant[index].option[i].text = text;
				Current.Participant[index].option[i].event_option_setting_id = View.getOptionId(i, text);
			}
		}	
    } 

    total() {
        $('#total_amount').val(Current.total); 
    }

    setSelectedByText(eID, text) {
        var ele = document.getElementById(eID);
        for (let i=0; i<ele.options.length; i++) {
            if ( ele.options[i].text == text) {
                ele.options[i].selected = true;
                return true;
            }
        }
    }

    sparShowPeople(data) {
        $('#first-name').val(data.people.first_name);  
        $('#last-name').val(data.people.last_name); 
        $('#part-address').val(data.people.address);  
        $('#part-postcode').val(data.people.postcode); 
        $('#part-city').val(data.people.city); 
    }

    getOptionId(selectionIndex, text) {
        var optionId = 0;
        for (let i=0; i<Current.Webform.selection[selectionIndex].option.length; i++) {
            if (Current.Webform.selection[selectionIndex].option[i].text == text) {
                optionId = Current.Webform.selection[selectionIndex].option[i].event_option_setting_id;
            }
        }
        return optionId;
    }

    isValidSwedishSSN (ssnInput) {
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

    validateEmail (mail) {
        if (/^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/.test(mail)) {
            return true;
        }
        else {
            return false;
        }
    }

    message(text) {
        $('#message-box-text').html(text);
        $('#message-box').addClass('is-active');
    }


}
</script>  