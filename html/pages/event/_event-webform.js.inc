<?php
/* 
	2021-07-01
    THis file id organize in 2 parts, Webform and Preview

    This is activtae from the Event list and the: webform.loadWebFormSetting 
*/
?>
<script>

// --
// --	WEBFORM 
// -- 

Current.eventId = '0' // '101'; // ??

var Webform = {}; // Used for data
var webform = {}; // Container for functions
var WebFormPreviewOn = false;

CurrentOption = {};
CurrentSelectionId = 0;
CurrentSelectionIndex = 0;
CurrentOptionIndex = 0;
var OptionBox = {};

// -- Preview
var Participant = new Array();
var OptionCounts;
var ParticipantCurrentIndex = 0;
var TotalAmount = 0;


// --
// -- Start
// --
webform.loadWebFormSetting =  function()  {
	
	/*
		

	*/
	$('.section-webform-item').show();
	// $('.tool-panel').show();
	// $('.section-webform-item').hide(); // Until loaded

	// -- Load the Webform (Event)
	var param = {};
	param._group = "Event";
	param._action = "EventCollection";
	param._token = Token;
	param._user_id = UserId;
	param._event_id = Current.eventId;
	
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			
			Webform = jQuery.parseJSON(result);
			delete Webform.code; 
			Webform['_event_id'] = Webform.event_id;
			Current.eventCreateType = Webform.event_create_type; // NY 20210808
			delete Webform.event_id; 
			
			if (Webform.tdb_on == 'y') {
				$('.tdb-hide').hide();
				//$('.eToolSelectionRemove').hide();
			}

			// -- Create the panel
			loadWebformPanel();
			
			// -- Create the editor part
			loadWebformEditor();

			// -- Create Webform footer
			loadWebformFooter();

			// Load the image
			loadWebformImage();

			setStatusAfterLoad();

			// $('#header_title').val(Webform.header_title);
			if (Webform.tdb_on == 'y') {
				$('.tdb-hide').hide();
				$('.eToolSelectionRemove').hide();
			}
		}
	});
}

function loadWebformPanel() {
	 
	// -- Inställningar
			
	$('#event_name').val(Webform.event_name); 

	$('#private_on').val(Webform.private_on);
	if (Webform.inherit_event_id == '0') {
		$('#private_on').prop('disabled', false);
	}
	else {
		$('#private_on').prop('disabled', true);
	}
			
	$('#event-url').val(Site + Webform.wa_url + '/?e=' + Webform.event_url);	
	if (Webform.private_on == 'n') {
		$('.event_url-panel').hide();
	}
	else {
		$('.event_url-panel').show();
	}

	$('#webform_on').val(Webform.webform_on);
	
	if (Webform._has_bo == 'y') {
		$('#has_vat').val(Webform.has_vat);
	}
	else {
		$('.has_vat-panel').hide();
	}
	 
	$('#amount_on').val(Webform.amount_on);
	if (Webform.amount_on == 'n') {
		$('.amount-standard-panel').hide();
	}

	$('#mobile_on').val(Webform.mobile_on);
	if (Webform.mobile_on == 'n') {
		$('.mobile-panel').hide();
	}
	
	$('#infobox_1_on').val(Webform.infobox_1_on);
	if (Webform.infobox_1_on == 'n') {
		$('.infobox_1-panel').hide();
	}

	$('#infobox_2_on').val(Webform.infobox_2_on);
	if (Webform.infobox_2_on == 'n') {
		$('.infobox_2-panel').hide();
	}

	$('#company_address_on').val(Webform.company_address_on);
	
	// -- Participant

	$('#participant_on').val(Webform.participant_on);
	$('#participant_title').val(Webform.participant_title);

	Helper.onYesNoShowHide(Webform.participant_on, '.participant-panel');


	$('.participant-tab a').html(Webform.participant_title);

		
	if (Webform.event_create_type == 'i') {
		$('.participant_max-panel').hide();
		$('#participant_title').prop('disabled', true);	// new
		$('.participant_apply-max-panel').hide();
		Webform.participant_apply_limit_on = 'n';
	}
	else if (Webform.event_create_type == 'g') {
		$('#participant_title').prop('disabled', true);	// new
		if (Webform._base_participant_limit_on == 'n') {
			$('.participant_max-panel').hide();
		}
		else {
			$('#participant_limit_on').val('y');
			$('#participant_limit_on').prop('disabled', true);
			$('#participant_max').val(Webform._base_participant_max);
			$('#participant_max').prop('disabled', true);
		}
	}
	else {
		
		$('#participant_limit_on').val(Webform.participant_limit_on);
		$('#participant_max').val(Webform.participant_max);
		// 2022-05-29
		$('#participant_limit_show').val(Webform.participant_limit_show);
		$('#participant_max').addClass('only-numeric');
		if (Webform.participant_limit_on == 'n') {
			$('.participant_max-panel-value').hide();
		}
	}

	if (Webform.participant_apply_limit_on == 'n') {
		$('.participant-apply_max-panel-value').hide();
	}
	
	$('#participant_apply_limit_on').val(Webform.participant_apply_limit_on);
	$('#participant_apply_max').val(Webform.participant_apply_max);
	$('#participant_apply_max').addClass('only-numeric');
	if (Webform.participant_apply_max == '1') {
		$('#eAddTab').hide();
		$('#eRemoveTab').hide();
	}
	
	$('#participant_address_on').val(Webform.participant_address_on);
	$('#collect_spar_on').val(Webform.collect_spar_on);
	$('#date_of_birth_on').val(Webform.date_of_birth_on);
	$('#note_on').val(Webform.note_on);

	// -- Design

	if (Webform._has_bo == 'y') {
		let html = '';
		for (let i=0; i<Webform._accounts.length; i++) {
			html += '<option value="' + Webform._accounts[i].company_account_id  + '">' + Webform._accounts[i].account_name + ' ' + Webform._accounts[i].account_no + '</option>';
		}
		$('#ddAccountList').html(html);
		$('#ddAccountStandardList').html(html)
		if (Webform.participant_on == 'y') {
			
			$('#ddAccountList').val(Webform.company_account_id);
			$('.accounting-standard-panel').hide();
			$('.accounting-panel').show();
		}
		else {
			$('#ddAccountStandardList').val(Webform.company_account_id);
			$('.accounting-panel').hide();
			$('.accounting-standard-panel').show();
		}
	}
	else {
		$('.accounting-panel').hide();
		$('.accounting-standard-panel').hide();
	}
	$('#header_image_on').val(Webform.header_image_on);

	// $('#header_tcolor').spectrum("set", Webform.header_tcolor);
	if (Webform.header_image_on == 'y') {
		$('.header_title-panel').hide();
		$('.logo-list-panel').show();
	}
	else {
		$('.logo-list-panel').hide();
		$('.header_title-panel').show();
	}

	// update 2021-09-10
	$('#has_attach').val(Webform.has_attach);
	if (Webform.has_attach == 'y') {
		$('.header_title-panel').hide();
		$('.attach-list-panel').show();
		if (Webform._attach_list.length > 0) {   
			for (var i=0; i < Webform._attach_list.length; i++) {                        
				$('#attach-list').append('<option value="' +  Webform._attach_list[i].event_attach_id + '">' + Webform._attach_list[i].realname + '</option>');
			}
		}
	}
	else {
		$('.attach-list-panel').hide();
	}
	
	/*
	if (Webform.event_create_type == 'g') {
		$('#participant_apply_max').prop('disabled', true);
	}
	*/
	return;
}

