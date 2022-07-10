<script type="text/javascript" src="js/w2ui-1.5.rc1.min.js"></script>
<script>

var Action = {};
var Session = {};
Session.Company = {};
Session.Company.insertMode = false;

Action.companyList = function() {
	Action.companyLoadList();
}

Action.companyLoadList = function() {
	var param = {};
	param._group = "Company";
    param._action = 'CompanyList';
    $.ajax({ type: "POST", url: 'Service.php', data: param,
        success: function(result) {
			w2ui['company-list'].clear();
			var data = jQuery.parseJSON(result);
			// Updated 2021-01-13
			for (let i=0; i<data.length; i++) {
				data[i].company_id = Number(data[i].company_id);
			}
			w2ui['company-list'].add(data);
        }
    });
}

Action.companyCreateGrid = function() {
	dg = {
		name: 'company-list',
		show: {
			toolbar: true,
			footer: true,
			toolbarAdd: false,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},
		onAdd: function(event ) {
			alert('Add');
			//Helper.clearForm('people-add');
			//Helper.gridAddRow('Add people', 'people' );
		},

		onDblClick: function(event) {
			event.onComplete = function () {
				 Action.companyLoad(this);
			}
		},
		recid   : 'company_id',
		columns: [
			{ field : "company_id", caption: "Company-id", size: "80px", attr: 'align=center', sortable: true},
			{ field : "known_as", caption: "KNown as",  size: "160px", sortable: true },
			{ field : "company_name", caption: "Company",  size: "160px", sortable: true },
			{ field : "company_id_number", caption: "Company ID-number",  size: "130px", sortable: true },
			{ field : "ocrno", caption: "Ocrno",  size: "130px", sortable: true },
			{ field : "phone", caption: "Phone",  size: "100px", sortable: true },
			{ field : "email", caption: "E-mail",  size: "170px", sortable: true },
			{ field : "company_status", caption: "Status",  size: "70px", attr: 'align=center', sortable: true },
			{ field : "is_vendor", caption: "Vendor",  size: "70px", attr: 'align=center', sortable: true },
			{ field : "is_lender", caption: "Lender",  size: "70px", attr: 'align=center', sortable: true },

		],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#company-list').w2grid(dg);
	Session.Company.gridCreated = true;
}

Action.storeCreateGrid = function() {
	dgStore = {
		name: 'company-store-list',
		show: {
			toolbar: false,
			footer: true,
			toolbarAdd: false,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},


		onDblClick: function(event) {
			event.onComplete = function () {

				var sel = this.getSelection();
			 	var sel_record = this.get(sel[0]);
				Session.Company.store_id = sel_record.store_id;
				$('#store-edit-name').val(sel_record.store_name);
				$('#store-edit-location').val(sel_record.location);
				$('#store-edit-modal').addClass('is-active');

			}
		},

		recid   : 'store_id',
		columns: [
			{ field : "company_id", caption: "Company-id", size: "60px", hidden: true },
			{ field : "store_name", caption: "Store",  size: "140px", sortable: true},
			{ field : "location", caption: "Location",  size: "140px", sortable: true }
			//{ field : "store_status", caption: "Status",  size: "60px", attr: 'align=center', sortable: true }
		],
		records: []
	};

	$('#company-store-list').w2grid(dgStore);
}

Action.peopleCreateGrid = function() {
	dgPeople = {
		name: 'company-people-list',
		show: {
			toolbar: false,
			footer: true,
			toolbarAdd: false,
			toolbarDelete: false,
			toolbarSave: false,
			//toolbarEdit: true
		},

		onDblClick: function(event) {
			event.onComplete = function () {
				var sel = this.getSelection();
			 	var sel_record = this.get(sel[0]);

				$('#people-modal-pesonal-id-number').val(sel_record.personal_id_number);
				$('#people-modal-pesonal-id-number').prop( "disabled", true );
				$("input[name=priv][value=" + sel_record.priv + "]").prop('checked', true);

				Session.Company.currentCpId = sel_record.recid;

				$('#people-modal-insert-button').hide();
				$('#people-modal-update-button').show();

				$('#people-modal-title').html('Change privilege');
				$('#people-modal').addClass('is-active');

			}
		},

		recid   : 'cp_id',
		columns: [
			{ field : "personal_id_number", caption: "Personal ID", size: "110px", sortable: true },
			{ field : "people_name", caption: "Namen",  size: "160px", sortable: true },
			{ field : "priv", caption: "Privilege",  size: "60px", attr: 'align=center', sortable: true }
		],
		records: []
	};
	//dg.records = jQuery.parseJSON(result);
	$('#company-people-list').w2grid(dgPeople);
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
		recid   : 'btrans_id',
		columns: [
			{ field : "booking_date", caption: "Date", size: "80px"},
			{ field : "trans_type", caption: "Type",  size: "120px" },
			{ field : "amount", caption: '<div style="text-align:right">Amount</div>',  size: "90px", attr: 'align=right' },
			{ field : "balance", caption: '<div style="text-align:right">Balance</div>',  size: "90px", attr: 'align=right' }
			//{ field : "settlement", caption: '<div style="text-align:right">Settlement acc</div>',  size: "90px", attr: 'align=right' }
		],
		records: []
	};

	$('#trans-list').w2grid(dgTrans);
	//if (Session.People.is_sp == 'y') {
		//w2ui['trans-list'].addColumn( { field : "amount_2380", caption: '<div style="text-align:right">Bonus</div>',  size: "90px", attr: 'align=right' });
	//}
	//w2ui['trans-list'].addColumn( { field : "extra", caption: 'Other',  size: "140px" });
}

