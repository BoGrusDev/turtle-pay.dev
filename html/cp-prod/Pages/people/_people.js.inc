<script>

/*
	People.js
*/
var Action = {};
var Session = {};
Session.People = {};
Session.People.gridCreated = false;
Session.People.gridRequestCreated = false;
Session.People.gridTransCreated = false;

var peopleObj;

var PreTrans; // NEW 2020-02-06
// var dataBillingFee;
var TransList;

Action.peopleList = function() {
	if (Session.People.gridCreated == false) {
		Action.peopleCreateGrid();
	}
	Action.peopleLoadList();
}

Action.peopleLoadList = function() {
	var param = {};
	param._group = 'People';
    param._action = 'List';
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
			w2ui['people-list'].clear();
			var data = jQuery.parseJSON(result);
			// Updated 2021-01-13
			for (let i=0; i<data.length; i++) {
				data[i].people_id = Number(data[i].people_id);
			}
			w2ui['people-list'].add(data);
        }
    });
}

Action.peopleCreateGrid = function() {
	dg = {
		name: 'people-list',
		show: {
			header         : false,
			toolbar: true,
			footer: true,
			//toolbarAdd: true,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},

		onDblClick: function(event) {
			event.onComplete = function () {
				Action.peopleLoad(this);
			}
		} ,

		recid   : 'people_id',
		columns: [
			{ field : "people_id", caption: '<div style="text-align:right">People-ID</div>', size: "70px", style: 'text-align: center', sortable: true },
			{ field : "personal_id_number", caption: "Personal ID-number",  size: "100px", sortable: true },
			{ field : "people_name", caption: '<div style="text-align:left">Name</div>',  size: "240px", sortable: true },
			{ field : "email", caption: "Email",  size: "170px", sortable: true },
			{ field : "mobile", caption: "Mobile no",  size: "90px", sortable: true },
			{ field : "address", caption: "Address",  size: "180px", sortable: true },
			{ field : "postcode", caption: "Postcode",  size: "60px", sortable: true },
			{ field : "city", caption: "City",  size: "100px", sortable: true },
			{ field : "ocrno", caption: "Ocrno",  size: "100px", sortable: true },
			{ field : "overdue", caption: '<div style="text-align:center">Overdues</div>',  size: "60px", style: 'text-align: center', sortable: true }

			//{ field : "people_status", caption: '<div style="text-align:center">Status</div>',  size: "70px", attr: 'align=center', sortable: true,
			//render:function(record) {
			//		return '<div style="font-size: 14px;">'+record.people_status + '</div>'}
			//}
			],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#people-list').w2grid(dg);
	Session.People.gridCreated = true;
}

Action.peopleCreateRequestGrid = function() {
	dg2 = {
		name: 'people-request-list',
		show: {
			toolbar: true,
			footer: true,
			toolbarAdd: false ,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},

		//onDblClick: function(event) {
			//Action.peopleLoad(this);
		//} ,

		recid   : 'invoice_request_id',
		columns: [
			//{ field : "request_id", caption: "Requestid", size: "80px", attr: 'align=center' },
			{ field : "request_time", caption: "Time",  size: "84px", sortable: true },
			{ field : "store_name", caption: "Store",  size: "120px", sortable: true },
			{ field : "amount", caption: "Amount",  size: "70px", sortable: true, attr: 'align=right' },
			{ field : "description", caption: "Desc.",  size: "80px", sortable: true },
			{ field : "denied_code", caption: "Denied",  size: "60px", sortable: true },
			{ field : "salesperson", caption: 'Salesperson',  size: "100px", sortable: true },
			{ field : "company_name", caption: "Company",  size: "100px", sortable: true},
		],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#people-request-list').w2grid(dg2);
	Session.People.gridRequestCreated = true;
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
		/*
		onRefresh: function(event) {
			alert('refresh');
		},
		*/
		onDblClick: function(event) {
			event.onComplete = function () {
				Action.tranItemLoad(this);
			}
		},
		/*
		onLoad: function(event) {
			event.done(function () {
	  			console.log("load complete");
  			});
    	},
		*/
		recid   : 'btrans_id',
		columns: [
			{ field : "booking_date", caption: "Date", size: "80px"},
			{ field : "booking_text", caption: "Text",  size: "130px" },
			{ field : "trans_type", caption: "Type",  size: "110px" },
			{ field : "known_as", caption: "Know as",  size: "140px"},
			//{ field : "company_name", caption: "Company",  size: "140px"},
			//{ field : "store_name", caption: "Store",  size: "160px"},
			{ field : "amount_1380", caption: '<div style="text-align:right">Credit amt.</div>',  size: "90px", style: 'text-align: right' },
			{ field : "balance_1380", caption: '<div style="text-align:right">Balance</div>',  size: "90px", style: 'text-align: right' },
				
			{ field : "amount_2350", caption: '<div style="text-align:right">Bond amt.</div>',  size: "90px", style: 'text-align: right' },
			{ field : "balance_2350", caption: '<div style="text-align:right">Balance</div>',  size: "90px", style: 'text-align: right' },
			
			{ field : "amount_1680", caption: '<div style="text-align:right">Settlement</div>',  size: "90px", style: 'text-align: right' },
			{ field : "balance_1680", caption: '<div style="text-align:right">Balance</div>',  size: "90px", style: 'text-align: right' },
				
			{ field : "total", caption: '<div style="font-weight:bold; text-align:right">Total</div>',  size: "90px", style: 'font-weight: bold;text-align: right' },
			{ field : "credit_id", caption: 'Credit/Bond ID',  size: "120px" },
			{ field : "booking_id", caption: 'Booking ID',  size: "90px" },
			{ field : "company_id", caption: 'Company ID',  size: "90px" }
		],

		records: []
	};

	$('#trans-list').w2grid(dgTrans);

}

Action.bondCreateGrid = function() {
	dgBond = {
		name: 'bond-list',
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
				var sel = this.getSelection();
				//console.log(sel);
				let row = this.get(sel[0]);
				Action.bondListLoad(row);
			}
		} ,


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
			{ field : "bond_status", caption: '<div style="text-align:center">Status</div>', size: "60px", sortable: true, style: 'text-align: center' },
			{ field : "term", caption: '<div style="text-align:center">Term</div>', size: "60px", sortable: true, style: 'text-align: center' },
			{ field : "interest_rate", caption: '<div style="text-align:center">Interest</div>', size: "60px", sortable: true, style: 'text-align: center' }
		],
		
		records: []
	};

	$('#bond-list').w2grid(dgBond);
	//if (Session.People.is_sp == 'y') {
		//w2ui['trans-list'].addColumn( { field : "amount_2380", caption: '<div style="text-align:right">Bonus</div>',  size: "90px", attr: 'align=right' });
	//}
	//w2ui['trans-list'].addColumn( { field : "extra", caption: 'Other',  size: "140px" });


}