function loadWebformEditor() {

	// -- Colors
	$('#webform').css("background-color", Webform.background_color);
	$('.webform-text-color').css("color", Webform.text_color);
	$('.webform-input-color').css("background-color", Webform.input_bcolor);
	$('.webform-input-color').css("color", Webform.input_color);
	
	// -- Header
	if (Webform.header_image_on == 'y') {
		$('#header-image-src').attr('src',  Site + '/logo/' + Webform.header_image);
		$('#header-text-panel').hide(); 
		$('#header-image-panel').show(); 
	}
	else {	
		$('#header-text-title').html(Webform.header_title);
		$('#header-text-title').css("background-color", Webform.header_bcolor).css("color", Webform.header_tcolor);
		$('#header-image-panel').hide(); 
		$('#header-text-panel').show(); 
	}

	// --  Intro title
	$('#intro_title').val(Webform.intro_title);
	$('#intro_text_edit').html(Webform.intro_text.split("\n").join("<br />"));
		
	// -- Fält
	$('#personal_id_number-label').val(Webform.personal_id_number_label);
	
	$('#email-label').val(Webform.email_label);

	$('#mobile-label').val(Webform.mobile_label);
	Helper.onYesNoShowHide(Webform.mobile_on, '.mobile-panel');

	$('#ref-label').val(Webform.ref_label);
	$('#ref').val(Webform.ref);

	$('#amount-label').val(Webform.amount_label);
	$('#amount').addClass('only-numeric');
	$('#amount').val(Webform.amount);
	Helper.onYesNoShowHide(Webform.amount_on, '.standard-amount-panel');
	
	$('#infobox_1-label').val(Webform.infobox_1_label);
	Helper.onYesNoShowHide(Webform.infobox_1_on, '.infobox_1-panel');

	$('#infobox_2-label').val(Webform.infobox_2_label);
	Helper.onYesNoShowHide(Webform.infobox_2_on, '.infobox_2-panel');

	// -- Participant
	Helper.onYesNoShowHide(Webform.participant_on, '.participant-form');  
	// Helper.onYesNoShowHide(Webform.participant_on, '.participant-panel');  

	$('.participant-title a').html(Webform.participant_title);	 
	Webform.participant_add_title = '+ Lägg till ' + Webform.participant_title;
	Webform.participant_remove_title = '- Ta bort ' + Webform.participant_title;
	$('#eAddTab a').html(Webform.participant_add_title);
	$('#eRemoveTab a').html(Webform.participant_remove_title);
	
	Helper.onYesNoShowHide(Webform.participant_address_on, '.participant_address_on');	

	$('#participant_personal_id-label').val(Webform.participant_personal_id_label);
	
	Helper.onYesNoShowHide(Webform.collect_spar_on , '.collect_spar-panel ');
		
	$('#participant_address-panel').val(Webform.participant_address_label);
	Helper.onYesNoShowHide(Webform.participant_address_on, '.participant_address-panel');
	
	$('#date_of_birth-label').val(Webform.date_of_birth_label);
	Helper.onYesNoShowHide(Webform.date_of_birth_on, '.date_of_birth-panel');
	
	$('#note-label').val(Webform.note_label);
	Helper.onYesNoShowHide(Webform.note_on, '.note-panel');

	if (Webform.note_on == 'n') {
		$('#eBoxActiveNote').show();
	}
	else {
		$('#eBoxActiveNote').hide();
	}

	$('#total_amount-label').val(Webform.total_amount_label);

	// 2022-02-04
	$('#participant_first_name-label').val(Webform.participant_first_name_label);
	$('#participant_last_name-label').val(Webform.participant_last_name_label);

	if (Webform.participant_on == 'y') {

		var param = {};
		param._group = "Event";
		param._action = "EventCollectionSelection";
		param._token = Token;
		param._user_id = UserId;
		param._event_id = Current.eventId;			
		$.ajax({ type: "POST", url: 'service2/', data: param,
			success: function(result) {
				
				Webform._selection = jQuery.parseJSON(result);
				webform.createSelectionBoxes();
			}
		});
	}
	else {
		Webform._selection = []; 
	}

	// -- Button - serring on top
	$('#eEdit').hide();
	
	$('#ePreview').show();

	// Show editor	
	// $('.section-webform-item').show();

}

function loadWebformFooter() {

	var monthlyInvoiceFee = Number(Webform._monthly_invoice_fee);
	var payment_text = 'Betalning sker mot ' + Webform._first_Invoice_due_days + ' dagars faktura ';
			
	payment_text += '<i>('; 
	if (Webform._first_invoice_start_fee > 0) {
		payment_text += 'Uppläggningsavg. ' + Webform._first_invoice_start_fee + 'kr ,';
	}
	payment_text += '0' + '% ränta under ' + Webform._credit_interest_grace_days + ' dagar och ' + parseInt(Webform._first_invoice_fee) + ' kr i aviavg.)</i> ';
	payment_text += 'som skickas till din e-postadress efter att du har bekräftat med BankID nedan.';
	payment_text += ' Fakturan kan även delbetalas i upp till ' + Webform._repayment_term + ' månader ';
	payment_text += '<i>(' + Webform._customerInterest + '% ränta och ' + monthlyInvoiceFee.toFixed(0) + ' kr i aviavg.';
	if (Webform._administration_fee > 0) {
		payment_text += ' Adm. avg. ' + Webform._administration_fee + 'kr/mån';
	}
	payment_text += ', effektiv ränta ' + Webform._effective_rate + '% på 10 000 kr)</i>. ';
	payment_text += ' Se villkor under <a href="https://www.turtle-pay.com/villkor" target="_blank">www.turtle-pay.com/villkor</a>';
	payment_text += ' och integritetspolicy <a href="https://www.turtle-pay.com/integritetspolicy" target="_blank">www.turtle-pay.com/integritetspolicy</a>.';
	
	//-- GDPR
	payment_text += ' Du samtycker samtidigt att Turtle Pay behandlar dina personuppgifter åt ';
	payment_text += Webform._company_name; 
	payment_text += ', enligt deras integritetspolicy.';
	
	$('#webform-payment-text').html(payment_text);
	
	var footer_line1 = Webform._known_as + " i samarbete med Turtle Pay AB.";
	$('#webform-footer-line1').html(footer_line1);
}

function loadWebformImage() {

	var param = {};
	param._group = "Event";
	param._action = "GetLogoList";
	param._token = Token;
	param._user_id = UserId;

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {		
			var data = jQuery.parseJSON(result);
			document.getElementById("logo-list").options.length = 0;
			if (data.dir.length > 0) {
				for (var i=0; i < data.dir.length; i++) {                        
					$('#logo-list').append('<option value="' + data.dir[i] + '">' + data.dir[i] + '</option>');
				}
			}

			var imageFile = Webform.header_image;
			var position =  imageFile.indexOf("-");
			imageFile = imageFile.substr(position + 1);
			$('#logo-list').val(imageFile);
		}
	});
}

function setStatusAfterLoad() {
	
	// -- Event has started (participant exist

	if (Webform._status.hasStarted == 'y') {	
		$('#participant_on').prop('disabled', true);
		// $('#participant_title').prop('disabled', true);		
				
		// $('#participant_limit_on').prop('disabled', true);	
		$('#participant_apply_limit_on').prop('disabled', true);	
		$('#participant_address_on').prop('disabled', true);	

		$('#collect_spar_on').prop('disabled', true);	
		$('#date_of_birth_on').prop('disabled', true);	
	}

	// -- If Events is Inherit
	if (Webform.inherit_event_id > 0) {
		$('#participant_on').prop('disabled', true);
		$('#participant_title').prop('disabled', true);		
		$('#participant_limit_on').prop('disabled', true);	
		$('#participant_apply_limit_on').prop('disabled', true);
		
		if (Webform.parent_address_on == 'y' || Webform.parent_collect_spar_on == 'y') {
		
			$('#participant_address_on').prop('disabled', true);
			$('#collect_spar_on').prop('disabled', true);
		}
		if (Webform.date_of_birth_on == 'y') {
			$('#date_of_birth_on').prop('disabled', true);	
		}
	}

}

function loadWebformPreview() {

}

function endWebformPreviewEditor() {
	
}

$(document).on('click', '#eAddTab', function(event) {
	event.preventDefault();
	if (WebFormPreviewOn) {
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
		$('#first_name').val('');  
		$('#last_name').val(''); 
		if (Webform.collect_spar_on == 'y') {
			$('#participant_personal_id').val('');
		}
		if (Webform.participant_address_on == 'y') {
			$('#address').val(''); 
			$('#postcode').val(''); 
			$('#city').val(''); 
			$('#part-mobile').val(''); 
			$('#part-email').val(''); 
			
		}
	}
});

$(document).on('click', '#eBackEdit', function(event) {
	event.preventDefault();
	endPreview();
	$('#eBackEdit').hide();
	$('#webform-preview-panel').hide();
	$('.main-header').show();
	$('.hide-preview').show();
	webform.loadWebFormSetting();
	$('#webform-panel').show();
});