Action.companyLoad = function(grid) {
	var sel = grid.getSelection();
	Session.Company.company_id = sel[0];
	Action.companyDetails();
	Action.settingsLoad();
	Action.signInfo();
	//Action.storeList();
	//Action.peopleList();
	Helper.hide('#companylist-section');
	Helper.show('#company-section');
	Helper.show('#eNavBarBack');

}

Action.companyDetails = function() {
	var param = {};
	param._group = 'Company';
	param._action = 'CompanyGet';
	param._company_id = Session.Company.company_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			//alert(result);
			var companyObj = jQuery.parseJSON(result);
			Helper.bindForm('company', companyObj);
			Helper.disableForm('company');
			$("select[name=has_invoice_service").prop('disabled', true);
			$("select[name=is_vendor").prop('disabled', true);
			$("select[name=is_lender").prop('disabled', true);
			$("select[name=company_status").prop('disabled', true);
			$("select[name=priv_on").prop('disabled', true);
			$("#wa_store_list").prop('disabled', true);
			$("#wa_sp_list").prop('disabled', true);
			$("#header-company-name").html(companyObj.company_name + " (" + companyObj.known_as + ")");
			Action.loadWaInfo(companyObj.wa_store_id,companyObj.wa_sp_id);
		}
	});
}

Action.loadWaInfo = function(storeId,spId) {
	var param = {};
	param._group = 'Company';
	param._action = 'WaInfo';
	param._company_id = Session.Company.company_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			var htmlStore = '';
			if (data.store.length > 0) {
				for (var i=0; i < data.store.length; i++) {
					htmlStore += '<option value="' + data.store[i].store_id + '">' + data.store[i].store_name + '</option>';
				}
			}
			else {
				htmlStore += '<option value="0">No store exist</option>';
			}
			$('#wa_store_list'). html(htmlStore);
			$('#wa_store_list').val(storeId);

			var htmlSp = '';
			if (data.sp.length > 0) {
				for (var i=0; i < data.sp.length; i++) {
					htmlSp += '<option value="' + data.sp[i].people_id + '">' + data.sp[i].people_name + '</option>';
				}
			}
			else {
				htmlSp += '<option selected value="0">No salesperson are connected</option>';
			}
			$('#wa_sp_list'). html(htmlSp);
			$('#wa_sp_list').val(spId);
		}
	});
}

