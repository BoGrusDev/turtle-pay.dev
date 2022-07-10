
<script type="text/javascript" src="js/w2ui-1.5.rc1.min.js"></script>
<script>

/*
	Request.js
*/
var Action = {};
var Session = {};
Session.Request = {};
Session.Request.gridCreated = false;

Action.requestList = function() {
	if (Session.Request.gridCreated == false) {
		Action.requestCreateGrid();
	}
	Action.requestLoadList();
}

Action.requestLoadList = function() {
	var param = {};
	param._group = "Request";
    param._action = 'RequestList';
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
			w2ui['request-list'].clear();
			w2ui['request-list'].add(jQuery.parseJSON(result));
        }
    });
}

Action.requestCreateGrid = function() {
	dg = {
		name: 'request-list',
		show: {
			toolbar: true,
			footer: true,
			toolbarAdd: true,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},
		/*
		onDblClick: function(event) {
			var grid = this;
			var sel = grid.getSelection();
			//var customer_id  = sel[0];
			var param = {};
			param._action = 'RequestGet';
			Session.Request.request_id = sel[0];
			param._invoice_request_id = Session.Request.request_id;
			$.ajax({ type: "POST", url: 'Service.php', data: param,
				success: function(result) {
					var dataObj = jQuery.parseJSON(result);
					// Bind data
					Helper.bindForm('request', dataObj);
					Helper.hide('#request-list');
					//Session.container = 'request';
					Helper.show('#request-info-area');
					// Get Period List for Customer
				}
			});
		} ,
		*/
		recid   : 'invoice_request_id',
		columns: [
			//{ field : "request_id", caption: "Requestid", size: "80px", attr: 'align=center' },
			{ field : "request_time", caption: "Time",  size: "140px", sortable: true },
			{ field : "personal_id_number", caption: "Personal ID",  size: "100px", sortable: true },
			{ field : "name", caption: "Name",  size: "160px", sortable: true },
			{ field : "amount", caption: '<div style="text-align:right">Amount</div>',  size: "80px", sortable: true, style: 'text-align: right' },
			{ field : "company_name", caption: "Company",  size: "120px" },
			{ field : "store_name", caption: "Store",  size: "140px",  sortable: true },
			{ field : "salesperson", caption: 'Salesperson',  size: "120px", },
			//{ field : "people_id", caption: "Peopleid",  size: "90px", attr: 'align=center' },
			//{ field : "description", caption: "Description",  size: "80px" },
			{ field : "credit_id", caption: "Credit",  size: "100px" },
			{ field : "denied_code", caption: "Denied",  size: "120px" },
			{ field : "source", caption: '<div style="text-align:center">Source</div>',  size: "80px", style: 'text-align: center' },
			{ field : "device", caption: '<div style="text-align:center">Device</div>',  size: "80px", style: 'text-align: center' },
			{ field : "invoice_request_status", caption: '<div style="text-align:center">Status</div>',  size: "70px", style: 'text-align: center', sortable: true }
		],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#request-list').w2grid(dg);
	Session.Request.gridCreated = true;
}
/*
	{ field : "salesperson", caption: '<span style="text-align:center; width:1200px">Salesperson</span>',  size: "70px", attr: 'align=center' },

$(document).on('click', '.eRequest', function(event) {
	event.preventDefault();
	var action = $(this).attr('action');
	if (action == 'cancel') {
		//$('#eCustomer-details').trigger('click');
		Helper.hide('.containers');
		Action.requestLoadList();
		Helper.show('#container-requests');
	}

	else if (action == "update") {
		alert('update');
		var param = $('#request-form').serializeArray();
		param .push(
			{ name: '_action', value: 'RequestUpdate'},
			{ name: '_request_id', value: Session.Request.request_id}
		);
		$.ajax({ type: "POST", url: Session.serviceUrl, data: param,
			success: function(result) {
				//Helper.hide('.member-edit');
				//Action.memberList();
				alert('Updated Done');
			}
		});
	}
});
*/
/*
Action.requestInsertGrid = function() {
    //Helper.validateFormClear('lender-add-form');
    //if (Helper.validateForm('lender-add-form')) {
        var param = $('#request-add-form').serializeArray();
        param .push({ name: '_action', value: 'requestInsertGrid'});
        $.ajax({ type: "POST", url: 'Service.php', data: param,
            success: function(result) {
                Action.requestLoadList();
            }
        });
    //}
}
*/

$(document).ready(function() {
	Action.requestList();
});

</script>
