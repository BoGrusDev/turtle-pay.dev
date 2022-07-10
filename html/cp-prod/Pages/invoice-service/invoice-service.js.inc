
<script>

var Session = {};
Session.reminderPreGridCreated = false;
Session.emailPreGridCreated = false;
Session.eventSendLogGridCreated = false;
Session.sendEmailInProgress = false;
Session.sendReminderInProgress = false;

function loadInvoiceEvents() {
    var param = {};
    param._group = "InvoiceEvent";
    param._action = 'GetInvoiceEvent';
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            //alert(result);
            var data = jQuery.parseJSON(result);
            var body = '';
            body += '<option selected value="0">All</option>';
            for (var i=0; i < data.length; i++) {
                body += '<option value="' + data[i].invoice_event_id + '">' + data[i].invoice_event_name + ' (' + data[i].known_as + ')</option>';
            }
            
            $('#eInvoiceEventSelection').html(body);
        }
    });
}

$(document).on('click', '#eGetOverview', function(event) {

    var eventId = $('#eInvoiceEventSelection').val();
    var status = $('#eInvoiceEventItemStatusSelection').val();
    var param = {};
    param._group = "InvoiceEvent";
    param._action = 'GetOverview';
    param._event_id = eventId;
    param._status = status;
    //param._period = $('#report_settlement-people-period').val();;
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            //alert(result);
            w2ui['invoice-service-overview-list'].clear();
            var data = jQuery.parseJSON(result);
            for (var i=0; i < data.length; i++ ) { 
                switch(data[i].invoice_event_item_status) {
                case 'c':
                    data[i].invoice_event_item_status = '<span style="color:green;">Collected</span>';
                    if (data[i].confirmed_datetime) {
                        data[i].date = data[i].confirmed_datetime.substr(0,16);
                    }
                    else {
                        data[i].date = "";
                    }
                    break;
                case 'p':
                    data[i].invoice_event_item_status = "Draft";
                    data[i].date = data[i].planed_date;
                    break;
                case 'a':
                    data[i].planed_date = "Send";
                    data[i].date = data[i].planed_datetime;
                    break;
                case 'r':
                    data[i].planed_date = "Reminder";
                    data[i].date = data[i].planed_datetime;
                    break;
                case 's':
                    data[i].invoice_event_item_status = "Sent";
                    if (data[i].sent_datetime) {
                        data[i].date = data[i].sent_datetime.substr(0,16);
                    }
                    else {
                        data[i].date = "";
                    }
                    break;
                case 'x':
                    data[i].invoice_event_item_status = "Bounced";
                    if (data[i].sent_datetime) {
                        data[i].date = data[i].sent_datetime.substr(0,16);
                    }
                    else {
                        data[i].date = "";
                    }
                    break;
                case 'd':
                    data[i].invoice_event_item_status = "Denied";
                    if (data[i].sent_datetime) {
                        data[i].date = data[i].sent_datetime.substr(0,16);
                    }
                    else {
                        data[i].date = "";
                    }
                    break;
                default:
                    // code block
                }
                if (data[i].auto_reminder == 'y') {
                    data[i].auto_reminder_text = '<span style="display: block;text-align:center; color:green;">On</span>';
                }
                else {
                    data[i].auto_reminder_text = '<span style="display: block;text-align:center;">Off</span>';
                }
            }
            w2ui['invoice-service-overview-list'].add(data);
        }

    });
});

