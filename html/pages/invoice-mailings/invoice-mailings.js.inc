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
var CustomerListIsLoaded = false;
var StoreList;

var Current = {};
Current.storeId = 0;
Current.eventName = '';
Current.eventSubject = '';
Current.eventBody = '';
Current.eventSpec = '';
Current.eventStatus;
Current.eventId = 0;
Current.itemId = 0;
Current.peopleId = 0;
Current.eventAllowedEdit = 'y';
Current.eventPreSendDate;
Current.eventSendDate;
Current.eventAutoReminder;
Current.eventReminderDays;
Current.eventReminderTimes;
Current.eventAmount = 0;
Current.filter = "0";

Current.reminderLastDate  = null;
Current.reminderTimes  = 0;
Current.sendDate = null;
Current.itemStatus = null;
Current.itemId = null;

function loadInvoiceEventList() {
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "EventList";
	param._token = Token;
	param._user_id = UserId;

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			//(result);
			InvoiceEventList = jQuery.parseJSON(result);
			createHtmlTable(InvoiceEventList) ;
		}
	});
}

function createHtmlTable(data) {

	var html = '<table class="table" style="width:100%; margin-bottom:20px"';
	html += '<tr>';
		html += '<th style="text-align:left; background-color: #ffffff;">Namn</th>';
		html += '<th style="text-align:left;width:104px;background-color: #ffffff;">Skapad</th>';
		html += '<th style="text-align:right;background-color: #ffffff;">Antal</th>';
		html += '<th style="text-align:right;background-color: #ffffff;">Pågående</th>';
		html += '<th style="text-align:right;background-color: #ffffff;">Hämtade</th>';
		html += '<th style="text-align:left;background-color: #ffffff;padding-left:12px!Important;">Status</th>';
		//html += '<th style="text-align:left;background-color: #ffffff; width:8%"></th>';
		//html += '<th style="text-align:left">Skapa ny</th>';		
	html += '</tr>';

	for (let i = 0; i < data.length; i++) {
		if (data[i].invoice_event_status == 'c') {
			var classEventComplete = " EventComplete";
		}
		else {
			var classEventComplete = '';
		}
		html += '<tr class="eOpenEvents pointer' + classEventComplete + '" i-name="' + data[i].invoice_event_name + '" ievent="' + data[i].invoice_event_id + '">';
		html += '<td>' + data[i].invoice_event_name + '</td>';
		html += '<td style="width:96px">' + data[i].create_date + '</td>';
		html += '<td style="text-align:right;">' + data[i].no_items + '</td>';
		html += '<td style="text-align:right;">' + data[i].no_sent + '</td>';
		html += '<td style="text-align:right;">' + data[i].no_confirmed + '</td>';
		var status = '';
		if (data[i].invoice_event_status == 'p') {
			status = "Utkast";
		} else if (data[i].invoice_event_status == 'c') {
			status = "Avslutad";
		} else if (data[i].invoice_event_status == 'a') {
			status = "Aktiv";
		}
		
		html += '<td style="text-align:left; padding-left:12px;">' + status + '</td>';
		//html += '<td style="text-align:right; width:8%"> <button i-name="' + data[i].invoice_event_name + '" ievent="' + data[i].invoice_event_id + '" class="eOpenEvents button is-dark is-small"> Öppna </button></td>';
		//html += '<td style="text-align:left"><a href="kopiera-group"> Kopiera</a></td>';
		html += '</tr>';
	}

	$('#invoice-event-list').html(html);
	$('.EventComplete').hide();

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
	$('#event-import').prop('checked', false);
	$('#event-send-date-pre').prop('checked', false);
	$('#event-send-date').hide();
	$('#event-spec-import').prop('checked', true);
	$('#event-spec').hide();
	$('#event-spec').val('');
	$('#event-amount-import').prop('checked', true);
	$('#event-amount').val('');
	$('#event-amount').hide();
	$('#event-amount-label').hide();
	$('#event-allow-edit-import').prop('checked', false);
	$('#event-auto-reminder').prop('checked', false);
	$('#event-referense-import').prop('checked', true);
	$('.import-group').hide();
	$('.required').show();

	if (StoreList.length > 1) {
		$('#ddStoreList').empty();
		var list = $("#ddStoreList");
		$.each(StoreList, function(index, item) {
  			list.append(new Option(item.store_name, item.store_id));
		});
		$("#ddStoreList").val($("#ddStoreList option:first").val());
		Current.storeId = StoreList[0].store_id;
		$('.many-stores').show();
	}
	else {
		Current.storeId = StoreList[0].store_id;
		$('.many-stores').hide();
	}

	$('#ddEventList').empty();
	var list = $("#ddEventList");
	$.each(InvoiceEventList, function(index, item) {
  		list.append(new Option(item.invoice_event_name, item.invoice_event_id));
	});
	$("#ddEventList").val($("#ddEventList option:first").val());
	$('#modal-import-group').prop('checked', false);

	$('#event-new-modal').addClass('is-active');
});