Action.creditsCreateGrid = function() {
	dgCredits = {
		name: 'credits-list',
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
				var sel = this.getSelection();
				// console.log(sel);
				let row = this.get(sel[0]);
				//console.log(row);
				Action.creditListLoad(row);
			}
		} ,
		recid   : 'credit_id',
		columns: [
			{ field : "credit_id", caption: "Creditno.", size: "100px"},
			{ field : "start_date", caption: "Date", size: "90px"},
			{ field : "known_as", caption: "Know as", size: "140px"},
			{ field : "receipt_number", caption: '<div style="text-align:right">Receipt</div>',  size: "100px"},
			{ field : "amount", caption: '<div style="text-align:right">Amount</div>',  size: "84px", style: 'text-align: right' },
			{ field : "monthly_no", caption: '<div style="text-align:center">Paym.terms</div>', style: 'text-align: center', size: "64px"},
			{ field : "interest_margin", caption: '<div style="text-align:center">Margin %</div>', style: 'text-align: center', size: "64px"}	,
			{ field : "credit_status", caption: '<div style="text-align:center">Status</div>', style: 'text-align: center', size: "60px"}
		],
		records: []
	};

	$('#credits-list').w2grid(dgCredits);
	//if (Session.People.is_sp == 'y') {
		//w2ui['trans-list'].addColumn( { field : "amount_2380", caption: '<div style="text-align:right">Bonus</div>',  size: "90px", attr: 'align=right' });
	//}
	//w2ui['trans-list'].addColumn( { field : "extra", caption: 'Other',  size: "140px" });


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
			//{ field : "name", caption: 'Name',  size: "160px", sortable: true },
			{ field : "company_name", caption: 'Company',  size: "160px", sortable: true },
			{ field : "shop_name", caption: 'Store',  size: "160px", sortable: true },
			{ field : "receipt_number", caption: 'Receipt',  size: "160px", sortable: true },
			{ field : "monthly_payment_total", caption: '<div style="text-align:right">Pay</div>',  size: "90px", style: 'text-align: right'},
			{ field : "total", caption: '<div style="text-align:right">Total</div>',  size: "100px", style: 'text-align: right'},
			{ field : "collection", caption: '<div style="text-align:right">Collection</div>',  size: "90px", style: 'text-align: right'},
			{ field : "overdue", caption: '<div style="text-align:right">Overdue</div>',  size: "90px", style: 'text-align: right'}

			//{ field : "email_sent", caption: '<div style="text-align:center">E-Mailed</div>', size: "80px", sortable: true, style: 'text-align: center' },
			//{ field : "printed", caption: '<div style="text-align:center">Posted</div>', size: "80px", sortable: true, style: 'text-align: center' }
		],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#invoice-list').w2grid(dg);
	//Session.Invoice.gridCreated = true;
}

Action.peopleLoad = function(grid) {
	var sel = grid.getSelection();
	Session.People.people_id = sel[0];
	Action.peopleDetails();
	Action.settingsLoad();
	Action.companyConnectios();
	Helper.hide('#peoplelist-section');
	Helper.show('#people-section');
	ucListCreateGrid();
}

Action.peopleDetails = function() {
	var param = {};
	param._group = 'People';
	param._action = 'Get';
	param._people_id = Session.People.people_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			peopleObj = jQuery.parseJSON(result); // Global
			Helper.bindForm('people', peopleObj);
			Helper.disableForm('people');
			$("#header-people-name").html(peopleObj.first_name + " " + peopleObj.last_name);
			$("#people-name").val(peopleObj.first_name + " " + peopleObj.last_name);
			$("select[name=people_status").prop('disabled', true);

			w2ui['uc-list'].clear();
			var data = new Array();
			data[0] = {};
			data[0].uc_item_id = '1';
			data[0].uc_item = '';
			if (peopleObj.pep == 'y' || peopleObj.rca == 'y') {
				data[0].value = '<b>High</b>';
			}
			else {
				data[0].value = 'Normal';
			}
			data[0].text = 'Risk';
			
			data[1] = {};
			data[1].uc_item_id = '2';
			data[1].uc_item = '';
			if (peopleObj.pep == 'y') {
				data[1].value = 'Yes';
			}
			else {
				data[1].value = 'No';
			}
			data[1].text = 'PEP';
			
			data[2] = {};
			data[2].uc_item_id = '2';
			data[2].uc_item = '';
			if (peopleObj.rca == 'y') {
				data[2].value = 'Yes';
			}
			else {
				data[2].value = 'No';
			}
			data[2].text = 'RCA';
			
			// Sanction list
			data[3] = {};
			data[3].uc_item_id = '4';
			data[3].uc_item = '';
			if (peopleObj.is_sanction_list == 'y') {
				data[3].value = 'Yes';
			}
			else {
				data[3].value = 'No';
			}
			data[3].text = 'Sanction list';

			w2ui['uc-list'].add(data);

			if (peopleObj.has_uc_check == 'y') {
				$('#eUcDetails').show();
				$('#eUcPrint').show();
				$('#eUcOpen').hide();
				Action.getUcStatus(Session.People.people_id); 
			}
			else {
				$('#eUcDetails').hide();
				$('#eUcPrint').hide();
				$('#eUcOpen').show();
			}
		}
	});
}

