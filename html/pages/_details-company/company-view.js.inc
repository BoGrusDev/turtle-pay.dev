<script> 
class CompanyView {
	init() {
		$('#navbar-company-details').addClass('is-active');

		document.getElementById('eEditOn').addEventListener("click", Controller.eEditOn);
		document.getElementById('eEditCancel').addEventListener("click", Controller.eEditCancel);
		document.getElementById('eEditUpdate').addEventListener("click", Controller.eEditUpdate);

		document.getElementById('eHasVatAccounting').addEventListener("change", Controller.eVatChanged);	
		document.getElementById('eNotiInvoiceOn').addEventListener("change", Controller.eNotiInvoiceChanged);	
		document.getElementById('eBoNotifyOn').addEventListener("change", Controller.eBoNotifyChanged);	
		document.getElementById('eHasBo').addEventListener("change", Controller.eBoChanged);	
		//document.getElementById('eHasSie').addEventListener("change", Controller.eSieChanged);	

		document.getElementById('eAccountNew').addEventListener("click", Controller.eAccountNew);
		document.getElementById('eContractPreViewPdf').addEventListener("click", View.eContractPreViewPdf);

		document.getElementById('eContractComplete').addEventListener("click", View.eContractComplete);
		document.getElementById('eContractCancel').addEventListener("click", View.eContractCancel);
		document.getElementById('eBankIdBoxContinue').addEventListener("click", View.eBankIdBoxContinue);
	}

	load(data) {
		this._showAdress(data);
		this._showVat(data);
		this._showBookingOrder(data);
		this._showAccountList(data._accounts, data.has_vat_accounting, data._vats);
		this._setSie(data);
		this._showSie();
		if (Current.hasSie == 'n') {
			$('.has-sie-view').hide();
		}
		else {
			$('#eHasSie').prop('disabled', true);
		}
		$('#page-section').show();
		if (Current.tdbOn == 'y') {
			$('.has-tdb-view').show();
			$("#dTdbOrgno").html(Current.tdbOrgno);
			$('#editTdbOrgno').val(Current.tdbOrgno);
			//$("#dTdbApikey").html(Current.tdbApikey);
			$("#dTdbApikey").html('******************');
			$('#editTdbApikey').val(Current.tdbApikey);
		}
	}
	
	_showAdress(data) {
			// -- Adress
		$("#dCompanyName").html(data.company_name);
		$("#dKnownAs").html(data.known_as);
		$("#dAddress").html(data.address);
		$("#dAddress2").html(data.address_2);
		$("#dPostAddress").html(data.postcode + ' ' + data.city);
		$('#dCompanyIdNumber').html(data.company_id_number);
		$('#dBankAccount').html(data.bank_account);
		$('#dOcrno').html(data.ocrno);
		$("#dEmailReport").html(data.email_report);
		$('#editEmailReport').val(data.email_report);
		$("#dNotiInvoiceEmail").html(data.noti_invoice_email);
		$('#editNotiInvoiceEmail').val(data.noti_invoice_email);
		
		$("#dPhone").html(data.phone);
		$('#editPhone').val(data.phone);
		if (data.noti_invoice_on == 'y') {
			$('#eNotiInvoiceOn').prop('checked', true);
			$('.noti-invoice-container').show();
		}
		else {
			$('#eNotiInvoiceOn').prop('checked', false);
			$('.noti-invoice-container').hide();
		}
		$('#eNotiInvoiceOn').prop('disabled', true);
	}
	
	_showVat(data) {
		
		if (data.has_vat_accounting == 'y') {
			$('.has-vat-view').show();
			$('.vat-view').show();
			$('#eHasVatAccounting').prop('checked', true);
		}
		else {
			$('.vat-view').hide();
			$('#eHasVatAccounting').prop('checked', false);
		}
		$('#eHasVatAccounting').prop('disabled', true);
		$('#dVatAccountNameCode1').html(data.vat_account_name_code_1);
		$('#editdVatAccountNameCode1').val(data.vat_account_name_code_1);
		$('#dVatAccountNoCode1').html(data.vat_account_no_code_1);
		$('#editdVatAccountNoCode1').val(data.vat_account_no_code_1);
	
		$('#dVatAccountNameCode2').html(data.vat_account_name_code_2);
		$('#editdVatAccountNameCode2').val(data.vat_account_name_code_2);
		$('#dVatAccountNoCode2').html(data.vat_account_no_code_2);
		$('#editdVatAccountNoCode2').val(data.vat_account_no_code_2);

		$('#dVatAccountNameCode3').html(data.vat_account_name_code_3);
		$('#editdVatAccountNameCode3').val(data.vat_account_name_code_3);
		$('#dVatAccountNoCode3').html(data.vat_account_no_code_3);
		$('#editdVatAccountNoCode3').val(data.vat_account_no_code_3);

		if (data.has_vat_invoice == 'y') {
			$('#eHasVatInvoice').prop('checked', true);
		}
		else {
			$('#eHasVatInvoice').prop('checked', false);
		}
		$('#eHasVatInvoice').prop('disabled', true);
	}
	
