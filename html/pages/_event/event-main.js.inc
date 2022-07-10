<?php
/*

*/
require_once 'base-lib/ModelBaseClass.js.inc';
?>

<script>

// 2022-02-01
class ModelBase extends ModelBaseClass {}
const Model = new ModelBase();
Current.serviceApi = 'service2/';
// Current.serviceApi = 'http://turtle-pay.grusit/kapi/';
//----ªª
Current.Event = {};

var EventItemData = {};	

$(document).ready(function() {
	// 2022-02-01
	$('#navbar-event').addClass('is-active');
	Current.init();
});

Current.init = function () {
	// 2022-02-01
	var param = {};
	param._group = "Company";
	param._action = "InfoGet";
	param._token = Token;
	param._user_id = UserId;
	Model.service(param, Current.serviceApi)
	.then(response => response.json())
	.then(function(data) {   
		if (data.code == '1') { 
			Current.companyInfo = data;
			eventListCreate();
		}
		else {
			alert('Not allowed');
			// location.reload();
			//logout
		}
	})
}

$(document).on('click', '.eBoxEventClose', function(event) {
	event.preventDefault();
	var index = $(this).attr('e-index');
	if (Current.eventList[index].parent_on == 'y') {
		$('#eYesNoCloseEventYes').attr('index', index);
		$('#yesno-close-event-box').addClass('is-active');
		return;
	}
	else if (Current.eventList[index].child_on == 'y' && Current.eventList[index].counter > 0) {
		$('#message-text-modal').html('Importerat och grupperat Event kan ej avslutas!');
		$('#message-modal').addClass('is-active');
		return;
	}
	eventClose(index);
});

$(document).on('click', '#eYesNoCloseEventYes', function(event) {
	event.preventDefault();
	var index = $(this).attr('index');
	$('#yesno-close-event-box').removeClass('is-active');
	eventClose(index);
});

$(document).on('click', '#eYesNoCloseEventNo', function(event) {
	event.preventDefault();
	$('#yesno-close-event-box').removeClass('is-active');
});


function eventClose(index) {
	var param = {};
	param._group = "Event";
	param._action = "EventStatusSet";
	param._token = Token;
	param._user_id = UserId;
	param._event_id = Current.eventList[index].event_id;
	param._parent_on = Current.eventList[index].parent_on;
	param.event_status = 'c';
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			eventListCreate();
		}
	});
}

$(document).on('click', '.eBoxEventInherit', function(event) {
	event.preventDefault();
	var eventId = $(this).attr('e-item');
	//$('#inherit-part-on').prop('checked', true);
	$('#eBoxInheritCreate').attr('eventid', eventId);
	$('#new-ref').val('');
	$("#webform-continue").prop("checked", true);
	$('#box-inherit').addClass('is-active');
});

$(document).on('click', '#eBackEventList', function(event) {
	event.preventDefault();
	location.reload();
});

$(document).on('click', '#eBoxEventNewClose', function(event) {
	event.preventDefault();
	$('#box-event-new').removeClass('is-active');
});

$(document).on('click', '#eBoxEventNewCreate', function(event) {
	// UPDATE 2022-02
	event.preventDefault();
	var eventName = $("#new-event-name").val();

	if (eventName.length < 2) {
		$('#box-event-new-error-container').show();
		$('#box-event-new-error').text('Namn på Event måste vara på minst 2 tecken!');
		return false;
	}
	if (Current.companyInfo.tdb_on == 'n') {
		var newSource = 'standard';
	} 
	else {
		var newSource = document.querySelector('input[name="new-source"]:checked').value;
	}
	if (newSource == 'standard') {
		var templateId = $('#event-template-list-items').val();
		var param = {};
		param._group = "Event";
		param._action = "EventCreate";
		param._token = Token;
		param._user_id = UserId;
		param.event_name = eventName;
		param._template_id = templateId;
	
		$.ajax({ type: "POST", url: 'service2/', data: param,
			success: function(result) {
				var data = jQuery.parseJSON(result);
				if (data.code == '1') {
					Current.eventId = data.id; 
					$('#box-event-new').removeClass('is-active');
					$('.page-section').hide();
					webform.loadWebFormSetting();
				}
				else {
					$('#box-event-new').removeClass('is-active');
					$('#message-text-modal-text').html('Eventet gick inte att spara!');
					$('#message-modal').addClass('is-active');
				}
			}
		});
	}
	else if (newSource == 'tdb') {
		let competionId = $('#event-tdb-list-items').val();
		let param = {};
		param._group = "Tdb";
		param._action = "EventCreate";
		param._token = Token;
		param._user_id = UserId;
		param.event_name = eventName;
		param._competion_id = competionId;
		Model.service(param, Current.serviceApi)
		.then(response => response.json())
		.then(function(data) {
			if (data.code == '1') {
				// Current.eventId = data.id; 
				$('#box-event-new').removeClass('is-active');
				$('.page-section').hide();
				eventListCreate();
			}
			else {
				$('#box-event-new').removeClass('is-active');
				$('#message-text-modal-text').html('Eventet gick inte att spara!');
				$('#message-modal').addClass('is-active');
			}
		})
	}
});

