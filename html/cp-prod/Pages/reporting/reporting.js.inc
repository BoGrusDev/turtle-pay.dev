
<script>



var Action = {};
var Session = {};
Session.Reporting = {};
Session.Reporting.ddmenuOpen = false;
Session.Reporting.transGridCreated = false;

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
	else if (action == 'sie-export') {
		Action.bookingSieExport();
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

Action.bookingSieExport = function() {

	// var fromDate = $('#from-date-booking').val();
	var toDate = $('#to-date-booking').val();
	var param = {};
	param._group = "Reporting";
	param._action = 'BookOrderSie';
	param._to_date = toDate;
	// param._from_date = fromDate;

	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			if (data.code == '1') {
				var html = '<table class="table" style="max-width:500px; margin:30px 10px">';
				html += '<tr><td colspan="2"><b>SIE export</b></td></tr>';
				html += '<tr><td>From date:</td><td>' + data.first_date + '</td></tr>';
				html += '<tr><td>To date:</td><td>' + data.last_date + '</td></tr>';
				html += '<tr><td>Number of verification:</td><td>' + data.counter + '</td></tr>';
				html += '<tr><td colspan="2"><a href="https://turtle-pay.com/cp-prod/sie/' + data.filename + '"><b>Ladda ner file</b></a></td></tr>';
				html += '</table>';
				$('#booking-report-list').html(html);
			}
			else {
				let html = '<table class="table" style="max-width:500px; margin:30px 10px">';
				html += '<tr><td colspan="2"><b>SIE export</b></td></tr>';
				html += '<tr><td>Message:</td><td>' + data.denied_code + '</td></tr>';
				html += '</table>';
				$('#booking-report-list').html(html);
			}
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
			let html = '<h2 class="title size-4" style="margin-bottom: 12px">Balance Account</h2>';
			html += '<p>To date: ' + param._to_date + '</p>';
			html += '<table class="report-table" style="width:620px">';
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
	
	
		var param2 = {};
		param2._group = 'Reporting';
		param2._action = 'IncomeStatement';
		param2._years = '2022,2021,2020,2019,2018';

		$.ajax({ type: "POST", url: 'Service.php', data: param2,
			success: function(result) {

				let data = jQuery.parseJSON(result);
				let html = '<h2 class="title size-4" style="padding-top:12px; margin-bottom: 12px"">Income Statement</h2>';
				
				let year =  param2._years.split(",");
			   
				html += '<table class="report-table" style="width:620px">';
				html += '<tr>';
				html += '<th style="width: 100px; text-align: left">Account no</th>';
				html += '<th style="width: 200px; text-align: left">Account</th>';
				for (let j=0; j<year.length; j++) {
					html += '<th style="width: 120px; text-align: right">' + year[j] + '</th>';
				}
				html += '</tr>';
				for(let i=0; i < data.length; i++) {
					html += '<tr>';
					html += '<td>' + data[i].account_no + '</td>';
					html += '<td>' + data[i].account_name + '</td>';
					for (j=0; j<year.length; j++) {
						if (data[i][year[j]] == null) {
							data[i][year[j]] = '';
						}
						html += '<td style="text-align: right">' + data[i][year[j]] + '</td>';
					}
					html += '</tr>';
				}
				html += '</table>';
				$('#accounts-result-list').html(html);
				Helper.show('#action-print');
			}
		});
		
	}

$(document).on('click', '#eSpecLoadList', function(event) {
	var toDate = $('#to-date-spec').val();
	var specObject = $('#spec-object').val();
	var param = {};
	param._group = "Reporting";
	param._to_date = toDate;
	if (specObject == 'customer') {
		param._action = 'SpecPeople';
	}
	else if (specObject == 'vendors') {
		param._action = 'SpecVendor';
	}
	else if (specObject == 'sp') {
		param._action = 'SpecSp';
	}
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
			var data = jQuery.parseJSON(result);
			var specObject = $('#spec-object').val();
			if (specObject == 'customer') {
				createSpecPeopleTable(data);
			}
			else if (specObject == 'vendors') {
				createSpecVendorTable(data);
			}
			else if (specObject == 'sp') {
				createSpecSpTable(data);
			}
        }
    });
});

