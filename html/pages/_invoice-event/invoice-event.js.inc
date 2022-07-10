<script>
/*
	Move to new Global Hlper
*/

function _GetCheckbox(element, checkedValue, uncheckedValue) {
	if ($(element).is(':checked')) {
		return checkedValue;
	}
	else {
		return uncheckedValue;
	}
}

var defaultSubject = 'Faktura från.';
var defaultBody = 'Hej,\n';
defaultBody += 'Dags att hämta din faktura för terminsavgiften under länken nedan.\n';
defaultBody += 'Fakturan är räntefri i 30 dagar med 19 kr i aviavgift och möjlig delbetalning upp till 6 mån.\n';
defaultBody += 'Mvh\n';
defaultBody += 'www.turtle-pay.com/\n';

var InvoiceEventList;
var EventList;

var ImportEmails;

var CustomerListIsLoaded = false;

var Current = {};

Current.invoiceEventName = '';

Current.invoiceEventItemStatus = null;
Current.eventId = null;
invoiceEventId = null;

Current.peopleId = 0;
//Current.eventAllowedEdit = 'y';
Current.eventPreSendDate;
Current.eventSendDate;

// Default settings
Current.eventAutoReminder = '5'; 
Current.eventReminderDays = "5";
Current.eventReminderTimes = "4";
Current.eventAmount = "";
Current.eventAmountOn = "y";
Current.eventRef = "";
Current.body = "";
Current.filter = "0";

Current.reminderLastDate  = null;
Current.reminderTimes  = 0;
Current.sendDate = null;
Current.invoiceEventItemStatus = null;
Current.invoiceEventItemId = null;

Current.invoiceEventType = 'f'; // Default

var MottagareLista;

function loadEventList() {
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "EventList";
	param._token = Token;
	param._user_id = UserId;

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			EventList = jQuery.parseJSON(result);
		}
	});
}

function loadInvoiceEventList() {
	invoiceEventListCreate();
}

$(document).on('click', '.eInvoiceEventClose', function(event) {
	event.preventDefault();
	var invoiceEventId = $(this).attr('ievent');

	var param = {};
	param._group = "InvoiceEvent";
	param._action = "InvoiceEventStatusSet";
	param._token = Token;
	param._user_id = UserId;
	param._invoice_event_id = invoiceEventId;
	param.invoice_event_status = 'c';
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			invoiceEventListCreate();
		}
	});
});

$(document).on('click', '.eInvoiceEventReOpen', function(event) {
	event.preventDefault();
	var invoiceEventId = $(this).attr('ievent');
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "InvoiceEventStatusSet";
	param._token = Token;
	param._user_id = UserId;
	param._invoice_event_id = invoiceEventId;
	param.invoice_event_status = 'p';
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			invoiceEventListCreate();
		}
	});
});

function invoiceEventListCreate() {

	var param = {};
	param._group = "InvoiceEvent";
	param._action = "InvoiceEventList";
	param._token = Token;
	param._user_id = UserId;

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			//(result);
			data = jQuery.parseJSON(result); // InvoiceEventList
			InvoiceEventList = data; // Used in import
			var html = '<table class="table" style="width:100%; margin-bottom:20px"';
			html += '<tr>';
				html += '<th style="text-align:left; background-color: #ffffff;">Namn</th>';
				html += '<th style="text-align:left;width:104px;background-color: #ffffff;">Skapad</th>';
				html += '<th style="text-align:right;background-color: #ffffff;">Antal</th>';
				html += '<th style="text-align:right;background-color: #ffffff;">Pågående</th>';
				html += '<th style="text-align:right;background-color: #ffffff;">Hämtade</th>';
				//html += '<th style="text-align:left;background-color: #ffffff;padding-left:12px!Important;">Status</th>';
				html += '<th style="text-align:left;background-color: #ffffff; width:8%"></th>';
				//html += '<th style="text-align:left">Skapa ny</th>';		
			html += '</tr>';

			for (let i = 0; i < data.length; i++) {
				if (data[i].invoice_event_status == 'c') {
					html += '<tr class="EventComplete">';
					html += '<td colspan="5" style="color:#aaaaaa; font-style: italic;">' + data[i].invoice_event_name + '</td>';
					html += '<td style="text-align:right; width:66px"> <button i-name="' + data[i].invoice_event_name + '" ievent="' + data[i].invoice_event_id + '" class="eInvoiceEventReOpen button is-light is-small">Öppna</button></td>';
					if (UserId == '69') {
						html += '<td style="text-align:right;width:66px">';
							html += '<button ievent="' + data[i].invoice_event_id + '" i-name="' + data[i].invoice_event_name +  '" class="eBoxInvoiceEventClear button is-dark is-small">Radera</button>';
						html += '</td>';
					}

					html += '</tr>';
				}
				else {
					
					html += '<tr class="pointer" i-name="' + data[i].invoice_event_name + '" ievent="' + data[i].invoice_event_id + '">';
					html += '<td class="eOpenEvents" ievent="' + data[i].invoice_event_id + '">' + data[i].invoice_event_name + '</td>';
					html += '<td class="eOpenEvents" style="width:96px" ievent="' + data[i].invoice_event_id + '">' + data[i].create_date + '</td>';
					html += '<td class="eOpenEvents" style="text-align:right;" ievent="' + data[i].invoice_event_id + '">' + data[i].no_items + '</td>';
					html += '<td class="eOpenEvents" style="text-align:right;" ievent="' + data[i].invoice_event_id + '">' + data[i].no_sent + '</td>';
					html += '<td class="eOpenEvents" style="text-align:right;" ievent="' + data[i].invoice_event_id + '">' + data[i].no_confirmed + '</td>';
					html += '<td style="text-align:right; width:66px"> <button i-name="' + data[i].invoice_event_name + '" ievent="' + data[i].invoice_event_id + '" class="eInvoiceEventClose button is-dark is-small"><i class="fas fa-times"></i></button></td>';
				}
				html += '</tr>';
			}

			$('#invoice-event-list').html(html);
			$('.EventComplete').hide();
		}
	});
}

$(document).on('change', '#eShowCompleted', function(event) {
	event.preventDefault();
	
	if(this.checked) {
		$('.EventComplete').show();
	}
	else {
		$('.EventComplete').hide();
	}   
});
	
$(document).on('click', '#eNewEvent', function(event) {
	event.preventDefault();
	$('#event-name').val('');

	$('#ddEventList').empty();
	var list = $("#ddEventList");
	//list.append(new Option('-- Välj event --', '0'));
	$.each(EventList, function(index, item) {
  		list.append(new Option(item.event_name, item.event_id));
	});
	$("#ddEventList").val($("#ddEventList option:first").val());
	$('#modal-import-group').prop('checked', false);
	$('#eCreateEvent').prop("disabled", true);
	$('#eCreateEvent').removeClass('is-primary');
	$('#eCreateEvent').addClass('is-warning');
	
	$('#event-new-modal').addClass('is-active');
});

$(document).on('change', '#ddEventList', function(event) {
	event.preventDefault();
	var value = $(this).val();
	if (value > '0') {
		$('#eCreateEvent').prop("disabled", false);
		$('#eCreateEvent').removeClass('is-warning');
		$('#eCreateEvent').addClass('is-primary');
	}
	else {
		$('#eCreateEvent').prop("disabled", true);
		$('#eCreateEvent').removeClass('is-primary');
		$('#eCreateEvent').addClass('is-warning');
	}
	var name = $('#event-name').val();
	if (name.length < 2) {
		var text = $('#ddEventList option:selected').text();
		$('#event-name').val(text);
	}
});

$(document).on('keyup', '#event-name', function(event) {
	event.preventDefault();
	var value = $(this).val();
	if (value.length > 2) {
		$('#eCreateEvent').prop("disabled", false);
		$('#eCreateEvent').removeClass('is-warning');
		$('#eCreateEvent').addClass('is-primary');
	}
	else {
		$('#eCreateEvent').prop("disabled", true);
		$('#eCreateEvent').removeClass('is-primary');
		$('#eCreateEvent').addClass('is-warning');
	}
});

$(document).on('click', '#eCloseEventNewModal', function(event) {
	event.preventDefault();
	$('#event-new-modal').removeClass('is-active');
});