function invoiceServiceOverviewListCreateGrid () {
	dg = {
		name: 'invoice-service-overview-list',
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
                //redirectPeople(this);
                var sel = this.getSelection();
			 	var sel_record = this.get(sel[0]);
                 Session.event_item_id = sel_record.invoice_event_item_id;
                $('#item-edit-modal-email').val(sel_record.email);
                $('#item-edit-modal-auto-reminder').val(sel_record.auto_reminder);
                $('#item-edit-modal').addClass('is-active');
			}
		} ,

		recid   : 'invoice_event_item_id',
		columns: [
			//{ field : "people_id", hidden: true },
			{ field : "invoice_event_item_id", caption: "Item ID",  size: "64px", sortable: true },
            { field : "known_as", caption: "Booking id",  size: "140px", sortable: true },
            { field : "invoice_event_name", caption: "Fakturautskick",  size: "200px", sortable: true },
            { field : "people_name", caption: "Name",  size: "200px", sortable: true },
            { field : "email", caption: "Email",  size: "200px", sortable: true },
            { field : "invoice_event_item_status", caption: "Status",  size: "80px", sortable: true }
            //{ field : "date", caption: "Date",  size: "120px", sortable: true },
            //{ field : "auto_reminder_text", caption: "Auto Reminder",  size: "110px", sortable: true },
            //{ field : "auto_reminder",  hidden: true }
			
		],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#invoice-service-overview-list').w2grid(dg);
	//Session.Invoice.gridCreated = true;
}

$(document).on('click', '#eItemEditModalClose', function(event) {
	$('#item-edit-modal').removeClass('is-active');
});

$(document).on('click', '#eItemEditModalUpdate', function(event) {
    var param = {};
    param._group = "InvoiceEvent";
    param._action = 'UpdateItem';
    param._event_item_id = Session.event_item_id;

    param.invoice_event_item_status = 'd';
   
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var obj = jQuery.parseJSON(result);
            //if (obj.code == "1") {
            $('#item-edit-modal').removeClass('is-active');
                
        }
    });
	
});

function eventEmailPreCreateGrid () {
	dg = {
		name: 'event-email-pre-list',
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
                //redirectPeople(this);
             
                var sel = this.getSelection();
			 	var sel_record = this.get(sel[0]);
                Session.event_item_id = sel_record.invoice_event_item_id;
                $('#item-edit-modal-email').val(sel_record.email);
                //$('#item-edit-modal-auto-reminder').val(sel_record.auto_reminder);
                $('#item-edit-modal').addClass('is-active');
			}
		} ,
        
		recid   : 'invoice_event_item_id',
		columns: [
			//{ field : "people_id", hidden: true },
			{ field : "invoice_event_item_id", caption: "Item ID",  size: "64px", sortable: true },
            { field : "known_as", caption: "Booking id",  size: "140px", sortable: true },
            { field : "invoice_event_name", caption: "Fakturautskick",  size: "200px", sortable: true },
            { field : "people_name", caption: "Name",  size: "200px", sortable: true },
            { field : "email", caption: "Email",  size: "200px", sortable: true },
            { field : "planed_date", caption: "Send date",  size: "110px", sortable: true },
            { field : "amount", caption: "Amount",  size: "110px", sortable: true }
            
            /*
            { field : "auto_reminder_text", caption: "Auto Reminder",  size: "110px", sortable: true },
            { field : "auto_reminder",  hidden: true }
			*/
		],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#invoice-service-event-email-pre-list').w2grid(dg);
    Session.emailPreGridCreated = true;
}

function loadEventEmailPre() {
    if (Session.emailPreGridCreated == false) {
        eventEmailPreCreateGrid();
    }
    var param = {};
    param._group = "InvoiceEvent";
    param._action = 'EmailPre';
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            //alert(result);
            w2ui['event-email-pre-list'].clear();
            var data = jQuery.parseJSON(result);
            w2ui['event-email-pre-list'].add(data);
            $('#invoice-service-event-email-pre').show();
        }
    });
}

