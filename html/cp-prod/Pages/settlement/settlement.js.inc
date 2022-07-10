
<script>

function summaryReport() {
    var param = {};
    param._group = "SettlementReport";
    param._action = 'Summary';
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            w2ui['settlement-summary-list'].clear();
            var data = jQuery.parseJSON(result);
            w2ui['settlement-summary-list'].add(data);
            $('#report-settlement-summary-section').show();
        }
    });
}

function reportSettlementSummaryCreateGrid () {
	dgSummaryList = {
		name: 'settlement-summary-list',
		show: {
			toolbar: false,
			footer: true,
			//toolbarAdd: true,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},

        /*
		onDblClick: function(event) {
			event.onComplete = function () {
				redirectPeople(this);
			}
		} ,
        */

		recid   : 'period',
		columns: [
			//{ field : "people_id", hidden: true },
			{ field : "period", caption: "Period",  size: "80px", sortable: true },
			{ field : "settlements", caption: '<div style="text-align:right">Settlement</div>',  size: "120px", sortable: true, style: 'text-align: right' },
			{ field : "invoices", caption: '<div style="text-align:right">Invoices</div>',  size: "120px", sortable: true, style: 'text-align: right' },
        	
		],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#settlement-summary-list').w2grid(dgSummaryList);
	//Session.Invoice.gridCreated = true;
}

$(document).on('click', '#ePeopleSettlementReport', function(event) {

    var param = {};
    param._group = "SettlementReport";
    param._action = 'People';
    param._period = $('#report_settlement-people-period').val();;
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            w2ui['settlement-people-list'].clear();
            var data = jQuery.parseJSON(result);
            w2ui['settlement-people-list'].add(data);
        }

    });
});

$(document).on('click', '#eCreateMonthlyBilling', function(event) {
    alert('create');
    return;
    var param = {};
    param._group = "SettlementReport";
    param._action = 'People';
    param._period = $('#report_settlement-people-period').val();;
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            w2ui['settlement-people-list'].clear();
            var data = jQuery.parseJSON(result);
            w2ui['settlement-people-list'].add(data);
        }

    });
});

function reportSettlementPeopleCreateGrid () {
	dg = {
		name: 'settlement-people-list',
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
				redirectPeople(this);
			}
		} ,

		recid   : 'people_id',
		columns: [
			//{ field : "people_id", hidden: true },
			{ field : "people_id", caption: "People ID",  size: "64px", sortable: true },
			{ field : "people_name", caption: "Name",  size: "350px", sortable: true },
			{ field : "booking_id", caption: "Booking id",  size: "86px", sortable: true },
        	{ field : "booking_date", caption: "Date",  size: "86px", sortable: true },
			{ field : "period", caption: "Period",  size: "80px", sortable: true }
		],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#settlement-people-list').w2grid(dg);
	//Session.Invoice.gridCreated = true;
}

function redirectPeople(grid) {
    var sel = grid.getSelection();
	var sel_record = grid.get(sel[0]);
    var peopleId = sel_record.people_id;
    
    var win = window.open('https://www.turtle-pay.com/cp-prod' + "/people-direct?" + peopleId, '_blank');
    // -- var win = window.open("http://localhost/cp-prod/people-direct?" + peopleId, '_blank');
    // var win = window.open(Settings.FirstInvoicePath  + filename, '_blank');
    win.focus();
}

$(document).on('change', '#eSettlementPeriod', function(event) {
    event.preventDefault();
    Period = $(this).val();
    getPeriodDetails();
});

function getPeriodDetails() {
    var param = {};
    param._group = "SettlementReport";
    param._action = 'PeriodDetails';
    param._period = Period;
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var data = jQuery.parseJSON(result);
            $('#counts-people-settlement').html(data.counts_people_settlement);      
            $('#counts-pre-settlement').html(data.counts_pre_settlement.toString() + ' / ' + data.counts_pre_settlement_done.toString());      
            $('#counts-created-invoices').html(data.counts_created_invoices);
            $('#counts-email-sent').html(data.counts_email_not_sent.toString() + ' / ' + data.counts_email_sent.toString()); 
            $('#counts-company-settlement').html(data.counts_company_settlement);
           
        }
    });
}

$(document).on('click', '#eDoPeopleSettlement', function(event) {
	event.preventDefault();
   
    var param = {};
    param._group = "SettlementPeople";
    param._action = 'ProcessOngoing';
	param._period = Period;
	param._pre = 'no';

    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var data = jQuery.parseJSON(result);
            alert('Complete: ' + data.counts);
            getPeriodDetails();
        }
    });
});

$(document).on('click', '#eDoPreSettlement', function(event) {
    event.preventDefault();
 
    var param = {};
    param._group = "SettlementPre";
    param._action = 'PrePeopleBulk';
    param._period = Number(Period) + 1;
	param._pre = 'no';

    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var data = jQuery.parseJSON(result);
            alert('Complete: ' + data.counts);
            getPeriodDetails();
        }
    });
});

$(document).on('click', '#eDoCreateInvoices', function(event) {
    event.preventDefault();
   
    var param = {};
    param._group = 'SettlementBilling';
    param._action = 'CreateBulk';
    param._period = Number(Period) + 1;
	param._pre = 'no';

    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var data = jQuery.parseJSON(result);
            alert('Complete: ' + data.counts);
            getPeriodDetails();
        }
    });
});

$(document).on('click', '#eDoMailing', function(event) {
    event.preventDefault();
   
    //var action = $(this).attr('action');
    var param = {};
    param._group = 'MailInvoice';
    param._action = 'Email';
    param._period = Number(Period);
	
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var data = jQuery.parseJSON(result);
            alert('Complete: ' + data.counts);
            getPeriodDetails();
        }
    });
});

$(document).on('click', '#eDoCompanySettlment', function(event) {
    event.preventDefault();
   
    //var action = $(this).attr('action');
    var param = {};
    param._group = 'SettlementCompany';
    param._action = 'CompanyInterestBulk';
    param._period = Number(Period);
	
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var data = jQuery.parseJSON(result);
            alert('Complete: ' + data.counts);
            getPeriodDetails();
        }
    });
});

//eDoCompanySettlment

/*
eDoPreSettlement
eDoCreateInvoices
eDoMailing
eDoCompanySettlment
*/


$(document).on('click', '.menu-select', function(event) {
	event.preventDefault();
    var action = $(this).attr('action');
    
    if (action == 'report-settlement-summary') {
        $('.settlement-section').hide();
        summaryReport();
    }
    
    else 
	if (action == 'settlement-admin') {
        
        var param = {};
        param._group = "SettlementReport";
        param._action = 'Period';
        $.ajax({ type: "POST", url: 'Service.php', data: param,
            success: function(result) {
                var data = jQuery.parseJSON(result);
                var options =  '<option val="0">-- Select --</option>'; 
                for (var i=0; i<data.length; i++) {
                    options += '<option val="' + data[i].period + '">' + data[i].period + '</option>'; 
                }
                $('#eSettlementPeriod').html(options);
                $('.settlement-section').hide();
                $('#settlement-admin-section').show();
            }
        });
    }
    
    else
    if (action == 'report-settlement-people') {
        $('.settlement-section').hide();
        $('#report-settlement-people-section').show();
    }
    

    
});


$(document).ready(function() {
    reportSettlementSummaryCreateGrid ();
    reportSettlementPeopleCreateGrid ();
});

</script>