$(document).on('click', '#eCreateEvent', function(event) {
	event.preventDefault();

	Current.eventId = $('#ddEventList').val();
	Current.invoiceEventName = $('#ddEventList option:selected').text();

	var param = {};
	param._group = "InvoiceEvent";
	param._action = "EventCreate";
	param._token = Token;
	param._user_id = UserId;
	param.invoice_event_name =$('#event-name').val();
	param.event_id = Current.eventId; 
	
	/*
	if ($('#event-import').is(':checked')) {
		param._import = 'y';
		param._import_id = $('#ddEventList').val();
	}
	else {
		param._import = 'n';
	}
	*/

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			Current.invoiceEventId = data.id;
			$('#event-new-modal').removeClass('is-active');
			loadInvoiceEventList();
		}
	});
});

$(document).on('click', '#eEventSettings', function(event) {
	event.preventDefault();

	//var subject = 'Subject';
	//var body = 'Body';

	var param = {};
	param._group = "InvoiceEvent";
	param._action = "InvoiceEventGet";
	param._token = Token;
	param._user_id = UserId;
	param._invoice_event_id = Current.invoiceEventId

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			Current.waUrl = data.wa_url; // 2021-10-06
			$('#setting-event-name').val(data.invoice_event_name);
			$('#settings-body').val(data.body);
	
			$('#test-email').val(data.email);

			if (_.isNull(data.webform_link)) {
				$("#ddFormLinkEventList").prop("selectedIndex", 0).val(); 
			}
			else {
				$('#ddFormLinkEventList').val(data.webform_link);
			}
			
			if (data.reminder_text_on == 'y') {
				$('#settings-reminder-text-on').prop('checked', true);
				$('#settings-reminder-body').val(data.reminder_body);
				$('#settings-reminder-body').show();
			} else {
				$('#settings-reminder-text-on').prop('checked', false);
				$('#settings-reminder-body').val(data.reminder_body);
				$('#settings-reminder-body').hide();
			}

		}
	});
	
	$('#invoice-event-settings-modal').addClass('is-active');
});

$(document).on('click', '#eEventSettingsSave', function(event) {

	var name = $('#setting-event-name').val();
	if (name.length < 2) {
		$('#message-text-modal').html('Namn måste vara på minst 2 tecken!');
		$('#message-modal').addClass('is-active');
		return false;
	}
	var body = $('#settings-body').val();
	if (body.length < 10) {
		$('#message-text-modal').html('E-post meddelandet måste vara på minst 10 tecken!');
		$('#message-modal').addClass('is-active');
		return false;
	}

	if ($('#settings-reminder-text-on').is(':checked')) {
		var reminderBody = $('#settings-reminder-body').val();
		if (reminderBody.length < 10) {
			$('#message-text-modal').html('Påminnelse  meddelandet måste vara på minst 10 tecken!');
			$('#message-modal').addClass('is-active');
			return false;
		}
	}

	var param = {};
	param._group = "InvoiceEvent";
	param._action = "EventUpdate";
	param._token = Token;
	param._user_id = UserId;
	param._event_id = Current.invoiceEventId;
	param.invoice_event_name = name;
	param.body = body;
	

	$('#title-invoice-event-name').html(data.invoice_event_name); //  + $status);

	param.webform_link = $('#ddFormLinkEventList').val();
	if ($('#settings-reminder-text-on').is(':checked')) {
		param.reminder_text_on = 'y';
	}
	else {
		param.reminder_text_on = 'n';
	}
	param.reminder_body = $('#settings-reminder-body').val();
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			Current.body = param.body; 
			$('#invoice-event-settings-modal').removeClass('is-active');
		
		}
	});	
});

function initInvoiceEventUpdating(oldSendDate, oldAutoReminder, oldReminderDays, oldReminderTimes) {
	
	var updateSendDateOn = false;
	var updateReminder = false;
	if (oldSendDate != Current.eventSendDate) {
		updateSendDateOn = true;
	}
	if (oldAutoReminder != Current.eventAutoReminder || oldReminderDays != Current.eventReminderDays || oldReminderTimes != Current.eventReminderTimes) {
		updateReminder = true;
	}
	var body = '';
	if (updateSendDateOn == true &&  updateReminder == true) {
		body = "Planerad utskicksdag och påminnelsefrekvens har ändrats,<br><br>ska alla pågående ändras till detta?";
		$('#eUpdatingBulk').attr('update-type', "3");
	}
	if (updateSendDateOn == true && updateReminder == false) {
		body = "Planerad utskicksdag har ändrats,<br><br>ska alla pågående ändras till detta?";
		$('#eUpdatingBulk').attr('update-type', "1");
	}
	if (updateSendDateOn == false &&  updateReminder == true) {
		body = "Planerad påminnelsefrekvens har ändrats,<br><br>ska alla pågående ändras till detta?";
		$('#eUpdatingBulk').attr('update-type', "2");
	}
	$('#update-bulk-item-text').html(body);
	$('#update-bulk-item-modal').addClass('is-active');
}

$(document).on('click', '#eCloseUpdateBulkItemModal', function(event) {
	event.preventDefault();
	$('#update-bulk-item-modal').removeClass('is-active');
});

$(document).on('click', '#eUpdatingBulk', function(event) {
	event.preventDefault();
	var updateType = $(this).attr('update-type');


	var param = {};
	param._group = "InvoiceEvent";
	param._action = "UpdatingBulk";
	param._token = Token;
	param._user_id = UserId;
	param._invoice_event_id = Current.eventId;
	if (updateType == '1' || updateType == '3') {
		param.send_date = Current.eventSendDate;
	}
	if (updateType == '2' || updateType == '3') {
		param.auto_reminder = Current.eventAutoReminder;
		param.reminder_days = Current.eventReminderDays;
		param.reminder_times  = Current.eventReminderTimes;
	}

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			loadInvoiceEventList();
			$('#update-bulk-item-modal').removeClass('is-active');
		}
	});	
});

$(document).on('click', '#ePreviewInvoice', function(event) {
	event.preventDefault();
	
	var name = $('#setting-event-name').val();
	if (name.length < 2) {
		$('#message-text-modal').html('Namn måste vara på minst 2 tecken!');
		$('#message-modal').addClass('is-active');
		return false;
	}
	var body = $('#settings-body').val();
	if (body.length < 10) {
		$('#message-text-modal').html('E-post meddelandet måste vara på minst 10 tecken!');
		$('#message-modal').addClass('is-active');
		return false;
	}

	if ($('#settings-reminder-text-on').is(':checked')) {
		var reminderBody = $('#settings-reminder-body').val();
		if (reminderBody.length < 10) {
			$('#message-text-modal').html('Påminnelse  meddelandet måste vara på minst 10 tecken!');
			$('#message-modal').addClass('is-active');
			return false;
		}
	}

	var param = {};
	param._group = "InvoiceEvent";
	param._action = "EventUpdate";
	param._token = Token;
	param._user_id = UserId;
	param._event_id = Current.invoiceEventId;
	param.invoice_event_name = name;
	param.body = body;
	
	$('#title-invoice-event-name').html(data.invoice_event_name); //  + $status);
	//$('#title-event-name').html('Event: <i>' + data.event_name + '</i>'); //  + $status); //  + $status);

	//$('#title-event-name').html(param.invoice_event_name); //  + $status);
	param.webform_link = $('#ddFormLinkEventList').val();
	if ($('#settings-reminder-text-on').is(':checked')) {
		param.reminder_text_on = 'y';
	}
	else {
		param.reminder_text_on = 'n';
	}
	param.reminder_body = $('#settings-reminder-body').val();
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			Current.body = param.body; 
			$('#test-email-modal').addClass('is-active');
		}
	});	

});

$(document).on('click', '#eTestEmailCancel', function(event) {
	event.preventDefault();
	$('#test-email-modal').removeClass('is-active');
});

$(document).on('click', '#eTestEmailSend', function(event) {
	event.preventDefault();
	var email = $('#test-email').val();
	if (Helper.validateEmail(email) == false) {
        $('#message-text-modal').html('E-postadress är inte giltigt');
		$('#message-modal').addClass('is-active');
		return;
	}	
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "TestEmail";
	param._token = Token;
	param._user_id = UserId;
	param._invoice_event_id = Current.invoiceEventId;
	param._email = email;
	
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			$('#message-text-modal').html('E-post är sänt till: ' + param._email);
			$('#message-modal').addClass('is-active');
		}
	});	
	$('#test-email-modal').removeClass('is-active');
});