$(document).on('click', '#eSparGet', function(event) {
	event.preventDefault();
	$('#spar-personal-id-number').val($('#personal_id_number').val());
	$('#spar-people-first-name-current').val(peopleObj.first_name);
	$('#spar-people-last-name-current').val(peopleObj.last_name);
	$('#spar-people-first-name').val('');
	$('#spar-people-last-name').val('');
	$('#spar-address').val('');
	$('#spar-postcode').val('');
	$('#spar-city').val('');
	$('#eDoSpar').show();
	$('#eSaveSpar').hide();
	Helper.addClass('spar-modal', 'is-active');
});

$(document).on('click', '#eCloseSpar', function(event) {
	event.preventDefault();
	Helper.removeClass('spar-modal', 'is-active');
});

$(document).on('click', '#eDoSpar', function(event) {
	event.preventDefault();

	$('#eDoSpar').hide();
    var param = {};
    param._group = "Tool";
    param._action = 'Spar';
	param._personal_id_number = $('#spar-personal-id-number').val();
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var data = jQuery.parseJSON(result);
			console.log(data);
			
			if(data.hasOwnProperty("Undantag")) {
				alert(data.Undantag.Beskrivning);
			}
			else {
				//if (typeof data.Undantag.Kod != "undefined") {
				if (Array.isArray(data.PersonsokningSvarsPost.Adresser.Folkbokforingsadress)) {
					var address = data.PersonsokningSvarsPost.Adresser.Folkbokforingsadress[0].Utdelningsadress2;
					var postcode = data.PersonsokningSvarsPost.Adresser.Folkbokforingsadress[0].PostNr;
					var city = data.PersonsokningSvarsPost.Adresser.Folkbokforingsadress[0].Postort;
				}
				else {
					var address = data.PersonsokningSvarsPost.Adresser.Folkbokforingsadress.Utdelningsadress2;
					var postcode = data.PersonsokningSvarsPost.Adresser.Folkbokforingsadress.PostNr;
					var city = data.PersonsokningSvarsPost.Adresser.Folkbokforingsadress.Postort;
				}

				if (Array.isArray(data.PersonsokningSvarsPost.Persondetaljer)) {
					var firstName = data.PersonsokningSvarsPost.Persondetaljer[0].Fornamn;
					var lastName = data.PersonsokningSvarsPost.Persondetaljer[0].Efternamn;
					var gender = data.PersonsokningSvarsPost.Persondetaljer[0].Kon;
				}
				else {
					var firstName = data.PersonsokningSvarsPost.Persondetaljer.Fornamn;
					var lastName = data.PersonsokningSvarsPost.Persondetaljer.Efternamn;
					var gender = data.PersonsokningSvarsPost.Persondetaljer.Kon;
				}

				$('#spar-people-first-name').val(firstName);
				$('#spar-people-last-name').val(lastName);

				var gender = data.PersonsokningSvarsPost.Persondetaljer.Kon;
				$('#spar-gender').val(gender);
				$('#spar-address').val(address);
				$('#spar-postcode').val(postcode);
				$('#spar-city').val(city);
				$('#eSaveSpar').show();
			}
		}
	});
});

$(document).on('click', '#eSaveSpar', function(event) {
	event.preventDefault();

	peopleObj.first_name = $('#spar-people-first-name').val();
	peopleObj.last_name = $('#spar-people-last-name').val();
	$("#people-name").val(peopleObj.first_name + " " + peopleObj.last_name);

    var param = {};
    param._group = "People";
    param._action = 'PeopleUpdate';
	param._people_id = Session.People.people_id;
	param.first_name = peopleObj.first_name;
	param.last_name = peopleObj.last_name;
	param.address = $('#spar-address').val();
	param.postcode = $('#spar-postcode').val();
	param.city = $('#spar-city').val();
	param.gender = $('#spar-gender').val();
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var data = jQuery.parseJSON(result);
			console.log(data);

			$('#address').val($('#spar-address').val());
			$('#postcode').val($('#spar-postcode').val());
			$('#city').val($('#spar-city').val());
			$('#gender').val($('#spar-gender').val());
			$('#eSaveSpar').hide();
			Helper.removeClass('spar-modal', 'is-active');
		}
	});
});

$(document).on('click', '#eUcOpen', function(event) {
	event.preventDefault();
	$('#uc-personal-id-number').val($('#personal_id_number').val());
	$('#uc-people-name').val($('#people-name').val());
	Helper.addClass('uc-modal', 'is-active');
});

$(document).on('click', '#eCloseUc', function(event) {
	event.preventDefault();
	Helper.removeClass('uc-modal', 'is-active');
});

$(document).on('click', '#eDoTheRealUc', function(event) {
	event.preventDefault();

    var param = {};
    param._group = "Uc";
    param._action = 'GetFromUc';
	param._personal_id_number = $('#uc-personal-id-number').val();
	
	param._people_id = Session.People.people_id;
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            var data = jQuery.parseJSON(result);
			console.log(data);
			if (data.code == '1') {
			
				Action.peopleDetails();
				Action.settingsLoad();
				Helper.removeClass('uc-modal', 'is-active');
			}
			else {
				alert('Problem to take UC');
				Helper.removeClass('uc-modal', 'is-active');
			}
		}
	});
	
});

Action.settingsLoad = function() {

	var param = {};
	param._group = 'Setting';
	param._action = 'GetPeople';
	param._people_id = Session.People.people_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			var dataObj = jQuery.parseJSON(result);
			Helper.bindForm('settings', dataObj);
			Helper.disableForm('settings');
		}
	});

	var param2 = {};
	param2._group = 'Setting';
	param2._action = 'GetGlobal';
	$.ajax({ type: "POST", url: 'Service.php', data: param2,
		success: function(result) {
			var dataObj = jQuery.parseJSON(result);
			Helper.bindForm('settings-global', dataObj);
			Helper.disableForm('settings-global');
		}
	});
}