$(document).on('click', '.eBoxEventSettings', function(event) {
	event.preventDefault();
	$('.page-section').hide();
	Current.eventId = $(this).attr('e-item');
	webform.loadWebFormSetting();
});

$(document).on('click', '#eBoxInheritClose', function(event) {
	event.preventDefault();
	$('#box-inherit').removeClass('is-active');
});

$(document).on('click', '#eBoxInheritCreate', function(event) {
	event.preventDefault();
	var newRef = $('#new-ref').val();
	if (newRef.length < 2) {
		$('#box-inherit-error-container').show();
		$('#box-inherit-error').text('Referens måste vara på minst 2 tecken!');
		return false;
	}
	var inheretType = $('input[name="inherit_type"]:checked').val();
	
	var eventId = $(this).attr('eventid');
	var param = {};
	param._group = "Event";
	param._action = "EventInherit";
	param._token = Token;
	param._user_id = UserId;
	param._ref = newRef;
	param._source_event_id = eventId;
	if (inheretType == 'continue') {
		param._inherit_part = 'y'; 
	}
	else {
		param._inherit_part = 'n'; 
	}
	
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			//alert(result);
			var data = jQuery.parseJSON(result);
			location.reload();
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

$(document).on('click', '.eBoxEventReOpen', function(event) {
	event.preventDefault();
	var index = $(this).attr('e-index');
	
	var param = {};
	param._group = "Event";
	param._action = "EventStatusSet";
	param._token = Token;
	param._user_id = UserId;
	param._event_id = Current.eventList[index].event_id;
	param._parent_on = Current.eventList[index].parent_on;
	param.event_status = 'p';
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			eventListCreate();
		}
	});
});

$(document).on('click', '.eBoxEventClear', function(event) {
	event.preventDefault();
	Current.eventClearId = $(this).attr('e-id');
	var eventName = $(this).attr('e-name');
	$('#event-clear-type-event').html(eventName);
	$('#box-event-clear').addClass('is-active');
});

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

$(document).on('click', '#eBoxEventClearClose', function(event) {
	event.preventDefault();
	$('#box-event-clear').removeClass('is-active');
});

$(document).on('click', '#eNewEvent', function(event) {
	// UPDATED 2022-02
	event.preventDefault();
	if (Current.companyInfo.tdb_on == 'y') {
		// 2022-02-01
		let paramTdb = {};
		paramTdb._group = "Tdb";
		paramTdb._action = "CompetionsList";
		paramTdb._token = Token;
		paramTdb._user_id = UserId;
		Model.service(paramTdb, Current.serviceApi)
		.then(response => response.json())
		.then(function(data) {   
			let html = '';
			html += '<label class="modal-label radio" style="margin-top:18px">';
				html += '<input type="radio" checked name="new-source" class="eNewSource" value="tdb">';
				html += '&nbsp;&nbsp;Välj TDB tävling';
			html += '</label>';
			html += ' <div class="select modal-select" style="margin-bottom:12px">';
				html += '<select id="event-tdb-list-items" class="w-max">';
					for (var i = 0; i < data.length; i++) {
						html += '<option value="' + data[i].id + '">' + data[i].name + ' (' + data[i].start_on + ')</option>';
					}
				html += '</select>';
			html += '</div>';
			$('#tdb-competions-list').html(html);
		})
	}
	var param = {};
	param._group = "Event";
	param._action = "EventTemplateList";
	param._token = Token;
	param._user_id = UserId;
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			var html = '';
			if (Current.companyInfo.tdb_on == 'y') {
				html += '<label class="modal-label radio">';
					html += '<input type="radio" checked name="new-source" class="eNewSource" value="standard">';
					html += '&nbsp;&nbsp;Välj standard eller tidigare event som mall';
				html += '</label>';
			}
			else {
				html += '<label class="modal-label">';
					html += '&nbsp;&nbsp;Välj standard eller tidigare event som mall';
				html += '</label>';
			}
			html += ' <div class="select modal-select">';
				html += '<select id="event-template-list-items" class="w-max">';
					for (var i = 0; i < data.length; i++) {
						html += '<option value="' + data[i].value + '">' + data[i].text + '</option>';
					}
				html += '</select>';
			html += '</div>';
			$('#event-template-list').html(html);
			$('#new-event-name').val('');
			$('#box-event-new-error-container').hide();
			$('#box-event-new').addClass('is-active');
			if (Current.companyInfo.tdb_on == 'y') {
				document.getElementById('event-template-list-items').disabled = true;
			}
		}
	});	
});

