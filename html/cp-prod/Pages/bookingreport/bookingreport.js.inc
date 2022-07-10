<script type="text/javascript" src="js/w2ui-1.5.rc1.min.js"></script>
<script>
''
/*
	Request.js
*/
var Action = {};
var Session = {};
Session.Bookreport= {};

Action.bookingreportList = function() {

	var param = {};
    param._action = 'BookOrderDaysReport';
	param._from_date = Helper.getValue('from_date');
	param._to_date = Helper.getValue('to_date');
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
			var data = jQuery.parseJSON(result);
			var html = "";
			html += '<h1>Booking Report</h1>';
			html += '<b>From date:  </b>' + param._from_date + '<br>';
			html += '<b>To date:    </b>' + param._to_date + '<br><br><br>';
			html += '<table class="report-table" style="width:720px">';
			html += '<tr>';
			html += '<th style="width: 70px; text-align: left">Account no</th>';
			html += '<th style="width: 200px; text-align: left">Account</th>';
			html += '<th style="width: 120px; text-align: right">Amount</th>';
			html += '</tr>';
			for(var i=0; i < data.length; i++) {
				html += '<tr>';
				html += '<td>' + data[i].account_no + '</td>';
				html += '<td>' + data[i].account_name + '</td>';
				html += '<td style="text-align: right">' + data[i].sum_account + '</td>';
				html += '</tr>';
			}
			html += '</table>';
			$('#bookingreport-list').html(html);
			Helper.show('#action-print');
		}
	});
}

$(document).on('click', '.eBookingreport', function(event) {
	event.preventDefault();
	var action = $(this).attr('action');
	if (action == 'back') {
	}
	else if (action == "GetBookingReport") {
		Action.bookingreportList();
	}
	else if (action == "print") {
    	var mywindow = window.open('', 'PRINT', 'height=600,width=800');
    	mywindow.document.write('<html><head></head><body>');
    	mywindow.document.write($('#bookingreport-list').html());
    	mywindow.document.write('</body></html>');
    	mywindow.document.close(); // necessary for IE >= 10
    	mywindow.focus(); // necessary for IE >= 10
    	mywindow.print();
    	mywindow.close();
}


});

$(document).ready(function() {
	// Setting the date
	
});

</script>