$(document).on('click', '#eCloseEventNewModal', function(event) {
	event.preventDefault();
	$('#event-new-modal').removeClass('is-active');
});

$(document).on('click', '#eCreateEvent', function(event) {
	event.preventDefault();
	var name = $('#event-name').val();
	if (name.length < 2) {
		$('#message-text-modal').html('Namn måste vara på minst 2 tecken!');
		$('#message-modal').addClass('is-active');
		return false;
	}
	
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "EventCreate";
	param._token = Token;
	param._user_id = UserId;
	param._store_id = Current.storeId;
	param.wa_url = Current.wa_url;
	param.invoice_event_name = name;
	 
	if ($('#event-import').is(':checked')) {
		param._import = 'y';
		param._import_id = $('#ddEventList').val();
		//
		param._referense_import = _GetCheckbox('#event-referense-import', 'y', 'n');
		param._spec_import = _GetCheckbox('#event-spec-import', 'y', 'n');
		if (param._spec_import == 'n') {
			param._spec = $('#event-spec').val();
		}
		
		param._amount_import = _GetCheckbox('#event-amount-import', 'y', 'n');
		if (param._amount_import == 'n') {
			var amount = $('#event-amount').val();
			amount = amount.trim();
			if (amount.length == 0) {
				param._amount = '0';
			} 
			else if (isNaN(amount)) {
				$('#message-text-modal').html('Belopp måste vara numeriskt.');
				$('#message-modal').addClass('is-active');
				return;
			}
			else {
				param._amount = amount;
			}
		}	
		param._send_date_pre = _GetCheckbox('#event-send-date-pre', 'y', 'n');
		if (param._send_date_pre == 'y') {
			param._send_date = $('#event-send-date').val();
		}

		param._allowed_edit = _GetCheckbox('#event-allow-edit-import', 'y', 'n');
		
		if ($('#event-auto-reminder').is(':checked')) {
			param._auto_reminder = 'y';
			param._reminder_days = $('#event-reminder-days').val();
			param._reminder_times = $('#event-reminder-times').val();
		}
		else {
			param._auto_reminder = 'n';
		}

	}
	else {
		param._import = 'n';
	}

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			//alert(result);
			loadInvoiceEventList();
			$('#event-new-modal').removeClass('is-active');
		}
	});

});