function createSpecPeopleTable(data) {

	
	var sumBalance = 0; 
	var sumBalance1380 = 0;
	var sumBalance1680 = 0;
	

	var html = '<table id="spec-list" class="table" style="width:100%;margin-bottom:20px; max-width:940px"';
	html += '<tr>';
	html += '<th style="width:104px; text-align:center">PeopleId</th>';
	html += '<th style="width:250px;text-align:left">People</th>';
	html += '<th style="width:120px;text-align:left">Personal ID number</th>';
	html += '<th style="width:110px;text-align:right">Balance 1380</th>';
	html += '<th style="width:110px;text-align:right">Balance 1680</th>';
	html += '<th style="width:110px;text-align:right">Balance</th>';
	html += '</tr>';

	for (let i = 0; i < data.length; i++) {
		html += '<tr>';
		html += '<td style="width:104px; text-align:center;">' + data[i].people_id + '</td>';
		html += '<td style="width:250px;">' + data[i].people_name + '</td>';
	
		html += '<td style="width:120px;">' + data[i].personal_id_number + '</td>';
		html += '<td style="width:110px;text-align:right">' + currencyFormat(Number(data[i].bal1380)) + '</td>';
		html += '<td style="width:110px;text-align:right">' + currencyFormat(Number(data[i].bal1680)) + '</td>';
		html += '<td style="width:110px;text-align:right;">' + currencyFormat(data[i].balance) + '</td>';
		html += '</tr>';

		sumBalance1380 = sumBalance1380 + Number(data[i].bal1380);
		sumBalance1680 = sumBalance1680 + Number(data[i].bal1680);
		sumBalance = sumBalance + Number(data[i].balance); 
		
	}
	
	html += '<tr>';
	html += '<td style="font-weight:bold; width:104px; text-align:center;">Totalt</td>';
	html += '<td style="width:250px;"></td>';

	html += '<td style="width:120px;"></td>';
	html += '<td style="font-weight:bold;width:110px;text-align:right">' + currencyFormat(sumBalance1380) + '</td>';
	html += '<td style="font-weight:bold;width:110px;text-align:right">' + currencyFormat(sumBalance1680) + '</td>';
	html += '<td style="font-weight:bold;width:110px;text-align:right;">' + currencyFormat(sumBalance) + '</td>';
	html += '</tr>';
	

	$('#spec-list').html(html);
}

function createSpecVendorTable(data) {
	
	var sumBalance = 0; 

	var html = '<table id="spec-list" class="table" style="width:100%;margin-bottom:20px; max-width:940px"';
	html += '<tr>';
	html += '<th style="width:104px; text-align:center">CompanyId</th>';
	html += '<th style="width:250px;text-align:left">Company</th>';
	html += '<th style="width:120px;text-align:left">Company ID numberP</th>';
	html += '<th style="width:110px;text-align:right">Balance</th>';
	html += '</tr>';

	for (let i = 0; i < data.length; i++) {
		html += '<tr>';
		html += '<td style="width:104px; text-align:center;">' + data[i].company_id + '</td>';
		html += '<td style="width:250px;">' + data[i].company_name + '</td>';

		html += '<td style="width:120px;">' + data[i].company_id_number + '</td>';
		html += '<td style="width:110px;text-align:right;">' + currencyFormat(Number(data[i].balance)) + '</td>';
		html += '</tr>';
		sumBalance = sumBalance + Number(data[i].balance); 
	}

	html += '<tr>';
	html += '<td style="font-weight:bold; width:104px; text-align:center;">Totalt</td>';
	html += '<td style="width:250px;"></td>';

	html += '<td style="width:120px;"></td>';
	html += '<td style="font-weight:bold;width:110px;text-align:right;">' + currencyFormat(sumBalance) + '</td>';
	html += '</tr>';

	$('#spec-list').html(html);
}