	_showBookingOrder(data) {
		if (data.has_bo == 'y') {
			$('.bo-view').show();
			$('#eHasBo').prop('checked', true);
			$('.bo-notify-on-checkbox').show();
			if (data.has_bo_notify_on == 'y') {
			
				$('#eBoNotifyOn').prop('checked', true);
				$('.bo-notify-on-container').show();
			}
			else {
				$('.bo-notify-on-container').hide();
				$('#eBoNotifyOn').prop('checked', false);
			}
		}
		else {
			$('#eHasBo').prop('checked', false);
		}
		$('#eBoNotifyOn').prop('disabled', true);
		$('#eHasBo').prop('disabled', true);

		$('#dBoText').html(data.bo_text);
		$('#editBoText').val(data.bo_text);
		
		$('#dBoSettlAccountName').html(data.bo_settl_account_name);
		$('#editBoSettlAccountName').val(data.bo_settl_account_name);
		$('#dBoSettlAccount').html(data.bo_settl_account);
		$('#editBoSettlAccount').val(data.bo_settl_account);

		$('#dBoBankAccountName').html(data.bo_bank_account_name);
		$('#editBoBankAccountName').val(data.bo_bank_account_name);
		$('#dBoBankAccount').html(data.bo_bank_account);
		$('#editBoBankAccount').val(data.bo_bank_account);

		$('#dBoTransfeeAccountName').html(data.bo_transfee_account_name);
		$('#editBoTransfeeAccountName').val(data.bo_transfee_account_name);
		$('#dBoTransfeeAccount').html(data.bo_transfee_account);
		$('#editBoTransfeeAccount').val(data.bo_transfee_account);

		$('#dBoInterestAccountName').html(data.bo_interest_account_name);
		$('#editBoInterestAccountName').val(data.bo_interest_account_name);
		$('#dBoInterestAccount').html(data.bo_interest_account);
		$('#editBoInterestAccount').val(data.bo_interest_account);
		
		$('#dBoAppAccountName').html(data.bo_app_account_name);
		$('#editBoAppAccountName').val(data.bo_app_account_name);
		$('#dBoAppAccount').html(data.bo_app_account);
		$('#editBoAppAccount').val(data.bo_app_account);
		
		$('#dBoIncomeAccount').html(data.bo_income_account);
		$('#editBoIncomeAccount').val(data.bo_income_account);
		$('#dBoIncomeText').html(data.bo_income_text);
		$('#editBoIncomeText').val(data.bo_income_text);

	}
	
	_setSie(data) {
		$('#editSieType').val(data.sie_type);
		$("#dSieSerie").html(data.sie_serie);
		$('#editSieSerie').val(data.sie_serie);		
		$("#dSieVerno").html(data.sie_first_verno);
		$('#editSieVerno').val(data.sie_first_verno);	

		$('#editFyYearNo').val(data.fy_year_no);	
		var sel = document.getElementById("editSieType");
		var text = sel.options[sel.selectedIndex].text;
		$('#dSieType').html(text);	
		$('#editSieKpType').val(data.sie_kp_type);
		var sel2 = document.getElementById("editSieKpType");
		var text = sel2.options[sel2.selectedIndex].text;
		$('#dSieKpType').html(text);	

		var sel3 = document.getElementById("editFyYearNo");
		var text = sel3.options[sel3.selectedIndex].text;
		$('#dFyYearNo').html(text);	

		$("#dSieStartDate").html(data.sie_start_date);
		$('#editSieStartDate').val(data.sie_start_date);	
		$("#dSieLastVerNo").html(data.sie_last_ver_no);
		$("#dSieLastBookingDate").html(data.sie_last_booking_date);

	}