$(document).on('click', '#eEventSettings', function(event) {
	event.preventDefault();

	//var subject = 'Subject';
	//var body = 'Body';

	var param = {};
	param._group = "InvoiceEvent";
	param._action = "EventGet";
	param._token = Token;
	param._user_id = UserId;
	param._event_id = Current.eventId

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			$('.required').show();
			$('#setting-event-name').val(data.invoice_event_name);
			$('#settings-subject').val(data.subject);
			$('#settings-body').val(data.body);
			//$('#settings-spec').val(data.spec);
			//$('#settings-ddStatus').val(data.invoice_event_status);
			//if (data.amount == '0.00') {
				//data.amount = '';
			//}
			//$('#settings-amount').val(data.amount);
			
			//if (data.allowed_edit == 'y') {
				//$('#settings-allowed-edit').prop('checked', true);
			//}
			//else {
				//$('#settings-allowed-edit').prop('checked', false);
			//}
			//if (data.pre_send_date == 'y') {
				//$('#settings-pre-send-date').prop('checked', true);
				$('#settings-send-date').val(data.send_date);
				//$('#settings-send-date').show();
			//}
			//else {
				//$('#settings-pre-send-date').prop('checked', false);
				//$('#settings-send-date').hide();
			//}
			if (data.auto_reminder == 'y') {
				$('#settings-auto-reminder').prop('checked', true);
				$('#settings-reminder-days').val(data.reminder_days);
				$('#settings-reminder-times').val(data.reminder_times);
				$('.settings-reminder-container').show();
			}
			else {
				$('#settings-auto-reminder').prop('checked', false);
				$('#settings-reminder-days').val('7');
				$('#settings-reminder-times').val('3');
				$('.settings-reminder-container').hide();
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
	param._event_id = Current.eventId;
	param.invoice_event_name = name;
	param.subject =	$('#settings-subject').val();
	param.body = body;
	param.spec = $('#settings-spec').val();
	param.invoice_event_status = $('#settings-ddStatus').val();


	if (param.invoice_event_status == "c") {
		$('#eNewInvoice').hide();
		$status = " (avslutad)";
	}
	else if (param.invoice_event_status == "p") {
		$('#eNewInvoice').show();
		$status = " (utkast)";
	}
	else if (param.invoice_event_status == "a") {
		$('#eNewInvoice').show();
		$status = " (aktiv)";
	}
	$('#title-event-name').html(param.invoice_event_name + $status);

	if ($('#settings-pre-send-date').is(':checked')) {
		param.pre_send_date = 'y';
		param.send_date = $('#settings-send-date').val();
	}
	else {
		param.pre_send_date = 'n';
	}

	if ($('#settings-allowed-edit').is(':checked')) {
		param.allowed_edit = 'y';
	}
	else {
		param.allowed_edit = 'n';
	}

	if ($('#settings-auto-reminder').is(':checked')) {
		param.auto_reminder = 'y';
		param.reminder_days = $('#settings-reminder-days').val();
		param.reminder_times = $('#settings-reminder-times').val();
	}
	else {
		param.auto_reminder = 'n';
		param.reminder_days = '0';
		param.reminder_times = '0';
	}
		
	if ($('#settings-reminder-text-on').is(':checked')) {
		param.reminder_text_on = 'y';
	}
	else {
		param.reminder_text_on = 'n';
	}
	param.reminder_body = $('#settings-reminder-body').val();
	var amount = $('#settings-amount').val();
	amount = amount.trim();
	if (amount.length == 0) {
		param.amount = 0;
	} else if (isNaN(amount)) {
		$('#message-text-modal').html('Belopp måste vara numeriskt.');
		$('#message-modal').addClass('is-active');
		return;
	}else {
		param.amount = amount;
	}
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			$('#invoice-event-settings-modal').removeClass('is-active');
			Current.eventAllowedEdit = param.allowed_edit;
			Current.eventSpec = param.spec;
			Current.eventPreSendDate = param.pre_send_date;
			if (Current.eventPreSendDate == "y") {
				Current.eventSendDate = param.send_date;
			} 
			else {
				Current.eventSendDate = '';
			}
			Current.eventAmount = param.amount;
			Current.eventAutoReminder = param.auto_reminder;
			Current.eventReminderDays = param.reminder_days;
			Current.eventReminderTimes = param.reminder_times;
			//$('#title-event-name').html(param.invoice_event_name)

		}
	});

	
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

	Current.eventId = $(this).attr('ievent');
	var eventName = $(this).attr('i-name');
	$('#event-name-header').html(eventName);

	var param = {};
	param._group = "InvoiceEvent";
	param._action = "EventGet";
	param._token = Token;
	param._user_id = UserId;
	param._event_id = Current.eventId

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			Current.eventName = data.invoice_event_name;
			Current.eventSubject = data.subject;
			Current.eventBody = data.body;
			Current.eventSpec = data.spec;
			Current.eventAllowedEdit = data.allowed_edit;
			Current.eventPreSendDate = data.pre_send_date;
			Current.eventSendDate = data.send_date;
			Current.eventAutoReminder = data.auto_reminder;
			Current.eventReminderDays = data.reminder_days;
			Current.eventReminderTimes = data.reminder_times;
			Current.eventStatus = data.invoice_event_status;
			Current.storeId = data.store_id;
			Current.eventAmount = data.amount;

			if (Current.eventStatus == "c") {
				$('#eNewInvoice').hide();
				$status = " (avslutad)";
			}
			else if (Current.eventStatus == "p") {
				$('#eNewInvoice').show();
				$status = " (utkast)";
			}
			else if (Current.eventStatus == "a") {
				$('#eNewInvoice').show();
				$status = " (aktiv)";
			}
			$('#title-event-name').html(data.invoice_event_name + $status);
		
		}
	});

	// Load Event Data
	loadEventList();
});

