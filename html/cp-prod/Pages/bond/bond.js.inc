<script type="text/javascript" src="js/w2ui-1.5.rc1.min.js"></script>
<script>


var Action = {};
var Session = {};
Session.Bond = {};
Session.Bond.gridCreated = false;

Action.bondList = function() {
	if (Session.Bond.gridCreated == false) {
		Action.bondCreateGrid();
		Action.transCreateGrid();
	}
	Action.bondLoadList('');
}

Action.bondLoadList = function(status) {
	var param = {};
	param._group = 'Bond';
    param._action = 'List';
	param._bond_status = status;
	if ($('#eCurrent').is(':checked')) {
		param._current = 'yes';
	}
	else {
		param._current = 'no';
	} 
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
			w2ui['bond-list'].clear();
			w2ui['bond-list'].add(jQuery.parseJSON(result));
			var amount = JSON.parse(result);

			var sum = 0;
			for (var i = 0; i < amount.length; i++) {
				sum += Number(bond[i].amount);
			}
			$('#bond-sum').text(sum);

        }
    });
}

Action.bondCreateGrid = function() {
	dg = {
		name: 'bond-list',
		show: {
			toolbar: false,
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
			var selId = Number(sel[0]);
			if (selId) {
				//alert('Clicked:' + sel[0] );
				//var customer_id  = sel[0];
				var param = {};
				param._group = "Bond";
				param._action = 'TransList';
				//Session.Credit.credit_id = sel[0];
				param._bond_id = sel[0];
				$.ajax({ type: "POST", url: 'Service.php', data: param,
					success: function(result) {
						//alert(result);
						w2ui['trans-list'].clear();
						w2ui['trans-list'].add(jQuery.parseJSON(result));
						$('#tab-trans').show();
					}
				});

			}
		} ,
		*/
		onContextMenu: function(event) {
			event.onComplete = function () {
				var sel = this.getSelection();	
				var bondId = sel[0];
				if(bondId == null){
					// Mobile
				}
				else {
					var filename = 'b' + sel[0] + '.pdf';
					var win = window.open(Settings.FirstInvoicePath  + filename, '_blank');
					win.focus();
				}
			}
		} ,

		recid   : 'bond_id',
		columns: [
			{ field : "bond_id", caption: "Bond-ID", size: "96px", attr: 'align=center' },
			{ field : "purchase_date", caption: "Date",  size: "90px", sortable: true },
			// { field : "duedate", caption: "Duedate",  size: "90px", sortable: true },
			{ field : "people_id", caption: '<div style="text-align:right">People ID</div>',  size: "80px", sortable: true, style: 'text-align: center' },
			{ field : "personal_id_number", caption: "Personal ID",  size: "100px", sortable: true },
			{ field : "people_name", caption: "Name", size: "180px", sortable: true },
			{ field : "amount", caption: '<div style="text-align:right">Amount</div>', size: "90px", sortable: true, style: 'text-align: right' },
			{ field : "bond_status", caption: '<div style="text-align:center">Status</div>', size: "60px", sortable: true, style: 'text-align: center' }
		],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#bond-list').w2grid(dg);
	Session.Bond.gridCreated = true;
}

Action.transCreateGrid = function() {
	dgTrans = {
		name: 'trans-list',
		show: {
			toolbar: false,
			footer: false,
			toolbarAdd: false,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},

		onDblClick: function(event) {
			event.onComplete = function () {
				Action.tranItemLoad(this);
			}
		},

		recid   : 'btrans_id',
		columns: [
			{ field : "booking_date", caption: "Date", size: "80px"},
			//{ field : "booking_text", caption: "Text",  size: "130px" },
			{ field : "trans_type", caption: "Type",  size: "110px" },
			//{ field : "known_as", caption: "Know as",  size: "140px"},
			//{ field : "company_name", caption: "Company",  size: "140px"},
			//{ field : "store_name", caption: "Store",  size: "160px"},
			{ field : "amount", caption: '<div style="text-align:right">Amount</div>',  size: "90px", style: 'text-align: right' },
			{ field : "balance_1380", caption: '<div style="text-align:right">Balance</div>',  size: "90px", style: 'text-align: right' },
			/*
			{ field : "amount_1680", caption: '<div style="text-align:right">Settlement</div>',  size: "90px", style: 'text-align: right' },
			{ field : "balance_1680", caption: '<div style="text-align:right">Balance</div>',  size: "90px", style: 'text-align: right' },
			{ field : "total", caption: '<div style="font-weight:bold; text-align:right">Total</div>',  size: "90px", style: 'font-weight: bold;text-align: right' },
			{ field : "credit_id", caption: 'Credit ID',  size: "120px" },
			*/
			{ field : "booking_id", caption: 'Booking ID',  size: "90px" }
		],

		records: []
	};

	$('#trans-list').w2grid(dgTrans);
	//if (Session.People.is_sp == 'y') {
		//w2ui['trans-list'].addColumn( { field : "amount_2380", caption: '<div style="text-align:right">Bonus</div>',  size: "90px", attr: 'align=right' });
	//}
	//w2ui['trans-list'].addColumn( { field : "extra", caption: 'Other',  size: "140px" });


}

$('#eSelectStatus').on('change', function(event) {
	event.preventDefault();
	var status = this.value;
	Action.bondLoadList(status);
});

$(document).ready(function() {
	Action.bondList();
});

</script>