$(document).on('click', '#eCloseEventSettingsModal', function(event) {
	event.preventDefault();
	$('#invoice-event-settings-modal').removeClass('is-active');
});

$(document).on('change', '#event-import', function(event) {
	event.preventDefault();
	if(this.checked) {
		$('.import-group').show();
	}
	else {
		$('.import-group').hide();
	}   
});

$(document).on('change', '#event-spec-import', function(event) {
	event.preventDefault();
	if(this.checked) {
		$('#event-spec').val('');
		$('#event-spec').hide();
	}
	else {
		$('#event-spec').show();
		
	}   
});

$(document).on('change', '#event-amount-import', function(event) {
	event.preventDefault();
	if(this.checked) {
		$('#event-amount').val('');
		$('#event-amount').hide();
		$('#event-amount-label').hide();
	}
	else {
		$('#event-amount').show();	
		$('#event-amount-label').show();
	}   
});

$(document).on('change', '#event-auto-reminder', function(event) {
	event.preventDefault();
	if(this.checked) {
		$('#event-reminder-days').val('7');
		//$('#settings-reminder-days-container').show();
		$('#event-reminder-times').val('3');
		$('.event-reminder-container').show();
	}
	else {
		$('#event-reminder-days').val('7');
		//$('#settings-reminder-days-container').hide();
		$('#event-reminder-times').val('3');
		$('.event-reminder-container').hide();
	}   
});

$(document).on('change', '#event-send-date-pre', function(event) {
	event.preventDefault();
	if(this.checked) {
		var currentDate = new Date();
		var nowDateString = currentDate.toISOString().substring(0, 10);
		$('#event-send-date').val(nowDateString);
		$('#event-send-date').show();
	}
	else {
		$('#event-send-date').hide();
	}   
});

$(document).on('change', '#settings-auto-reminder', function(event) {
	event.preventDefault();
	if(this.checked) {
		$('#settings-reminder-days').val('7');
		//$('#settings-reminder-days-container').show();
		$('#settings-reminder-times').val('3');
		$('.settings-reminder-container').show();
	}
	else {
		$('#settings-reminder-days').val('7');
		//$('#settings-reminder-days-container').hide();
		$('#settings-reminder-times').val('3');
		$('.settings-reminder-container').hide();
	}   
});

$(document).on('change', '#settings-reminder-text-on', function(event) {
	event.preventDefault();
	if(this.checked) {
		$('#settings-reminder-body').show();
	}
	else {
		$('#settings-reminder-body').hide();
	}
});

$(document).on('change', '#settings-pre-send-date', function(event) {
	event.preventDefault();
	if(this.checked) {
		var currentDate = new Date();
		var nowDateString = currentDate.toISOString().substring(0, 10);
		$('#settings-send-date').val(nowDateString);
		$('#settings-send-date').show();
	}
	else {
		$('#settings-send-date').hide();
	}   
});

$(document).on('click', '.eOpenEvents', function(event) {
	event.preventDefault();

	Current.invoiceEventId = $(this).attr('ievent');
	var eventName = $(this).attr('i-name');
	$('#event-name-header').html(eventName);

	loadEventItemList();

	var param = {};
	param._group = "InvoiceEvent";
	param._action = "InvoiceEventGet";
	param._token = Token;
	param._user_id = UserId;
	param._invoice_event_id = Current.invoiceEventId

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			Current.waUrl = data.wa_url; // 2021-10-06
			Current.invoiceEventName = data.invoice_event_name;
			Current.invoiceEventItemStatus = data.invoice_event_status;
			Current.eventId = data.event_id;
			Current.eventAmount = data.amount;
			Current.eventAmountOn = data.amount_on;
			Current.eventRef = data.ref;
			Current.eventName = data.event_name;
			Current.invoiceEventType = data.invoice_event_type;
			CurrentAmountOn = data.amount_on;
			Current.body = data.body;
			// 2021-02-02
			Current.participantOn = data.participant_on;
			if (_.isNull(Current.body)) {
				Current.body = '';
			}
			$('#title-invoice-event-name').html(data.invoice_event_name); //  + $status);
			$('#title-event-name').html('Event: <i>' + data.event_name + '</i>'); //  + $status); //  + $status);
			if (data.inherit_event_id == '0') {
				$('#eImportModalOpen').show();
				$('#eNewInvoice').show();
			}
			else {
				$('#eImportModalOpen').hide();
				$('#eNewInvoice').hide();
			}
		}
	});
});

function loadEventItemList() {
	
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "EventItemList";
	param._token = Token;
	param._user_id = UserId;
	param._invoice_event_id = Current.invoiceEventId;
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			Current.filter = "0";
			createHtmlTableEventItems(data) ;
			$('.page-section').hide();
			$('.section-event-items').show();
		}
	});
}

function createHtmlTableEventItems(data) {

	var html = '<table class="table table-list" style="table-layout: fixed; width:100%; margin-bottom:20px; font-size: 14px;"';
	html += '<tr>';
		html += '<th >Mottagare</th>';
		html += '<th >E-post</th>';
		html += '<th >Referens</th>';
		html += '<th style="text-align:right;width:96px;padding-right:14px!important;">Belopp</th>';
		html += '<th style="width:200px">';
			html += '<div class="select">';
				html += '<select id="eFilterStatus" style="width:150px">';
					html += '<option selected value="0">Pågående</option>';
					html += '<option value="p">Utkast</option>';
					html += '<option value="a">Skickas</option>';
					html += '<option value="s">Skickade</option>';
					html += '<option value="r">Påminda</option>';
					html += '<option value="c">Hämtade</option>';
					html += '<option value="m">Stängda</option>';
					//html += '<option value="d">Medges ej</option>';
					html += '<option value="x">Stutsade</option>';
				html += '</select>';
			html += '</div>';
		html += '</th>';
		html += '<th style="width:66px"></th>';
		html += '<th style="width:66px"></th>';
		
	html += '</tr>';

	for (let i = 0; i < data.length; i++) {

		html += '<tr class="st-filter st-' + data[i].invoice_event_item_status + '" style="display:none">';

		html += '<td>' + data[i].people_name + '</td>';
		html += '<td>' + data[i].email + '</td>';
		if (data[i].referens === null) {
			data[i].referens = '';
		}
		html += '<td>'+ data[i].referens + '</td>';
	
		if (data[i].amount == 0) {
			var amount = "";
		}
		else {
			var amount = data[i].amount;
		}
		
		html += '<td style="text-align:right; padding-right:12px;">' + amount + '</td>';
		
		if (data[i].invoice_event_item_status == "p") {
			var status = "Utkast:";
			html += '<td style="color #8C4600; width:200px">' + status + ' ' + data[i].planed_date  +'</td>';
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" item-status="d" class="eDeleteInvoice button is-small"><i class="fas fa-times"></button></td>';
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" class="eOpenInvoice button is-link is-small">Öppna</button></td>';

		} 
		else if (data[i].invoice_event_item_status == "a") {
		
			var status = "Skickas:";
			html += '<td style="color: #8B0000; width:200px">' + status + ' ' + data[i].planed_date  + '</td>';
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" item-status="d" class="eDeleteInvoice button is-small"><i class="fas fa-times"></button></td>';
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" class="eOpenInvoice button is-link is-small">Öppna</button></td>';

		} 
		else if (data[i].invoice_event_item_status == "s") {
			var status = "Skickad:";
			html += '<td style="color: #006500; width:200px">' + status + ' ' + data[i].sent_datetime.substr(0, 10) + ' </td>';
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" item-status="m" class="eDeleteInvoice button is-small"><i class="fas fa-times"></button></td>';
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" class="eOpenInvoice button is-link is-small">Öppna</button></td>';

		} 
		else if (data[i].invoice_event_item_status == "c") {
			var status = "Hämtad:"; // Godkänd
			html += '<td style="color: #008C8C; width:200px">'+ status + ' ' +data[i].confirmed_datetime.substr(0, 10)  + '</td>';
			html += '<td style="width:66px"></td>';
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" class="eOpenInvoice button is-link is-small">Öppna</button></td>';

			//var color = 'green'; #1B4D3E
		}
		else if (data[i].invoice_event_item_status == "r") {
			var status = "Påmind";
			html += '<td style="color: #8B0000; width:200px">'+ status + ' ' +data[i].reminder_last_datetime.substr(0, 10)  + '</td>';
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" item-status="m" class="eDeleteInvoice button is-small"><i class="fas fa-times"></button></td>';
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" class="eOpenInvoice button is-link is-small">Öppna</button></td>';

			//var color = 'yellow';
		}
		else if (data[i].invoice_event_item_status == "m") {
			var status = 'Stängd';
			html += '<td style="width:66px"></td>';
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" class="eOpenInvoice button is-link is-small">Öppna</button></td>';

		}
		else if (data[i].invoice_event_item_status == "x") {
			var status = "Studsad";
			html += '<td style="width:66px"></td>';
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" class="eOpenInvoice button is-link is-small">Öppna</button></td>';

		}
		else if (data[i].invoice_event_item_status == "d") {
			var status = 'Medges ej';
			html += '<td style="width:66px"></td>';
		}

		html += '</tr>';
	}
	html += '</table>';
	$('#event-items-list').html(html);
	if (Current.filter == '0') {
		$('.st-a').show();
		$('.st-p').show();
		$('.st-s').show();
		$('.st-r').show();
	} 
	else {
		$('.st-' + Current.filter).show();
	}
	$('#eFilterStatus').val( Current.filter);
	$('.EventItemComplete').hide();
}