$(document).on('change', '.eNewSource', function(event) {
	// 2022-02-01
	if (this.value == 'standard') {
		document.getElementById('event-tdb-list-items').disabled = true;
		document.getElementById('event-template-list-items').disabled = false;
	}
	else {
		document.getElementById('event-template-list-items').disabled = true;
		document.getElementById('event-tdb-list-items').disabled = false;
	}
});

$(document).on('click', '#eExportCsv', function(event) {
	event.preventDefault();
	exportTableToCsv("Event-Lista.csv");
});

$(document).on('click', '.eOpenEvents', function(event) {
	event.preventDefault();
	$('#event-item-list').html('');
	$('.page-section').hide();
	$('.section-event-item').show();
	Current.eventIndex = $(this).attr('index'); // 2021-10-07
	Current.eventId = $(this).attr('e-id');
	Current.eventName = $(this).attr('e-name');
	Current.counter =  $(this).attr('counter');
	Current.tdbOn = Current.eventList[Current.eventIndex].tdb_on; // 2021-10-07
	panelLoad();
	return;

});

$(document).on('change', '#select-option', function(event) {
	event.preventDefault();
	var className= $(this).val();
	if (className == '0') {
		$('.option-row').show();
	}
	else {
		$('.option-row').hide();
		$('.' + className).parent().show();
	}
});	

