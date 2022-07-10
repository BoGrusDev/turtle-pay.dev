<script>

function BookingOrder(fromDate, toDate) {
	var param = {};
	param._group = "CompanyReport";
	param._action = "BookingOrder";
	param._date_from = fromDate;
	param._date_to = toDate;
	param._token = Token;
	param._user_id = UserId;

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			createHtmlBoOrder(data);
		}
	});
}

function BookingOrderPdf(fromDate, toDate) {
	var param = {};
	param._group = "CompanyReport";
	param._action = "BookingOrderPdf";
	param._date_from = fromDate;
	param._date_to = toDate;
	param._token = Token;
	param._user_id = UserId;

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			var path = 'https://turtle-pay.com/pdf-files/' + data.filename + '.pdf';
			//var path = 'http://turtle-pay.prod/pdf-files/' + data.filename + '.pdf';
			var win = window.open(path, '_blank');
			win.focus();
		}
	});
}

function createHtmlBoOrder(data) {
	var width = (window.innerWidth > 0) ? window.innerWidth : screen.width;
	$('#print-trans').hide();
	$('#print-boorder').show();
	var html = '<table id="boorder-list" class="table" style="width:100%;margin-bottom:20px"';
		html += '<tr>';
			html += '<th style="width:104px; text-align:left">Datum</th>';
			html += '<th style="text-align:left">Text</th>';		
			html += '<th style="text-align:left">Namn</th>';
			html += '<th style="text-align:left">Konto</th>';
			html += '<th style="text-align:right">Debet</th>';	
			html += '<th style="text-align:right">Kredit </th>';
		html += '</tr>';
	for (let i = 0; i < data.length; i++) {
		html += '<tr>';
			html += '<td style="font-weight:bold">' + data[i].date + '</td>';
			html += '<td style="font-weight:bold">' + data[i].bo_text + '</td>';
		html += '</tr>';
		for (var j=0; j<data[i].trans.length; j++) {
			if (data[i].trans[j].amount == 0) {
				// Skip
			}
			else {
				html += '<tr>';
					html += '<td></td><td></td>'; 
					html += '<td>' + data[i].trans[j].name + '</td>';
					if (data[i].trans[j].account_no == null || data[i].trans[j].account_no == '0') {
						data[i].trans[j].account_no = '';
					}
					html += '<td>' + data[i].trans[j].account_no + '</td>';
					
					if (data[i].trans[j].amount > 0) {
						html += '<td style="text-align:right">' + data[i].trans[j].list_amount + '</td>';
						html += '<td>';
					}
					else { 
						html += '<td>';
						html += '<td style="text-align:right">' + data[i].trans[j].list_amount.substring(1) + ' </td>';
					}
					
				html += '</tr>';
			}
		}
	}
	
	html += '</table>'; 
	//alert(html);
	$('#boorder-list').html(html);
}

function createSieFile(data) {
	var text = '#Header';
	var data = new Blob([text], {type: 'text/plain'});
	var url = window.URL.createObjectURL(data);
	document.getElementById('eSieDownload').href = url;
}