Action.settingsLoad = function() {

	var param = {};
	param._group = 'Setting';
	param._action = 'GetCompany';
	param._company_id = Session.Company.company_id;

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

Action.signInfo = function() {
	var param = {};
	param._group = "Company";
	param._action = 'SignInfo';
	param._company_id = Session.Company.company_id;
	//param5._company_id = Session.Company.company_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			if (data.length > 0) {
				var html = "";
				html += '<h3>Sign contracts</h3>';
				html += '<table class="table">';
				html += '<tr>';
				html += '<th>Name</th>';
				html += '<th>Contract</th>';
				html += '</tr>';
				for(var i=0; i < data.length; i++) {
					html += '<tr>';
					html += '<td>' + data[i].people_name + '</td>';
					html += '<td>' + data[i].contract_no + '</td>';
					html += '</tr>';
				}
				html += '</table>';
				$('#company-sign-info').html(html);

			}
		}
	});
}

$(document).on('click', '#eNavBarBack', function(event) {
	Session.Company.insertMode = false;
	Helper.hide('#companylist-section');
	Helper.hide('#eNavBarBack');
	Helper.hide('#company-section');
	Helper.show('#companylist-section');
});

$(document).on('click', '#eCompanySave', function(event) {
	event.preventDefault();
	var param = $('#company-form').serializeArray();

	if(Helper.validateForm('company')) {
		if (Session.Company.insertMode == false) {
			param .push(
				{ name: '_group', value: 'Company'},
				{ name: '_action', value: 'CompanyUpdate'},
				{ name: '_company_id', value: Session.Company.company_id }
			);
			$.ajax({ type: "POST", url: 'Service.php', data: param,
				success: function(result) {
					Helper.disableForm('company');
					$("select[name=has_invoice_service").prop('disabled', true);
					$("select[name=is_vendor").prop('disabled', true);
					$("select[name=is_lender").prop('disabled', true);
					$("select[name=company_status").prop('disabled', true);
					$("select[name=priv_on").prop('disabled', true);
					$("#wa_store_list").prop('disabled', true);
					$("#wa_sp_list").prop('disabled', true);
					Helper.hide('#eCompanySave');
					Helper.hide('#eCompanyCancel');
					Helper.show('#eCompanyEdit');
					Helper.show('#eSettingsEdit');
				}
			});
		}
		else if (Session.Company.insertMode == true) {
			param .push(
				{ name: '_group', value: 'Company'},
				{ name: '_action', value: 'CompanyInsert'}
			);
			Session.Company.insertMode == false; // prevent dubbel
			$.ajax({ type: "POST", url: 'Service.php', data: param,
				success: function(result) {

					var insertObj = jQuery.parseJSON(result);
					Session.Company.company_id = insertObj.id;
					Action.companyDetails();
					Action.settingsLoad();
					Helper.disableForm('company');
					Helper.hide('#eCompanySave');
					Helper.hide('#eCompanyCancel');
					Helper.show('#eCompanyEdit');
					Helper.show('#eSettingsEdit');

				}
			});
		}
	}
});