Action.companyConnectios = function() {
	var param = {};
	param._group = "People";
	param._action = 'CompanyConnections';
	param._people_id = Session.People.people_id;
	//param5._company_id = Session.Company.company_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			if (data.length > 0) {
				$('#tab-people-tp').show();
				var html = "";
				html += '<h3>Company connections</h3>';

				html += '<table class="table">';
				html += '<tr>';
				html += '<th>Known as</th>';
				html += '<th>Company</th>';
				html += '<th>Priv</th>';
				html += '</tr>';
				for(var i=0; i < data.length; i++) {
					html += '<tr>';
					html += '<td>' + data[i].known_as + '</td>';
					html += '<td>' + data[i].company_name + '</td>';
					html += '<td>' + data[i].priv + '</td>';
					html += '</tr>';
				}
				html += '</table>';
				$('#people-info-company-connections').html(html);
			}
		}
	});
}

Action.detailsCreate = function() {

	$('#people-section').w2form({
	   name   : 'peopleform',
	   header : 'Details',
	   url    : 'server/post',
	   fields : [
		   { field: 'first_name', type: 'text', required: true },
		   { field: 'last_name',  type: 'text', required: true },
		   { field: 'comments',   type: 'text'},
		   { field: 'address1', type: 'text', required: true },
		   { field: 'address2', type: 'text' },
		   { field: 'city', type: 'text', required: true },
		   { field: 'state', type: 'text', required: true },
		   { field: 'zip', type: 'int', required: true },
		   { field: 'short_bio', type: 'text' },
		   { field: 'talk_name', type: 'text', required: true },
		   { field: 'description', type: 'text' }
	   ],
	   tabs: [
		   { id: 'tab1', caption: 'General' },
		   { id: 'tab2', caption: 'Address'},
		   { id: 'tab3', caption: 'About' }
	   ],
	   actions: {
		   reset: function () {
			   this.clear();
		   },
		   save: function () {
			   this.save();
		   }
	   }
   });

}

function tabDetails () {
	$('.people-tabs').hide();
	$('#tab-details').show();
}

Action.creditCreateDetailGrid = function() {
	dgCreditDetailList = {
		name: 'credit-detail-list',
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
				Action.creditDetailLoad(this);
			}
		},
		

		recid   : 'btrans_id',
		columns: [
			{ field : "booking_date", caption: "Date", size: "80px"},
			//{ field : "booking_text", caption: "Text",  size: "130px" },
			{ field : "trans_type", caption: "Type",  size: "110px" },
			{ field : "amount", caption: '<div style="text-align:right">Amount</div>',  size: "90px", style: 'text-align: right' },
			{ field : "balance", caption: '<div style="text-align:right">Balance</div>',  size: "90px", style: 'text-align: right' }
			//{ field : "booking_id", caption: 'Booking ID',  size: "90px" }
		],

		records: []
	};

	$('#credit-detail-list').w2grid(dgCreditDetailList);

}
	
Action.creditListLoad = function(sel) {
	Session.People.credit_id = sel.credit_id;
	Session.People.monthly_no = sel.monthly_no;
	Session.People.interest_margin = sel.interest_margin;
	var param = {};
	param._group = 'People';
	param._action = 'CreditListLoad';
	param._credit_id = Session.People.credit_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			w2ui['credit-detail-list'].clear();
			var data = jQuery.parseJSON(result);
			w2ui['credit-detail-list'].add(data);
			for (i=0; i<data.length; i++) {
				if (data[i].booking_type == 'p-settl') {
					$('#grid_credit-detail-list_rec_' +data[i].btrans_id).addClass('PreRow');
				}
				else if (data[i].booking_type == 'cust-pmt') {
					$('#grid_credit-detail-list_rec_' + data[i].btrans_id).addClass('PayRow');
				}
			}
		}
	});
	$('#eTermsChange').show();
}

Action.creditDetailLoad = function(grid) {

	var sel = grid.getSelection();
	var row = grid.get(sel);
	var transType = row[0].trans_type;
	Session.People.credit_id  = row[0].credit_id;
	if (transType == 'new-credit') {
		$('#change-credit-status-id').val(Session.People.credit_id);
		$('#change-monthly-no').val(Session.People.monthly_no);
		$('#change-interest-margin').val(Session.People.interest_margin);
		Helper.addClass('change-credit-status-modal', 'is-active');	
	}

}

Action.bondCreateDetailGrid = function() {
	dgBondDetailList = {
		name: 'bond-detail-list',
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
				//Action.creditDetailLoad(this);
			}
		},
		

		recid   : 'btrans_id',
		columns: [
			{ field : "booking_date", caption: "Date", size: "80px"},
			//{ field : "booking_text", caption: "Text",  size: "130px" },
			{ field : "trans_type", caption: "Type",  size: "110px" },
			{ field : "amount", caption: '<div style="text-align:right">Amount</div>',  size: "90px", style: 'text-align: right' },
			{ field : "balance", caption: '<div style="text-align:right">Balance</div>',  size: "90px", style: 'text-align: right' }
			//{ field : "booking_id", caption: 'Booking ID',  size: "90px" }
		],

		records: []
	};

	$('#bond-detail-list').w2grid(dgBondDetailList);

}

Action.bondListLoad = function(sel) {

	Session.People.bond_id = sel.bond_id;
	//Session.People.monthly_no = sel.monthly_no;
	//Session.People.interest_margin = sel.interest_margin;

	//var sel = grid.getSelection();
	//Session.People.bond_id = sel[0];
	//alert(Session.People.credit_id);
	var param = {};
	param._group = 'People';
	param._action = 'BondListLoad';
	param._bond_id = Session.People.bond_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			w2ui['bond-detail-list'].clear();
			var data = jQuery.parseJSON(result);
			w2ui['bond-detail-list'].add(data);
			
		}
	});
}