function eventReminderPreCreateGrid () {
	dg = {
		name: 'event-reminder-pre-list',
		show: {
			toolbar: true,
			footer: true,
			//toolbarAdd: true,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},

        /*
		onDblClick: function(event) {
			event.onComplete = function () {
                //redirectPeople(this);
                var sel = this.getSelection();
			 	var sel_record = this.get(sel[0]);
                 Session.event_item_id = sel_record.invoice_event_item_id;
                $('#item-edit-modal-email').val(sel_record.email);
                $('#item-edit-modal-auto-reminder').val(sel_record.auto_reminder);
                $('#item-edit-modal').addClass('is-active');
			}
		} ,
        */
		recid   : 'invoice_event_item_id',
		columns: [
			//{ field : "people_id", hidden: true },
			{ field : "invoice_event_item_id", caption: "Item ID",  size: "64px", sortable: true },
            { field : "known_as", caption: "Booking id",  size: "140px", sortable: true },
            { field : "invoice_event_name", caption: "Fakturautskick",  size: "200px", sortable: true },
            { field : "people_name", caption: "Name",  size: "200px", sortable: true },
            { field : "email", caption: "Email",  size: "200px", sortable: true },
            { field : "reminder_next_date", caption: "Reminder date",  size: "110px", sortable: true },
            { field : "sent_datetime", caption: "Sent date",  size: "150px", sortable: true },
            { field : "reminder_last_datetime", caption: "Last",  size: "150px", sortable: true },
            { field : "reminder_times", caption: "Times left",  size: "100px", sortable: true }

            /*
            { field : "auto_reminder_text", caption: "Auto Reminder",  size: "110px", sortable: true },
            { field : "auto_reminder",  hidden: true }
			*/
		],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#invoice-service-event-reminder-pre-list').w2grid(dg);
    Session.reminderPreGridCreated = true;
}

function loadEventReminderPre() {
    if (Session.reminderPreGridCreated == false) {
        eventReminderPreCreateGrid();
    }
    var param = {};
    param._group = "InvoiceEvent";
    param._action = 'EmailReminderPre';
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            //alert(result);
            w2ui['event-reminder-pre-list'].clear();
            var data = jQuery.parseJSON(result);
            w2ui['event-reminder-pre-list'].add(data);
            $('#invoice-service-event-reminder-pre').show();
        }
    });
}

function eventSendLogGridCreateGrid () {
	dg = {
		name: 'invoice-service-send-log-list',
		show: {
			toolbar: true,
			footer: true,
			//toolbarAdd: true,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},

		recid   : 'invoice_event_log_id',
		columns: [
            { field : "	invoice_event_log_id", caption: "Item ID",  size: "64px", sortable: true },
            { field : "invoice_event_name", caption: "Fakturautskick",  size: "200px", sortable: true },
            { field : "email", caption: "Email",  size: "180px", sortable: true },
            { field : "referens", caption: "Rererens",  size: "180px", sortable: true },
            { field : "amount", caption: "Amount",  size: "150px", sortable: true },
            { field : "email_type", caption: "Type",  size: "80px", sortable: true },
            { field : "status", caption: "Status",  size: "80px", sortable: true },
            { field : "action_dt", caption: "Time",  size: "160px", sortable: true },	
		],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#invoice-service-event-send-log-list').w2grid(dg);
	Session.eventSendLogGridCreated = true;
}

function initEventSendLog() {
    if (Session.eventSendLogGridCreated == false) {
        eventSendLogGridCreateGrid();
    }
    var todaysDate = new Date();
    $('#from-date-log').val(Helper.convertDate(todaysDate));
    $('#to-date-log').val(Helper.convertDate(todaysDate));
    $('#invoice-service-event-send-log').show();
}

$(document).on('click', '#eGetEventSendLog', function(event) {
	event.preventDefault();

    var param = {};
    param._group = "InvoiceEvent";
    param._action = 'SentEmail';
    param._from_date = $('#from-date-log').val();
    param._to_date = $('#to-date-log').val();
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            w2ui['invoice-service-send-log-list'].clear();
            var data = jQuery.parseJSON(result);
            w2ui['invoice-service-send-log-list'].add(data);
        }
    });
});

function initEventSendEmail() {
	Session.sendEmailInProgress = false;
    Session.sendReminderInProgress = false;
    $('#invoice-service-event-send-email').show();
}

$(document).on('click', '#eSendEmail', function(event) {
	event.preventDefault();
	if ( Session.sendEmailInProgress == true) {
        alert('Already in progress');
        return false;
    }
    Session.sendEmailInProgress = true;
    var param = {};
    param._group = "InvoiceEvent";
    param._action = 'EmailBulk';
    param._pre = "no";
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var data = jQuery.parseJSON(result);
            var html = '<pre><code>';
            html += JSON.stringify(data, null, 4) + '</pre></code>';
            $('#invoice-service-event-send-email-result').html(html);
        }
    });
    
});