function loadEventList() {
	
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "EventItemList";
	param._token = Token;
	param._user_id = UserId;
	param._invoice_event_id = Current.eventId;
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
					html += '<option value="d">Medges ej</option>';
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
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" item-name="' + data[i].people_name + '" class="eDeleteInvoice button is-small">Ta bort</button></td>';
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" class="eOpenInvoice button is-link is-small">Öppna</button></td>';

		} 
		else if (data[i].invoice_event_item_status == "a") {
		
			var status = "Skickas:";
			html += '<td style="color: #8B0000; width:200px">' + status + ' ' + data[i].planed_date  + '</td>';
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" item-name="' + data[i].people_name + '" class="eDeleteInvoice button is-small">Ta bort</button></td>';
			html += '<td style="text-align:right;width:66px"><button item-id="' + data[i].invoice_event_item_id + '" class="eOpenInvoice button is-link is-small">Öppna</button></td>';

		} 
		else if (data[i].invoice_event_item_status == "s") {
			var status = "Skickad:";
			html += '<td style="color: #006500; width:200px">' + status + ' ' + data[i].sent_datetime.substr(0, 10) + ' </td>';
			html += '<td style="width:66px"></td>';
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
			html += '<td style="width:66px"></td>';
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

$(document).on('click', '#eNewInvoice', function(event) {
	event.preventDefault();
	Current.itemId = 0;
	Current.itemStatus = '';

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
	
	$('#eUpdateInvoiceItemModal').hide();
	$('#eSaveInvoiceItemModal').show();
	$('.required').show();

	$('#invoice-people-name').val('');
	$('#invoice-email').val('');
	$('#invoice-referens').val('');
	$('#invoice-spec').val(Current.eventSpec);
	$('#invoice-planed-date').val('');
	$('#invoice-people-name').prop('disabled', false);
	$('#invoice-email').prop('disabled', false);
	$('#invoice-referens').prop('disabled', false);
	$('#invoice-spec').prop('disabled', false);
	$('#invoice-amount').prop('disabled', false);
	//$('.check-start').show();
	
	if (Current.eventAllowedEdit == 'y') {
		$('#invoice-allowed-edit').prop('checked', true);
	}
	else {
		$('#invoice-allowed-edit').prop('checked', false);
	}

	if ( Current.eventPreSendDate == 'y') {
		$('#invoice-planed-date').val(Current.eventSendDate);
	}
	else {
		var currentDate = new Date();
		var nowDateString = currentDate.toISOString().substring(0, 10);
		$('#invoice-planed-date').val(nowDateString);
	}

	if (Current.eventAmount > 0) {
		$('#invoice-amount').val(Current.eventAmount);
	} 
	else {
		$('#invoice-amount').val('');
	}

	if (Current.eventAutoReminder == 'y') {
		$('#invoice-auto-reminder').prop('checked', true);
		$('#invoice-reminder-days-container').show();
		$('#invoice-reminder-times-container').show();
		$('#invoice-reminder-days').val(Current.eventReminderDays);
		$('#invoice-reminder-times').val(Current.eventReminderTimes);
	}
	else {
		$('#invoice-auto-reminder').prop('checked', false);
		$('#invoice-reminder-days').val(Current.eventReminderDays);
		$('#invoice-reminder-times').val(Current.eventReminderTimes);
		$('#invoice-reminder-days-container').hide();
		$('#invoice-reminder-times-container').hide();
	}
	
	$('#invoice-label-reminder-next-date').hide();
	$('#invoice-reminder-next-date').hide();

	$('#invoice-planed-date').prop('disabled', false);
	$('#invoice-allowed-edit').prop('disabled', false);
	$('#invoice-draft').prop('checked', false);
	$('#invoice-confirmed-datetime').val('');
	$('#invoice-item-modal').addClass('is-active');
});

$(document).on('change', '#invoice-auto-reminder', function(event) {
	event.preventDefault();
	if(this.checked) {
		if (Current.itemStatus == "s" || Current.itemStatus == "r") {
			if (Current.itemStatus == "s") {
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
		$('#eUpdateInvoiceItemModal').show()
	}
});

$('#invoice-reminder-days').on('change', function() {
	var times = $('#invoice-reminder-times').val();
	if (Number(times) > 0) {
		var days = $(this).val();
		//alert(Current.reminderLastDate);
		if (Current.itemStatus == "s" || Current.itemStatus == "r") {
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
		$('#eUpdateInvoiceItemModal').show()
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
		if (Current.itemStatus == "s" || Current.itemStatus == "r") {
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
		$('#eUpdateInvoiceItemModal').show()
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

$(document).on('click', '#eSaveInvoiceItemModal', function(event) {
	event.preventDefault();

	var peopleName = $('#invoice-people-name').val();
	var email = $('#invoice-email').val();
	var referens = $('#invoice-referens').val();
	var spec = $('#invoice-spec').val();
	var amount = $('#invoice-amount').val();
	var planedDate = $('#invoice-planed-date').val();

	if (email.length < 5) {
		$('#message-text-modal').html('E-postadress är inte giltigt.');
		$('#message-modal').addClass('is-active');
        return;
    }
    if (Helper.validateEmail(email) == false) {
        $('#message-text-modal').html('E-postadress är inte giltigt');
        $('#message-modal').addClass('is-active');
        return;
    }

	if ($('#invoice-allowed-edit').is(':checked')) {
	}
	else {
		if (amount.length == 0 || isNaN(amount)) {
			$('#message-text-modal').html('Belopp måste anges, när mottagaren inte tillåts ändra uppgifter.');
			$('#message-modal').addClass('is-active');
			return;
		}
		else {
			if (amount.length < 0 || isNaN(amount)) {
				$('#message-text-modal').html('Belopp måste vara numeriskt.');
				$('#message-modal').addClass('is-active');
				return;
			}
		}
	}


	var param = {};
	param._group = "InvoiceEvent";
	param._action = "ItemCreate";
	param._token = Token;
	param._user_id = UserId;
	param._store_id = Current.storeId;
	param.people_name = peopleName;
	param.email = email;
	param.referens = referens;
	param.spec = spec;
	amount = amount.trim();
	if (amount.length == 0 || isNaN(amount)) {
		param.amount = 0;
	}
	else{
		param.amount = amount;
	}
	param.planed_date = planedDate;
	param.event_id = Current.eventId;
	if ($('#invoice-auto-reminder').is(':checked')) {
		param.auto_reminder = 'y';
		param.reminder_days = $('#invoice-reminder-days').val();
		param.reminder_times = $('#invoice-reminder-times').val();
	}
	else {
		param.auto_reminder = 'n';
		param.reminder_days = 0;
		param.reminder_times = 0;
	}
	if ($('#invoice-allowed-edit').is(':checked')) {
		param.allowed_edit = 'y';
	}
	else {
		param.allowed_edit = 'n';
	}

	if ($('#invoice-draft').is(':checked')) {
		param.invoice_event_item_status = 'p';
	}
	else {
		param.invoice_event_item_status = 'a';
	}
	
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			loadEventList();
			$('#invoice-item-modal').removeClass('is-active');
		}
	});
});

$(document).on('click', '.eOpenInvoice', function(event) {
	event.preventDefault();
	Current.itemId = $(this).attr('item-id');
	
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "ItemGet";
	param._token = Token;
	param._user_id = UserId;
	param._item_id = Current.itemId;

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			Current.itemStatus = data.invoice_event_item_status;
			$('#invoice-people-name').val(data.people_name);
			$('#invoice-email').val(data.email);
			$('#invoice-referens').val(data.referens);
			$('#invoice-spec').val(data.spec);
			
			if (data.amount > '0.00') {
				$('#invoice-amount').val(data.amount);
			}
			else {
				$('#invoice-amount').val('');
			}
			
			$('#invoice-planed-date').val(data.planed_date);
			$('#invoice-allowed-edit').prop('disabled', false);
			if (data.allowed_edit == "y") {
				$('#invoice-allowed-edit').prop('checked', true);
			}
			else {
				$('#invoice-allowed-edit').prop('checked', false);
			}
			$('#invoice-planed-date').val(data.planed_date);
			
			if (data.invoice_event_item_status == 'p' || data.invoice_event_item_status == 'a') {

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
				
				$('#eUpdateInvoiceItemModal').show();
				$('#eSaveInvoiceItemModal').hide();
				$('.required').show();

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
				$('#invoice-referens').prop('disabled', false);
				$('#invoice-spec').prop('disabled', false);
				$('#invoice-amount').prop('disabled', false);
				$('#invoice-planed-date').prop('disabled', false);
				$('#invoice-allowed-edit').prop('disabled', false);
				
			}

			else if (data.invoice_event_item_status == 's' || data.invoice_event_item_status == 'r') {
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
				$('#eSaveInvoiceItemModal').hide();
				$('#eUpdateInvoiceItemModal').hide(); 
				$('.required').hide();
				
				$('#invoice-people-name').prop('disabled', true);
				$('#invoice-email').prop('disabled', true);
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
			}
			else if (data.invoice_event_item_status == 'c' || data.invoice_event_item_status == 'm') {
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
				$('.required').hide();

				$('#invoice-people-name').prop('disabled', true);
				$('#invoice-email').prop('disabled', true);
				$('#invoice-referens').prop('disabled', true);
				$('#invoice-spec').prop('disabled', true);
				$('#invoice-amount').prop('disabled', true);
				$('#invoice-planed-date').prop('disabled', true);
				$('#invoice-allowed-edit').prop('disabled', true);
				
				if (data.invoice_event_item_status == 'c') {
					$('#invoice-sent-datetime').val(data.sent_datetime.substr(0,10));
					$('#invoice-sent-datetime').prop('disabled', true);

					$('#invoice-confirmed-datetime').val(data.confirmed_datetime.substr(0,10));
					$('#invoice-confirmed-datetime').prop('disabled', true);
				}
			}
			$('#invoice-item-modal').addClass('is-active');
		}
	});

});

$(document).on('click', '#eBackinvoiceEventList', function(event) {
	event.preventDefault();
	loadInvoiceEventList();
	$('.page-section').hide();
	$('.section-event').show();
});

$(document).on('click', '#eUpdateInvoiceItemModal', function(event) {
	event.preventDefault();

	var param = {};
	param._group = "InvoiceEvent";
	param._action = "ItemUpdate";
	param._token = Token;
	param._user_id = UserId;
	param._item_id = Current.itemId;

	if (Current.itemStatus == "m") {
		param.invoice_event_item_status = 'p';
	} 
	else if ($('#invoice-item-close').is(':checked')) {
		param.auto_reminder = 'n';
		param.invoice_event_item_status = 'm';
	}
	else {

		var peopleName = $('#invoice-people-name').val();
		var email = $('#invoice-email').val();
		var referens = $('#invoice-referens').val();
		var spec = $('#invoice-spec').val();
		var amount = $('#invoice-amount').val();
		amount = amount.trim();
		var planedDate = $('#invoice-planed-date').val();

		if ($('#invoice-allowed-edit').is(':checked')) {
			var allowedEdit = 'y';
		}
		else {
			var allowedEdit = 'n';
		}
	
		if (email.length < 5) {
			$('#message-text-modal').html('E-postadress är inte giltigt.');
			$('#message-modal').addClass('is-active');
			return;
		}
		if (Helper.validateEmail(email) == false) {
			$('#message-text-modal').html('E-postadress är inte giltigt');
			$('#message-modal').addClass('is-active');
			return;
		}
		if (allowedEdit == 'n') {
			if (amount.length == 0 || isNaN(amount)) {
				$('#message-text-modal').html('Belopp måste anges, när mottagaren inte tillåts ändra uppgifter.');
				$('#message-modal').addClass('is-active');
				return;
			}
		}
		else {
			if (amount.length < 0 || isNaN(amount)) {
				$('#message-text-modal').html('Belopp måste vara numeriskt.');
				$('#message-modal').addClass('is-active');
				return;
			}
		}

		param.people_name = peopleName;
		param.email = email;
		param.referens = referens;
		param.spec = spec;
		param.allowed_edit = allowedEdit;
		param.amount = amount;
	
		if (Current.itemStatus == 'p' || Current.itemStatus == 'a') {
			if ($('#invoice-draft').is(':checked')) {
				param.invoice_event_item_status = 'p';
			}
			else {
				param.invoice_event_item_status = 'a';
			}
		} 

		if ($('#invoice-auto-reminder').is(':checked')) {
			param.auto_reminder = 'y';
			param.reminder_days = $('#invoice-reminder-days').val();
			param.reminder_times = $('#invoice-reminder-times').val();
		}
		else {
			param.auto_reminder = 'n';
			param.reminder_days = '0';
			param.reminder_times = '0';
		}
	
		if (Current.itemStatus == 's' || Current.itemStatus == 'r') {
			if (param.reminder_times != '0') {
				param.reminder_next_date = $('#invoice-reminder-next-date').val();
				//alert($('#invoice-reminder-next-date').val());
			}
		}
		param.planed_date = planedDate;
	}
	
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			loadEventList();
			$('#invoice-item-modal').removeClass('is-active');
		}
	});
	//var allowed_edit = $('#invoice-allowed-edit').prop('checked', true);
	$('#invoice-item-modal').removeClass('is-active');
});