Action.tranItemLoad = function(grid) {
	// NEW 2020-02-06
	var sel = grid.getSelection();
	//Session.People.booking_id = sel[0];
	var row = grid.get(sel);
	var transType = row[0].trans_type;
	var bookingType = row[0].booking_type ;
	var bookingDate = row[0].booking_date;
	var btransId = row[0].btrans_id
	var creditId = row[0].credit_id;
	Session.People.booking_id = row[0].booking_id; // Not used
	Session.People.company_id = row[0].company_id;

	if (bookingType == 'p-settl') {
		var param = {};
		param._group = 'People';
		param._action = 'GetPreTrans';
		param._btrans_id = btransId;
		
		$.ajax({ type: "POST", url: 'Service.php', data: param,
			success: function(result) {
				PreTrans = jQuery.parseJSON(result);
				$('#pre-trans-type').html(PreTrans._trans_type1);
				$('#pre-amount').val(PreTrans.amount1);
				Helper.addClass('rebook-pre-modal', 'is-active');	
			}
		});		
	}
	else if (transType == 'billing-fee' || transType == 'reminder-fee' || transType == 'collection-fee') {
		// Update 2020-11-27
		var param = {};
		param._group = 'People';
		param._action = 'GetFee';
		param._trans_type = transType;
		param._booking_id = Session.People.booking_id;
		$.ajax({ type: "POST", url: 'Service.php', data: param,
			success: function(result) {
					/*
						alert(result);
						return;
					*/
				data = jQuery.parseJSON(result);

				$('#current_fee').val(data.amount.substring(1));
				$('#new_fee').val(data.amount); // Is negativ

				$('#current_date').val(bookingDate);
				var todaysDate = new Date();
				$('#new_date').val(Helper.convertDate(todaysDate));
				$('#selRebooking').val(transType);
				$('#eDoRebook').attr('action', transType);
				if (transType == 'billing-fee') {
					$('#srebook-title').html('Billing fee');
				}
				else if (transType == 'reminder-fee') {
					$('#srebook-title').html('Reminder fee');
				}
				else if (transType == 'collection-fee') {
					$('#srebook-title').html('Collection fee');
				}
				Helper.hide('.rebook-body');
			  	Helper.show('#rebook-body-fee');
			 	Helper.addClass('rebook-modal', 'is-active');
			}
		});
	}
	else if (transType == 'interest') {
		var amount = row[0].amount_1380;
		amount = amount.split(',').join('');
		var todaysDate = new Date();
		$('#interest-credit-date').val(Helper.convertDate(todaysDate));
		$('#interest-credit-id').val(creditId);
		$('#interest-credit-amount').val(amount);
		Helper.addClass('credit-interest-modal', 'is-active');	

	}
	else if (transType == 'o-interest') {
		var amount = row[0].amount_1680;
		amount = amount.split(',').join('');
		var todaysDate = new Date();
		$('#ointerest-credit-date').val(Helper.convertDate(todaysDate));
		$('#ointerest-credit-amount').val(amount);
		Helper.addClass('credit-ointerest-modal', 'is-active');	

	}
	else if (transType == 'new-credit') {
		var amount = row[0].amount_1380;
		amount = amount.split(',').join('');
		var todaysDate = new Date();
        $('#full-credit-date').val(Helper.convertDate(todaysDate));
		$('#full-credit-id').val(creditId);
		$('#full-credit-amount').val(amount);
		$('#full-receipt_number').val(''); // 20211101 */
		Helper.addClass('credit-full-modal', 'is-active');	
	} 
	else if (transType == 'amortization') {
		var amount = row[0].amount_1380;
		if (typeof amount === "undefined") {
			amount = row[0].amount_1680;
		}
		if (amount < 0) {
			amount = amount * -1; 
		}
		amount = Helper.removeComma(amount);  // Add 2020-07-10
		var todaysDate = new Date();
        $('#credit-amor-date').val(Helper.convertDate(todaysDate));
		$('#amor-credit-id').val(creditId);
		$('#amor-credit-amount').val(amount);
		Helper.addClass('credit-amor-modal', 'is-active');	
		// alert('amortering ' + amount);
	} 
	else if (transType == 'crediting') {
		Helper.addClass('crediting-cancel-modal', 'is-active');
	}	
}

$(document).on('click', '#eDoRebookPre', function(event) {
	// NEW 2020-02-06
	event.preventDefault();
	
	var amount = $('#pre-amount').val();
	if (isNaN(amount) || amount.length == 0) {
		alert('No numeric value');
		return;
	}
	PreTrans.amount1 = amount;
	if (amount > 0) {
		PreTrans.amount2 = - amount;
	}
	else if (amount < 0) {
		PreTrans.amount2 = amount * -1;
	}
	else {
		PreTrans.amount2 = amount;
	}
	//alert(amount + " : " + PreTrans.amount1 + PreTrans.amount2);
	PreTrans._group = 'People';
	PreTrans._action = 'UpdatePreTrans';
	
	$.ajax({ type: "POST", url: 'Service.php', data: PreTrans,
		success: function(result) {
			//alert(result);		
			
			Helper.removeClass('rebook-pre-modal', 'is-active');
			tabTrans ();
		}
	});
	
});

$(document).on('click', '#eCloseRebookPre', function(event) {
	event.preventDefault();
	Helper.removeClass('rebook-pre-modal', 'is-active');
});

$(document).on('click', '#eDoCreditingCancel', function(event) {
	event.preventDefault();
	
	var param = {};
	param._group = 'People';
	param._action = 'CancelBooking';
	param._booking_id = Session.People.booking_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			Helper.removeClass('crediting-cancel-modal', 'is-active');
			tabTrans ();
		}
	});
});

$(document).on('click', '#eCloseCreditingCancel', function(event) {
	event.preventDefault();
	Helper.removeClass('crediting-cancel-modal', 'is-active');
});

$(document).on('click', '#eDoChangeCreditStatus', function(event) {
	event.preventDefault();
	
	let monthlyNo =  $('#change-monthly-no').val();
	let interestMargin = $('#change-interest-margin').val();
	if (monthlyNo.length < 1 ) {
		alert('Payment Terms must be a number');
		return;
	}
	if (interestMargin.length < 1 ) {
		alert('Interst Margin must be a number');
		return;
	}

	if (isNaN(Number(interestMargin))) {
		alert('Interst Margin must be a number');
		return;
	}

	var param = {};
	param._group = 'People';
	param._action = 'ChangeCreditStatus';
	param._credit_id = Session.People.credit_id;
	// param.credit_status = $('#change-credit-status').val();
	param.monthly_no = monthlyNo;
	param.interest_margin = interestMargin;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			Helper.removeClass('change-credit-status-modal', 'is-active');
			tabCredits();
		}
	});
});

