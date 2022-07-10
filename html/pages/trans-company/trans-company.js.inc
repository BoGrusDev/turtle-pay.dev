<script>


function TransLoad(fromDate, toDate) {
	var param = {};
	param._group = "Company";
	param._action = "Trans";
	param._date_from = fromDate;
	param._date_to = toDate;
	param._token = Token;
	param._user_id = UserId;

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			createHtmlTable(data) ;
		}
	});
}

function createHtmlTable(data) {

	var width = (window.innerWidth > 0) ? window.innerWidth : screen.width;

	//if (isMobile == "yes") {
	//	var html = '<table class="table is-fullwidth "';
	//}
	//else {
		var html = '<table id="trans-list" class="table" style="width:100%;margin-bottom:20px"';
	//}

	html += '<tr>';
		html += '<th style="width:104px; text-align:left">Datum</th>';
		html += '<th style="text-align:left">Typ</th>';
		if (isMobile == "yes" && width <= 768) {
			//
		}
		else {
			html += '<th style="text-align:left">Kund</th>';
		}
		html += '<th style="text-align:left">Referens</th>';
		html += '<th style="text-align:right">Belopp</th>';
		html += '<th style="text-align:right;width:110px">Balans</th>';
	html += '</tr>';


	for (let i = 0; i < data.length; i++) {
		html += '<tr>';
			html += '<td style="width:104px">' + data[i].date + '</td>';
			html += '<td>' + data[i].type + '</td>';
			if (isMobile == "yes" && width <= 768) {
			}
			else {
				html += '<td>' + data[i].customer + '</td>';
			}
			html += '<td>' + data[i].ref + '</td>';
			html += '<td style="text-align:right">' + data[i].amount + '</td>';
			html += '<td style="text-align:right;width:110px">' + data[i].balance + '</td>';
		html += '</tr>';

	}

	//alert(html);
	$('#trans-company-list').html(html);
}

$(document).on('click', '#ePrintTrans', function(event) {
	event.preventDefault();
	var mywindow = window.open('', 'PRINT', 'height=600,width=800');
	mywindow.document.write('<html><head></head><body>');
	mywindow.document.write($('#print-trans').html());
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

    // Lanzamos
    downloadLink.click();
}

function exportTableToCsv(filename) {
	var csv = [];
	
	// -- var d = new Date();
	// -- var dateNow = getTimeStamp();
	// -- csv.push(Current.eventName + ';;'+ dateNow + '\n'); 
	csv.push("Transaktioner" + '\n'); 
	csv.push("Datum;Typ;Kund;Referens;Belopp;Balans;"); 
	var rows = document.querySelectorAll('#trans-list tr');
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
	exportTableToCsv("Transaktionslista.csv");
});


$(document).on('click', '#eGetTrans', function(event) {
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
	TransLoad(fromDate, toDate);

});

/*
	"date": "2019-01-01",
	"type": "Ing.bal.",
	"ref": "",
	"amount": "",
	"balance": "0.00"
*/


$(document).ready(function() {

	$('#navbar-company-trans').addClass('is-active');
	var currentDate = new Date();
	var month = currentDate.getMonth() + 1;
	if (month < 10) {
		month = '0' + month;
	}
	var toDate = currentDate.toISOString().substring(0, 10);
	var fromDate = currentDate.getFullYear() + '-' + month + '-01';
	$('#from_date').val(fromDate);
	$('#to_date').val(toDate);

	TransLoad(fromDate, toDate);

});

</script>