$(document).on('click', '#eBoxSelectionAdd', function(event) {
	event.preventDefault();
	var newOption = {};
		newOption.text = ''; //$('#selection-text-new').val();
		newOption.value = ''; // $('#selection-value-new').val();
		newOption.sortorder = (CurrentOption.length * 10) + 100;
		newOption.event_selection_setting_id = CurrentSelectionId;
		newOption.event_option_setting_id = '0';
		newOption.sortorder = (CurrentOption.length * 10) + 100;
		newOption.event_selection_setting_id = CurrentSelectionId;
		CurrentOption.push(newOption);
		
		var index = CurrentOption.length - 1;

	var htmlList = '';
	htmlList += '<tr>';
		htmlList += '<td><input class="box-input" type="text" id="selection-text-' + index + '" " maxlength="27"></td>';
		htmlList +='<td><input class="box-input only-numeric-neg" type="text" id="selection-value-' + index + '" maxlength="10"></td>';
			
		htmlList +='<td style="white-space: nowrap;"><input class="has-text-centered selection-max-on" type="checkbox" id="selection-max-on-' + index + '"></td>';
		htmlList +='<td class="has-text-centered" ><input style="width:50px; margin-right:12px; border: 1px solid #cccccc; padding: 2px; border-radius: 4px; text-align: right; display: none" class="box-input only-numeric" type="input" id="selection-max-number-' + index + '"></td>';
		htmlList += '<td class="option-tool-panel-edit" style="display:none">';
			htmlList += '<a action="update" class="button eOptionTool is-primary"><span class="icon is-small"><i class="fas fa-check"></i></span></a>';
		htmlList +='</td>';
		htmlList +='<td style="white-space:nowrap;" class="option-tool-panel">';
			htmlList += '<a class="button eOptionTool" action="up" index="' + index + '"><span class="icon is-small"><i class="fas fa-arrow-up"></i></span></a>';
			htmlList += '&nbsp;&nbsp;';
			htmlList += '<a class="button eOptionTool" action="down" index="' + index + '"><span class="icon is-small"><i class="fas fa-arrow-down"></i></span></a>';
			htmlList += '&nbsp;&nbsp;';
			htmlList += '<a class="button eOptionTool" action="remove" index="' + index + '"><span class="icon is-small"><i class="fas fa-times"></i></span></a>';
			htmlList +='</td>';
	htmlList +='</tr>';
	$("#box-selection-table tbody").append(htmlList);
	
}); 

$(document).on('click', '#eBackWebform', function(event) {
	event.preventDefault();
	
	var event_name = $("#event_name").val();
	if (event_name.length < 2) {
		$('#message-text-modal').html('Namn på Event måste vara på minst 2 tecken!');
		$('#message-modal').addClass('is-active');
		
		return false;
	}
	var param = Webform;
	param._group =  'Event';
	param._action = 'EventCollectionUpdate';
	param._token = Token;
	param._user_id = UserId;
	$.ajax({ type: "POST", url: 'service2/index2.php/', data: JSON.stringify(param),
		success: function(result) {
			location.reload();
		}
	});
});

$(document).on('click', '#eSelectFile', function(event) {
	event.preventDefault();
	$('#upload-file').trigger('click');

});

$(document).on('click', '#eSelectAttach', function(event) {
	event.preventDefault();
	$('#upload-attach').trigger('click');

});

$(document).on('click', '#eBoxSelectionClose', function(event) {
	event.preventDefault();
	// --
	// ADD: Need control question 
	// --
	$('#box-selection').removeClass('is-active');
});

$(document).on('click', '#eBoxSelectionNew', function(event) {
	event.preventDefault();
	CurrentOption = [];
	CurrentSelectionId = 0;
	CurrentOptionIndex = 0;
	CurrentSelectionIndex = -1;
	// -- Current.selectionOpen = true;
	$('#eBoxSelectionAdd').show();
	$('#selection_header').val('');
	$('#selection_required').prop('checked', false);
	// New 20210811
	$('#selection_header').prop('disabled', false);
	OptionBox.listRefresh();
	$('#box-selection').addClass('is-active');
});

$(document).on('click', '#eBoxSelectionSave', function(event) {
	event.preventDefault();

	var header = $('#selection_header').val();
	var requiredOn  = 'n';
	if($("#selection_required").is(':checked')) {
		requiredOn = 'y';
	}
	if (header.length < 1) {
		$('#message-text-modal').html('Urvals rubrik får inte vara tom!');
		$('#message-modal').addClass('is-active');
		return;
	}

	OptionBox.refresh();

	// cehck if its a value
	for (var i=0; i<CurrentOption.length; i++) {
		if (CurrentOption[i].sortorder != '9999999') {
			if (CurrentOption[i].text.length < 1) {
				$('#message-text-modal').html('Rubriktext får inte vara tomt');
				$('#message-modal').addClass('is-active');
				return;
			}
			if (isNaN(CurrentOption[i].value) || CurrentOption[i].value.length < 1 ) {
				$('#message-text-modal').html('Värdet måste vara numeriskt');
				$('#message-modal').addClass('is-active');
				return;
			}
		}
	}

	var param = {};
	param._group =  'Event';
	param._action = 'EventCollectionSelectionUpdate';
	param._token = Token;
	param._user_id = UserId;
	param._event_id = Current.eventId;
	param._event_selection_id  = CurrentSelectionId;
	param._selection_name =$('#selection_header').val();
	param._required_on = requiredOn;
	param._options = CurrentOption;

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			webform.createSelectionBoxes();
			var param = {};
			param._group = "Event";
			param._action = "EventCollectionSelection";
			param._token = Token;
			param._user_id = UserId;
			param._event_id = Current.eventId;
			
			$.ajax({ type: "POST", url: 'service2/', data: param,
				success: function(result) {
					Webform._selection = jQuery.parseJSON(result);
					webform.createSelectionBoxes();
					$('#box-selection').removeClass('is-active');
				}
			});
		}
	});
	
	//Webform._selection[0].option = CurrentOption; // ??
	//$('#box-selection').hide(); 
});

$(document).on('click', '.eEditIntroText', function(event) {
	event.preventDefault();
	$('#intro_text_edit').hide();
	$('#intro_text').val(Webform.intro_text);
	$('#intro_text').show();
	$('.eEditPanelIntroText').show();
});

$(document).on('click', '.eEditPanel', function(event) {
	event.preventDefault();
	var itemId = $(this).attr('itemid');
	var action = $(this).attr('action');
	if (action == "ok") {
		Webform[itemId + '_label'] = $('#' + itemId + '-label').val();

	} else {
		$('#' + itemId + '-label').val(Webform[itemId + '_label']);
	}
	$('#' + itemId + '-label').prop("disabled", true);
	$('#' + itemId + '-label').css("color", Webform.text_color);
	$('.edit-panel-' + itemId).hide();	
	if (action == "ok") {
		updateEventCollection();
	}
});

$(document).on('click', '.eEditPanelIntroText', function(event) {
	event.preventDefault();
	var action = $(this).attr('action');
	if (action == "ok") {
		Webform.intro_text = $('#intro_text').val();
		$('#intro_text_edit').html(Webform.intro_text.split("\n").join("<br />"));
	} else {
		// nothing need tio be done
	}
	$('#intro_text').hide();
	$('#intro_text').val('');
	$('#intro_text_edit').show();
	$('.eEditPanelIntroText').hide();	

	if (action == "ok") {
		updateEventCollection();
	}
});

$(document).on('click', '.eEditValue', function(event) {
	event.preventDefault();
	var itemId = $(this).attr('itemid');
	var action = $(this).attr('action');
	if (action == "ok") {
		if (itemId == 'accounting')  {
			Webform['company_account_id'] = $('#ddAccountList').val();
			$('#ddAccountList').prop("disabled", true);
		}
		else if (itemId == 'accounting-standard')  {
			Webform['company_account_id'] = $('#ddAccountStandardList').val();
			$('#ddAccountStandardList').prop("disabled", true);
		}
		else {
			Webform[itemId] = $('#' + itemId).val();
		}
	} else {
		if (itemId == 'accounting')  {
			$('#ddAccountList').prop("disabled", true);
			//$('.edit-value-' + itemId).show();
		 	$('#ddAccountList').val(Current.accountingId);
		}
		else if (itemId == 'accounting-standard')  {
			$('#ddAccountListStandard').prop("disabled", true);
			//$('.edit-value-' + itemId).show();
		 	$('#ddAccountStandardList').val(Current.accountingId);
		}
		else {
			('#' + itemId).val(Webform[itemId]);
		}
	}
	if (itemId != 'accounting') {
		$('#' + itemId).prop("disabled", true);
		$('#' + itemId).css("color", Webform.input_color);
		$('#' + itemId).css("background-color", Webform.input_bcolor);
	}
	$('.edit-value-' + itemId).hide();	
	if (action == "ok") {
		updateEventCollection();
	}
});

