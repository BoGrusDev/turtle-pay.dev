<script>

var Current = {};
Current.Event = {};
var EventItemData = {};	

function EventsClass() {
	
}


$(document).on('click', '.eBoxEventSettings', function(event) {
	event.preventDefault();
	$('.page-section').hide();
	Current.eventId = $(this).attr('e-item');
	webform.loadWebFormSetting();
});

$(document).on('click', '.eOpenEvents', function(event) {
	event.preventDefault();
	Current.eventId = $(this).attr('e-id');
	Current.eventName = $(this).attr('e-name');
	
	var param = {};
	param._group = "Event";
	param._action = "EventItemPanelReportList";
	param._token = Token;
	param._user_id = UserId;
	param._event_id = Current.eventId;

	$.ajax({ type: "POST", url: 'service/', data: param,
		success: function(result) {
		
			EventItemData = JSON.parse(result);
			//$('#event-item-list').html(eventItemListHtml(data));
			$('#event-item-list').html(eventItemSimpleListHtml());
			$('.page-section').hide();
			$('.section-event-item').show();
			/*
			var data = JSON.parse(result);
			alert(data.event.participant_on);
			if (data.event.participant_on == 'y') {
				$('#event-item-list').html(eventItemListHtml(data));
				$('.page-section').hide();
				$('.section-event-item').show();
			}
			*/
		}
	});
	
});

function eventItemSimpleListHtml() {
	alert('simple');
	$('#event-title').text(Current.eventName + ' [' +EventItemData.items.length + ']');
	var html = '<table id = "EventListTable" class="table" style="width:100%; margin-bottom:20px"';

	html += '<tr>';
		html += '<th style="text-align:left">' + EventItemData.labels.participant_title + '</th>';

		// -- 2020-05-29
		html += '<th style="text-align:left">' + 'Trans.datum' + '</th>';

		for (j=0; j<EventItemData.olabels.length; j++) {        
		
       		html += '<th>';
				html += '<div class="select">';
					html += '<select class="select-option">';
						html += '<option value="0">' +  EventItemData.olabels[j]['text'] + '</option>';
						for (k=0; k<EventItemData.olabels[j]['option'].length; k++) {    
							html += '<option value="p' + j + '-' + EventItemData.olabels[j]['option'][k].event_option_setting_id +  '">' +  EventItemData.olabels[j]['option'][k].text + '</option>';
						}
					html += '</select>';
				html += '</div>';
			html += '</th>';
		}
		
		html += '</tr>';
		
	html += '</tr>';
		
	for (var i=0; i<EventItemData.items.length; i++) {

		html += '<tr class="option-row">';
			html += '<td>' + EventItemData.items[i].people_name + '</td>';
			
			// -- 2020-05-29
			var signUp = EventItemData.items[i].request_time;
			if (signUp.length > 16) {
				signUp = signUp.substring(0,16);
			}
			html += '<td style="text-align:left">' + signUp + '</td>'; 
			
			
			for (j=0; j<EventItemData.olabels.length; j++) {        
				if (typeof EventItemData.items[i]['option'][j] == 'undefined') {
					html += '<td>&nbsp;</td>';
				}
				else {    
					html += '<td class="p' + j + '-' + EventItemData.items[i]['option'][j]['event_option_setting_id'] + '">' + EventItemData.items[i]['option'][j]['text'] + '</td>';
				}
			}

		html += '</tr>';
	}
	return html;
}

$(document).on('change', '.select-option', function(event) {
	event.preventDefault();
	var className= $(this).val();
	if (className == '0') {
		$('.option-row').show();
	}
	else {
		//className = 'p0-' + className;
		//alert(className);
		$('.option-row').hide();
		$('.' + className).parent().show();
	}
});	

function eventItemListHtml(data) {
	alert('list');
	$('#event-title').text(Current.eventName + ' [' + data.part.length + ']');
	var html = '<table id = "EventListTable" class="table" style="width:100%; margin-bottom:20px"';

	html += '<tr>';
        html += '<th style="text-align:left">' + data.event['participant_title'] + '</th>';
        
        for (j=0; j<data.event['selection'].length; j++) {        
            html += '<th>' + data.event['selection'][j]['text'] + '</th>';
        }

        if (data.event['your_ref_on'] == 'y') {
            html += '<th style="text-align:left">' + data.event['your_ref_label'] + '</th>';
        }
       
		html += '<th style="text-align:left">' + 'Fakturamottagare' + '</th>';
       
		html += '<th style="text-align:left">' + data.event['email_label'] + '</th>';
        
        if (data.event['mobile_on'] == 'y') {
            html += '<th style="text-align:left">' + data.event['mobile_label'] + '</th>';
        }
        if (data.event['other_info_on'] == 'y') {
            html += '<th style="text-align:left">' + data.event['other_info_label'] + '</th>';
        }
	html += '</tr>';
		
	for (var i=0; i<data.part.length; i++) {

		html += '<tr>';
			html += '<td>' + data.part[i]['last_name'] + ', ' + data.part[i]['first_name'] + '</td>';
		
		for (var j=0; j<data.event['selection'].length; j++) {   
			//alert(i + " " + data.part[i]['option'][j]['text']);     
			html += '<td>' + data.part[i]['option'][j]['text'] + '</td>';
		}
		
		if (data.event['infobox_1'] == 'y') {
			html += '<td>' + data.part[i]['infobox_1'] + '</td>';
		}
		
		html += '<td>' + data.part[i]['people_name'] + '</td>';
		html += '<td>' + data.part[i]['email'] + '</td>';
		
		if (data.event['mobile_on'] == 'y') {
			html += '<td>' + data.part[i]['mobile'] + '</td>';
		}
		if (data.event['infobox_2'] == 'y') {
			html += '<td>' + data.part[i]['infobox_2'] + '</td>';
		}
		
		html += '</tr>';
	}
	return html;
}