$(document).on('change', '#eFilterStatus', function(event) {
	var filter = $(this).val();
	$('.st-filter').hide();
	if (filter == '0') {
		$('.st-p').show();
		$('.st-a').show();
		$('.st-s').show();
		$('.st-r').show();
	}
	else {
		$('.st-' + filter).show();
	}
	Current.filter = filter;
});

// -- NEV INVOICE
$(document).on('click', '#eNewInvoice', function(event) {
	event.preventDefault();
	
	$('.check-reminder-all').hide();
	$('.check-send-all').hide();
	$('.invoice-status-modal').hide('');

	Current.invoiceEventItemId = 0;
	Current.invoiceEventItemStatus = 'a';

	$('.check-start').show();
	$('.col-reminder').show();
	$('.col-planed-date').show();
	$('.col-send-date').hide();
	$('.col-sent-date').hide();
	$('.col-reminder-next-date').hide();
	$('.col-reminder-last-datetime').hide();
	$('.col-confirmed').hide();
	$('.col-empty').show();
	$('.col-empty').show();
	$('.col-empty2').show();
	$('.col-remider').show();
	$('.col-close-item').hide();
	
	//$('#eUpdateInvoiceItemModal').html('Test'); // Vad
	$('#eSaveInvoiceItemModal').hide();
	$('#eUpdateInvoiceItemModal').hide();
	$('#eAddInvoiceItemModal').show();
	$('#eSaveInvoiceItemAsDraftModal').show();

	$('.required').show();

	$('#invoice-people-name').val('');
	$('#invoice-email').val('');
	$('#invoice-referens').val('');

	$('#invoice-planed-date').val('');
	$('#invoice-people-name').prop('disabled', false);
	$('#invoice-email').prop('disabled', false);

	if (Current.eventAmountOn == 'n' ) { 
		$('#invoice-amount').hide();
		$('#invoice-amount-label').hide();
	}

	if (_.isNull(Current.eventAmount) || Current.eventAmount.length == 0) {
		$('#invoice-amount').val('');
		$('#invoice-amount').prop('disabled', false);
	}
	else {
		$('#invoice-amount').val(Current.eventAmount);
		$('#invoice-amount').prop('disabled', true);
	}

	// 2021-02-02
	if (Current.participantOn == 'n') {
		$('#invoice-amount').prop('disabled', false);
	}


	if (_.isNull(Current.eventRef) || Current.eventRef.length == 0) {
		$('#invoice-referens').val(Current.eventRef);
		$('#invoice-referens').prop('disabled', false);
	}
	else {
		$('#invoice-referens').val(Current.eventRef);
		$('#invoice-referens').prop('disabled', true);
	}
	

	/*
		if (Current.eventRef.length > 0) {
			$('#invoice-referens').val(Current.eventRef);
			$('#invoice-referens').prop('disabled', true);
		} 
		else {
			$('#invoice-referens').val('');
			$('#invoice-referens').prop('disabled', false);
		}
		if (Current.eventAmount.length  > 0) {
			$('#invoice-amount').val(Current.eventAmount);
			$('#invoice-amount').prop('disabled', true);
		} 
		else {
			$('#invoice-amount').val('');
			$('#invoice-amount').prop('disabled', false);
		}
	*/

	var currentDate = new Date();
	var nowDateString = currentDate.toISOString().substring(0, 10);
	$('#invoice-planed-date').val(nowDateString);
	$('#invoice-planed-date').prop('disabled', false);

	// // Current.eventAmount = "500";
	//Current.eventRef = "Ölresan nummer 2";

	
	if (Current.eventAutoReminder == 'y') {
		$('#invoice-auto-reminder').prop('checked', true);
		$('#invoice-reminder-days-container').show();
		$('#invoice-reminder-times-container').show();
		$('#invoice-reminder-days').val(Current.eventReminderDays);
		$('#invoice-reminder-times').val(Current.eventReminderTimes);
		$('#invoice-reminder-next-date').hide();
	}
	else {
		$('#invoice-auto-reminder').prop('checked', false);
		$('.reminder-container').hide();
		$('#invoice-reminder-days').val(Current.eventReminderDays);
		$('#invoice-reminder-times').val(Current.eventReminderTimes);
		$('#invoice-reminder-days').val(Current.eventReminderDays);
		$('#invoice-reminder-times').val(Current.eventReminderTimes);
	}

	$('#invoice-reminder-all').show();
	$('#invoice-send-all').show();
	$('#invoice-reminder-all').prop('checked', false);
	$('#invoice-send-all').prop('checked', false);

	$('#invoice-item-modal').addClass('is-active');
});

$(document).on('change', '#invoice-auto-reminder', function(event) {
	event.preventDefault();
	if(this.checked) {
		if (Current.invoiceEventItemStatus == "s" || Current.invoiceEventItemStatus == "r") {
			if (Current.invoiceEventItemStatus == "s") {
				var sentDate = $('#invoice-sent-datetime').val();
				sentDate = sentDate.substr(0,10);
			} 
			else {
				var sentDate = Current.reminderLastDate;
			}
			Current.reminderLastDate = sentDate;
			var now = new Date();
			var date = new Date(sentDate);
			date = date.setDate(date.getDate() + Number(Current.eventReminderDays));
			var now = new Date();
			if (now > date) { 
				$('#invoice-reminder-next-date').val(formatDate(now));
			}
			else {
				$('#invoice-reminder-next-date').val(formatDate(date));
			}
			$('#invoice-reminder-days').val(Current.eventReminderDays);
			$('#invoice-reminder-times').val(Current.eventReminderTimes);
			Current.reminderTimes = Current.eventReminderTimes;
		}
		else {
			$('#invoice-label-reminder-next-date').hide();
			$('#invoice-reminder-next-date').hide();
			$('#invoice-reminder-days').val(Current.eventReminderDays);
			$('#invoice-reminder-times').val(Current.eventReminderTimes);
		}
		$('#invoice-auto-reminder').prop('checked', true);
		$('.reminder-container').show();
		
	}
	else {
		$('#invoice-auto-reminder').prop('checked', false);
		$('.reminder-container').hide();
		$('#invoice-reminder-days').val(Current.eventReminderDays);
		$('#invoice-reminder-times').val(Current.eventReminderTimes);
	}   


	if($('#eSaveInvoiceItemModal').is(':visible')){
	}
	else {

		// $('#eUpdateInvoiceItemModal').show()
	}
});

$('#invoice-reminder-days').on('change', function() {
	var times = $('#invoice-reminder-times').val();
	if (Number(times) > 0) {
		var days = $(this).val();
		//alert(Current.reminderLastDate);
		if (Current.invoiceEventItemStatus == "s" || Current.invoiceEventItemStatus == "r") {
			if (Current.reminderLastDate == null ) {
				var lastDate = $('#invoice-sent-datetime').val();
			}
			else {
				var lastDate = Current.reminderLastDate;
			}
			var now = new Date();
			var date = new Date(lastDate);
			date = date.setDate(date.getDate() + Number(days)); // Number(days));
			if (now > date) { 
				$('#invoice-reminder-next-date').val(formatDate(now));
			}
			else {
				$('#invoice-reminder-next-date').val(formatDate(date));
			}
		}	
	} 
	if($('#eSaveInvoiceItemModal').is(':visible')){
	}
	else {
		//$('#eUpdateInvoiceItemModal').show()
	}
});