$(document).on('keypress', '.only-numeric', function (e) {
	var keyCode = e.which ? e.which : e.keyCode     
	if (!(keyCode >= 48 && keyCode <= 57)) {
		return false;
	}
});

$(document).on('keypress', '.only-numeric-neg', function (e) {
	var keyCode = e.which ? e.which : e.keyCode     
	if (keyCode == 45) {
		// return true; - tecken
	} 
	else if (!(keyCode >= 48 && keyCode <= 57)) {
		return false;
	}
});

$(document).on('keypress', '.no-comma', function (e) {
	var keyCode = e.which ? e.which : e.keyCode   
	//alert(keyCode);  
	if (keyCode == 44) {
		return false;
	} 
	else {
		return true;
	}
});

$(document).on('click', '.eOptionTool', function(event) {
	event.preventDefault();
	var index = $(this).attr('index');
	var action = $(this).attr('action');

	if (action == 'remove') {
		if (Webform._status.hasStarted == 'y') {
			
			$('#message-text-modal').html('Kan ej ta bort!<br><br>Webformuläret har deltagare');
			$('#message-modal').addClass('is-active');
			return;
		}
		CurrentOption[index].sortorder = '9999999'; 
		CurrentOption = _.sortBy( CurrentOption, 'sortorder' );
		OptionBox.listRefresh();
	}
	else if (action == 'up') {
		if (Number(CurrentOption[index].sortorder) > 100) {
			OptionBox.refresh();
			CurrentOption[index].sortorder = Number(CurrentOption[index].sortorder) - 15;
			CurrentOption = _.sortBy( CurrentOption, 'sortorder' );
			//OptionBox.sortorderSet();
			OptionBox.listRefresh();
		}
		else {
			$('#message-text-modal').html('Är redan den första');
			$('#message-modal').addClass('is-active');
			return;
		}
	}
	else if (action == 'down') {
		if (Number(CurrentOption[index].sortorder) < Number(CurrentOption[CurrentOption.length - 1].sortorder)) {
			CurrentOption[index].sortorder = Number(CurrentOption[index].sortorder) + 15;
			CurrentOption = _.sortBy( CurrentOption, 'sortorder' );
			OptionBox.sortorderSet();
			OptionBox.listRefresh();
		}
		else {
			$('#message-text-modal').html('Är redan den sista');
			$('#message-modal').addClass('is-active');
			return;
		}
	}
	
	else if (action == 'cancel-new') {	
    	$('#box-selection-table tr:last').remove();
	}
	else if (action == 'cancel') {	
		alert('cancel');
	}
	else if (action == 'update') {	
		$('.option-tool-panel-edit').hide();
		CurrentOption[CurrentOptionIndex].text = $('#selection-text-' + CurrentOptionIndex).val();
		CurrentOption[CurrentOptionIndex].value = $('#selection-value-' + CurrentOptionIndex).val();
		$('#selection-text-' + CurrentOptionIndex).prop("disabled", true);
		$('#selection-value-' + CurrentOptionIndex).prop("disabled", true);
		$('.option-tool-panel').show();
	}

});

$(document).on('change', '.ePanelYes', function(event) {
	event.preventDefault();
	var value = $(this).val();
	var id = $(this).attr('id');

	switch (id) {

		case 'private_on' :
			if (value == 'n') {
				$('.event_url-panel').hide();
			}
			else {
				$('.event_url-panel').show();
			}
			Webform.private_on = value;
		
			break;
		
		case 'webform_on' :
			Webform.webform_on = value;
			break;
		case 'has_vat' :
			Webform.has_vat = value;
			break;
			/*	
			case 'limited_time_on' :
				Helper.onYesNoShowHide(value, '.limited_time-panel');
				Webform.limited_time_on = value;
				break;
			*/
		case 'participant_limit_on' :
			if (value == 'n') {
				$('.participant_max-panel-value').hide();
				// 2022-05-21
				$('.participant_limit-show').hide();
			}
			else {
				$('.participant_max-panel-value').show();
				// 2022-05-21
				$('.participant_limit-show').show();
			}
			Webform.participant_limit_on = value;
			break;
			
			// 20220529
		case 'participant_limit_show' :
			Webform.participant_limit_show = value;
			break;
		
		case 'participant_apply_limit_on' :
			if (value == 'n') {
				$('.participant-apply_max-panel-value').hide();
			} else {
				$('.participant-apply_max-panel-value').show();
			}
			Webform.participant_apply_limit_on = value;
			break;
		case 'amount_on' :
			if (value == 'n' && Webform.participant_on == 'n') {
				$('#amount_on').val('y');
				return;
			}
			Helper.onYesNoShowHide(value, '.standard-amount-panel');
			if (value == 'n') {
				Webform.amount = 0;
				$('#amount').val('');
			}
			Webform.amount_on = value;
			break;
		case 'mobile_on' :
			Helper.onYesNoShowHide(value, '.mobile-panel');
			Webform.mobile_on = value;
			break;
		case 'infobox_1_on' :
			Helper.onYesNoShowHide(value, '.infobox_1-panel');
			Webform.infobox_1_on = value;
			break;
		case 'infobox_2_on' :
			Helper.onYesNoShowHide(value, '.infobox_2-panel');
			Webform.infobox_2_on = value;
			break;
		case 'company_address_on' :
			//Helper.onYesNoShowHide(value, '.mobile-panel');
			Webform.company_address_on = value;
			break;
		case 'participant_on' :	
		
			Helper.onYesNoShowHide(value, '.participant-form');  
			Helper.onYesNoShowHide(value, '.participant-panel');  
			Webform.participant_on = value;

			if (Webform.participant_on == 'y') {
				$('#ddAccountList').val(Webform.company_account_id);
				if (Webform._has_bo == 'y') {
					$('.standard-panel').hide();
					$('.accounting-panel').show();
					$('.accounting-standard-panel').hide();
					
				}
				Webform.amount_on = 'n';
				Webform.amount = 0;
				$('#amount').val('');
				$('#amount_on').val('n');
				if (Webform.participant_apply_limit_on == 'n') {
					$('.participant-apply_max-panel-value').hide();
				}
				else {
					$('.participant-apply_max-panel-value').show();
				}
				if (Webform.participant_limit_on == 'n') {
					$('.participant_max-panel-value').hide();
				}
				else {
					$('.participant_max-panel-value').show();
				}
				
			}
			else {
				if (Webform.amount_on == 'n') {
					Webform.amount_on = 'y';
					$('#amount_on').val('y');
					$('.standard-amount-panel').show();
					if (Webform._has_bo == 'y') {
						$('.accounting-panel').hide();
						$('.accounting-standard-panel').show();
					}
					
				}
			}
			Webform.participant_on = value;
		
			if (value == 'y') {
				Webform.amount = 0;
				$('#amount').val('');
				Webform.amount_on = 'n';
				$('#amount_on').val(Webform.amount_on);
				Helper.onYesNoShowHide(Webform.amount_on, '.standard-amount-panel');
			}
			break;
		case 'participant_personal_id_on' :	
			Helper.onYesNoShowHide(value, '.participant_personal_id-panel');
			Webform.participant_personal_id_on = value;
			break;
		case 'participant_address_on' :	
			Helper.onYesNoShowHide(value, '.participant_address-panel');
			Webform.participant_address_on = value;
			break;
		case 'collect_spar_on' :	
			Helper.onYesNoShowHide(value, '.collect_spar-panel');
			Webform.collect_spar_on = value;
			break;
		
		case 'date_of_birth_on' :	
			Helper.onYesNoShowHide(value, '.date_of_birth-panel');
			Webform.date_of_birth_on = value;
			break;
			
		case 'note_on' :	
			Helper.onYesNoShowHide(value, '.note-panel');
			Webform.note_on = value;
			break;

		case 'header_image_on' :	
			if (value == "y") {
				$('.header_title-panel').hide();
    			$('.logo-list-panel').show();
				$('#header-text-panel').hide(); 
				$('#header-image-panel').show(); 
				Webform.header_image_on = 'y';
			}
			else {
				$('.logo-list-panel').hide();
				$('.header_title-panel').show();
				$('#header-image-panel').hide(); 
				$('#header-text-panel').show(); 
				Webform.header_image_on = 'n';
			}
			break;

		case 'has_attach' :	
			if (value == "y") {
				$('#attach-list').empty();
				if (Webform._attach_list.length > 0) {   
					for (var i=0; i < Webform._attach_list.length; i++) {                        
						$('#attach-list').append('<option value="' +  Webform._attach_list[i].event_attach_id + '">' + Webform._attach_list[i].realname + '</option>');
					}
				}	
				$('.attach-list-panel').show();
				Webform.has_attach = 'y';
			}
			else {
				$('.attach-list-panel').hide();
				Webform.has_attach = 'n';
			}
			break;
	}
	
	updateEventCollection();

});