function createSpecSpTable(data) {
	
	var sumBalance = 0; 

	var html = '<table id="spec-list" class="table" style="width:100%;margin-bottom:20px; max-width:940px"';
	html += '<tr>';
	html += '<th style="width:104px; text-align:center">PeopleId</th>';
	html += '<th style="width:250px;text-align:left">People</th>';
	html += '<th style="width:120px;text-align:left">Personal ID number</th>';
	html += '<th style="width:110px;text-align:right">Balance</th>';
	html += '</tr>';

	for (let i = 0; i < data.length; i++) {
		html += '<tr>';
		html += '<td style="width:104px; text-align:center;">' + data[i].people_id + '</td>';
		html += '<td style="width:250px;">' + data[i].people_name + '</td>';

		html += '<td style="width:120px;">' + data[i].personal_id_number + '</td>';
		html += '<td style="width:110px;text-align:right;">' + currencyFormat(Number(data[i].balance)) + '</td>';
		html += '</tr>';
		sumBalance = sumBalance + Number(data[i].balance); 		
	}

	html += '<tr>';
	html += '<td style="font-weight:bold; width:104px; text-align:center;">Totalt</td>';
	html += '<td style="width:250px;"></td>';

	html += '<td style="width:120px;"></td>';
	html += '<td style="font-weight:bold;width:110px;text-align:right;">' + currencyFormat(sumBalance) + '</td>';
	html += '</tr>';

	$('#spec-list').html(html);
}

function currencyFormat(num) {
  return num.toFixed(2).replace(/(\d)(?=(\d{3})+(?!\d))/g, '$1,')
}

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

function exportTableToCsv(filename, header) {
	var csv = [];
	
	// -- var d = new Date();
	// -- var dateNow = getTimeStamp();
	// -- csv.push(Current.eventName + ';;'+ dateNow + '\n'); 
	csv.push("Specification " + header + '\n'); 
	//csv.push("Datum;Typ;Kund;Referens;Belopp;Balans;"); 
	var rows = document.querySelectorAll('#spec-list tr');

	
    for (var i = 0; i < rows.length; i++) {
		var row = [], cols = rows[i].querySelectorAll("td, th");
		//var row = [], cols = rows[i].querySelectorAll("td");
        for (var j = 0; j < cols.length; j++) {
			var value = cols[j].innerText;
			value =  value.replace(";", ":"); // Fix	
			value =  value.replace(",", "");
			value =  value.replace(".", ",");
            row.push(value);
		}
		csv.push(row.join(";"));		
	}

    download_csv(csv.join("\n"), filename);
}

$(document).on('click', '#eExportSpec', function(event) {
	event.preventDefault();
	var header = '';
	var specObject = $('#spec-object').val();
	if (specObject == 'customer') {
		header = "Customer dept";
	}
	else if (specObject == 'vendors') {
		header = "Vendors dept";
	}
	else if (specObject == 'sp') {
		header = "Sales person rebate";
	}
	exportTableToCsv("Specification.csv", header);
});

$(document).on('click', '#eSpecItemPrint', function(event) {
	var mywindow = window.open('', 'PRINT', 'height=600,width=800');
	mywindow.document.write('<html><head></head><body>');
	mywindow.document.write($('#spec-list').html());
	mywindow.document.write('</body></html>');
	mywindow.document.close(); // necessary for IE >= 10
	mywindow.focus(); // necessary for IE >= 10
	mywindow.print();
	mywindow.close();
});

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

