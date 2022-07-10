
<script>



var Action = {};
var Session = {};
Session.Reporting = {};
Session.Reporting.ddmenuOpen = false;
Session.Reporting.transGridCreated = false;

/*
Action.companyReportListCreate = function() {

    var fromDate = $('#from-date').val();
	var toDate = $('#to-date').val();
    var param = {};
	param._group = "Reporting";
	param._action = 'CompanyReportList';
    param._to_date = toDate;
	param._from_date = fromDate;

	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {

			var data = jQuery.parseJSON(result);
			var html = "";
			html += '<h1 class="title is-size-4">Company report List</h1>';
			html += '<b>From date:  </b>' + param._from_date + '<br>';
			html += '<b>To date:    </b>' + param._to_date + '<br><br>';
			html += '<table class="table is-striped" style="width:720px">';
			html += '<tr>';
			html += '<th style="width: 250px; text-align: left">Company</th>';
			html += '<th style="width: 120px; text-align: left">Transno</th>';

			html += '</tr>';
			for(var i=0; i < data.length; i++) {
                if (data[i].transno != '0') {

    				html += '<tr>';
    				html += '<td>' + data[i].company_name + '</td>';
    				html += '<td>' + data[i].transno + '</td>';

                    html += '<td><a class="button is-small is-primary" index="'+ i + '"';
                    html += ' company-id="' + data[i].company_id;
                    html += '" id="do-send">Send report</a></td>';

    				html += '</tr>';
                }
			}
			html += '</table>';
			$('#company-report-list').html(html);
			//Helper.show('#action-print');

        }
	});
}

$(document).on('click', '.eReporting', function(event) {
	event.preventDefault();
	var action = $(this).attr('action');
	if (action == 'company-list') {
		Action.companyReportListCreate();
	}
    else if (action == 'booking-list') {
		Action.bookingReportListCreate();
	}

    else if (action == "booking-print") {
    	var mywindow = window.open('', 'PRINT', 'height=600,width=800');
    	mywindow.document.write('<html><head></head><body>');
    	mywindow.document.write($('#booking-report-list').html());
    	mywindow.document.write('</body></html>');
    	mywindow.document.close(); // necessary for IE >= 10
    	mywindow.focus(); // necessary for IE >= 10
    	mywindow.print();
    	mywindow.close();
	}
	
	else if (action == 'accounts-balance-list') {
		Action.accountsBalanceReportListCreate();
	}

	else if (action == "accounts-balance-print") {
    	var mywindow = window.open('', 'PRINT', 'height=600,width=800');
    	mywindow.document.write('<html><head></head><body>');
    	mywindow.document.write($('#accounts-balance-report-list').html());
    	mywindow.document.write('</body></html>');
    	mywindow.document.close(); // necessary for IE >= 10
    	mywindow.focus(); // necessary for IE >= 10
    	mywindow.print();
    	mywindow.close();
	}
	
});

$(document).on('click', '#do-send', function(event) {

    var fromDate = $('#from-date').val();
	var toDate = $('#to-date').val();
    var param = {};
	param._group = "Reporting";
	param._action = 'CompanyReportEmail';
    param._from_date = fromDate;
    param._to_date = toDate;
    param._company_id = $(this).attr('company-id');
    $.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			alert('Send');
			//var data = jQuery.parseJSON(result);
        }
    });
});

$(document).on('click', '#dd-trigger', function(event) {
	event.preventDefault();
	if (Session.Accounting.ddmenuOpen) {
		Session.Accounting.ddmenuOpen = false;
		$('#dd-menu').removeClass('is-active');
	}
	else {
		Session.Accounting.ddmenuOpen = true;
		$('#dd-menu').addClass('is-active');
	}
});

Action.bookingReportListCreate = function() {

    var fromDate = $('#from-date-booking').val();
	var toDate = $('#to-date-booking').val();
    var param = {};
	param._group = "Reporting";
	param._action = 'BookOrderDaysReport';
    param._to_date = toDate;
	param._from_date = fromDate;

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
			$('#booking-report-list').html(html);
			Helper.show('#action-print');
		}
	});
}

Action.ingoingPaymentCreateGrid = function() {
	dg = {
		name: 'IncommingPayment-list',
		show: {
			header         : false,
			toolbar: true,
			footer: true,
			//toolbarAdd: true,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},

		recid   : 'booking_id',
		columns: [
            { field : "booking_date", caption: "Date",  size: "80px", sortable: true },

			{ field : "people_name", caption: '<div style="text-align:left">Name</div>',  size: "230px", sortable: true },
			{ field : "ocrno", caption: "OCR no",  size: "120px", sortable: true },
			{ field : "credit_id", caption: "Credit ID",  size: "120px", sortable: true },
			{ field : "amount", caption: '<div style="text-align:right">Amount</div>',  size: "100px", style: 'text-align: right' },
            	{ field : "people_id", caption: '<div style="text-align:right">Peopl ID</div>', size: "90px", style: 'text-align: right', sortable: true }
			],
		records: []
	};
	$('#IncommingPayment-list').w2grid(dg);
}

Action.incomingPaymentLoadList = function() {
	var param = {};
	param._group = 'Reporting';
    param._action = 'IngoingPaymentList';
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
			//w2ui['ingoing-payment-list'].clear();
			var data = jQuery.parseJSON(result);
			w2ui['IncommingPayment-list'].add(data);
        }
    });
}

Action.accountsBalanceReportListCreate = function() {

	var toDate = $('#to-date-accounts-balance').val();
	var param = {};
	param._group = 'Reporting';
	param._action = 'AccountsBalance';
	param._to_date = toDate;

	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			
			var data = jQuery.parseJSON(result);
			var html = "";
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
			$('#accounts-balance-report-list').html(html);
			Helper.show('#action-print');
		}
	});
}

$(document).on('click', '#eTransLoadList', function(event) {
	var fromDate = $('#from-date-trans').val();
	var toDate = $('#to-date-trans').val();
	var param = {};
	param._group = "Reporting";
	param._action = 'TransList';
	param._to_date = toDate;
	param._from_date = fromDate;
	
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {

			w2ui['trans-list'].clear();
			var data = jQuery.parseJSON(result);
			w2ui['trans-list'].add(data);
        }
    });
});

$(document).on('click', '#eTransItemPrint', function(event) {
	var mywindow = window.open('', 'PRINT', 'height=600,width=800');
	mywindow.document.write('<html><head></head><body>');
	mywindow.document.write($('#trans-item').html());
	mywindow.document.write('</body></html>');
	mywindow.document.close(); // necessary for IE >= 10
	mywindow.focus(); // necessary for IE >= 10
	mywindow.print();
	mywindow.close();
});

Action.transCreateGrid = function() {
	dgTrans = {
		name: 'trans-list',
		show: {
			toolbar: true,
			footer: true,
			//toolbarAdd: true,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},

		onDblClick: function(event) {
			event.onComplete = function () {
				Action.transItemLoad(this);
			}
		} ,

		recid   : 'booking_id',
		columns: [		
			{ field : "booking_id", caption: "Booking ID",  size: "110px" },
			{ field : "booking_date", caption: "Date",  size: "86px", sortable: true },
			{ field : "booking_type", caption: 'Type',  size: "100px", sortable: true },
			{ field : "people_name", caption: 'Namn',  size: "160px", sortable: true },
			{ field : "known_as", caption: 'Know as',  size: "160px", sortable: true }
		],
		records: []
	};
	$('#trans-list').w2grid(dgTrans);
}

*/