$(document).on('click', '.eDeleteInvoice', function(event) {
	event.preventDefault();
	Current.itemId = $(this).attr('item-id');
	var itemName = $(this).attr('item-name');

	$('#remove-item-modal-text').html(itemName);
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
	param._item_id = Current.itemId; 

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			loadEventList();
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
		
			var data = jQuery.parseJSON(result);
			
			var html = '<table class="table" style="table-layout: fixed; width:100%; margin-bottom:20px; font-size: 14px;"';
			html += '<tr>';
				html += '<th style="text-align:left; background-color: #ffffff;">Namn</th>';
				html += '<th style="text-align:left; background-color: #ffffff; ">Email</th>';
				html += '<th style="width:9%; background-color: #ffffff; "></th>';	
			html += '</tr>';

			for (let i = 0; i < data.length; i++) {
				html += '<tr class="no-uborder">';
					html += '<td style="vertical-align:middle; font-weight: bold;padding-bottom:0">' + data[i].last_name + ', ' + data[i].first_name + '</td>';
					html += '<td style="vertical-align:middle; font-size:12px; padding-bottom:0">' + data[i].address + '</td>';
					html += '<td rowspan="2" style="width:9%; text-align:right"> <button people-id="' + data[i].people_id + '" pname="' + data[i].last_name + ', ' + data[i].first_name + '" pmail="' + data[i].email + '" class="eSelectPeople button is-dark is-small">Välj</button> </td>';
				html += '</tr>';
				html += '<tr>';
					html += '<td style="vertical-align:middle;padding-top:0;">' + data[i].email + '</td>';
					html += '<td style="vertical-align:middle; font-size:12px;padding-top:0;">' + data[i].postcode + ' ' +  data[i].city + '</td>';
					//html += '<td style="width:9%; text-align:right"> <button people-id="' + data[i].people_id + '" pname="' + data[i].people_name + '" pmail="' + data[i].email + '" class="eSelectPeople button is-dark is-small">Välj</button> </td>';
				html += '</tr>';
			}
			html += '</table>';
			CustomerListIsLoaded  = true;
			$('#customer-list').html(html);
		}
	});
}