Action.transItemLoad = function(grid) {

	var sel = grid.getSelection();
	var booking = grid.get(sel[0]);
	var param = {};
	param._group = 'Reporting';
	param._action = 'TransGet';
	param._booking_id = booking.booking_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			
			var transObj = jQuery.parseJSON(result);
			console.log(transObj);
			var html = "";
			html += '<div class="columns">';
			html += '<div clas="column">';
			html += '<table class="table">';
			html += '<tr><th>Booking ID:</th><td>' + transObj.booking_id + '</td></tr>';
			html += '<tr><th>Booking date:</th><td>' + transObj.booking_date + '</td></tr>';
			html += '<tr><th>Type:</th><td>' + transObj.booking_type + '</td></tr>';
			if (transObj.people_id) {
				html += '<tr><th>People ID:</th><td>' + transObj.people_id + '</td></tr>';
				html += '<tr><th>Name:</th><td>' + transObj.people_name + '</td></tr>';
			}
			if (transObj.company_id) {
				html += '<tr><th>Company ID:</th><td>' + transObj.company_id + '</td></tr>';
				html += '<tr><th>Know as:</th><td>' + transObj.known_as + '</td></tr>';
			}
			if (transObj.store_id) {
				html += '<tr><th>Store ID:</th><td>' + transObj.store_id + '</td></tr>';
				html += '<tr><th>Store:</th><td>' + transObj.store_name + '</td></tr>';
			}
			if (transObj.credit_id) {
				html += '<tr><th>Credi ID:</th><td>' + transObj.credit_id + '</td></tr>';
			}
			if (transObj.ocrno) {
				html += '<tr><th>OCR no:</th><td>' + transObj.ocrno + '</td></tr>';
			}
			if (transObj.refund_id > 0)  {
				html += '<tr><th>Refund ID:</th><td>' + transObj.refund_id + '</td></tr>';
			}
			if (transObj.sales_person_people_id) {
				html += '<tr><th>Sales person ID:</th><td>' + transObj.store_id + '</td></tr>';
				html += '<tr><th>Sales person:</th><td>' + transObj.sales_people_name + '</td></tr>';
			}
			
			if (transObj.bank_account) {
				html += '<tr><th>Bank account:</th><td>' + transObj.bank_account + '</td></tr>';
			}
			
			if (transObj.invoice_filename) {
				html += '<tr><th>Invoice PDF:</th><td><a href="' + Settings.FirstInvoicePath + transObj.invoice_filename + '" target="_blank">Open</a></td></tr>';
			}
			

			html += '</table>';
			html += '</div>';
			html += '<div clas="column">';
			html += '<table class="table" >';
			html += '<tr><th>No</th><th>Account</th><th>Type</th><th class="right">Amount</th></tr>';
			for (var i=0; i<transObj.trans.length; i++) {
				
				html += '<tr>';
				html += '<td>' + transObj.trans[i].account_no + '</td>';
				html += '<td>' + transObj.trans[i].account_name + '</td>';
				html += '<td>' + transObj.trans[i].trans_type + '</td>';
				html += '<td class="right">' + transObj.trans[i].amount + '</td>';
				html += '</tr>';
			
			}

			html += '</div>';

			html += '</div>';
			$('#trans-item').html(html);
			/*
			var companyObj = jQuery.parseJSON(result);
			Helper.bindForm('company', companyObj);
			Helper.disableForm('company');
			$("select[name=is_vendor").prop('disabled', true);
			$("select[name=is_lender").prop('disabled', true);
			$("select[name=company_status").prop('disabled', true);
			$("#header-company-name").html(companyObj.company_name + " (" + companyObj.known_as + ")");
			*/
		}
	});

}