$(document).on('click', '#eFinansiellReportCreate', function(event) {


	var fromDate = $('#fi-date-from').val();
	
	var toDate = $('#fi-date-to').val();
	var param = {};
	param._group = "FiReporting";
	param._action = 'Summary';
	param._date_from = fromDate;
	param._date_to = toDate;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			
			/*
			"amount_of_1380": "1468039.05",
			"amount_of_1680": "-55443.50",
			"amount_of_granted_credits": "3045998.80",
			"number_of_outstanding_credits": "440",
			"number_of_granted_credits": "688",
			"number_of_customer": "698",
			"interest_income": 12428,
			"fee_income": 21104.63
			*/
			var data = jQuery.parseJSON(result);
		
			var html = "";
			html += '<div class="columns">';
			html += '<div clas="column">';
			html += '<table class="table">';
			html += '<tr><th>Amount of 1380:</th><td>' + data.amount_of_1380 + '</td></tr>';
			html += '<tr><th>Amount of 1680:</th><td>' + data.amount_of_1680 + '</td></tr>';

			html += '<tr><th>Amount of granted credits:</th><td>' + data.amount_of_granted_credits + '</td></tr>';
			html += '<tr><th>Number of outstanding credits:</th><td>' + data.number_of_outstanding_credits + '</td></tr>';
			html += '<tr><th>Number of granted credits:</th><td>' + data.number_of_granted_credits + '</td></tr>';
			html += '<tr><th>Number of customer:</th><td>' + data.number_of_customer + '</td></tr>';
			html += '<tr><th>Interest income:</th><td>' + data.interest_income + '</td></tr>';
			html += '<tr><th>Fee income:</th><td>' + data.fee_income + '</td></tr>';

			html += '</table>';
			html += '</div>';
			

			html += '</div>';
			$('#finansiell-report-list').html(html);
			
		}
	});
	
});

$(document).on('click', '.menu-select', function(event) {
	event.preventDefault();
    var action = $(this).attr('action');
	if (action == 'fi-report') {
        var todaysDate = new Date();
        //$('#from-date').val(Helper.convertDate(todaysDate));
		//$('#to-date').val(Helper.convertDate(todaysDate));
		$('#fi-date-from').val('2019-10-01');
        $('#fi-date-to').val('2019-12-31');
        $('.report-section').hide();
        $('#FiReport-section').show();
	}
	/*
    else
    if (action == 'booking') {
        var todaysDate = new Date();
        $('#from-date-booking').val(Helper.convertDate(todaysDate));
        $('#to-date-booking').val(Helper.convertDate(todaysDate));
        $('.report-section').hide();
        $('#BookingReportList-section').show();
	}
	*/
    
});

$(document).ready(function() {

});

</script>
