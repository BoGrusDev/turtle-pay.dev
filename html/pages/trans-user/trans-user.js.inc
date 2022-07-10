<script>


function TransLoad(fromDate, toDate) {
	var param = {};
	param._group = "People";
	param._action = "Trans";
	param._date_from = fromDate;
	param._date_to = toDate;
	param._token = Token;

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			createHtmlTable(data) ;
		}
	});
}

function createHtmlTable(data) {
	//if (isMobile == "yes") {
	//	var html = '<table class="table is-fullwidth "';
	//}
	//else {
		var html = '<table class="table" style="width:100%; max-width: 1064px; margin-bottom:20px"';
	//}

	html += '<tr>';
		html += '<th style="text-align:left; width:104px">Datum</th>';
		html += '<th style="text-align:left;">Typ</th>';
		html += '<th style="text-align:left;">Avsändare</th>';
		html += '<th style="text-align:right;">Belopp</th>';
		html += '<th style="text-align:right;">Saldo</th>';
	html += '</tr>';


	for (let i = 0; i < data.length; i++) {
		html += '<tr>';
		//if (isMobile == "yes") {
		//	html += '<td style="width:76px">' + data[i].date.substring(2) + '</td>';
		//}
		//else {
			html += '<td style="width:104px">' + data[i].date + '</td>';
		//}
			html += '<td>' + data[i].type + '</td>';
			html += '<td>' + data[i].ref + '</td>';
			html += '<td style="text-align:right;">' + data[i].amount + '</td>';
			html += '<td style="text-align:right;">' + data[i].balance + '</td>';
		html += '</tr>';

	}

	//alert(html);
	$('#trans-user-list').html(html);
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

	$('#navbar-user-trans').addClass('is-active');

	if (isMobile == "yes") {
		$('#ePrintTrans').hide();
	}
	else {
		$('#ePrintTrans').show();
	}

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