	_showSie() {
		//alert(Current.hasBo);
		if (Current.hasBo == 'y') {
			$('.has-sie-view').show();
			if (Current.hasSie == 'y') {
				$('#eHasSie').prop('checked', true);
				$('.sie-view').show();
				if (Current.sie_started == 'n') {
					$('.sie-view-ver-no').show();
					$('.sie-view-start-date').show();
					$('.sie-view-last-vern-no').hide();
					$('.sie-view-last-booking-date').hide();
				}
				else {
					$('.sie-view-start-date').hide();
					$('.sie-view-ver-no').hide();
					$('.sie-view-last-ver-no').show();
					$('.sie-view-last-booking-date').show();
				}
			}
		}
		else {
			$('.sie-view').hide();
			$('.has-sie-view').hide();
			$('.sie-view-ver-no').hide();
			$('.sie-view-start-date').hide();
			$('.sie-view-last-vern-no').hide();
			$('.sie-view-last-booking-date').hide();
		}
			
	}
	
	_showAccountList(data, hasVatAccounting, vatList) {
		if (data.length > 0) {
			let html = '<div class="table-content-account">';
			html += '<table class="table-account-list">';
			html += '<tbody>';
			for (var i=0; i<data.length; i++) {
				if (data[i].company_account_status == 'a') {
					let vatCode = '';
					let vatAccount = '';
					if ( hasVatAccounting == 'y') {
						vatCode = vatList[data[i].vat_code].vat_code;
						vatAccount = vatList[data[i].vat_code].account_name;
					}
					html += '<tr class="details-row edit-off">';
						html += '<td>';
							html += '<div class="columns" style="margin-top:2px; margin-bottom:0">';
								html += '<div class="column details-label w-col1"><span>' +  data[i].account_name + '</span></div>';
								html += '<div class="column details-column">';
									html += '<span>' + data[i].account_no + '</span>';
									if (hasVatAccounting == 'y') {
										html += '<span style="margin-left:22px">' + vatAccount + '</span>';
									}
								html += '</div>';
						html += '</td>';
					html += '</tr>';
	
					html += '<tr class="details-row edit-on" style="display:none">';
						html += '<td>';
							html += '<div class="columns" style="margin-top:2px; margin-bottom:0">';
								html += '<div class="column details-label w-col1">';
									html += '<span>';
										html += '<input class="input" maxlength="24" style="max-width:184px; padding: 0 4px; height:26px;" id="account-name-' + i + '" value="' +  data[i].account_name + '"/>';
									html += '</span>'
								html += '</div>';
								html += '<div class="column details-column">';
									html += '<span>';
										html += '<input class="input is-numeric" maxlength="6" style="max-width:80px; padding: 0 4px; height:26px;" id="account-no-' + i + '" value="' + data[i].account_no + '"/>';
											if (i > 0 ) {
												html += '&nbsp <button index="' + i + '"  class="eAccountRemove button is-dark is-small"><i class="fas fa-times"></i></button>';
											}
											if (hasVatAccounting == 'y') {
												html += '<div class="select" style="margin-top: 6px; margin-bottom:4px">'; 
													html += '<select id="moms-' + i + '">'; // style="width:100%"
													for (let j=0; j<vatList.length; j++) {
														if (vatCode == vatList[j].vat_code) {
															var selected = ' selected ';
														}
														else {
															var selected = '';
														}
														html += '<option ' + selected + 'value="' + vatList[j].vat_code + '">' + vatList[j].account_no + ' ' + vatList[j].account_name + '</option>';
													}
													html += '</select>';
												html += '</div>';
											}
										html += '</span>';
								html += '</div>';
						html += '</td>';
					html += '</tr>';

				}
			}
			html += '</tbody>';
		
			html += '</table>';
			html += '</div>';
			//alert(html);
			$('#AccountList').html(html);
		}	
		
	}

	eEditOn() {
		$('#eNotiInvoiceOn').prop('disabled',false);
		$('#eBoNotifyOn').prop('disabled',false);
		$('#eHasBo').prop('disabled',false);
		// $('#eHasSie').prop('disabled',false); // Temp disabled
		$('#eHasVatAccounting').prop('disabled', false);
		$('#eHasVatInvoice').prop('disabled', false);
		$('.edit-off').hide();
		$('.edit-on').show();
		$('.has-vat-view').show();
		if (Current.sieAllowed == 'y') {
			if (Current.hasBo == 'y') {
				if (Current.sie_started == 'n') {
					this._showSie();
				}
				else {
					$('.sie-view').hide();
					$('.sie-view-last-ver-no').hide();
					$('.sie-view-last-booking-date').hide();
				}
				$('.has-sie-view').show();
			}
		}
	}