$('#invoice-reminder-times').on('change', function() {

	var times = $(this).val();
	if (Number(times) == 0) {
		Current.reminderLastDate == null;
		$('#invoice-reminder-next-date').val('');
	}
	else {
		var days = $('#invoice-reminder-days').val();
		if (Current.invoiceEventItemStatus == "s" || Current.invoiceEventItemStatus == "r") {
			if (Current.reminderLastDate == null ) {
				var lastDate = $('#invoice-sent-datetime').val();
			}
			else {
				var lastDate = Current.reminderLastDate;
			}
			var date = new Date(lastDate);
			date = date.setDate(date.getDate() + Number(days)); // Number(days)); 
			var now = new Date();
			if (now > date) { 
				$('#invoice-reminder-next-date').val(formatDate(now));
			}
			else {
				$('#invoice-reminder-next-date').val(formatDate(date));
			}
			//var date = new Date(lastDate);
			//date = date.setDate(date.getDate() + Number(days)); // Number(days)); 
			//$('#invoice-reminder-next-date').val(formatDate(date));
		}	
	}
	//Current.reminderTimes = times;
	if($('#eSaveInvoiceItemModal').is(':visible')){
	}
	else {
		//$('#eUpdateInvoiceItemModal').show()
	}
});

$(document).on('change', '#invoice-item-close', function(event) {
	if($('#eSaveInvoiceItemModal').is(':visible')){
	}
	else {
		$('#eUpdateInvoiceItemModal').show()
	}
});

function calculateNextReminder(reminderDays, reminderTimes, lastRemiderDate = null) {	
}

$(document).on('click', '#eCloseInvoiceItemModal', function(event) {
	event.preventDefault();
	$('#invoice-item-modal').removeClass('is-active');
});

$(document).on('click', '.eOpenInvoice', function(event) {
	event.preventDefault();
	Current.invoiceEventItemId = $(this).attr('item-id');
	
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "ItemGet";
	param._token = Token;
	param._user_id = UserId;
	param._item_id = Current.invoiceEventItemId;
	
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			Current.invoiceEventItemStatus = data.invoice_event_item_status;
		
			$('#invoice-people-name').val(data.people_name);
			$('#invoice-email').val(data.email);
			$('#invoice-referens').val(data.referens);
			$('#invoice-spec').val(data.spec);
			

			if (Current.eventAmountOn == 'n' ) { 
				$('#invoice-amount').hide();
				$('#invoice-amount-label').hide();
			}


			if (data.amount > '0.00') {
				$('#invoice-amount').val(data.amount);
			}
			else {
				$('#invoice-amount').val('');
			}
			
			
			$('#invoice-planed-date').val(data.planed_date);
			
			$('#ePreviewInvoiceItemModal').hide(); // 2021-10-06
			
			if (data.invoice_event_item_status == 'p' || data.invoice_event_item_status == 'a') {

				$('.check-reminder-all').show();
				$('.check-send-all').show();

				if (data.invoice_event_item_status == 'p') {
					//$('#invoice-status-modal').html('Utkast');
					$('#label-send-all-status').html('Utkast');
					$('#label-reminder-all-status').html('Utkast');
				}
				else {
					//$('#invoice-status-modal').html('Skickas');
					$('#label-send-all-status').html('Skickas');
					$('#label-reminder-all-status').html('Skickas');
				}

				$('#eInvoiceGetTab').show();
				$('.check-start').show();
				$('.col-reminder').show();
				$('.col-planed-date').show();
				$('.col-send-date').hide();
				$('.col-sent-date').hide();
				$('.col-reminder-next-date').hide();
				$('.col-reminder-last-datetime').hide();
				$('.col-confirmed').hide();
				$('.col-empty').show();
				$('.col-empty2').show();
				$('.col-remider').show();
				$('.col-close-item').hide();
				$('#invoice-label-reminder-next-date').hide();
				$('#invoice-reminder-next-date').hide();
				
				//$('#eUpdateInvoiceItemModal').html('Skicka');
				$('#eSaveInvoiceItemModal').hide();
				$('#eUpdateInvoiceItemModal').show();
				$('#eAddInvoiceItemModal').hide();
				$('#eSaveInvoiceItemAsDraftModal').show();
			
				$('.required').show();

				$('#invoice-reminder-all').show();
				$('#invoice-send-all').show();
				$('#invoice-reminder-all').prop('checked', false);
				$('#invoice-send-all').prop('checked', false);

				$('#invoice-draft').prop('checked', false);

				if (data.invoice_event_item_status == 'p') {
					$('#invoice-draft').prop('checked', true);
				}
				else {
					$('#invoice-draft').prop('checked', false);
				}
				$('#invoice-label-sent-datetime').hide();
				$('#invoice-sent-datetime').hide();
				$('#invoice-sent-datetime').val('');
				
				if (data.auto_reminder == 'y') {
					$('#invoice-auto-reminder').prop('checked', true);					
					$('#invoice-reminder-days').val(data.reminder_days);
					$('#invoice-reminder-times').val(data.reminder_times);
					$('.reminder-container').show();
				}
				else {
					$('#invoice-auto-reminder').prop('checked', false);
					$('.reminder-container').hide();
					$('#invoice-reminder-days').val(Current.eventReminderDays);
					$('#invoice-reminder-times').val(Current.eventReminderTimes);
					//$('#invoice-reminder-next-date').val();
				}

				$('#invoice-label-confirmed-datetime').hide();
				$('#invoice-confirmed-datetime').hide();
    			$('#invoice-confirmed-datetime').val('');
				
				$('#invoice-people-name').prop('disabled', false);
				$('#invoice-email').prop('disabled', false);

				if (data.amount == 0) {
					$('#invoice-amount').val('');
				}
				else {
					$('#invoice-amount').val(data.amount);
				}

				if (_.isNull(Current.eventAmount) || Current.eventAmount.length == 0) {
					$('#invoice-amount').prop('disabled', false);
				}
				else {
					$('#invoice-amount').prop('disabled', true);
				}

				// 2021-02-02
				if (Current.participantOn == 'n') {
					$('#invoice-amount').prop('disabled', false);
				}

				if (data.referens.length > 0) {
					$('#invoice-referens').val(data.referens);
				}
				else {
					$('#invoice-referens').val('');
				}

				if (_.isNull(Current.eventRef) || Current.eventRef.length == 0) {
					$('#invoice-referens').prop('disabled', false);
				}
				else {
					$('#invoice-referens').prop('disabled', true);
				}

				$('#invoice-planed-date').prop('disabled', false);
			}

			else if (data.invoice_event_item_status == 's' || data.invoice_event_item_status == 'r') {

				//$('.check-reminder-all').show();
				$('.check-send-all').hide();
				$('.check-reminder-all').show();
				if (data.invoice_event_item_status == 's') {
					$('#label-reminder-all-status').html('Skickad');
					//$('#eSaveInvoiceItemModal').attr("status", 's');
				}
				else {
					$('#label-reminder-all-status').html('Påmind');
					//$('#eSaveInvoiceItemModal').attr("status", 'r');
				}

				$('#eInvoiceGetTab').show();
				$('.check-start').hide();
				$('.col-reminder').show();
				$('.col-planed-date').hide();
				$('.col-sent-date').show();
				$('.col-reminder-next-date').show();
				$('.col-reminder-last-datetime').hide();
				$('.col-confirmed').hide();
				$('.col-empty').show();
				$('.col-empty2').hide();
				$('.col-remider').show();
				$('.col-close-item').show();
				$('#invoice-label-reminder-next-date').show();
				$('#invoice-reminder-next-date').show();

				$('#eUpdateInvoiceItemModal').hide();
				$('#eSaveInvoiceItemModal').show();
				$('#eAddInvoiceItemModal').hide();
				$('#eSaveInvoiceItemAsDraftModal').hide();

				$('.required').hide();
				//$('#invoice-reminder-all').hide();
				$('#invoice-send-all').hide();
				$('#invoice-people-name').prop('disabled', true);
				// $('#invoice-email').prop('disabled', true); 20210812
				$('#invoice-referens').prop('disabled', true);
				$('#invoice-spec').prop('disabled', true);
				$('#invoice-amount').prop('disabled', true);
			
				$('#invoice-sent-datetime').val(data.sent_datetime.substr(0,10));
				$('#invoice-sent-datetime').prop('disabled', true);
				
				$('#invoice-item-close').prop('checked', false);
				$('#invoice-reminder-next-date').prop('disabled', true);

				Current.sendDate = data.sent_datetime.substr(0, 10);
				
				if (data.auto_reminder == 'y') {
					$('#invoice-auto-reminder').prop('checked', true);					
					$('#invoice-reminder-days').val(data.reminder_days);
					$('#invoice-reminder-times').val(data.reminder_times);
					if (data.reminder_times == '0') {
						$('#invoice-reminder-next-date').val('');
					}
					else {
						$('#invoice-reminder-next-date').val(data.reminder_next_date);
					}
					$('.reminder-container').show();
				}
				else {
					$('#invoice-auto-reminder').prop('checked', false);
					$('.reminder-container').hide();
					$('#invoice-reminder-days').val(Current.eventReminderDays);
					$('#invoice-reminder-times').val(Current.eventReminderTimes);
					$('#invoice-reminder-next-date').val('');
				}

				if (data.invoice_event_item_status == "r") {
					$('#invoice-reminder-last-datetime').val(data.reminder_last_datetime.substr(0,10));
					$('#invoice-reminder-last-datetime').prop('disabled', true);
					$('.col-reminder-last-datetime').show();
					Current.reminderLastDate = data.reminder_last_datetime.substr(0,10);
				} 
				else {
					$('.col-empty').show();
					Current.reminderLastDate = null;
				}
				
					$('#ePreviewInvoiceItemModal').attr('code', data.invoice_event_item_code); // 2021-10-06
				$('#ePreviewInvoiceItemModal').show(); // 2021-10-06
				
			}
			else if (data.invoice_event_item_status == 'c' || data.invoice_event_item_status == 'm') {

				$('.check-reminder-all').hide();
				$('.check-send-all').hide();

				$('#eInvoiceGetTab').hide();
				$('.check-start').hide();
				$('.col-reminder').hide();
				$('.col-planed-date').hide();
				
				$('.col-reminder-next-date').hide();
				$('.col-reminder-last-datetime').hide();
				$('.col-confirmed').show();
				$('.col-empty').show();
				$('.col-empty2').hide();
				$('.col-remider').hide();
				if (data.invoice_event_item_status == 'm') {
					$('#invoice-item-close').prop('checked', true);
					$('.col-close-item').show();
					$('.col-sent-date').hide();
					$('.col-confirmed').hide();
				}
				else {
					$('.col-close-item').hide();
					$('.col-sent-date').show();
					$('.col-confirmed').show();
				}
				$('#invoice-label-reminder-next-date').hide();
				$('#invoice-reminder-next-date').hide();
				$('.reminder-container').hide();
				
				$('#eSaveInvoiceItemModal').hide();
				$('#eUpdateInvoiceItemModal').hide();

				$('#eSaveInvoiceItemAsDraftModal').hide();

				$('.required').hide();
				$('#invoice-reminder-all').hide();
				$('#invoice-send-all').hide();

				$('#invoice-people-name').prop('disabled', true);
				$('#invoice-email').prop('disabled', true);
				$('#invoice-referens').prop('disabled', true);
				$('#invoice-spec').prop('disabled', true);
				$('#invoice-amount').prop('disabled', true);
				$('#invoice-planed-date').prop('disabled', true);
				
				if (data.invoice_event_item_status == 'c') {
					$('#invoice-sent-datetime').val(data.sent_datetime.substr(0,10));
					$('#invoice-sent-datetime').prop('disabled', true);

					$('#invoice-confirmed-datetime').val(data.confirmed_datetime.substr(0,10));
					$('#invoice-confirmed-datetime').prop('disabled', true);
				}
			}
			$('#eAddInvoiceItemModal').hide();
			$('#invoice-item-modal').addClass('is-active');
		}
	});
});