$(document).on('click', '.participant-tab', function(event) {
	event.preventDefault();	
	
	if (WebFormPreviewOn) {
		saveParticipant(ParticipantCurrentIndex);
		$('.participant-tab').removeClass('is-active');
		ParticipantCurrentIndex = $(this).attr('index');
		$(this).addClass('is-active');
		$('#first_name').val(Participant[ParticipantCurrentIndex].first_name);  
		$('#last_name').val(Participant[ParticipantCurrentIndex].last_name); 
		if (Webform.collect_spar_on == 'y') {
			$('#participant_personal_id').val(Participant[ParticipantCurrentIndex].personal_id_number);
		}
		if (Webform.participant_address_on == 'y') {
			$('#address').val(Participant[ParticipantCurrentIndex].address);
			$('#postcode').val(Participant[ParticipantCurrentIndex].postcode);
			$('#city').val(Participant[ParticipantCurrentIndex].city);
			$('#part-mobile').val(Participant[ParticipantCurrentIndex].mobile);
			$('#part-email').val(Participant[ParticipantCurrentIndex].email);
		}
		// If Spar
		for (var i=0; i < OptionCounts; i++) {
			setSelectedByText('option-' + i, Participant[ParticipantCurrentIndex].option[i].text);
		}
	}
});

$(document).on('click', '#ePreview', function(event) {
	event.preventDefault();
	// Need valuation
	var event_name = $("#event_name").val();
	if (event_name.length < 2) {
		$('#message-text-modal').html('Namn på Event måste vara på minst 2 tecken!');
		$('#message-modal').addClass('is-active');
		
		return false;
	}
	var param = Webform;
	param._group =  'Event';
	param._action = 'EventCollectionUpdate';
	param._token = Token;
	param._user_id = UserId;
	//param._event_id = Current.eventId;
	//param.event_name = event_name;

	$.ajax({ type: "POST", url: 'service2/index2.php', data: JSON.stringify(param),
		success: function(result) {
			$('.tool-panel').hide(); 
			$('.main-header').hide();
			$('.hide-preview').hide();
			$('#webform-panel').hide();
			$('#eBackEdit').show();
			// $('.ref-panel').show();	
			initPreview();
		}
	});
});