$(document).on('click', '#ePrintList', function(event) {
	event.preventDefault();
	var mywindow = window.open('', 'PRINT', 'height=600,width=800');
	mywindow.document.write('<html><head></head><body>');
	mywindow.document.write($('#print-list').html());
	mywindow.document.write('</body></html>');
	mywindow.document.close(); // necessary for IE >= 10
	mywindow.focus(); // necessary for IE >= 10
	mywindow.print();
	mywindow.close();
});

function download_csv(csv, filename) {
    var csvFile;
    var downloadLink;

    // CSV FILE
	//csvFile = new Blob([csv], {type: "text/plain;charset=utf-8"});
	csvFile = new Blob(["\uFEFF"+csv], {type: 'text/csv; charset=utf-18'});
	//var blob = new Blob(["Hello, world!"], {type: "text/plain;charset=utf-8"});
    // Download link
    downloadLink = document.createElement("a");

    // File name
    downloadLink.download = filename;

    // We have to create a link to the file
    downloadLink.href = window.URL.createObjectURL(csvFile);

    // Make sure that the link is not displayed
    downloadLink.style.display = "none";

    // Add the link to your DOM
    document.body.appendChild(downloadLink);

    // Lanzamos
    downloadLink.click();
}

function exportTableToCsv(filename) {
	var csv = [];
	
	var d = new Date();
	var dateNow = getTimeStamp();
	csv.push(Current.eventName + ';;'+ dateNow + '\n'); 

	var rows = document.querySelectorAll('#EventListTable tr');
    for (var i = 0; i < rows.length; i++) {
		var row = [], cols = rows[i].querySelectorAll("td, th");
		//var row = [], cols = rows[i].querySelectorAll("td");
        for (var j = 0; j < cols.length; j++) 
            row.push(cols[j].innerText);
        
		csv.push(row.join(";"));		
	}

    download_csv(csv.join("\n"), filename);
}

$(document).on('click', '#eExportCsv', function(event) {
	event.preventDefault();
	exportTableToCsv("Event-Lista.csv");
});

function getTimeStamp () {
  now = new Date();
  year = "" + now.getFullYear();
  month = "" + (now.getMonth() + 1); if (month.length == 1) { month = "0" + month; }
  day = "" + now.getDate(); if (day.length == 1) { day = "0" + day; }
  hour = "" + now.getHours(); if (hour.length == 1) { hour = "0" + hour; }
  minute = "" + now.getMinutes(); if (minute.length == 1) { minute = "0" + minute; }
  //second = "" + now.getSeconds(); if (second.length == 1) { second = "0" + second; }
  return year + "-" + month + "-" + day + " " + hour + ":" + minute;
}

function eventListLoad() {
	eventListCreate();
}

$(document).on('click', '.eBoxEventClose', function(event) {
	event.preventDefault();
	var eventId = $(this).attr('e-item');

	var param = {};
	param._group = "Event";
	param._action = "EventStatusSet";
	param._token = Token;
	param._user_id = UserId;
	param._event_id =eventId;
	param.event_status = 'c';
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			eventListCreate();
		}
	});
});

$(document).on('click', '.eBoxEventReOpen', function(event) {
	event.preventDefault();
	var eventId = $(this).attr('e-item');
	var param = {};
	param._group = "Event";
	param._action = "EventStatusSet";
	param._token = Token;
	param._user_id = UserId;
	param._event_id = eventId;
	param.event_status = 'p';
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			eventListCreate();
		}
	});
});

$(document).on('change', '#eEventListFiler', function(event) {
	event.preventDefault();
	if(this.checked) {
		$('.EventComplete').show();
	}
	else {
		$('.EventComplete').hide();
	}
	//eEventListFiler
});

function eventListCreate() {

	$( "#eEventListFiler" ).prop( "checked", false );
	var param = {};
	param._group = "Event";
	param._action = "EventList";
	param._token = Token;
	param._user_id = UserId;
	//param._event_status = status;
	$.ajax({ type: "POST", url: 'service/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			//Current.filter = "0";
			var html = '<table class="table" style="width:100%; margin-bottom:20px"';
			html += '<tr>';
				html += '<th style="text-align:left; background-color: #ffffff;font-size:14px">' + UserName + '</th>';
			html += '</tr>';

			for (let i = 0; i < data.length; i++) {
				if (data[i].event_status == 'p' && data[i].participant_on == 'y' && data[i].event_id == data[i].base_event_id ) {
					html += '<tr>';
					html += '<td class="eOpenEvents pointer" e-name="' + data[i].event_name + '" e-id="' + data[i].event_id + '">' + data[i].event_name + '</td>';		
					html += '</tr>';
				}
			}
			$('#event-list').html(html);
			$('.page-section').hide();
			$('.section-event-list').show();
		}
	});
}

$(document).on('click', '#eBackEventList', function(event) {
	event.preventDefault();

	// KOntroll fråga om att avsluat
	location.reload();

	//loadInvoiceEventList();
	//$('.page-section').hide();
	//$('.section-event-list').show();
});

$(document).ready(function() {
	$('#navbar-event').addClass('is-active');
	//UserId = 75;
	eventListLoad();
});


</script>