$(document).on('click', '#eSendReminder', function(event) {
	event.preventDefault();
	 if ( Session.sendReminderInProgress == true) {
        alert('Already in progress');
        return false;
    }
    Session.sendReminderInProgress = true;
    var param = {};
    param._group = "InvoiceEvent";
    param._action = 'EmailReminderBulk';
    param._pre = "no";
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var data = jQuery.parseJSON(result);
            var html = '<pre><code>';
            html += JSON.stringify(data, null, 4) + '</pre></code>';
            $('#invoice-service-event-send-email-result').html(html);
        }
    });
});

$(document).on('click', '#eUpdateNames', function(event) {
	event.preventDefault();
    var param = {};
    param._group = "Tool";
    param._action = 'FixPeopleInvoiceEventItem';
    param._credit_date = "2019-08-01";
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var data = jQuery.parseJSON(result);
            var html = '<pre><code>';
            html += JSON.stringify(data, null, 4) + '</pre></code>';
            $('#invoice-service-event-send-email-result').html(html);
        }
    });
});

function CompanyNotifyPre() {
    /*
    {
        "_group" : "InvoiceEvent",
        "_action" : "BookingOrderPre"
    }
    */

    var param = {};
    param._group = "InvoiceEvent";
    param._action = 'BookingOrderPre';
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
           
            var data = jQuery.parseJSON(result);
            var html = '';
            html += '<table class="table" style="max-width:800px: width:100%">';
            html += '<tr><td>Company</td><td>Email</td><td>Date</td><td style="text-align:right">Transaktioner</td></tr>';
            for (let i=0; i<data.length; i++) {
                html += '<tr>';
                    html += '<td>' + data[i].company_name + '</td>';
                    html += '<td>' + data[i].email_report + '</td>';
                    html += '<td>' + data[i].booking_date + '</td>';
                    html += '<td style="text-align:right">' + data[i].transno + '</td>';
                html += '</tr>';
            }
            html += '</table>';

            $('#company-notify-pre-list').html(html);
            $('#company-notify-pre').show();
           
        }
    });
}

function CompanyNotifySend() {
    /*
    {
        "_group" : "InvoiceEvent",
        "_action" : "BookingOrderPre"
    }
    */
    
    var param = {};
    param._group = "InvoiceEvent";
    param._action = 'BookingOrderSend';
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var data = jQuery.parseJSON(result);
            var html = '';
            html += '<table class="table" style="max-width:800px: width:100%">';
            html += '<tr><td>Company</td><td>Email</td><td>Date</td><td>Status</td></tr>';
            for (let i=0; i<data.length; i++) {
                html += '<tr>';
                    html += '<td>' + data[i].company_name + '</td>';
                    html += '<td>' + data[i].email_report + '</td>';
                    html += '<td>' + data[i].booking_date + '</td>';
                    html += '<td>' + data[i].status + '</td>';
                html += '</tr>';
            }
            html += '</table>';

            $('#company-notify-send-list').html(html);
            $('#company-notify-send').show();
           
        }
    });
}

$(document).on('click', '.menu-select', function(event) {
	event.preventDefault();
    var action = $(this).attr('action');
	if (action == 'overview-invoicing') {
        $('.invoice-service-section').hide();
        loadInvoiceEvents();
        $('#invoice-service-overview').show();
    }
    else if (action == 'event-email-pre') {
        $('.invoice-service-section').hide();
        loadEventEmailPre();
    }
    else if (action == 'event-reminder-pre') {
        $('.invoice-service-section').hide();
        loadEventReminderPre();
    }
    else if (action == 'event-send-log') {
        $('.invoice-service-section').hide();
        initEventSendLog();
    }
    else if (action == 'event-send-email') {
        $('.invoice-service-section').hide();
        initEventSendEmail();
    }
    else if (action == 'event-company-notify-pre') {
        $('.invoice-service-section').hide();
        CompanyNotifyPre();
    }
    else if (action == 'event-company-notify-send') {
        $('.invoice-service-section').hide();
        CompanyNotifySend();
    }
    
});

$(document).ready(function() {
    invoiceServiceOverviewListCreateGrid ();
});

</script>