$(document).on('click', '#eRemoveTab', function(event) {
	event.preventDefault();
	if (WebFormPreviewOn) {
		var active = 0;
		for (var i = 0; i < Participant.length; i++) {
			if (Participant[i].status == 'a') {
				active++;
			}
		}
	
		if (active == 1) {
			$('#message-text-modal').html('Kan inte ta bort alla ' + WEBFORM_PARTICIPANT_LABEL);
			$('#message-modal').addClass('is-active');
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
		$('#first_name').val(Participant[ParticipantCurrentIndex].first_name);  
		$('#last_name').val(Participant[ParticipantCurrentIndex].last_name); 
		for (var i=0; i < OptionCounts; i++) {
			setSelectedByText('option-' + i, Participant[ParticipantCurrentIndex].option[i].text);
		}

		saveParticipant(ParticipantCurrentIndex);
		calculateTotal();
	}
});

$(document).on('change', '.selection-max-on', function(event) {
	event.preventDefault();
	OptionBox.refresh();
	OptionBox.maxFieldShow();
});

$(document).on('click', '.eToolSelection', function(event) {
	event.preventDefault();
	var index = $(this).attr('index');
	if (Webform._selection[index].parent_event_selection_setting_id == '0') {
		$('#eBoxSelectionAdd').show();
		// -- Current.selectionOpen = true;
	}
	else {
		$('#eBoxSelectionAdd').hide();
		// -- Current.selectionOpen = false;
	}
	if (Webform._status.hasChildren == 'y') {
		$('#eBoxSelectionAdd').hide();
	}
	CurrentOption = Webform._selection[index].option;
	CurrentSelectionId = Webform._selection[index].event_selection_setting_id;
	CurrentSelectionIndex = index;

	CurrentOption = _.sortBy(CurrentOption, 'sortorder' ); // Later removed, all will already be sorted at this moment
	//console.log(CurrentOption);
	
	$('#selection_header').val(Webform._selection[index].text);
	if (Webform._selection[index].group_selection_setting_id < Webform._selection[index].event_selection_setting_id) {
		$('#selection_header').prop('disabled', true);
	}
	else if (Webform._has_grouped == 'y') {
		$('#selection_header').prop('disabled', true);
	}
	else {
		$('#selection_header').prop('disabled', false);
	}
	if (Webform._selection[index].required_on == 'y') {
		$('#selection_required').prop('checked', true);
	}
	else {
		$('#selection_required').prop('checked', false);
	}

	OptionBox.listRefresh(); // Ny

	$('#box-selection').addClass('is-active');
});

$(document).on('change', '.select-option', function(event) {
	event.preventDefault();
	if (WebFormPreviewOn) {
		saveParticipant(ParticipantCurrentIndex);
		calculateTotal();
	}
});

$(document).on('click', '.eToolSelectionRemove', function(event) {
	event.preventDefault();
	var index = $(this).attr('index');
	if (Webform._status.hasStarted == 'y') {
		$('#message-text-modal').html('Kan ej ta bort urval!<br><br>Webformuläret har deltagare');
		$('#message-modal').addClass('is-active');
		return;
	}

	if (Webform._selection[index].parent_event_selection_setting_id == '0') {
		$('.remove-selection-warning').hide();
	} 
	else {
		$('.remove-selection-warning').show();
	}
	$('#eYesNoRemoveSelectionYes').attr('index', index);
	$('#yesno-remove-selection-modal').addClass('is-active');
});

$(document).on('click', '.eToolLabel', function(event) {
	event.preventDefault();
	var itemId = $(this).attr('itemid');
	$('#' + itemId + '-label').prop("disabled", false);
	$('#' + itemId + '-label').css("color", '#eeeeee');
	$('.edit-panel-' + itemId).show();
});

$(document).on('click', '.eToolValue', function(event) {
	event.preventDefault();
	var itemId = $(this).attr('itemid');
	if (itemId == 'accounting')  {
		$('#ddAccountList').prop("disabled", false);
		$('.edit-value-' + itemId).show();
		Current.accountingId = $('#ddAccountList').val();
	}
	else if (itemId == 'accounting-standard')  {
		$('#ddAccountStandardList').prop("disabled", false);
		$('.edit-value-' + itemId).show();
		Current.accountingId = $('#ddAccountStandardList').val();
	}
	else {
		$('#' + itemId).prop("disabled", false);
		$('#' + itemId).css("color", '#eeeeee');
		$('#' + itemId).css("background-color", '#666666');	
		$('.edit-value-' + itemId).show();
	}
});

$(document).on('click', '#eBoxActiveNote', function(event) {
	event.preventDefault();
	$('.note-panel').show();
	$(this).hide();
	Webform.note_on = 'y';
	updateEventCollection();
});

$(document).on('click', '.eToolRemove', function(event) {
	event.preventDefault();
	var itemId = $(this).attr('itemid');
	if (itemId == "note") {
		$('#yesno-remove-note-box').addClass('is-active');
	}
});

$(document).on('click', '#eYesNoRemoveNoteNo', function(event) {
	event.preventDefault();
	$('#yesno-remove-note-box').removeClass('is-active');
});

$(document).on('click', '#eYesNoRemoveNoteYes', function(event) {
	event.preventDefault();
	$('#yesno-remove-note-box').removeClass('is-active');
	$('.note-panel').hide();
	$('#eBoxActiveNote').show();
	Webform.note_on = 'n';
	Webform.note_label = 'Fritext';
	$('#note-label').val();
	updateEventCollection(Webform.note_label);
});

$('#upload-file').change(function (e) {

    const fi = document.getElementById('upload-file'); 

    if (fi.files.length > 0) { 
        for (var i = 0; i <= fi.files.length - 1; i++) { 
            const fsize = fi.files.item(i).size; 
            const file = Math.round((fsize / 1024)); 
            if (file > 300) { 
                $('#message-text-modal').html('Logotyp bild är för stor, max storlek är 300kb!');
                $('#message-modal').addClass('is-active');
                return;
            } 
            else {
                if (this.files && this.files[0]) {
                    var reader = new FileReader();
                    reader.onload = function (e) {
                        $('#header-image-src').attr('src', e.target.result);
                    }
                    reader.readAsDataURL(this.files[0]);
                    var file_data = $('.image').prop('files')[0];

                    if (file_data != undefined) {
                        var form_data = new FormData();                  
                        form_data.append('file', file_data);
                        $.ajax({
                            type: 'POST',
                            url: 'service2/upload.php?id=' + UserId,
                            contentType: false,
                            processData: false,
                            data: form_data,
                            success:function(result) {
                                var data = jQuery.parseJSON(result); 
                                if (data.code =='1')  {
                                    var imageFile = data.logo_name;
                                    var position =  imageFile.indexOf("-");
                                    imageFile = imageFile.substr(position + 1);
                                
                                    $('#logo-list').append('<option value="' + imageFile + '">' + imageFile + '</option>');
                                    $('#logo-list').val(imageFile);
                                    Webform.header_image = data.logo_name;
                                    if (Webform.header_image_on == 'n') {
                                        Webform.header_image_on = 'y';
                                        $('.header_title-panel').hide();
                                        $('.logo-list-panel').show();
                                        $('#header-text-panel').hide(); 
                                        $('#header-image-panel').show(); 
                                    }
                                    updateEventCollection();
                                }
                                else if (data.code == '0') {
                                    $('#message-text-modal').html('Logotyp bild format är inte gilltigt!');
                                    $('#message-modal').addClass('is-active');
                                    return;
                                } 
                                else {
                                    $('#message-text-modal').html('Logotyp bild kunde inte laddas upp!');
                                    $('#message-modal').addClass('is-active');
                                    return;
                                }
                            }
                        });
                    }
                }
            }
        }
    }

});

$('#upload-attach').change(function (e) {

	// alert('attach-upload');
	
	const fi = document.getElementById('upload-attach'); 

	if (fi.files.length > 0) { 
	
		for (var i = 0; i <= fi.files.length - 1; i++) { 
			const fsize = fi.files.item(i).size; 
			
			const file = Math.round((fsize / 1024)); 
			if (file > 3000) { 
				$('#message-text-modal').html('Bilaga är för stor, max storlek är 1000kb!');
				$('#message-modal').addClass('is-active');
				return;
			} 
			else {
			
				if (this.files && this.files[0]) {
					var file_data = $('.attach').prop('files')[0];
					if (file_data != undefined) {
						var form_data = new FormData();                  
						form_data.append('file', file_data);
						$.ajax({
							type: 'POST',
							url: 'service2/upload-attach.php?id=' + UserId + '&event=' + Webform._event_id,
							contentType: false,
							processData: false,
							data: form_data,
							success:function(result) {
								var data = jQuery.parseJSON(result); 
								if (data.code =='1')  {
									var param = {};
									param._group = 'Event';
									param._action = 'EventAttachAdd';
									param._token = Token;
									param._user_id = UserId;
									param.event_id = Webform._event_id;
									param.filename = data.filename;
									param.realname = data.realname;
									$.ajax({ type: "POST", url: 'service2/', data: param,
										success:function(result) {
											var data = jQuery.parseJSON(result); 
											if (data.code =='1') {
												Webform._attach_list = data._attach_list;
												$('#attach-list').empty();
												if (Webform._attach_list.length > 0) {   
													for (var i=0; i < Webform._attach_list.length; i++) {                        
														$('#attach-list').append('<option value="' +  Webform._attach_list[i].event_attach_id + '">' + Webform._attach_list[i].realname + '</option>');
													}
													$('#attach-list').val(Webform._attach_list[Webform._attach_list.length - 1].event_attach_id);
												}	
											}
											else {
												$('#message-text-modal').html('Bilagan kunde inte laddas upp!');
												$('#message-modal').addClass('is-active');
												return;
											}
										}
									});
								}
								else if (data.code == '0') {
									$('#message-text-modal').html('Bilagans format är inte gilltigt!');
									$('#message-modal').addClass('is-active');
									return;
								} 
								else {
									$('#message-text-modal').html('Bilagan kunde inte laddas upp!');
									$('#message-modal').addClass('is-active');
									return;
								}
							}
						});
					}
				}
			}
		}
	}
});

$(document).on('click', '#eEventAttachRemove', function(event) {
	event.preventDefault();
	if (Webform._attach_list.length > 0) {
		Current.eventAttachId = $('#attach-list').val();
		var attachText = $('#attach-list option:selected').text();
		$('#attach_remove-yesno-text-modal').html(attachText);
		$('#attach-remove-modal').addClass('is-active');
	}
});

$(document).on('click', '#eAttachRemoveNo', function(event) {
	event.preventDefault();
	$('#attach-remove-modal').removeClass('is-active');
});

$(document).on('click', '#eAttachRemoveYes', function(event) {
	event.preventDefault();
	$('#attach-remove-modal').removeClass('is-active');
	AttachemtRemove(Current.eventAttachId);
});

function AttachemtRemove(id) {
	var param = {};
	param._group = 'Event';
	param._action = 'EventAttachRemove';
	param._token = Token;
	param._user_id = UserId;
	param.event_id = Webform._event_id;
	param.event_attach_id = id;
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success:function(result) {
			var data = jQuery.parseJSON(result); 
			if (data.code =='1') {
				Webform._attach_list = data._attach_list;
				$('#attach-list').empty();
				if (Webform._attach_list.length > 0) {   
					for (var i=0; i < Webform._attach_list.length; i++) {                        
						$('#attach-list').append('<option value="' +  Webform._attach_list[i].event_attach_id + '">' + Webform._attach_list[i].realname + '</option>');
					}
					// $('#attach-list').val(Webform._attach_list[Webform._attach_list.length - 1].event_attach_id);
				}	
			}
			else {
				$('#message-text-modal').html('Bilagan kunde inte tas bort!');
				$('#message-modal').addClass('is-active');
				return;
			}
		}
	});
}

$(document).on('click', '#eYesNoRemoveSelectionNo', function(event) {
	event.preventDefault();
	$('#yesno-remove-selection-modal').removeClass('is-active');
});

$(document).on('click', '#eYesNoRemoveSelectionYes', function(event) {
	event.preventDefault();
	var index = $(this).attr('index');

	var param = {};
	param._group =  'Event';
	param._action = 'EventCollectionSelectionRemove';
	param._token = Token;
	param._user_id = UserId;
	param._event_id = Current.eventId;
	param._event_selection_setting_id  = Webform._selection[index].event_selection_setting_id;
	

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
		
			webform.createSelectionBoxes();
			var param = {};
			param._group = "Event";
			param._action = "EventCollectionSelection";
			param._token = Token;
			param._user_id = UserId;
			param._event_id = Current.eventId;
			
			$.ajax({ type: "POST", url: 'service2/', data: param,
				success: function(result) {
					Webform._selection = jQuery.parseJSON(result);
					webform.createSelectionBoxes();
					$('#yesno-remove-selection-modal').removeClass('is-active');
				}
			});
		}
	});

});