// 2021-10-06
$(document).on('click', '#ePreviewInvoiceItemModal', function(event) {
	var path = Site + Current.waUrl + '/?f=' + $('#ePreviewInvoiceItemModal').attr('code');
	var win = window.open(path, '_blank');
	win.focus();
});

$(document).on('click', '#eBackinvoiceEventList', function(event) {
	location.reload();
});

$(document).on('click', '#eAddInvoiceItemModal', function(event) {
	event.preventDefault();
	updateInvoiceItem('a');
});

$(document).on('click', '#eSaveInvoiceItemAsDraftModal', function(event) {
	event.preventDefault();
	updateInvoiceItem('p');
});

$(document).on('click', '#eSaveInvoiceItemModal', function(event) {
	event.preventDefault();
	var invoiceEventItemstatus = Current.invoiceEventItemStatus;
	updateInvoiceItem(invoiceEventItemstatus);
});

$(document).on('click', '#eUpdateInvoiceItemModal', function(event) {
	event.preventDefault();
	var today = Helper.getDate();
	var planedDate = $('#invoice-planed-date').val();
	
	//alert(today + " " + planedDate);
	
	if ($('#invoice-send-all').is(':checked') && planedDate <= today) {

		var param = {};
		param._group = "InvoiceEvent";
		param._action = "GetMailCounter";
		param._token = Token;
		param._user_id = UserId;
		param._invoice_event_id = Current.invoiceEventId
		param._planed_date = planedDate;
		param._invoice_event_item_status = Current.invoiceEventItemStatus;
		$.ajax({ type: "POST", url: 'service2/', data: param,
			success: function(result) {
				var data = jQuery.parseJSON(result);
			
				if (data.counter > 0) {
					var text = data.counter + ' st e-post meddelande kommer nu att skickas?';
					$('#yesno-text-modal').html(text);
					$('#yesno-modal').addClass('is-active');
				}
			}
		});
	}
	else {
		updateInvoiceItem('a');
	}
		
});

$(document).on('click', '#eYesNoModalNo', function(event) {
	event.preventDefault();
	$('#eMessageModalClose').show();
	$('#yesno-modal').removeClass('is-active');
});

$(document).on('click', '#eYesNoModalYes', function(event) {
	event.preventDefault();
	$('#yesno-modal').removeClass('is-active');
	$('#message-text-modal').html('Mailutskick pågår var god vänta!');
	$('#eMessageModalClose').hide();
	$('#message-modal').addClass('is-active');
	updateInvoiceItem('a');
});

