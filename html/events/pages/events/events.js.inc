<script>


//Current.Event = {};
// var EventItemData = {};	

class EventsModel {
	async eventList() {
		let param = {};
		param._group = "Event";
		param._action = "EventList";
		param._token = Token;  // App.token
		param._user_id = UserId;
		let response = await fetch('service/', { method: 'post', body: JSON.stringify(param) })
		return response;
	}

	async reportsList(eventId) {
		let param = {};
		param._group = "Event";
		param._action = "EventItemPanelReportList";
		param._token = Token; // App.token
		param._user_id = UserId; // Globala.userId
		param._event_id = eventId;
		let response = await fetch('service/', { method: 'post', body: JSON.stringify(param) })
		return response;
	}	
	
	async reportLoad(reportId) {
		let param = {};
		param._group = "Event";
		param._action = "EventItemPanelReportLoad";
		param._token = Token; // App.token
		param._user_id = UserId; // Globala.userId
		param._panel_report_id = reportId;
		let response = await fetch('service/', { method: 'post', body: JSON.stringify(param) })
		return response;
	}

	async reportRun(data) {
		let param = {};
		param._group = "Event";
		param._action = "EventItemList2";
		param._token = Token; // App.token
		param._user_id = UserId; // Globala.userId
		param._event_id = Current.eventId; 
		param._fields = data.fields;
		param._sort = data.fields_sort;
		param._sort_order = data.sort_order;
		param._header = data.fields;
		param._part_sum = data.part_sum_on;
		param._abandoned = 'n';
		param._participant_status = 'c';

				/*
				var labels = '';
				$('#panel-form input:checked').each(function(index, value){
					//$(this).val(data[$(this).attr('name')]);
					labels += $(this).attr('label') + ',';
				});
				labels = 'Deltagare,' + labels;
				labels = labels.substring(0, labels.length - 1);
				param2._header = labels;
				*/
		let response = await fetch('service/', { method: 'post', body: JSON.stringify(param) })
		return response;

	}
}

class EventsView {
	init() {
	}
	eventList(data) {
		let html = '<table class="table" style="width:100%; margin-bottom:20px"';
		html += '<tr>';
			html += '<th style="text-align:left; background-color: #ffffff;font-size:14px">' + '' + '</th>';
			html += '<th style="text-align:center; background-color: #ffffff;font-size:14px">Antal</th>';
		html += '</tr>';
		for (let i = 0; i < data.length; i++) {
			if (data[i].event_status == 'p' && data[i].participant_on == 'y' && data[i].event_id == data[i].base_event_id ) {
				html += '<tr>';
				html += '<td class="eEventList pointer" counter="' + data[i].counter + '" e-name="' + data[i].event_name + '" e-id="' + data[i].event_id + '">' + data[i].event_name + '</td>';		
				html += '<td style="text-align:center;">' + data[i].counter + '</th>';
				html += '</tr>';
			}
		}
		$('#event-list').html(html);
		$('.page-section').hide();
		$('.section-event-list').show();
	}

	reportsList(data) { 
		let html = '<table class="table" style="width:100%; margin-bottom:20px"';
		//html += '<tr>';
			//html += '<th style="text-align:left; background-color: #ffffff;font-size:14px">' + 'Rapporter' + '</th>';
		//html += '</tr>';
		for (let i = 0; i < data.length; i++) {
			html += '<tr>';
			html += '<td class="eReportList pointer" r-id="' + data[i].panel_report_id + '">' + data[i].report_name + '</td>';		
			html += '</tr>';
		}
		$('#report-list').html(html);
		$('.page-section').hide();
		$('.section-report-list').show();
	}