$(document).on('click', '.eCompany', function(event) {
	event.preventDefault();
	var action = $(this).attr('action');

	switch(action) {
		case 'new-company' :
			Session.Company.insertMode = true;
			Helper.clearForm('company');
			Helper.hide('#companylist-section');
			w2ui['company-store-list'].clear();
			Helper.enableForm('company');
			$("select[name=has_invoice_service").prop('disabled', false);
			$("select[name=is_vendor").prop('disabled', false);
			$("select[name=is_lender").prop('disabled', false);
			$("select[name=company_status").prop('disabled', false);
			$("#wa_store_list").prop('disabled', false);
			$("#wa_sp_list").prop('disabled', false);
			$("select[name=priv_on").prop('disabled', false);
			$('#wa_store_list'). html('<option value="0">No store exist</option>');
			$('#wa_store_list').val('0');

			$('#wa_sp_list'). html('<option selected value="0">No salesperson are connected</option>');
			$('#wa_sp_list').val('0');

			Helper.hide('#eCompanyEdit');
			Helper.hide('#eSettingsEdit');
			Helper.show('#eCompanySave');
			Helper.hide('#eCompanyCancel');
			Helper.show('#company-section');
			Helper.show('#eNavBarBack');
			break;

  		case 'close' :
			Session.Company.insertMode = false;
			Helper.hide('#company-section');
			Helper.show('#companylist-section');
			break;

		case 'edit-company' :
			Helper.enableForm('company');
			$("select[name=has_invoice_service").prop('disabled', false);
			$("select[name=is_vendor").prop('disabled', false);
			$("select[name=is_lender").prop('disabled', false);
			$("select[name=company_status").prop('disabled', false);
			$("#wa_store_list").prop('disabled', false);
			$("#wa_sp_list").prop('disabled', false);
			$("select[name=priv_on").prop('disabled', false);
			Helper.hide('#eCompanyEdit');
			Helper.hide('#eSettingsEdit');
			Helper.show('#eCompanySave');
			Helper.show('#eCompanyCancel');
			break;

		case 'cancel-company' :
			Helper.disableForm('company');
			Helper.hide('#eCompanySave');
			Helper.hide('#eCompanyCancel');
			Helper.show('#eCompanyEdit');
			Helper.show('#eSettingsEdit');
			$("select[name=has_invoice_service").prop('disabled', true);
			$("select[name=is_vendor").prop('disabled', true);
			$("select[name=is_lender").prop('disabled', true);
			$("select[name=company_status").prop('disabled', true);
			$("#wa_store_list").prop('disabled', true);
			$("#wa_sp_list").prop('disabled', true);
			$("select[name=priv_on").prop('disabled', true);
			break;

		case 'add-people' :
			$('#people-modal-update-button').hide();
			$('#people-modal-insert-button').show();
			$('#people-modal-title').html('Add people');
			$('#people-modal-pesonal-id-number').val('');
			$('#people-modal-pesonal-id-number').prop( "disabled", false );
			$('#people-modal').addClass('is-active');
			 break;

		case 'people-modal-close' :
		 	$('#people-modal').removeClass('is-active');
			break;

		case "people-insert" :
		   	var personal_id_number = $('#people-modal-pesonal-id-number').val();
		   	if (personal_id_number.length != 12) {
			   alert('Personal Id has to be 12 numbers');
		   	} else {
				var param = {};
				param._group = "Company";
				param._action = 'PeopleInsert';
				param.company_id = Session.Company.company_id;
				param.personal_id_number = personal_id_number;
				param.priv = $('input[name=priv]:checked').val();

				$.ajax({ type: "POST", url: 'Service.php', data: param,
					success: function(result) {
						var obj = jQuery.parseJSON(result);
						if (obj.code == "1") {
							$('#people-modal').removeClass('is-active');
							Action.peopleList();
						}
						else if (obj.code == "0") {
							if (obj.denied_code == 'people_exist') {
								alert('Already exist');
							}
							if (obj.denied_code == 'people_not_exist') {
								alert('Personal no. not avalible');
							}
							$('#people-modal').removeClass('is-active');
						} else {
							alert('Okänt fel, contact IT department');
						}
					}
				});
			}
			break;

		case 'people-update' :
		// Obsolete ?
			var priv = $('input[name=priv]:checked').val();
			var param = {};
			param._group = "Company";
			param._action = 'PeopleUpdate';
			param._cp_id = Session.Company.currentCpId;
		 	param.priv = $('input[name=priv]:checked').val();
			$.ajax({ type: "POST", url: 'Service.php', data: param,
				success: function(result) {
					$('#people-modal').removeClass('is-active');
					Action.peopleList();
				}
			});
		 	break;

		case 'add-store' :

				$('#add-store-modal').addClass('is-active');
				 break;

		case 'store-modal-close' :
		 	$('#add-store-modal').removeClass('is-active');
			break;

		case "store-insert" :
		   	var storeName = $('#store-add-name').val();
			var location = $('#store-add-location').val();
		   	if (storeName.length < 4) {
			   alert('Store name length must be 4 charachers');
		   	} else {

				var param = {};
				param._group = "Company";
				param._action = 'StoreInsert';
				param.company_id = Session.Company.company_id;
				param.store_name = storeName;
				param.location = location;
				$.ajax({ type: "POST", url: 'Service.php', data: param,
					success: function(result) {
						var obj = jQuery.parseJSON(result);
						if (obj.code == "1") {
							$('#add-store-modal').removeClass('is-active');
							Action.storeList();
						} else {
							alert('Problem add store');
						}
					}
				});
			}
			break;

		case 'store-edit-modal-close' :
		 	$('#store-edit-modal').removeClass('is-active');
			break;

		case "store-update" :
			var storeName = $('#store-edit-name').val();
			var location = $('#store-edit-location').val();
			if (storeName.length < 4) {
			   alert('Store name length must be 4 charachers');
			} else {
				var param = {};
				param._group = "Company";
				param._action = 'StoreUpdate';
				param._store_id = Session.Company.store_id;
				param.store_name = storeName;
				param.location = location;
				$.ajax({ type: "POST", url: 'Service.php', data: param,
					success: function(result) {
						var obj = jQuery.parseJSON(result);
						if (obj.code == "1") {
							$('#store-edit-modal').removeClass('is-active');
							Action.storeList();
						} else {
							alert('Problem add store');
						}
					}
				});
			}



			break;



		case 'edit-settings' :
			Helper.enableForm('settings');
			$('#start-date').prop('disabled', true);
			Helper.hide('#eSettingsEdit');
			Helper.hide('#eCompanyEdit');
			Helper.show('#eSettingsSave');
			Helper.show('#eSettingsCancel');

			break;

		case 'cancel-settings':
			Helper.disableForm('settings');
			Helper.hide('#eSettingsSave');
			Helper.hide('#eSettingsCancel');
			Helper.show('#eSettingsEdit');
			Helper.show('#eCompanyEdit');
			break;

		case "save-settings" :
			var param = $('#settings-form').serializeArray();
			//if(Helper.validateForm('settings')) {
			param .push(
				{ name: '_group', value: 'Setting'},
				{ name: '_action', value: 'CompanyUpdate'},
				{ name: 'setting_type', value: 'c'},
				{ name: 'id', value: Session.Company.company_id});

			$.ajax({ type: "POST", url: 'Service.php', data: param,
				success: function(result) {

					Action.settingsLoad();
					Helper.show('#eSettingsEdit');
					Helper.show('#eCompanyEdit');
					Helper.hide('#eSettingsSave');
					Helper.hide('#eSettingsCancel');

				}
			});
			break;

			default:

	}

});