$(document).on('click', '#eCloseChangeCreditStatus', function(event) {
	event.preventDefault();
	Helper.removeClass('change-credit-status-modal', 'is-active');
});

$(document).on('click', '#eCloseRebook', function(event) {
	event.preventDefault();
	Helper.removeClass('rebook-modal', 'is-active');
});

function doBooking() {

	var action = $('#eDoRebook').attr('action');
	var bookingDate = $('#new_date').val();
	var amount = $('#new_fee').val();
	amount = amount.substring(1);
	var param = {};
	param._group = 'People';
	param._action = 'CreditingPeople';
	param.booking_date = bookingDate;
	param.people_id =  Session.People.people_id;
	param.type = action;
	param.amount = amount;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			Helper.removeClass('rebook-modal', 'is-active');
			tabTrans ();
		}
	});	
}

$(document).on('click', '#eDoCreditAmor', function(event) {
	event.preventDefault();
	
	var param = {};
	param._group = 'People';
	param._action = 'CreditAmor';
	param._people_id = Session.People.people_id;
	//param._booking_id = Session.People.booking_id;
	param._credit_id = $('#amor-credit-id').val();
	param._amount = $('#amor-credit-amount').val();
	param._booking_date = $('#credit-amor-date').val();
	//console.log(param);
	
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			Helper.removeClass('credit-amor-modal', 'is-active');
			tabTrans ();
		}
	});
});

$(document).on('click', '#eCloseCreditAmor', function(event) {
	event.preventDefault();
	Helper.removeClass('credit-amor-modal', 'is-active');
});

$(document).on('click', '#eDoCreditInterest', function(event) {
	event.preventDefault();
	
	var param = {};
	param._group = 'People';
	param._action = 'CreditInterest';
	param._people_id = Session.People.people_id;
	//param._booking_id = Session.People.booking_id;
	param._credit_id = $('#interest-credit-id').val();
	param._amount = $('#interest-credit-amount').val();
	param._booking_date = $('#interest-credit-date').val();
	//console.log(param);
	
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			Helper.removeClass('credit-interest-modal', 'is-active');
			tabTrans ();
		}
	});
});

$(document).on('click', '#eCloseCreditInterest', function(event) {
	event.preventDefault();
	Helper.removeClass('credit-interest-modal', 'is-active');
});

$(document).on('click', '#eDoCreditOinterest', function(event) {
	event.preventDefault();

	var action = 'o-interest' ;
	var bookingDate =  $('#ointerest-credit-date').val();
	var amount = $('#ointerest-credit-amount').val();
	// amount = amount.substring(1);
	var param = {};
	param._group = 'People';
	param._action = 'CreditingPeople';
	param.booking_date = bookingDate;
	param.people_id = Session.People.people_id;
	param.type = action;
	param.amount = amount;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			Helper.removeClass('credit-ointerest-modal', 'is-active');
			tabTrans ();
		}
	});	

});

$(document).on('click', '#eCloseCreditOinterest', function(event) {
	event.preventDefault();
	Helper.removeClass('credit-ointerest-modal', 'is-active');
});

$(document).on('click', '#eDoCreditFull', function(event) {
	event.preventDefault();
	
	var param = {};
	param._group = 'People';
	param._action = 'CreditFull';
	param._people_id = Session.People.people_id;
	param._company_id = Session.People.company_id;
	//param._booking_id = Session.People.booking_id;
	param._credit_id = $('#full-credit-id').val();
	param._amount = $('#full-credit-amount').val();
	param._booking_date = $('#full-credit-date').val();
	param._receipt_number = $('#full-receipt_number').val(); // 20211101 */
	//console.log(param);
	
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			Helper.removeClass('credit-full-modal', 'is-active');
			tabTrans ();
		}
	});
});

$(document).on('click', '#eCloseCreditFull', function(event) {
	event.preventDefault();
	Helper.removeClass('credit-full-modal', 'is-active');
});

function tabCredits () {
	$('.people-tabs').hide();
	var param = {};
	param._group = "People";
	param._action = 'CreditsList';
	param._people_id = Session.People.people_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			//alert(result);
			w2ui['credits-list'].clear();
			w2ui['credits-list'].add(jQuery.parseJSON(result));
			$('#tab-credits').show();
			w2ui['credit-detail-list'].clear();
		}
	});
}

function tabBond () {

	$('.people-tabs').hide();
	var param = {};
	param._group = "People";
	param._action = 'BondList';
	param._people_id = Session.People.people_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			//alert(result);
			w2ui['bond-list'].clear();
			w2ui['bond-list'].add(jQuery.parseJSON(result));
			$('#tab-bond').show();
		}
	});
}

function CheckBond() {
	var param = {};
	param._group = "People";
	param._action = 'CheckBond';
	param._people_id = Session.People.people_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			//alert(result);
			//w2ui['bond-list'].clear();
			//w2ui['bond-list'].add(jQuery.parseJSON(result));
		}
	});
}

function tabInvoices () {
	$('.people-tabs').hide();
	var param = {};
	param._group = "People";
    param._action = 'InvoiceList';
	param._people_id = Session.People.people_id;
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
			w2ui['invoice-list'].clear();
			var data = jQuery.parseJSON(result);
			w2ui['invoice-list'].add(data);
        }
    });
	$('#tab-invoices').show();
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
		//var win = window.open("http://localhost/finvoice-pre/" + filename, '_blank');
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

function tabTrans () {
	$('.people-tabs').hide();
	$('#tab-trans').show();
	var param = {};
	param._group = "People";
	param._action = 'TransList';
	param._people_id = Session.People.people_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			TransList = jQuery.parseJSON(result);
			var list = jQuery.parseJSON(result);

			var preList = [];
			w2ui['trans-list'].clear();
			w2ui['trans-list'].add(list);
			//$('#tab-trans').show();
			setPreTrans();

		}
	});
}