	reportParticipantList(data) {
		
		let fields = Current.report.fields.split(',');
		let headers = Current.report.headers.split(',');
		//let fieldsSort = Current.report.field_sort;
		let sortOrder = Current.report.sort_order;
		/*
		if (data.code == "2") {
				if ($('#ePanelCanceled').prop('checked')) {
					//$('#ePanelCanceled').prop('checked', false);
					$('#message-text-modal').html('Inga avbokade finns!');
				} 
				else {
					$('#message-text-modal').html('Inga deltagare finns!');
				}
				$('#message-modal').addClass('is-active');
				return;
			}
		*/
		
		if (Current.report.report_name.length == 0) {
			$('#title-report-name').html('Deltagarlista');
		}
		else {
			$('#title-report-name').html(Current.report.report_name);
		}
		$('#title-event-name').html('Event: <i>' + Current.eventName + '</i>'); 
		$('#title-event-counter').html('Antal: <i>' + Current.counter + '</i>'); 
		let html = '<table id="ReportListTable" class="table" style="width:100%; margin-bottom:20px"';
		html += '<tr>';
		
		$.each(headers, function(index, value) {
			/*
			let sortOrder = 'o';
			if (fieldsSort == fields[index]) {	
				sortOrder = sortOrder;
			} 
			*/
			html += '<th class="ePanelSort" col="' + fields[index] + '" order="' + sortOrder + '" style="cursor:pointer">' + value + '</th>';
		});

		html += '</tr>';
		for (var i=0; i<data.report.length; i++) {
			html += '<tr>';
			$.each(data.report[i], function(index, value) {
				if (index == '_base_participant_id') {
					// skip
				}
				else {
					html += '<td>' + value + '</td>';
				}
			});
			// html += '<td style="text-align:right;width:66px"><button e-item="' + data.report[i]._base_participant_id + '" class="eParticipantDetails button is-dark is-small">Öppna</button></td>';
			html += '</tr>';
		}
		$('#participant-list').html(html);
		$('.page-section').hide();
		$('.section-participant-list').show();
	}
}

class EventsController {

	constructor(model, view) {
	}
	 
  	init() {
		Model.eventList()
		.then(response => response.json())
		.then(function(data) {   
			View.eventList(data);
		})
	}
	
	reportsList(eventId) {
		Current.eventId = eventId;
		Model.reportsList(eventId)
		.then(response => response.json())
		.then(function(data) {   
			View.reportsList(data);
		})
	}

	report(reportId) {
		Current.reportId = reportId;
		Model.reportLoad(reportId)
		.then(response => response.json())
		.then(function(data) {   
			Current.report = data;	
			Model.reportRun(data)
			.then(response => response.json())
			.then(function(data) {  
				View.reportParticipantList(data);
			})	
		})
	}

	reportSort(fieldsSort, sortOrder) {
		if (sortOrder == 'a') {
			sortOrder = 'd'
		}
		else {
			sortOrder = 'a';
		}
		Current.report.fields_sort = fieldsSort;
		Current.report.sort_order = sortOrder;
		Model.reportRun(Current.report)
			.then(response => response.json())
			.then(function(data) {  
			View.reportParticipantList(data);
		})	
	}
}

var Current = {};
const Model = new EventsModel();
const View = new EventsView();
const Controller = new EventsController();  // (new EventsModel(), new EventsView());


$(document).on('click', '.eEventList', function(event) {
	event.preventDefault();
	Current.counter = $(this).attr('counter');
	Current.eventId = $(this).attr('e-id');
	Current.eventName = $(this).attr('e-name');
	Controller.reportsList(Current.eventId);
});

$(document).on('click', '#eBackEventList', function(event) {
	event.preventDefault();
	$('.page-section').hide();
	$('.section-event-list').show();
});

$(document).on('click', '.eReportList', function(event) {
	event.preventDefault();
	let reportId = $(this).attr('r-id');
	Controller.report(reportId);
});

$(document).on('click', '.ePanelSort', function(event) {
	event.preventDefault();
	let fieldsSort = $(this).attr('col');
	let sortOrder = $(this).attr('order');
	Controller.reportSort(fieldsSort, sortOrder);
});

$(document).on('click', '#eBackReportList', function(event) {
	event.preventDefault();
	$('.page-section').hide();
	$('.section-report-list').show();
});

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

$(document).on('click', '#eExportCsv', function(event) {
	event.preventDefault();
	exportTableToCsv("Event-Lista.csv");
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

	var rows = document.querySelectorAll('#ReportListTable tr');
    for (var i = 0; i < rows.length; i++) {
		//var row = [], cols = rows[i].querySelectorAll("td, th");
		var row = [], cols = rows[i].querySelectorAll("td, th");
        for (var j = 0; j < cols.length; j++)
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


</script>