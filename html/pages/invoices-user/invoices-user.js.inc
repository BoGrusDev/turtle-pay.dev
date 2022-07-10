<script>

function InvoicesLoad() {
	var param = {};
	param._group = "People";
	param._action = "Invoices";
	param._token = Token;
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			createHtmlTable(data) ;
		}
	});
}

function createHtmlTable(data) {
	if (isMobile == "yes") {
		var html = '<table class="table is-fullwidth "';
	}
	else {
		var html = '<table class="table" style="width:100%; max-width: 850px; margin-bottom:40px"';
	}

	html += '<tr>';
		html += '<th style="width:96px">Datum</th>';
		html += '<th class="left">Avsändare</th>';
		html += '<th class="left">Referens</th>';
		html += '<th class="right">Belopp</th>';
		html += '<th></th>';
	html += '</tr>';


	for (let i = 0; i < data.length; i++) {
		html += '<tr>';
			html += '<td style="width:94px">' + data[i].date + '</td>';
			html += '<td>' + data[i].type + '</td>';
			html += '<td>' + data[i].ref + '</td>';
			html += '<td class="right">' + data[i].total + '</td>';
			html += '<td class="right" ><button onClick="viewPdf(' + "'" + data[i].filname + "')" + '" class="button is-primary is-small">Visa faktura</button></td>';
		html += '</tr>';
	}
	$('#invoices-user-list').html(html);
}

function viewPdf(filename) {
	var path = Site + 'finvoice/' + filename;
	var win = window.open(path, '_blank');
	win.focus();
}

$(document).ready(function() {
	$('#navbar-user-invoices').addClass('is-active');
	InvoicesLoad();;
});

</script>