Action.storeList = function() {
	var param = {};
	param._group = "Company";
	param._action = 'StoreList';
	param._company_id = Session.Company.company_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {

			w2ui['company-store-list'].clear();
			w2ui['company-store-list'].add(jQuery.parseJSON(result));
		}
	});
}

Action.peopleList = function() {
	var param = {};
	param._group = "Company";
	param._action = 'PeopleList';
	param._company_id = Session.Company.company_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			w2ui['company-people-list'].clear();
			w2ui['company-people-list'].add(jQuery.parseJSON(result));
			w2ui['company-people-list'].refresh();
		}
	});
}

function tabDetails () {
	Action.companyDetails();
	$('.company-tabs').hide();
	$('.tabs-company').removeClass("is-active");
	$('#tab-company-details').addClass("is-active");
	$('#tab-details').show();
}

function tabCredits() {

}

function tabTrans () {
	$('.company-tabs').hide();
	$('.tabs-company').removeClass("is-active");
	$('#tab-company-trans').addClass("is-active");
	$('#tab-trans').show();
	var param = {};
	param._group = "Company";
	param._action = 'TransList';
	param._company_id = Session.Company.company_id;
	//param5._company_id = Session.Company.company_id;
	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {
			w2ui['trans-list'].clear();
			w2ui['trans-list'].add(jQuery.parseJSON(result));
			$('#tab-trans').show();
		}
	});
}

function tabTp () {
	Action.storeList();
	Action.peopleList();
	$('.company-tabs').hide();
	$('.tabs-company').removeClass("is-active");
	$('#tab-company-tp').addClass("is-active");
	$('#tab-tp').show();
}

$(document).ready(function() {

	Action.companyCreateGrid();
	$('#tab-tp').show();
	Action.storeCreateGrid();

	Action.peopleCreateGrid();
		$('#tab-tp').hide();
	//Action.principalCreateGrid();
	Action.transCreateGrid();
	Action.companyList();
});

</script>