function updateInvoiceItem(invoiceEventItemStatus) {

	var param = {};
	param._group = "InvoiceEvent";
	param._action = "ItemUpdate";
	param._token = Token;
	param._user_id = UserId;
	param._invoice_event_item_id = Current.invoiceEventItemId; // Zero if new
	param._invoice_event_id = Current.invoiceEventId;
	param._current_invoice_event_item_status = Current.invoiceEventItemStatus;

	//alert(invoiceEventItemStatus);

	if (Current.invoiceEventItemId == '0') {
		param.event_id = Current.eventId;
		param.invoice_event_id = Current.invoiceEventId;
	}
	
	var email = $('#invoice-email').val();
	var referens = $('#invoice-referens').val();
	var spec = $('#invoice-spec').val();
	var amount = $('#invoice-amount').val();
	amount = amount.trim();
	if (amount.length == 0) {
		amount = '0';
	}

	var planedDate = $('#invoice-planed-date').val();

	if (email.length < 5) {
		$('#message-text-modal').html('E-postadress är inte giltigt.');
		$('#eMessageModalClose').show();
		$('#message-modal').addClass('is-active');
		return;
	}
	if (Helper.validateEmail(email) == false) {
		$('#message-text-modal').html('E-postadress är inte giltigt.');
		$('#eMessageModalClose').show();
		$('#message-modal').addClass('is-active');
		return;
	}
	
	if (invoiceEventItemStatus == 'a' && Current.body.length < 1 ) {
		$('#message-text-modal').html('E-post meddelande är inte komplett.');
		$('#eMessageModalClose').show();
		$('#message-modal').addClass('is-active');
		return;
	}
	
	/*
	if (amount.length == 0 || isNaN(amount)) {
		$('#message-text-modal').html('Belopp måste vara numeriskt.');
		$('#message-modal').addClass('is-active');
		return;
	}
	*/	
	param.people_name = $('#invoice-people-name').val();
	param.email = email;
	param.referens = referens;
	param.amount = amount;
	param.invoice_event_item_status = invoiceEventItemStatus;
	//alert(invoiceEventItemStatus);
	if (invoiceEventItemStatus == 'a' || invoiceEventItemStatus == 'p' || invoiceEventItemStatus == 'n') {		
		param.invoice_event_item_status = invoiceEventItemStatus;
		if ($('#invoice-reminder-all').is(':checked')) {
			param._invoice_reminder_all = 'y';
		}
		else {
			param._invoice_reminder_all = 'n';
		}
		// if ($('#invoice-send-all').is(':checked')) {
		if ($('#invoice-send-all').is(':checked')) {
			param._invoice_send_all = 'y';
		}
		else {
			param._invoice_send_all = 'n';
		}
		param.planed_date = planedDate;
	}
	else {
		
		// When edit after after status
		// param._invoice_reminder_all = 'n';
		// param._invoice_send_all = 'n';
	}

	if (invoiceEventItemStatus == 'a' || invoiceEventItemStatus == 'p') {
		if ($('#invoice-auto-reminder').is(':checked')) {
			param.auto_reminder = 'y';
			param.reminder_days = $('#invoice-reminder-days').val();
			param.reminder_times = $('#invoice-reminder-times').val();
			//param.reminder_next_date = $('#invoice-reminder-next-date').val();
		}
		else {
			param.auto_reminder = 'n';
			param.reminder_days = '0';
			param.reminder_times = '0';
		}
	}
	else if(Current.invoiceEventItemStatus== 's' || Current.invoiceEventItemStatus == 'r') {
			//if (param.reminder_times != '0') {
			//param.reminder_next_date = $('#invoice-reminder-next-date').val();
			//alert($('#invoice-reminder-next-date').val());
		if ($('#invoice-auto-reminder').is(':checked')) {
			param.auto_reminder = 'y';
			param.reminder_days = $('#invoice-reminder-days').val();
			param.reminder_times = $('#invoice-reminder-times').val();
			//-- Fix 2020-06-30
			// param._invoice_reminder_all = 'y';
			if ($('#invoice-reminder-all').is(':checked')) {
				param._invoice_reminder_all = 'y';
			}
			else {
				param._invoice_reminder_all = 'n';
			}
			//-- 2020-06-30 update
			if (param.reminder_times > 0) {
				param.reminder_next_date = $('#invoice-reminder-next-date').val();
			}
		}
		else {
			//-- Fix 2020-06-30
			//param._invoice_reminder_all = 'n';
			if ($('#invoice-reminder-all').is(':checked')) {
				param._invoice_reminder_all = 'y';
			}
			else {
				param._invoice_reminder_all = 'n';
			}
			//--
			param.auto_reminder = 'n';
			param.reminder_days = '0';
			param.reminder_times = '0';
		}
	}
	// --alert( param._invoice_reminder_all);
	// --return;

	//console.log(param);
	//return;

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			$('#message-modal').removeClass('is-active');
			$('#eMessageModalClose').show();
			$('#invoice-item-modal').removeClass('is-active');
			loadEventItemList();
		}
	});

	$('#invoice-item-modal').removeClass('is-active');
}

$(document).on('click', '.eDeleteInvoice', function(event) {
	event.preventDefault();
	Current.invoiceEventItemId = $(this).attr('item-id');
	Current.invoiceEventItemStatus = $(this).attr('item-status');
	//$('#remove-item-modal-text').html(itemName);
	$('#remove-item-modal').addClass('is-active');

});

$(document).on('click', '#eCloseRemoveItemModal', function(event) {
	event.preventDefault();
	$('#remove-item-modal').removeClass('is-active');
});

$(document).on('click', '#eRemoveItemModal', function(event) {
	event.preventDefault();
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "ItemRemove";
	param._token = Token;
	param._user_id = UserId;
	param._invoice_event_item_id = Current.invoiceEventItemId; 
	param._status = Current.invoiceEventItemStatus;
	
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			loadEventItemList();
			$('#remove-item-modal').removeClass('is-active');
		}
	});
});

function loadCustomerList() {
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "CustomerList";
	param._token = Token;
	param._user_id = UserId;
	
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
		
			data = jQuery.parseJSON(result);
			var html = '<table class="table" style="table-layout: fixed; width:100%; margin-bottom:20px; font-size: 14px;"';
			html += '<tr>';
				html += '<th style="text-align:left; background-color: #ffffff;">Namn</th>';
				html += '<th style="text-align:left; background-color: #ffffff; ">Adress</th>';
				html += '<th style="width:9%; background-color: #ffffff; "></th>';	
			html += '</tr>';

			for (let i = 0; i < data.length; i++) {
				html += '<tr class="no-uborder eSelectPeople" people-id="' + data[i].people_id + '" index="' + i + '" style="cursor:pointer">';
					html += '<td style="vertical-align:middle; font-weight: bold;padding-bottom:0">' + data[i].last_name + ', ' + data[i].first_name + '</td>';
					html += '<td style="vertical-align:middle; font-size:12px; padding-bottom:0">' + data[i].address + '</td>';
					//html += '<td rowspan="2" style="width:9%; text-align:right"> <button people-id="' + data[i].people_id + '" pname="' + data[i].last_name + ', ' + data[i].first_name + '" pmail="' + data[i].email + '" class="eSelectPeople button is-dark is-small">Välj</button> </td>';
				html += '</tr>';
				html += '<tr class="eSelectPeople" people-id="' + data[i].people_id + '" index="' + i + '" style="cursor:pointer">';
					html += '<td style="vertical-align:middle;padding-top:0;">' + data[i].email + '</td>';
					html += '<td style="vertical-align:middle; font-size:12px;padding-top:0;">' + data[i].postcode + ' ' +  data[i].city + '</td>';
					//html += '<td style="width:9%; text-align:right"> <button people-id="' + data[i].people_id + '" pname="' + data[i].people_name + '" pmail="' + data[i].email + '" class="eSelectPeople button is-dark is-small">Välj</button> </td>';
				html += '</tr>';
			}
			html += '</table>';
			CustomerListIsLoaded  = true;
			$('#customer-list').html(html);
			MottagareLista = data;
		}
	});
}

$(document).on('click', '#eInvoiceGetTab', function(event) {
	event.preventDefault();
	$('#title-invoice-item-modal').html('Hämta mottagare');
	if (CustomerListIsLoaded == false) {
		loadCustomerList();
	}
	$('#ItemTab').hide();
	$('#GetTab').show();

	$('#eCloseInvoiceItemModal').hide();
    $('#eSaveInvoiceItemAsDraftModal').hide();
    $('#eAddInvoiceItemModal').hide();
    $('#eUpdateInvoiceItemModal').hide(); 
    $('#eInvoiceItemTab').show();

});

$(document).on('click', '#eInvoiceItemTab', function(event) {
	event.preventDefault();
	$('#title-invoice-item-modal').html('Mottagare i utskick');
	$('#GetTab').hide();
	$('#ItemTab').show();
	if (Current.invoiceEventItemId == 0) {
		$('#eUpdateInvoiceItemModal').hide();
	}
	else {
		$('#eSaveInvoiceItemModal').hide();
	}

	$('#eCloseInvoiceItemModal').show();
    $('#eSaveInvoiceItemAsDraftModal').show();
    $('#eAddInvoiceItemModal').show();
    $('#eInvoiceItemTab').hide();

	/*
	if ($('#invoice-auto-reminder').is(':checked'))  {
		$('.reminder-container').show();
	}
	else {
		$('.reminder-container').hide();
	} 
	*/  
});

$(document).on('click', '.eSelectPeople', function(event) {
	event.preventDefault();

	Current.peopleId = $(this).attr('people-id'); // Only set when get earlier
	var index = $(this).attr('index');
	var peopleName = MottagareLista[index].last_name + ', ' + MottagareLista[index].first_name;
	var peopleEmail =  MottagareLista[index].email;
	$('#invoice-people-name').val(peopleName);
	$('#invoice-email').val(peopleEmail);
	
	$('#title-invoice-item-modal').html('Mottagare i utskick');
	$('#GetTab').hide();
	$('#ItemTab').show();
	if (Current.invoiceEventItemId == 0) {
		$('#eUpdateInvoiceItemModal').hide();
	}
	else {
		$('#eSaveInvoiceItemModal').hide();
	}

	$('#eCloseInvoiceItemModal').show();
    $('#eSaveInvoiceItemAsDraftModal').show();
    $('#eAddInvoiceItemModal').show();
    $('#eInvoiceItemTab').hide();


});