$(document).on('change', '#logo-list', function(event) {
	event.preventDefault();	// NEW PART
	var imageFile = UserId + '-' + $(this).val();
	$('#header-image-src').attr('src', 'logo/' + imageFile);
	Webform.header_image = imageFile;
	updateEventCollection();

});

$(document).on('focusout', '#webform-panel input', function(event) {
	event.preventDefault();
	var id = $(this).attr('id');
	var value = $(this).val();
	if (id == 'header_title') {
		Webform[id] = value;
		$('#header-text-title').html(Webform.header_title);
	} 
	else if (id == 'participant_title') {
		Webform.participant_title = value;
		Webform.participant_add_title = '+ Lägg till ' + Webform.participant_title;
		Webform.participant_remove_title = '- Ta bort ' + Webform.participant_title;
		$('.participant-tab a').html(Webform.participant_title);
		$('#eAddTab a').html(Webform.participant_add_title);
		$('#eRemoveTab a').html(Webform.participant_remove_title);
	}
	else if (id == 'participant_apply_max') {

		/*
		if (isNaN(value)) { //  || value.length < 1
			$('#message-text-modal').html('Max antal per anmälan måste vara ett värde');
			$('#message-modal').addClass('is-active');
			return;
		}
		*/

		if (value == '1') {
			$('#eAddTab').hide();
			$('#eRemoveTab').hide();
		}
		else {
			$('#eAddTab').show();
			$('#eRemoveTab').show();
		}
		Webform[id] = value;
	}
	else {
		Webform[id] = value;
	}
		
	updateEventCollection();
	
});

$('.submit').on('click', function() {
	event.preventDefault();
	
	var file_data = $('.image').prop('files')[0];
	if(file_data != undefined) {
		var form_data = new FormData();                  
		form_data.append('file', file_data);
		$.ajax({
			type: 'POST',
			url: 'service2/upload.php',
			contentType: false,
			processData: false,
			data: form_data,
			success:function(response) {
				if(response == 'success') {
					alert('File uploaded successfully.');
				} else if(response == 'false') {
					alert('Invalid file type.');
				} else {
					alert('Something went wrong. Please try again.');
				}

				$('.image').val('');
			}
		});
	}
	return false;
});

function updateEventCollection() {
	var param = Webform;
	param._group =  'Event';
	param._action = 'EventCollectionUpdate';
	param._token = Token;
	param._user_id = UserId;
	
	$.ajax({ type: "POST", url: 'service2/index2.php', data: JSON.stringify(param),
		success: function(result) {
			//alert(result);
		}
	});
}

webform.createSelectionBoxes = function() {
	
	var html = '';
	if (Webform._selection.length > 0 ) {
		var newRow = true;
		var gridCol = 0;
		for (var i=0; i<Webform._selection.length; i++) {
			if (newRow == true) {
				html += '<div class="columns">';
				newRow = false;
				gridCol = 0;
			}		
			gridCol++;
			html += '<div class="column">';
			if (i < Webform._selection.length) {
				var selectionLabel = Webform._selection[i].text;
				
				if (Webform._selection[i].parent_event_selection_setting_id > 0) {
					selectionLabel += '<span style="color:#5a7d22;font-weight:normal;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(Importerad)</span>';
				}

				if (Webform._selection[i].group_selection_setting_id < Webform._selection[i].event_selection_setting_id) {
					selectionLabel += '<span style="color: #5a7d22;font-weight:normal;">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(Grupperad)</span>';
				}

	
				html += '<label class="label">' + selectionLabel + '</label>';
				html += '<div class="select" style="width:100%; ">';
					html += '<select class="select-option" id="option-' + i +  '" style="width:100%">';
						html += '<option selected value="8E1C7E8F67D0">' + '-- Välj --' + '</option>';
						for (var j = 0; j <  Webform._selection[i].option.length; j++) { 

							html += '<option value="' + Webform._selection[i].option[j].value + '">' + Webform._selection[i].option[j].text + '</option>';
						}	
					html +=  '</select>';
				html +=  '</div>';

				html +=  '<div class="control tool-panel" style="padding-top:6px;">';  
    				html +=  '<a class="button eToolSelection" index="' + i +  '"><span class="icon is-small"><i class="far fa-edit"></i></span>&nbsp;&nbsp;Urval</a>';
					html +=  '&nbsp;&nbsp;';
					if (Webform._status.hasChildren == 'n') {
						if (Webform.tdb_on == 'n') {
							html += '<a class="button is-dark eToolSelectionRemove" index="' + i + '"><span class="icon is-small"><i class="fas fa-times"></i></span></a>';
						}
					}
    			html += '</div>';

			}
			html += '</div>';  
			
			if (gridCol == Webform.option_grid) {
				html += '</div>';
				newRow = true;
			}
		}
		if (newRow == false) {
			for (var i = 0; i < Webform.option_grid - gridCol; i++) {
				html += '<div class="column"></div>';
				;
			}	
		}	
	}
	$('#webform-selections').html(html);	
	if (Webform.tdb_on == 'y') {		
		$('.tool-panel').hide();	
		$('.ref-panel').show();			
	}
}

function endPreview() {
	WebFormPreviewOn = false;
	$('#personal_id_number').prop("disabled", true);	
	$('#email').prop("disabled", true);
	$('#amount').css("background-color", '#ffffff'); 
	$('#amount').prop("disabled", true);
	$('#mobile').prop("disabled", true);
	
	$('#infobox_1').prop("disabled", true);
	$('#infobox_2').prop("disabled", true);
	
	$('#personal_id_number').val('');	
	$('#email').val('');

	if (Webform.amount.length > 0) {
		$('#amount').css("background-color", '#ffffff'); 
	} 
	else {
		$('#amount').val(''); 
		$('#amount').prop("disabled", true);
	} 
	if (Webform.ref.length > 0) {
		$('#ref').css("background-color", '#ffffff');
		
	}
	else {
		$('#ref').val('');
		$('#ref').prop("disabled", true);
	}


	$('#mobile').val('');
	
	$('#infobox_1').val('');
	$('#infobox_2').val('');

	if (Webform.participant_on == 'y') {
		//OptionCounts = Webform._selection.length;
		Participant = new Array();
		$('#first_name').val('');
		$('#last_name').val('');
		$('#first_name').prop("disabled", true);
		$('#last_name').prop("disabled", true);
		if (Webform.participant_address_on == 'y') {
			$('#address').prop("disabled", true);
			$('#postcode').prop("disabled", true);
			$('#city').prop("disabled", true);
			$('#part-mobile').prop("disabled", true);
			$('#part-email').prop("disabled", true);
			$('#participant_personal_id').prop("disabled", true);
		
			$('#address').val('');
			$('#postcode').val('');
			$('#city').val('');
			$('#part-mobile').val('');
			$('#part-email').val('');
			$('#participant_personal_id').val('');
		}

		if (Webform.note_on == 'y') {
			$('#note').val('');
			$('#note').prop("disabled", true);
		}
		if (Webform.date_of_birth_on == 'y') {
			$('#date_of_birth').val('');
			$('#date_of_birth').prop("disabled",true);
		}
	}
}

function initPreview() {
	WebFormPreviewOn = true;
	$('#webform-preview-panel').show();
	$('#personal_id_number').prop("disabled", false);	
	$('#email').prop("disabled", false);

	if (Webform.amount.length > 0) {
		$('#amount').css("background-color", '#eeeeee'); 
		$('#amount').prop("disabled", true);
	}
	else {
		$('#amount').prop("disabled", false);
	}
	$('#mobile').prop("disabled", false);
	if (Webform.ref.length > 0) {
		$('#ref').css("background-color", '#eeeeee');
		$('#ref').prop("disabled", true);
	}
	else {
		$('#ref').prop("disabled", false);
	}
	$('#infobox_1').prop("disabled", false);
	$('#infobox_2').prop("disabled", false);
	
	if (Webform.participant_on == 'y') {
		OptionCounts = Webform._selection.length;
		Participant[0] = {};
		Participant[0].status = "a";
		Participant[0].option = new Array();
		for (var i=0; i <  OptionCounts; i++) {
			Participant[0].option[i] = {};
		}
		calculateTotal();
		$('#first_name').prop("disabled", false);
		$('#last_name').prop("disabled", false);

		if (Webform.collect_spar_on == 'y') {
			$('#participant_personal_id').prop("disabled", false);
		}
		if (Webform.participant_address_on == 'y') {
			$('#address').prop("disabled", false);
			$('#postcode').prop("disabled", false);
			$('#city').prop("disabled", false);
			$('#part-mobile').prop("disabled", false);
			$('#part-email').prop("disabled", false);
			$('#participant_personal_id').prop("disabled", false);
		}
		if (Webform.note_on == 'y') {
			$('#note').prop("disabled", false);
		}
		if (Webform.date_of_birth_on == 'y') {
			$('#date_of_birth').prop("disabled", false);
		}
	}
}