	editGetForm() {
		let data = {};

		// Details
		data.phone = $('#editPhone').val();
		if ($('#eNotiInvoiceOn').prop('checked')) {
			data.noti_invoice_on = 'y';
		}
		else {
			data.noti_invoice_on = 'n';
		}
		data.noti_invoice_email = $("#editNotiInvoiceEmail").val();
		// data.email_report = $('#editEmailReport').val();

		// Vat
		if ($('#eHasVatAccounting').prop('checked')) {
			data.has_vat_accounting = 'y';
		}
		else {
			data.has_vat_accounting = 'n';
		}
		data.vat_account_name_code_1 = $('#editdVatAccountNameCode1').val();
		data.vat_account_no_code_1 = $('#editdVatAccountNoCode1').val();
		data.vat_account_name_code_2 = $('#editdVatAccountNameCode2').val();
		data.vat_account_no_code_2 = $('#editdVatAccountNoCode2').val();
		data.vat_account_name_code_3 = $('#editdVatAccountNameCode3').val();
		data.vat_account_no_code_3 = $('#editdVatAccountNoCode3').val();
		// Bookingorder

		if ($('#eBoNotifyOn').prop('checked')) {
			data.has_bo_notify_on = 'y';
			data.email_report = $('#editEmailReport').val();
		}
		else {
			data.has_bo_notify_on = 'n';
		}

		if ($('#eHasBo').prop('checked')) {
			data.has_bo = 'y';

			data.bo_text = $('#editBoText').val();
			
			data.bo_settl_account_name = $('#editBoSettlAccountName').val();
			data.bo_settl_account = $('#editBoSettlAccount').val();
			
			data.bo_bank_account_name = $('#editBoBankAccountName').val();
			data.bo_bank_account = $('#editBoBankAccount').val();

			data.bo_transfee_account_name = $('#editBoTransfeeAccountName').val();
			data.bo_transfee_account = $('#editBoTransfeeAccount').val();
			
			data.bo_interest_account_name = $('#editBoInterestAccountName').val();
			data.bo_interest_account = $('#editBoInterestAccount').val();
			
			data.bo_income_account = $('#editBoIncomeAccount').val();
			
			data.bo_income_text = $('#editBoIncomeText').val();
			
			// AccountList
				if (Current.accountList.length > 0) {
				for (let i=0; i<Current.accountList.length; i++) {
					Current.accountList[i].account_no = $('#account-no-' + i).val();
					Current.accountList[i].account_name = $('#account-name-' + i).val();
					if (Current.hasVatAccounting == 'y') {
						Current.accountList[i].vat_code = $('#moms-' + i).val();
					}
					if (Current.accountList[i].account_no.length < 4) {
						this.message('Ett intäktskonto saknar kontonr');
						return false;
					}
					if (Current.accountList[i].account_no.length < 1) {
						this.message('Ett intäktskonto saknar kontonamn');
						return false;
					}
				}
				// Dubblet check
				for (let i=0; i<Current.accountList.length; i++) {
					var accountToCheck = Current.accountList[i].account_no;
					var findOriginal = false;
					for (let j=0; j<Current.accountList.length; j++) {
						if (accountToCheck == Current.accountList[j].account_no) {
							if (findOriginal == false) {
								findOriginal = true;
							}
							else {
								this.message('Kontonr ' + accountToCheck + ' finns redan!');
								return false;
							}
						}
					}
				}

				
				data._accounts = Current.accountList;
			}
		}
		else {
			data.has_bo = 'n';
		}	
		
		/*
		if ($('#eHasSie').prop('checked')) {
			data.has_sie = 'y';
		}
		else {
			data.has_sie = 'n'; 
		}
		*/

		if (Current.hasSie == 'y' && Current.sie_started == 'n') { 
			data.fy_year_no = $('#editFyYearNo').val();
			data.sie_serie = $('#editSieSerie').val();		
			data.sie_type = $('#editSieType').val();
			data.sie_kp_type = $('#editSieKpType').val();
			//if (Current.sie_started == 'n') {
				data.sie_first_verno = $('#editSieVerno').val();
				data.sie_start_date = $('#editSieStartDate').val();
			//}
		}
			
		if (data.noti_invoice_on == 'y') {
			if (Helper.validateEmail(data.noti_invoice_email) == false) {
				this.message('E-postadress för Fakturavisering är inte giltigt.');
				return false;
			}
		}
		if (data.has_bo_notify_on == 'y') {
			if (Helper.validateEmail(data.email_report) == false) {
				this.message('E-postadress för Bokföringsorderavisering är inte giltigt.');	
				return false;
			}
		}
		if (data.phone.length < 6) {
			this.message('Telefonr inte komplett.');
			return false;
		}
		
		if (Current.tdbOn == 'y') {
			data.tdb_apikey = $('#editTdbApikey').val();
			data.tdb_orgno = $('#editTdbOrgno').val();
		}

		return data;
	}