$(document).on('click', '.menu-select', function(event) {
	event.preventDefault();
    var action = $(this).attr('action');
	if (action == 'company') {
        var todaysDate = new Date();
        $('#from-date').val(Helper.convertDate(todaysDate));
        $('#to-date').val(Helper.convertDate(todaysDate));
        $('.report-section').hide();
        $('#CompanyReportList-section').show();
	}
    else
    if (action == 'booking') {
        var todaysDate = new Date();
        $('#from-date-booking').val(Helper.convertDate(todaysDate));
        $('#to-date-booking').val(Helper.convertDate(todaysDate));
        $('.report-section').hide();
        $('#BookingReportList-section').show();
	}
    else
    if (action == 'outgoing-payment') {
        alert('outgoing');
    }
    else
    if (action == 'incoming-payment') {
        Action.ingoingPaymentCreateGrid();
        Action.incomingPaymentLoadList();
        $('.report-section').hide();
        $('#IncomingPaymentReportList-section').show();
	}
	else
    if (action == 'accounts-balance') {
        var todaysDate = new Date();
        $('#from-date-accounts-balance').val(Helper.convertDate(todaysDate));
        $('#to-date-accounts-balance').val(Helper.convertDate(todaysDate));
        $('.report-section').hide();
        $('#AccountsBalanceList-section').show();
	}
	else
    if (action == 'spec') {
        var todaysDate = new Date();
        $('#to-date-spec').val(Helper.convertDate(todaysDate));
        $('.report-section').hide();
        $('#Spec-section').show();
	}
	else
    if (action == 'trans') {
        var todaysDate = new Date();
        $('#from-date-trans').val(Helper.convertDate(todaysDate));
		$('#to-date-trans').val(Helper.convertDate(todaysDate));
		
		if (Session.Reporting.transGridCreated == false) {
			Action.transCreateGrid();
			Session.Reporting.transGridCreated = true;
		}
        $('.report-section').hide();
        $('#trans-section').show();
	}
	else
    if (action == 'pep-list') {
	
		var param = {};
		param._group = "Pep";
		param._action = 'PepList';
    	$.ajax({ type: "POST", url: 'Service.php', data: param,
        	success: function(result) {
				var data = jQuery.parseJSON(result);
				html = '<table class="table is-striped" style="width:720px">';
				html += '<tr>';
				html += '<th style="width: 80px; text-align: center">People ID</th>';
				html += '<th style="width: 100px; text-align: left">Personal ID number</th>';
				html += '<th style="width: 120px; text-align: left">Name</th>';
				html += '<th style="width: 100px; text-align: left">Date</th>';
				html += '<th style="width: 80px; text-align: center">PEP</th>';
				html += '<th style="width: 80px; text-align: center">RCA</th>';
				html += '</tr>';
				for(var i=0; i < data.length; i++) {
					if (data[i].transno != '0') {

						html += '<tr>';
							html += '<td>' + data[i].people_id + '</td>';
							html += '<td>' + data[i].personal_id_number + '</td>';
							html += '<td>' + data[i].last_name + ' ' + data[i].first_name + '</td>';
							html += '<td>' + data[i].pep_date + '</td>';
							html += '<td>' + data[i].pep + '</td>';
							html += '<td>' + data[i].rca + '</td>';
						html += '</tr>';
					}
				}
				html += '</table>';
				$('#pep-report-list').html(html);
				$('.report-section').hide();
        		$('#pep-section').show();
			}
		});
	}

	else
    if (action == 'fi-report') {
        var todaysDate = new Date();
        //$('#from-date').val(Helper.convertDate(todaysDate));
		//$('#to-date').val(Helper.convertDate(todaysDate));
		$('#fi-date-from').val('2019-10-01');
        $('#fi-date-to').val('2019-12-31');
        $('.report-section').hide();
        $('#FiReport-section').show();
	}
	else
    if (action == 'tax-reporting-list') {
		$('.report-section').hide();
        $('#tax-reporting-section').show();
	}
	else
	if (action == 'tax-reporting-create') {
        var todaysDate = new Date();
		$('.report-section').hide();
        $('#tax-reporting-create-section').show();
	}
	else if (action == 'tax-reporting-mail') {
        var todaysDate = new Date();
		$('.report-section').hide();
		$('#tax-reporting-mail-section').show();
	}
});

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

$(document).on('click', '#eCreateTaxReporting', function(event) {
	
	var incomeYear =  $('#tax-reporting-create-income-year').val();
	$('#create-tax-reporting-reply').html('');
	$('#create-tax-reporting-filename').html('');
	var param = {};
	param._group = "Tax";
	param._action = 'Create';
	param._income_year = incomeYear;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			if (data.code == '1') {
				$('#create-tax-reporting-reply').html('Number of reporting created: ' + data.counter_created);
				$('#create-tax-reporting-filename').html('Tax reportfile (XML): ' + data.report_file);
			}
			else if (data.code == '0') {
				if (data.denied_code == 'reporting-already-done') {
					$('#create-tax-reporting-reply').html('Tax reporting is already done for this year!');
				}
				else if (data.denied_code == 'reporting-nothing-to-report') {
					$('#create-tax-reporting-reply').html('Noting to report for this year!');
				}
				else {
					$('#create-tax-reporting-reply').html('Something go wrong!');
				}
			}
			else  {
				$('#create-tax-reporting-reply').html('Something went wrong!');
			}
		}
	});
});