function setPreTrans() {
	for (i=0; i<TransList.length; i++) {
		if (TransList[i].booking_type == 'p-settl') {
			//alert(TransList[i].btrans_id)
			$('#grid_trans-list_rec_' + TransList[i].btrans_id).addClass('PreRow');
			//$('#grid_trans-list_rec_' + TransList[i].btrans_id).css('color', '#cc3333');
			
			
		}
		else if (TransList[i].booking_type == 'cust-pmt') {
			//alert(TransList[i].btrans_id)
			$('#grid_trans-list_rec_' + TransList[i].btrans_id).addClass('PayRow');
		}
	}
}

$(document).on('click', '#Test', function(event) {
	event.preventDefault();
	setPreTrans();
	/*
	for (i=0; i<TransList.length; i++) {
		if (TransList[i].booking_type == 'p-settl') {
			//alert(TransList[i].btrans_id)
			$('#grid_trans-list_rec_' + TransList[i].btrans_id).addClass('PreRow');
		}
	}
	*/

});

function tabTp () {
	$('.people-tabs').hide();
	$('#tab-tp').show();
}

$(document).on('click', '#ePeopleSave', function(event) {
	event.preventDefault();
	var param = {};
	if(Helper.validateForm('people')) {
		param._group = 'People';
		param._action = 'PeopleUpdate';
		param._people_id = Session.People.people_id;
		
		param.address = $("input[name=address").val();
		param.postcode = $("input[name=postcode").val();
		param.city = $("input[name=city").val();

		param.email = $("input[name=email").val();
		param.mobile = $("input[name=mobile").val();
		param.overdue = $("input[name=overdue").val();
		param.clearing_no = $("input[name=clearing_no").val();
		param.bank_account = $("input[name=bank_account").val();
		param.people_status = $("#edit-people_status").val();
		
		param.is_sanction_list = $("input[name=is_sanction_list").val();
		param.is_sanction_list = param.is_sanction_list.toLowerCase();
		if (param.is_sanction_list == 'n' || param.is_sanction_list == 'y') {
			// OK
		}
		else {
			alert('Must be y or n');
			return;
		}
		
		$.ajax({ type: "POST", url: 'Service.php', data: param,
			success: function(result) {
				Helper.disableForm('people');
				$("select[name=people_status").prop('disabled', true);
				Helper.hide('#ePeopleSave');
				Helper.hide('#ePeopleCancel');
				Helper.show('#ePeopleEdit');
				Helper.show('#eSettingsEdit');
				Action.peopleDetails();
			}
		});
	}
});

$(document).on('click', '.ePeople', function(event) {
	event.preventDefault();
	var action = $(this).attr('action');

	switch(action) {

  		case 'close' :
			//Session.Company.insertMode = false;
			Helper.hide('#people-section');
			Helper.show('#peoplelist-section');
			break;

		case 'edit-people' :
			//Helper.enableForm('people');

			$("input[name=address").prop('disabled', false);
			$("input[name=postcode").prop('disabled', false);
			$("input[name=city").prop('disabled', false);

			$("input[name=email").prop('disabled', false);
			$("input[name=mobile").prop('disabled', false);
			$("input[name=overdue").prop('disabled', false);
			$("input[name=clearing_no").prop('disabled', false);
			$("input[name=bank_account").prop('disabled', false);
			$("select[name=people_status").prop('disabled', false);
			$("input[name=is_sanction_list").prop('disabled', false);
			Helper.hide('#ePeopleEdit');
			Helper.hide('#eSettingsEdit');
			Helper.show('#ePeopleSave');
			Helper.show('#ePeopleCancel');
			break;

		case 'cancel-people' :
			Helper.disableForm('people');
			$("select[name=people_status").prop('disabled', true);
			Helper.hide('#ePeopleSave');
			Helper.hide('#ePeopleCancel');
			Helper.show('#ePeopleEdit');
			Helper.show('#eSettingsEdit');
			break;

		case 'edit-settings' :
			Helper.enableForm('settings');
			$('#start-date').prop('disabled', true);
			Helper.hide('#eSettingsEdit');
			Helper.hide('#ePeopleEdit');
			Helper.show('#eSettingsSave');
			Helper.show('#eSettingsCancel');

			break;

		case 'cancel-settings':
			Helper.disableForm('settings');
			Helper.hide('#eSettingsSave');
			Helper.hide('#eSettingsCancel');
			Helper.show('#eSettingsEdit');
			Helper.show('#ePeopleEdit');
			break;

			case "save-settings" :
				var param = $('#settings-form').serializeArray();
				//if(Helper.validateForm('settings')) {
				param .push(
					{ name: '_group', value: 'Setting'},
					{ name: '_action', value: 'PeopleUpdate'},
					{ name: 'setting_type', value: 'p'},
					{ name: 'id', value: Session.People.people_id});

				$.ajax({ type: "POST", url: 'Service.php', data: param,
					success: function(result) {

						Helper.show('#eSettingsEdit');
						Helper.show('#ePeopleEdit');
						Helper.hide('#eSettingsSave');
						Helper.hide('#eSettingsCancel');
					}
				});
				break;

			default:

	}

});

$(document).on('click', '#people-tab li', function(event) {
	event.preventDefault();
	$('#people-tab li').removeClass("is-active");
	$(this).addClass("is-active");
});

$(document).ready(function() {

	document.getElementById('eDoRebook').addEventListener("click", doBooking);
	Action.transCreateGrid();
	Action.creditsCreateGrid();

	// Check if have
	Action.bondCreateGrid();
	Action.bondCreateDetailGrid();
	Action.creditCreateDetailGrid();
	Action.invoiceCreateGrid();
	if (PeopleDirect == '0') {
		Action.peopleList();
	} else {
		Session.People.people_id = PeopleIdDirect;
		Action.peopleDetails();
		Action.settingsLoad();
		Action.companyConnectios();
		Helper.hide('#peoplelist-section');
		Helper.show('#people-section');
	}
});