function eventListCreate() {

	$( "#eEventListFiler" ).prop( "checked", false );
	var param = {};
	param._group = "Event";
	param._action = "EventList";
	param._token = Token;
	param._user_id = UserId;
	//param._event_status = status;
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			Current.eventList = data;
			//Current.filter = "0";
			var html = '<table class="table" style="width:100%; margin-bottom:20px"';
			html += '<tr>';
				html += '<th style="text-align:left; background-color: #ffffff;font-size:14px">Namn</th>';
				html += '<th style="text-align:center;width:120px;background-color: #ffffff;font-size:14px">Antal</th>';
				html += '<th style="text-align:left;width:104px;background-color: #ffffff;font-size:14px">Skapad</th>';
				html += '<th style="width:104px;background-color: #ffffff;"></th>';
				html += '<th colspan="3" style="background-color: #ffffff"></th>';
			html += '</tr>';

			for (let i = 0; i < data.length; i++) {
				if (data[i].event_id == '1') {
					//
				}
				else {
						if (data[i].parent_on == 'y') {
							if (data[i].event_status == 'c') {
								html += '<tr class="EventComplete">';
							}
							else {
								html += '<tr>';
							}	
							html += '<td class="eOpenEvents pointer" index="' + i + '" e-name="' + data[i].event_name + '" e-id="' + data[i].event_id + '" counter="' +  data[i].counter + '">' + data[i].event_name + '</td>';		
							html += '<td style="text-align:center">' + data[i].counter + '</td>';	
							html += '</tr>';
						}
						if (data[i].event_status == 'c') {
							html += '<tr class="EventComplete">';
						}
						else {
							html += '<tr>';
						}
						if (data[i].participant_on == 'y') {
							if (data[i].parent_on == 'y' || data[i].child_on == 'y') {
								if (data[i].ref.length < 1) {
									data[i].ref = 'Webform 1';
								}
								html += '<td colspan="2">&nbsp;&nbsp;&nbsp;-&nbsp;&nbsp;' + data[i].ref + '</td>';		
							}
							else 
							{	
								html += '<td class="eOpenEvents pointer" index="' + i + '" e-name="' + data[i].event_name + '" e-id="' + data[i].event_id + '" counter="' +  data[i].counter + '">' + data[i].event_name + '</td>';		
								html += '<td style="text-align:center">' + data[i].counter + '</td>';
							}
						}
						else {
							html += '<td>' + data[i].event_name + '</td>';	
							html += '<td></td>';	
						}	
						
						html += '<td style="width:96px; font-size:14px">' + data[i].create_date + '</td>';
						parentOpen = 'n'; 
					
					if (data[i].event_status == 'c') { 
						html += '<td style="width:100px"></td>';
						if (data[i].parent_on == 'y') {
							//html += '<td style="text-align:right;width:66px">';
							html += '<td style="text-align:right;width:66px"><button e-index="' + i + '" class="eBoxEventReOpen button is-light is-small">Öppna</button></td>';
							if (UserId == '69') {
								html += '<td style="text-align:right;width:66px">';
									html += '<button e-id="' + data[i].event_id + '" e-name="' + data[i].event_name + '" e-index="' + i + '" class="eBoxEventClear button is-dark is-small">Radera</button>';
								html += '</td>';
							}
						}
						else if (data[i].parent_on == 'n' && data[i].child_on == 'n') {
							html += '<td style="text-align:right;width:66px">';
								html += '<button e-index="' + i + '" class="eBoxEventReOpen button is-light is-small">Öppna</button> ';
							html += '</td>';
							if (UserId == '69') {
								html += '<td style="text-align:right;width:66px">';
									html += '<button e-id="' + data[i].event_id + '" ' + 'e-name="' + data[i].event_name + '" e-index="' + i + '" class="eBoxEventClear button is-dark is-small">Radera</button>';
								html += '</td>';
							}
						}
						else if (data[i].child_on == 'y' && parentOpen == 'p') {
							html += '<td style="text-align:right;width:66px">';
								html += '<button e-index="' + i + '" class="eBoxEventReOpen button is-light is-small">Öppna</button> ';
							html += '</td>';
							if (UserId == '69') {
								html += '<td style="text-align:right;width:66px">';
									html += '<button e-id="' + data[i].event_id + '" ' + 'e-name="' + data[i].event_name + '" e-index="' + i + '" class="eBoxEventClear button is-dark is-small">Radera</button>';
								html += '</td>';
							}
						} 
						//else {
						//	html += '<button e-index="' + i + '" class="eBoxEventClear button is-dark is-small">Radera</button>';
						//}
						html += '</tr>';
					}
		
					else {
						html += '<td style="width:100px"></td>';
						if (data[i].participant_on == 'y') { 
							html += '<td style="width:30px"><button e-item="' + data[i].event_id + '" class="eBoxEventInherit button is-small"><i class="fa fa-link"></i></button></td>';
						}
						else {
							html += '<td style="width:30px"></td>';
						}
						html += '<td style="text-align:right;width:66px"><button e-item="' +data[i].event_id + '" class="eBoxEventSettings button is-link is-small">Webformulär</button></td>';
						
						html += '<td style="width:30px"><button e-index="' + i + '" class="eBoxEventClose button is-dark is-small"><i class="fas fa-times"></i></button></td>';
						html += '</tr>';
					}
					
				}
			}
			$('#event-list').html(html);
			$('.EventComplete').hide();
			$('.page-section').hide();
			$('.section-event-list').show();
		}
	});
}

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
		//var row = [], cols = rows[i].querySelectorAll("td, th");
		var row = [], cols = rows[i].querySelectorAll("td, th");
        for (var j = 0; j < cols.length - 1; j++)  // Remove the Open button -1
            row.push(cols[j].innerText);
        
		csv.push(row.join(";"));		
	}

    download_csv(csv.join("\n"), filename);
}

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

// Move to helper.js

$(document).on('click', '#eMessageBoxClose', function(event) {
	event.preventDefault();
	$('#message-box').removeClass('is-active');
});


</script>