	eVatChanged(isChecked) {
		if (isChecked) {
			Current.hasVatAccounting = 'y';
			$('.vat-view').show();
			this._showAccountList(Current.accountList, Current.hasVatAccounting, Current.vatList);
			$('.edit-off').hide();
			$('.edit-on').show();
		}
		else {
			Current.hasVatAccounting = 'n';
			$('.vat-view').hide();
			this._showAccountList(Current.accountList, Current.hasVatAccounting, Current.vatList);
			$('.edit-off').hide();
			$('.edit-on').show();
		}
		$('.has-vat-view').show();
	}

	eNotiInvoiceChanged(isChecked) {
		if (isChecked) {
			$('#eNotiInvoiceOn').prop('checked', true);
			$('.noti-invoice-container').show();
		}
		else {
			$('#eNotiInvoiceOn').prop('checked', false);
			$('.noti-invoice-container').hide();
		}
    }

    eBoNotifyChanged(isChecked) {
		if (isChecked) {
			if ($('#eBoNotifyOn').prop('checked')) {
				$('.bo-notify-on-container').show();
			}
			else {
				$('.bo-notify-on-container').hide();
			}
		}
		else {
			$('#eBoNotifyOn').prop('checked', false);
			$('.bo-notify-on-container').hide();
		}
    }

	eBoChanged(isChecked) {
		if (isChecked) {
			$('.bo-view').show();
			$('.bo-notify-on-checkbox').show();
			$('.bo-notify-on-container').show();
			
			$('.has-vat-view').show();
			if (Current.sieAllowed == 'y') {
				this._showSie();
				$('.has-sie-view').show();
			}
			return 'y';
		}
		else {
			$('.bo-view').hide();
			$('.bo-notify-on-checkbox').hide();
			$('.bo-notify-on-container').hide();
			$('.has-vat-view').hide();
			this._showSie();
			$('.has-sie-view').hide();
			return 'n';
		}
	}

	eSieChanged(isChecked) {
		if (isChecked) {
			
			if (Current.sie_started == 'n') {
				$('.sie-view-ver-no').show();
				$('.sie-view-start-date').show();
				$('.sie-view-last-vern-no').hide();
				$('.sie-view-last-booking-date').hide();
				$('.sie-view').show();
			}
			else {
				$('.sie-view').hide();
				$('.sie-view-start-date').hide();
				$('.sie-view-ver-no').hide();
				$('.sie-view-last-ver-no').hide();
				$('.sie-view-last-booking-date').hide();
			}
			return 'y';
		}
		else {
			// $('.has-sie-view').hide();
			$('.sie-view').hide();
			$('.sie-view-ver-no').hide();
			$('.sie-view-start-date').hide();
			$('.sie-view-last-ver-no').hide();
			$('.sie-view-last-booking-date').hide();
			return 'n';
		}
	}

	message(message) {
		$('#message-text-modal').html(message);
		$('#message-modal').addClass('is-active');
	}

	accountNew(index) {

		/*
		let emptyAccount = {};
		emptyAccount.company_account_id = '0';
		emptyAccount.account_name = '';
		emptyAccount.account_no = '';
		emptyAccount.company_account_status = 'a'; 
		Current.accountList.push(emptyAccount);
		*/
		this._showAccountList(Current.accountList, Current.hasVatAccounting, Current.vatList);

	    // let html = this._accountInsert(index, '', '');
		//$('#AccountList').append(html);
		$('.edit-off').hide();
		$('.edit-on').show();
	}

	accounWithVatNew(index, vatList) {
	    let html = this._accountWithVatInsert(index, '', '', '0', vatList, '0');
		$('#AccountList').append(html);
		$('.edit-off').hide();
		$('.edit-on').show();
	}

	eContractPreViewPdf() {
		var path = Site + 'foretagsvillkor/' +  'Turtle-Pay-AB-Avtal-om-samarbete.pdf';
		var win = window.open(path, '_blank');
		win.focus();
	}

	eContractComplete() {
		Controller.eContractComplete();
	}

	eContractCancel() {
		let url = Current.siteUrl + 'konto?nr=0';
		window.location = url;
	}

	eBankIdBoxContinue() {
		let url = Current.siteUrl;
		window.location = url;
	}

	checkbox(tag) {
        if ($('#' + tag).prop('checked')) {
            return true;
        }
        else {
            return false;
        }
    }

}
</script>  