function ucListCreateGrid () {
	dgUcList = {
		name: 'uc-list',
		show: {
			toolbar: false,
			footer: false,
			//toolbarAdd: true,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},

		recid   : 'uc_item_id',
		columns: [
			{ field : "uc_item", caption: "",  size: "80px", sortable: true },
            { field : "text", caption: "Text",  size: "250px", sortable: true },
            { field : "value", caption: "Value",  size: "250px", sortable: true }
			
		],
		records: []
	};
	
	$('#uc-list').w2grid(dgUcList);
	
}

$(document).on('click', '#eUcDetails', function(event) {
    event.preventDefault();
    //w2ui['uc-list'].clear();
    Session.ucId = $('#eUcPeople').val();
    //alert(Session.currentPeopleId);
    var param = {};
    param._group = "People";
    param._action = 'GetUcFull';
    param._people_id = Session.People.people_id; // Dyn
    //param._filter = "n";
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            //alert(result);
			var data = jQuery.parseJSON(result);

			var html = '';
			html += '<h2 style="font-family: arial; font-size:20px; margin-bottom: 14px;">' + $('#people-name').val() + '<h2>';
			html += '<table style="width:100%; font-family: arial; font-size: 12px;">'; // font-family: arial; font-size: 14px;">';
			/*
			html += '<tr>';
			html += '<th style="align:left; width:100px">Item</th>';
			html += '<th style="align:left; width:300px">Text</th>';
			html += '<th style="align:left;">Value</th>';
			//html += '<th style="align:left; width:100px">Item</th><th style="align:left; width:400px">Text</th><th style="align:left">Value</th>';
			html += '</tr>';
			*/
			for (var i=0; i<data.length; i++) {
				html += '<tr>';
				html += '<td style="width:100px">' + data[i].uc_item + '</td>';
				html += '<td>' + data[i].text + '</td>';
				html += '<td>' + data[i].value + '</td>';
				html += '</tr>';
			}

			html += '</table>';

			alert(html);

			$('#uc-details-body').html(html);


			Helper.addClass('uc-details-modal', 'is-active');
            w2ui['uc-list'].add(data);
        }
    });
});

Action.getUcStatus = function(peopleId) {
    //event.preventDefault();
    //w2ui['uc-list'].clear();
  
    var param = {};
    param._group = "People";
    param._action = 'GetUcStatus';
    param._people_id = peopleId;
    //param._filter = "n";
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
            //alert(result);
            var data = jQuery.parseJSON(result);
            w2ui['uc-list'].add(data);
        }
    });
}

$(document).on('click', '#eUcPrint', function(event) {
	event.preventDefault();
	var mywindow = window.open('', 'PRINT', 'height=600,width=800');
	mywindow.document.write('<html><head></head><body>');
	mywindow.document.write($('#uc-details-body').html());
	mywindow.document.write('</body></html>');
	mywindow.document.close(); // necessary for IE >= 10
	mywindow.focus(); // necessary for IE >= 10
	mywindow.print();
	mywindow.close();
});

$(document).on('click', '#eUclose', function(event) {
	event.preventDefault();
	Helper.removeClass('uc-details-modal', 'is-active');
});

$(document).on('change', '#eSelectPeopleAction', function(event) {
	event.preventDefault();
	var action = $(this).val();
	if (action == 'write-off') {
		Action.initWriteOff();
	}
	else if (action == 'payout') {
		$('#payout-amount').val('');
		let currentDate = new Date();
		let todayDate = currentDate.toISOString().substring(0, 10);
		$('#payout-date').val(todayDate);
		Helper.addClass('payout-modal', 'is-active');
	}
});

$(document).on('click', '#eClosePayout', function(event) {
	event.preventDefault();
	Helper.removeClass('payout-modal', 'is-active');
});

$(document).on('click', '#eDoPayout', function(event) {
	event.preventDefault();
	let amount = $('#payout-amount').val();
	if (amount.length < 1) {
		alert('No amount!!');
		returnM
	}
	var param = {};
    param._group = "People";
    param._action = 'Payout';
	param._people_id = Session.People.people_id; 
	param.payout_date = $('#payout-date').val();
	param.payout_amount = amount;
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
			Helper.removeClass('payout-modal', 'is-active');
			tabTrans();
		}
	});
});

Action.initWriteOff = function() {
	// Collect all data
	var param = {};
    param._group = "People";
    param._action = 'WriteOff';
	param._people_id = Session.People.people_id; 
	param._init = 'y';
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
           
			var data = jQuery.parseJSON(result);

			Helper.addClass('write-off-modal', 'is-active');
		
			var html = '';
			html = '<b>This credits vill be closed and written-off</b>';
			html += '<ul>';
			if (data.credits.length > 0) {
				for (var i=0; i < data.credits.length; i++) {
					html += '<li> - ' + data.credits[i].credit_id + ' (' + data.credits[i].summa + 'kr)';
				}
			}
			html += '</ul>';
			html += '<b>Settlement write off with: ' + data.amount1680 + 'kr</br>';
			html += '<b>Pre-settlement will be removed</b><br>';
			$('#write-off-body').html(html);
		}
	});
}

$(document).on('click', '#eCloseWriteOff', function(event) {
	event.preventDefault();
	Helper.removeClass('write-off-modal', 'is-active');
});

$(document).on('click', '#eDoWriteOff', function(event) {
	event.preventDefault();
	var param = {};
    param._group = "People";
    param._action = 'WriteOff';
	param._people_id = Session.People.people_id; 
	param._init = 'n';
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
			//var data = jQuery.parseJSON(result);
			Helper.removeClass('write-off-modal', 'is-active');
			tabTrans();
		}
	});
});

$(document).on('keypress', '.is-numeric', function (e) {
	var keyCode = e.which ? e.which : e.keyCode ; 
  	if (!(keyCode >= 48 && keyCode <= 57)) {
		return false;
	}
});

$(document).on('keypress', '.is-numeric-comma', function (e) {
	var keyCode = e.which ? e.which : e.keyCode ; 
	if (keyCode == 46) {
		return true;
	}
  	if (!(keyCode >= 48 && keyCode <= 57)) {
		return false;
	}
});
</script>