$(document).on('click', '#eImportModalOpen', function(event) {
	event.preventDefault();
	$('#import-area').val('');
	$('#import-preview-list').val('');
	$('#import-preview-error-list').val('');
	$('#eImportModal').hide();
	$('.cut-in-step-1').hide();
	$('.cut-in-step-2').hide();
	$('.import-part-recent').hide();
	$('#eImportPreviewModal').hide();
	$('.import-main').show();
	$('#import-modal').addClass('is-active');
});

$(document).on('click', '#eImportPartCutIn', function(event) {
	event.preventDefault();
	$('.import-main').hide();
	$('.cut-in-step-1').show();
	$('#eImportPreviewModal').show();
});

$(document).on('click', '#eImportPartRecent', function(event) {
	event.preventDefault();
	$('.import-main').hide();
	$('#ddImportInvoiceEventList').empty();
	var list = $("#ddImportInvoiceEventList");
	
	$.each(InvoiceEventList, function(index, item) {
		  list.append(new Option(item.invoice_event_name, item.invoice_event_id));
	});
	$("#ddImportInvoiceEventList").val($("#ddImportInvoiceEventList option:first").val());
	
	$('.import-part-recent').show();
	//$('#eImportPreviewModal').show();
});

$(document).on('click', '#eCloseImportModal', function(event) {
	event.preventDefault();
	/*
	if($('.cut-in-step-1').is(":visible")) {
		$('.cut-in-step-1').hide();
		$('#import-area').val('');
		$('#import-modal').removeClass('is-active');
	}
	else if ($('.cut-in-step-2').is(":visible")) {
		$('.cut-in-step-2').hide();
		$('.cut-in-step-1').show();
	}
	else if ($('.import-part-recent').is(":visible")) {
		$('.import-part-recent').hide();
		$('.import-main').show();
	}
	else {
		*/
		$('#import-area').val('');
		$('#import-modal').removeClass('is-active');
	//}
});

$(document).on('click', '#eImportPreviewModal', function(event) {
	event.preventDefault();
	var importArea = $('#import-area').val();
	var delimiter = document.querySelector('input[name="delimiter"]:checked').value;
	
	if (delimiter == 'comma') {
		emails = importArea.split(',');
		//alert('Komma');
	}
	else if (delimiter == 'semi') {
		emails = importArea.split(';');
		//alert('semi');
	}
	// line excel
	else {
		emails = importArea.split('\n');
		//alert('Excel');
	}
	let specialChar = '";:()&+<>/[]!';
	for (var i=0; i<emails.length; i++) {
		emails[i] = emails[i].trim();
		while(specialChar.includes(emails[i][0])) {
			emails[i] = emails[i].substring(1);
		}
		while(specialChar.includes(emails[i][emails[i].length-1])) {
			emails[i] = emails[i].slice(0, -1);
		}	
	}
	$('.cut-in-step-1').hide();
	var importPreviewList = '';
	var previewErrorList = '';
	ImportEmails = Array();
	for (var i=0; i<emails.length; i++) {
		if (Helper.validateEmail(emails[i])) {
			importPreviewList += emails[i] + "\n";
			ImportEmails.push(emails[i]);
		}
		else {
			previewErrorList += emails[i] + "\n";
		}
	}
	
	$('#import-preview-list').val(importPreviewList);
	$('#import-preview-error-list').val(previewErrorList);
	$('.cut-in-step-2').show();
	$('#eImportPreviewModal').hide();
	$('#eImportModal').show();
});

$(document).on('click', '#eImportModal', function(event) {
	event.preventDefault();
	
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "EventImportCutIn";
	param._token = Token;
	param._user_id = UserId;
	
	param.invoice_event_id = Current.invoiceEventId; 
	param.event_id = Current.eventId; 
	param.importData = ImportEmails;
	if (!_.isNull(Current.eventAmount)) {
		param._amount = Current.eventAmount;
	}
	if (!_.isNull(Current.eventRef)) {
		param._ref = Current.eventRef;
	}
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			//alert(result);
			var data = jQuery.parseJSON(result);
			loadEventItemList();
			$('#message-text-modal').html(data.imported_number + ' st. importerade e-postadresser');
			$('#import-modal').removeClass('is-active');
			$('#message-modal').addClass('is-active');
		}
	});
});

$(document).on('click', '#eImportRecentModal', function(event) {
	event.preventDefault();
	var invoiceEventId = $('#ddImportInvoiceEventList').val();
	
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "ImportFromOld";
	param._token = Token;
	param._user_id = UserId;
	param.invoice_event_id = Current.invoiceEventId; 
	param.event_id = Current.eventId; 
	param.invoice_event_id_from = invoiceEventId; 
	if ($('#import-referense').is(':checked')) {
		param._ref_on = 'y';
	}
	else {
		param._ref_on = 'n';
	}
	if (!_.isNull(Current.eventAmount)) {
		param._amount = Current.eventAmount;
	}
	if (!_.isNull(Current.eventRef)) {
		param._ref = Current.eventRef;
	}
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			//alert(result);
			var data = jQuery.parseJSON(result);
			loadEventItemList();
			$('#message-text-modal').html(data.imported_number + 'st. importerade e-postadresser');
			$('#import-modal').removeClass('is-active');
			$('#message-modal').addClass('is-active');
		}
	});
});

function isNumber (text) {
	reg = new RegExp('[0-9]+$');
	if(text) {
	return reg.test(text);
	}
	return false;
}

function removeSpecial (text) {
  if(text) {
    var lower = text.toLowerCase();
    var upper = text.toUpperCase();
    var result = "";
    for(var i=0; i<lower.length; ++i) {
      if(isNumber(text[i]) || (lower[i] != upper[i]) || (lower[i].trim() === '') ||  (lower[i].trim() === '_') || (lower[i].trim() === '-') || (lower[i].trim() === '.') || (lower[i].trim() === '@')) {
        result += text[i];
      }
    }
    return result;
  }
  return '';
}

function CompanyStatus() {
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "CompanyStatus";
	param._token = Token;
	param._user_id = UserId;
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			data = jQuery.parseJSON(result);
			Current.wa_url = data.wa_url;
		}
	});
}

function formatDate(date) {
    var d = new Date(date),
        month = '' + (d.getMonth() + 1),
        day = '' + d.getDate(),
        year = d.getFullYear();

    if (month.length < 2) month = '0' + month;
    if (day.length < 2) day = '0' + day;

    return [year, month, day].join('-');
}

function daysBetween(date1, date2) {

	var ONE_DAY = 1000 * 60 * 60 * 24;
	var date1_ms = date1.getTime();	
	var date2_ms = date2.getTime();
	var difference_ms = Math.abs(date1_ms - date2_ms);
	return Math.round(difference_ms/ONE_DAY) - 1;
}

$(document).on('click', '.eBoxInvoiceEventClear', function(event) {
	event.preventDefault();
	Current.invoiceEventClearId = $(this).attr('ievent');
	//alert(Current.invoiceEventClearId);
	var invoiceEventName = $(this).attr('i-name');
	$('#invoice-event-clear-type-event').html(invoiceEventName);
	$('#box-invoice-event-clear').addClass('is-active');
});

/*
	$(document).on('click', '#eBoxEventClearStart', function(event) {
		event.preventDefault();
		//alert(Current.eventClearId);
		$('#box-event-clear').removeClass('is-active');
		var param = {};
		param._group = "EventClear";
		param._action = "ParticipantClear";
		param._token = Token;
		param._user_id = UserId;
		param._event_id = Current.eventClearId;

		$.ajax({ type: "POST", url: 'service2/', data: param,
			success: function(result) {
				eventListCreate();
				$('#box-event-clear').removeClass('is-active');
			}
		});
	});
*/

$(document).on('click', '#eBoxInvoiceEventClearClose', function(event) {
	event.preventDefault();
	$('#box-invoice-event-clear').removeClass('is-active');
});


$(document).ready(function() {
	$('#navbar-invoice-event').addClass('is-active');
	CompanyStatus();
	loadEventList();
	loadInvoiceEventList();
	
	//StoreList();

});

</script>