$(document).on('click', '#eGetTaxReporting', function(event) {
	
	var incomeYear =  $('#tax-reporting-income-year').val();
	Session.taxYear = incomeYear;
	var param = {};
	param._group = "Tax";
	param._action = 'ReportList';
	param._income_year = incomeYear;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			if (data.result.length > 0) {
				Action.taxReportingCreateGrid();
				for (let i=0; i<data.result.length; i++) {
					data.result[i].interest_income = Number(data.result[i].interest_income);
					data.result[i].interest_expense = Number(data.result[i].interest_expense);
				}
				w2ui['TaxReportingList'].add(data.result);
				$('#eGetTaxReporting').prop('disabled', true);
				$('#eGetTaxReporting').removeClass('is-primary');
				$('#eGetTaxReporting').hide();

				$('#taxControllerLink').attr('href', Settings.SiteUrl + 'internal-report/tax-control-records-' + Session.taxYear + '.xml');
				$('#taxControllerLink').show();
				/// Activate link

			}
			else {
				alert('No reporting exist on this year')
			}
			Session.taxNotCreated = data.not_created;
			//alert(data.not_created);
			if (data.not_created > 0) {
				$('#eTaxCreatePdf').show();
			}
			else {
				$('#eTaxCreatePdf').hide();
			}
		}
	});
});


$(document).on('click', '#eTaxCreatePdf', function(event) {
	
	var incomeYear =  $('#tax-reporting-income-year').val();
	var param = {};
	param._group = "Tax";
	param._action = 'StatementCreate';
	param._income_year = Session.taxYear;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			if (data.code == '1') {
				Session.taxNotCreated = Session.taxNotCreated - data.counter;
				if (Session.taxNotCreated > 0) {
					alert(Session.taxNotCreated + ' remains to create');
				}
				else {
					$('#eTaxCreatePdf').hide();
				}
			}
		}
	});
});

Action.taxReportingCreateGrid = function() {
	dg = {
		name: 'TaxReportingList',
		show: {
			header : false,
			toolbar: true,
			footer: true,
			//toolbarAdd: true,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},
		onDblClick: function(event) {
			event.onComplete = function () {
				let sel = this.getSelection();
				let row = this.get(sel);
				if (row[0].tax_reporting_status == 'Created') {
					let ocrno = row[0].ocrno;
					let fileUrl = Settings.FirstInvoicePath + 'k' + Session.taxYear + '-' + ocrno + '.pdf';
					var win = window.open(fileUrl, '_blank');
					win.focus();
				}
			}
		} ,
		recid   : 'tax_reporting_id',
		columns: [
            { field : "people_id", caption: "Date",  size: "80px", sortable: true },

			{ field : "last_name", caption: "LastnameName",  size: "120px", sortable: true },
			{ field : "first_name", caption: "Firstname",  size: "120px", sortable: true },
			{ field : "interest_income", caption: '<div style="text-align:right">Interest income</div>',  size: "100px", style: 'text-align: right', sortable: true  },
			{ field : "interest_expense", caption: '<div style="text-align:right">Interest cost</div>',  size: "100px", style: 'text-align: right', sortable: true  },
			{ field : "tax_reporting_status", caption: "Status", size: "90px",  sortable: true },
			{ field : "ocrno", caption: "Ocrno", size: "90px",  sortable: true },
			{ field : "email", caption: "Email", size: "240px",  sortable: true }
			// { field : "created_status", caption: "Skapad", size: "90px",  sortable: true }
			],
		records: []
	};
	$('#tax-reporting-list').w2grid(dg);
}

$(document).on('click', '#eSendTaxReportingMail', function(event) {
		
	var incomeYear =  $('#tax-reporting-mail-income-year').val();

	
	var param = {};
	param._group = "Tax";
	param._action = 'ControlStatmentBulkEmail';
	param._income_year = incomeYear;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			alert(result);
		}
	});
	
});

$(document).ready(function() {

});

</script>