$(document).on('click', '#ePrintBoOrder', function(event) {
	event.preventDefault();
	var mywindow = window.open('', 'PRINT', 'height=600,width=800');
	mywindow.document.write('<html><head></head><body>');
	mywindow.document.write($('#print-boorder').html());
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
	csvFile = new Blob(["\uFEFF"+csv], {type: 'text/csv; charset=utf-8'});
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

    downloadLink.click();
}

function exportTableToCsv(filename) {
	var csv = [];
	
	//csv.push("Transaktioner" + '\n'); 
	//csv.push("Datum;Typ;Kund;Referens;Belopp;Balans;"); 
	csv.push("Bokforingsorder" + '\n'); 
	csv.push("Datum;Text;Konto;Namn;Belopp;"); 
	var rows = document.querySelectorAll('#boorder-list tr');
    for (var i = 0; i < rows.length; i++) {
		// var row = [], cols = rows[i].querySelectorAll("td, th");
		var row = [], cols = rows[i].querySelectorAll("td");
        for (var j = 0; j < cols.length; j++) {
			var value = cols[j].innerText;
			value =  value.replace(";", ":"); // Fix
			if (j == 4 || j == 5) {
				
				value =  value.replace(",", "");
				value =  value.replace(".", ",");
			}
            row.push(value);
		}
		csv.push(row.join(";"));		
	}
    download_csv(csv.join("\n"), filename);
}

$(document).on('click', '#eExportCsv', function(event) {
	event.preventDefault();
	exportTableToCsv("Bokföringsorder.csv");
});

$(document).on('click', '#eBoOrder', function(event) {
	event.preventDefault();
	var fromDate = $('#from_date').val();
	if (Date.parse(fromDate) && fromDate.length == 10) {
		// OK
	}
	else {
		$('#message-text-modal').html("Felaktigt från datum");
		$('#message-modal').addClass('is-active');
		return;
	}
	var toDate = $('#to_date').val();
	if (Date.parse(toDate) && toDate.length == 10) {
		// OK
	}
	else {
		$('#message-text-modal').html("Felaktigt till datum");
		$('#message-modal').addClass('is-active');
		return;
	}
	BookingOrder(fromDate, toDate);

});

$(document).on('click', '#eBoOrderPdf', function(event) {
	event.preventDefault();
	var fromDate = $('#from_date').val();
	if (Date.parse(fromDate) && fromDate.length == 10) {
		// OK
	}
	else {
		$('#message-text-modal').html("Felaktigt från datum");
		$('#message-modal').addClass('is-active');
		return;
	}
	var toDate = $('#to_date').val();
	if (Date.parse(toDate) && toDate.length == 10) {
		// OK
	}
	else {
		$('#message-text-modal').html("Felaktigt till datum");
		$('#message-modal').addClass('is-active');
		return;
	}
	BookingOrderPdf(fromDate, toDate);

});

$(document).on('click', '#eSieFileInit', function(event) {
	event.preventDefault();
	$('#eSieExportClose').html('Avbryt');
	$('#eSieExportClose').show();
	
	$('.sie-file-modal-date').show();
	$('.sie-file-modal-result').hide();
	$('.sie-file-modal-normal').show();
	$('#sie-file-modal-result-text').html(''); //style="margin-top: 6px">Antal verifikat i SIE-file: 24st</p>
	$('#sie-file-modal').addClass('is-active');
});

// new 2022-02-04
$(document).on('click', '#eSieExport', function(event) {
	event.preventDefault();
	let sieDate = $('#sie-date').val();
	let param = {};
	param._group = "CompanyReport";
	param._action = "SieExportCheck";
	param._sie_date = sieDate;
	param._token = Token;
	param._user_id = UserId;
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			// alert(result);
			var data = jQuery.parseJSON(result);
			if (data.code == '1') {
				sieExport(data.last_ver_no);
			}
			else if (data.code == '2') {
				$('#sie-date').val(data.new_sie_date);
				$('#sie-file-modal-result-text').html('<i>Exporten överlappar räkenskapsåret,<br>till datum har ändrats till<br>sista räkenskapsårets datum.</i>');
			}
			else if (data.code == '3') {
				sieExport(data.last_ver_no);
			}
		}
	});
});

function sieExport(lastVerNo) {
	
	$('.sie-file-modal-normal').hide();
	$('#sie-file-modal-result-text').html('Export pågår, vänta ...');

	var param = {};
	param._group = "CompanyReport";
	param._action = "SieExport";
	param._date_to = $('#sie-date').val();
	param._token = Token;
	param._user_id = UserId;
	param._last_ver_no = lastVerNo;

	//alert(JSON.stringify(param)); return;

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			// alert(result);
			var data = jQuery.parseJSON(result);
			if (data.code == '1') { 
				$('#sie-file-modal-file').attr('href', Site + 'sie-filer/' + data.siefile_name + '.zip');
				$('#sie-file-modal-file').attr('download', data.siefile_save_as);
				$('#sie-file-modal-result-text').html('Antal verifikat i SIE-file: ' + data.no_of_ver);
				$('.sie-file-modal-result').show();
				$('#eSieExportClose').html('Stäng');
				$('#eSieExportClose').show();
			}
			else if (data.code == '0') { 
				$('.sie-file-modal-normal').hide();
				if (data.denied_code == 'has-no-event-bo-account') {
					var html = '<b>Följande event saknar konto</b><br>';
					for (let i=0; i<data.list.length; i++) {
						html += data.list[i].event_name + '<br>';
					}
					$('#sie-file-modal-result-text').html(html);
					$('.sie-file-modal-date').hide();
					$('#sie-file-modal-result-text').show();
					$('#eSieExportClose').show();
				
				}
				else {
					$('#sie-file-modal-result-text').html('Inget finns att exportera!');
					$('#eSieExportClose').html('Stäng');
					$('#eSieExportClose').show();
				}
			}
			//createHtmlBoOrder(data);
			// createSieFile(data);
		}
	});	
}

$(document).on('click', '#eSieExportClose', function(event) {
	event.preventDefault();
	$('#sie-file-modal').removeClass('is-active');
});

$(document).ready(function() {

	const today = new Date()
	const yesterday = new Date(today)
	yesterday.setDate(yesterday.getDate() - 1)
	$('#sie-date').val(yesterday.toISOString().substring(0, 10));

	$('#navbar-account-order').addClass('is-active');
	var currentDate = new Date();
	var month = currentDate.getMonth() + 1;
	if (month < 10) {
		month = '0' + month;
	}
	var toDate = currentDate.toISOString().substring(0, 10);
	var fromDate = currentDate.getFullYear() + '-' + month + '-01';
	$('#from_date').val(fromDate);
	$('#to_date').val(toDate);
	$('#eBoOrder').trigger('click');
	//if (UserId != 78) {
	//	$('#eSieFileInit').hide();  // Temp 2022-02-07
	//}
});

</script>