$(document).on('click', '#eInvoiceGetTab', function(event) {
	event.preventDefault();
	$('#title-invoice-item-modal').html('Hämta mottagare');
	if (CustomerListIsLoaded == false) {
		loadCustomerList();
	}
	$('.item-tab').hide();
	$('.get-tab').show();
});

$(document).on('click', '#eInvoiceItemTab', function(event) {
	event.preventDefault();
	$('#title-invoice-item-modal').html('Faktura i utskick');
	$('.get-tab').hide();
	$('.item-tab').show();
	if (Current.itemId == 0) {
		$('#eUpdateInvoiceItemModal').hide();
	}
	else {
		$('#eSaveInvoiceItemModal').hide();
	}
	if ($('#invoice-auto-reminder').is(':checked'))  {
		$('.reminder-container').show();
	}
	else {
		$('.reminder-container').hide();
	}   
});

$(document).on('click', '.eSelectPeople', function(event) {
	event.preventDefault();
	Current.peopleId = $(this).attr('people-id'); // Only set when get earlier
	var peopleName = $(this).attr('pname');
	var peopleEmail = $(this).attr('pmail');
	$('#invoice-people-name').val(peopleName);
	$('#invoice-email').val(peopleEmail);
	
	$('#title-invoice-item-modal').html('Faktura i utskick');
	$('.get-tab').hide();
	$('.item-tab').show();
	if (Current.itemId == 0) {
		$('#eUpdateInvoiceItemModal').hide();
	}
	else {
		$('#eSaveInvoiceItemModal').hide();
	}
});

function StoreList() {
	var param = {};
	param._group = "InvoiceEvent";
	param._action = "StoreList";
	param._token = Token;
	param._user_id = UserId;
	
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			StoreList = jQuery.parseJSON(result);
		}
	});
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

$(document).ready(function() {

	$('#navbar-invoice-event').addClass('is-active');
	CompanyStatus();
	loadInvoiceEventList();
	StoreList();

});


</script>