OptionBox.listRefresh = function () {
	var htmlList = '';
    htmlList += '<table id="box-selection-table" class="w100p">';

		//alert(CurrentSelectionIndex);
		if (Current.eventCreateType == 'i' && CurrentSelectionIndex >= 0  && Webform._selection[CurrentSelectionIndex].parent_event_selection_setting_id > '0') {
			htmlList += '<tr><th>Urvalstext <span style="font-weight: normal">(max 27 tecken)</span></th><th>Värde</th><th class="edit-panel"></th><th></th></tr>';
		}
		else {
			htmlList += '<tr><th>Urvalstext <span style="font-weight: normal">(max 27 tecken)</span></th><th>Värde</th><th style="white-space: nowrap;" class="has-text-centered">Max antal</th><th id = "max-antal-header" class="has-text-centered"></th><th class="edit-panel"></th><th></th></tr>';
		}
		
		// htmlList += '<tbody>';
		for (var i=0; i<CurrentOption.length; i++) {
			if (CurrentOption[i].sortorder == '9999999') {
				// removed
			}
			else {
				htmlList += '<tr>';
					htmlList += '<td><input class="box-input no-comma" type="text" id="selection-text-' + i + '" value="' + CurrentOption[i].text + '" maxlength="27"></td>';
					htmlList +='<td><input class="box-input only-numeric-neg" type="text" id="selection-value-' + i + '" value="' + CurrentOption[i].value + '" maxlength="10"></td>';
					if (CurrentOption[i].max_on == 'y') {
						$checked = ' checked ';
					}
					else {
						$checked = '';
					}
					if (Current.eventCreateType == 'i' && CurrentSelectionIndex >= 0 && Webform._selection[CurrentSelectionIndex].parent_event_selection_setting_id > '0') {
						// Skip
					}
					else {
						htmlList +='<td style="white-space: nowrap;"><input class="has-text-centered selection-max-on" type="checkbox" id="selection-max-on-' + i + '"' + $checked + '></td>';
						htmlList +='<td class="has-text-centered" ><input style="width:50px; margin-right:12px; border: 1px solid #cccccc; padding: 2px; border-radius: 4px; text-align: right; display: none" class="box-input only-numeric" type="input" id="selection-max-number-' + i + '" value="' + CurrentOption[i].max_number + '"></td>';
					}
					htmlList += '<td class="option-tool-panel-edit" style="display:none">';
						htmlList += '<a action="update" class="button eOptionTool is-primary"><span class="icon is-small"><i class="fas fa-check"></i></span></a>';
					htmlList +='</td>';
					htmlList +='<td style="white-space:nowrap;" class="option-tool-panel">';
					
					htmlList += '<a class="button eOptionTool" action="up" index="' + i + '"><span class="icon is-small"><i class="fas fa-arrow-up"></i></span></a>';
					htmlList += '&nbsp;&nbsp;';
					htmlList += '<a class="button eOptionTool" action="down" index="' + i + '"><span class="icon is-small"><i class="fas fa-arrow-down"></i></span></a>';
					htmlList += '&nbsp;&nbsp;';
				
					if (Webform._status.hasStarted == 'y') {
						// dont create remove button
					} 
					else if (Webform._status.hasChildren == 'y') {
						// dont create remove button
					}
					else if (Webform._selection[CurrentSelectionIndex].parent_event_selection_setting_id == 0) {
						htmlList += '<a class="button eOptionTool" action="remove" index="' + i + '"><span class="icon is-small"><i class="fas fa-times"></i></span></a>';
					}
					htmlList +='</td>';
				htmlList +='</tr>';
			}
		}
		//htmlList += '</tbody>';
    htmlList += '</table>';
	$('#box-selection-list').html(htmlList); 
	OptionBox.maxFieldShow() ;
}

OptionBox.maxFieldShow = function() {
	$('#max-antal-header').html('');
	for (var i=0; i<CurrentOption.length; i++) {
		if (CurrentOption[i].max_on == 'y') {
			$('#max-antal-header').html('Antal');
			$('#selection-max-number-' + i).show();
		}
		else {
			$('#selection-max-number-'  + i).hide();
		}
	}
}

OptionBox.refresh = function() {
	for (var i=0; i<CurrentOption.length; i++) {
		CurrentOption[i].text = $('#selection-text-' + i).val();
		CurrentOption[i].value = $('#selection-value-' + i).val();
		if ($('#selection-max-on-' + i).is(":checked")) {
			CurrentOption[i].max_on = 'y';
			CurrentOption[i].max_number = $('#selection-max-number-' + i).val();
		}
		else {
			CurrentOption[i].max_on = 'n';
			CurrentOption[i].max_number = '0';
		}
	}
}

OptionBox.sortorderSet = function () {
	console.log(CurrentOption);
	for (var i=0; i<CurrentOption.length; i++) {
		if (CurrentOption[i].sortorder != '9999999') {
			CurrentOption[i].sortorder = 100 + (i * 10)
		}
	}	
}

OptionBox.update = function () {
	Webform._selection[index].option = CurrentOption;
}

function calculateTotal() {
    var total = 0;
    for (var i = 0; i < Participant.length; i++) {
        if (Participant[i].status == "a") {
            for (var j = 0; j < Webform._selection.length; j++) {
                if(isNaN(Participant[i].option[j].value)) {
                    // do nothing
                }
                else {
                    if(Webform._selection[j].calculate_on == 'y') {
                        total = total + Number(Participant[i].option[j].value);
                    }
                }  
            }
        }
    }
    var amount = $('#amount').val();;
    if (Number(amount) == false || Number(amount) == NaN) {
        // Skip no value
    }
    else {
        total = total + Number(amount);
    }
    $('#total_amount').val(total); // Total
}

function saveParticipant(index) {

    Participant[index].first_name = $('#first_name').val();  
    Participant[index].last_name = $('#last_name').val(); 
	
	if (Webform.collect_spar_on == 'y') {
		Participant[index].personal_id_number = $('#participant_personal_id').val();
	}

	if (Webform.participant_address_on== 'y') {
		Participant[index].address = $('#address').val(); 
		Participant[index].postcode = $('#postcode').val(); 
		Participant[index].city = $('#city').val(); 
		Participant[index].mobile = $('#part-mobile').val(); 
		Participant[index].email = $('#part-email').val(); 
	}
	// If spar
	//Participant[index].personal_id = $('#participant_personal_id').val(); 

    for (var i=0; i < OptionCounts; i++) {
       
        var value = $('#option-' + i).val();
        
        if(Webform._selection[i].calculate_on == 'y') {
            Participant[index].option[i].value = value;
        }
        else {
            Participant[index].option[i].value
        }

            Participant[index].option[i].value

        var text = $('#option-' + i + ' option:selected').text(); 
        Participant[index].option[i].text = text;
        Participant[index].option[i].event_option_setting_id = getOptionId(i, text);
    } 
}

function optionCheck() {
    var checkOK = true;
    for (var i = 0; i < Participant.length; i++) {
        for (var j=0; j < OptionCounts; j++) {
           
        }
    }

    return checkOK;
}

function setSelectedByText(eID, text) {
    var ele=document.getElementById(eID);
    for(var ii=0; ii<ele.length; ii++)
        if(ele.options[ii].text==text) { //Found!
            ele.options[ii].selected=true;
            return true;
        }
    return false;
}

function getOptionId(selectionIndex, text) {

    //("Option id: " + selectionIndex + " " + text);
    var optionId = 0;
    for (i=0; i<Webform._selection[selectionIndex].option.length; i++) {
        if (Webform._selection[selectionIndex].option[i].text == text) {     
            optionId = Webform._selection[selectionIndex].option[i].event_option_setting_id;
        }
    }
    return optionId;
}

</script>
