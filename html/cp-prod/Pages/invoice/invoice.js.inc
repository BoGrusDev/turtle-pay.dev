
<script type="text/javascript" src="js/w2ui-1.5.rc1.min.js"></script>
<script>

/*
	Invoice.js
*/
var Action = {};
var Session = {};
Session.Invoice = {};
Session.Invoice.gridCreated = false;
Session.Invoice.gridRequestCreated = false;
Session.Invoice.gridTransCreated = false;

Action.invoiceList = function() {
	//alert('Invoice');
	if (Session.Invoice.gridCreated == false) {
		Action.invoiceCreateGrid();
	}
	Action.invoiceLoadList();
}

Action.invoiceLoadList = function() {
	var param = {};
	param._group = "Invoice";
    param._action = 'InvoiceList';
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {

			w2ui['invoice-list'].clear();
			var data = jQuery.parseJSON(result);
			w2ui['invoice-list'].add(data);
        }
    });
}

Action.invoiceCreateGrid = function() {
	dg = {
		name: 'invoice-list',
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
				Action.invoiceLoad(this);
			}
		} ,

		recid   : 'invoice_filename',
		columns: [
			{ field : "invoice_filename", hidden: true },
			{ field : "type", caption: "Type",  size: "64px", sortable: true },
			{ field : "ocrno", caption: "Ocrno",  size: "110px", sortable: true },
			{ field : "date", caption: "Date",  size: "86px", sortable: true },
			{ field : "duedate", caption: "Duedate",  size: "86px", sortable: true },
			{ field : "name", caption: 'Name',  size: "160px", sortable: true },
			{ field : "company_name", caption: 'Company',  size: "140px", sortable: true },
			{ field : "shop_name", caption: 'Store',  size: "120px", sortable: true },
			{ field : "total", caption: "Total",  size: "170px"},
			{ field : "email_sent", caption: "E-Mailed", size: "80px", sortable: true, attr: 'align=center' },
			{ field : "printed", caption: "Posted", size: "80px", sortable: true, attr: 'align=center' },
			{ field : "period", caption: "Period",  size: "140px", sortable: true },
		],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#invoice-list').w2grid(dg);
	Session.Invoice.gridCreated = true;
}

Action.invoiceLoad = function(grid) {

	var sel = grid.getSelection();
	var sel_record = grid.get(sel[0]);

	var invoiceType = sel_record.type;

	Helper.setText('invoiceModal-date', sel_record.date);
	Helper.setText('invoiceModal-duedate', sel_record.duedate);
	Helper.setText('invoiceModal-name', sel_record.name);
	if (invoiceType == 'First') {
		Helper.setText('invoiceModal-company_name', sel_record.company_name);
		Helper.setText('invoiceModal-store_name', sel_record.shop_name);
		$('#eInvoicePost').attr('filename', sel_record.invoice_filename );
		$('#eInvoicePost').show();
	}
	else {
		Helper.setText('invoiceModal-company_name', '');
		Helper.setText('invoiceModal-store_name', '');
		$('#eInvoicePost').hide();
	}
	Helper.setText('invoiceModal-total', sel_record.total);
	$('#eInvoiceView').attr('filename', sel_record.invoice_filename );
	$('#eInvoicePost').attr('filename', sel_record.invoice_filename );
	$('#invoice-modal').addClass('is-active');

}

$(document).on('click', '.eInvoice', function(event) {
	event.preventDefault();
	var action = $(this).attr('action');
	if (action == 'view') {
		var filename = $('#eInvoiceView').attr('filename');
		/// var win = window.open("http://localhost/TurtlePay/f-invoice/12344410209-5F1C47E0-0149-9F2D-2ADA-E5B5DB3469BA.pdf", '_blank');
		var win = window.open(Settings.FirstInvoicePath  + filename, '_blank');
  		win.focus();
	}
	else if (action == 'post') {
		var filename = $('#eInvoicePost').attr('filename');
		var param = {};
		param._group = 'Invoice';
		param._action = 'SetPrinted';
		param._invoice_filename = filename;
		param.printed = 'y';
		$.ajax({ type: "POST", url: 'Service.php', data: param,
			success: function(result) {
				w2ui['invoice-list'].set(filename, {printed: "y"});
			}
		});
	}
	else
	if (action == 'close') {
		$('#invoice-modal').removeClass('is-active');
	}
});

$(document).ready(function() {
	Action.invoiceList();
});
</script>
