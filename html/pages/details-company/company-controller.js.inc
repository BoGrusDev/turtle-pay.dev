<script> 

class CompanyController  {
	
	init() {
        View.init();
	}

	load() {
        let param = {};
		param._group = "Company";
		param._action = "DetailsLoad";
		param._token = Token;
		param._user_id = UserId;
		Model.service(param)
		.then(response => response.json())
		.then(function(data) {   
			if (data.code == '1') { 
                Current.hasBo = data.has_bo;
                Current.sieAllowed = data.sie_allowed;
                Current.hasSie =data.has_sie;
                Current.sie_started = data.sie_started;
                Current.hasVatAccounting = data.has_vat_accounting;
                Current.accountList = data._accounts;
                Current.vatList = data._vats;
                Current.tdbOn = data.tdb_on;
                if (Current.tdbOn == 'y') {
                    Current.tdbApikey = data.tdb_apikey;
                    Current.tdbOrgno = data.tdb_orgno;
                }
                View.load(data);
                Controller.ContractCheck();          
			}
			else if (data.code == '8') {
                document.cookie = "turtlepay=; expires=Thu, 01 Jan 1970 00:00:00 UTC; "; 
                document.cookie = "turtlepayv=; expires=Thu, 01 Jan 1970 00:00:00 UTC; ";
                document.cookie = "turtlepayp=; expires=Thu, 01 Jan 1970 00:00:00 UTC; ";
                //window.location.href = Site;
                location.reload();
			}
			else {	
				//alert('error');
				// View.message('Updatera foretagsdetaljer är för tillfället inte möjligt!');
			}
		})
	}

    ContractCheck() {
        let param = {};
		param._group = "Company";
		param._action = "ContractCheck";
		param._token = Token;
		param._user_id = UserId;
		Model.service(param)
		.then(response => response.json())
		.then(function(data) {   
			if (data.code == '1') {     
                $('#contract-box').addClass('is-active');
                //$('#contract-box-message').html('Det gick inte att signera för tillfället! Vänta ett tag och försök igen<br>eller kontakta Turtle Pay');
                       
            }
        })
    }

	eEditOn() {
		View.eEditOn();
    }
    
	eEditCancel() {
		location.reload();
    }
    
	eEditUpdate() {

        let param = View.editGetForm() ;
        if (param) {
            param._group = "Company";
		    param._action = 'DetailsUpdate';
		    param._user_id = UserId;
		    param._token = Token; 
            param.has_bo = Current.hasBo;
            delete param.has_sie; // Not save the sie on / off
            Model.service(param)
            .then(response => response.json())
		    .then(function(data) {      
                if (data.code == '1') {
                    location.reload();
                }
                else {
                    View.message('Inte möjligt att spara uppgifterna för tillfället');
                }
            })
        }
	}

    eVatChanged() {
        let isChecked = $(this).is(':checked');
        View.eVatChanged(isChecked);
    }

    eNotiInvoiceChanged() {
        let isChecked = $(this).is(':checked');
        View.eNotiInvoiceChanged(isChecked);
    }
   
    eBoNotifyChanged() {
        let isChecked = $(this).is(':checked');
       View.eBoNotifyChanged(isChecked);
    }
   
    eBoChanged() {
        let isChecked = $(this).is(':checked');
        Current.hasBo = View.eBoChanged(isChecked);
    }
    
    /*
    eSieChanged() {
        let isChecked = $(this).is(':checked');
        Current.hasSie = View.eSieChanged(isChecked);
    }
    */

    eAccountNew() {

        // -- prevent double insert
	    if (Current.accountList.length > 0) {
		    let index = Current.accountList.length - 1;
		    let accountName =  $('#account-no-' + index).val();
		    let accountNo =  $('#account-name-' + index).val();
		    if (accountName.length != 0 || accountNo.length != 0) {			
			   // Continue
		    }	
            else {
                return;
            }
	    }
        
        // -- Create empy account
	    let emptyAccount = {};
	    emptyAccount.company_account_id = '0';
        emptyAccount.account_name = '';
        emptyAccount.account_no = '';
        emptyAccount.vat_code = '0';
        emptyAccount.company_account_status = 'a'; 
	    Current.accountList.push(emptyAccount);
        let index = Current.accountList.length - 1;
        //if (Current.hasVatAccounting == 'y') {
            // View.accounWithVatNew(index, Current.vatList)
        //}
        //else {
            View.accountNew(index)
        //}
	}

	accountRemove(index) {
        Current.accountList[index].company_account_status = 'r';
	}

    eContractComplete() {
        let param = {};
        param._group = "Company";
        param._action = 'ContractSignInit';
        param._user_id = UserId;
		param._token = Token;  
		param.bankid_text = "Signering av Avtal om samarbete och personuppgiftsbiträde för ";
        Model.service(param)
        .then(response => response.json())
        .then(function(data) {      
            if (data.code == '1') {

                Current.eBankIdInternal = View.checkbox('eBankIdInternal');

                //if (Current.eBankIdInternal) {
                    // Model.bankIdMobileAutoStart();
                //}
                // Should be in View
                $('#contract-box').removeClass('is-active');
                $('#bankid-box').addClass('is-active');
                // Mobile auto_start_token": "7a0479f4-f5d8-42a9-85b9-80154da98298"

                let param2 = {};
                param2._group = "Company";
                param2._action = 'Contract';
                param2._user_id = UserId;
                param2._token = Token;  
                param2._order_ref = data.order_ref;
                Model.service(param2)
                .then(response => response.json())
                .then(function(data) {      
                    if (data.code == '1') {
                       View.eBankIdBoxContinue();
                    }
                    else {
                        $('#bankid-box').removeClass('is-active');
                        $('#contract-box-message').html('Det gick inte att signera för tillfället! Vänta ett tag och försök igen<br>eller kontakta Turtle Pay');
                        $('#contract-box').addClass('is-active');
                    }
                })
            }
            else {
                $('#contract-box-message').html('Det gick inte att signera för tillfället! Vänta ett tag och försök igen<br>eller kontakta Turtle Pay');
                //$('#contract-box').addClass('is-active');
            }
        })
    }
	
    ePrivOpen() {
        // privController.init();
        
        privModel.privList()
        .then(response => response.json())
        .then(function(data) {
            Current.privList = data;
            privView.privListTable();      
            $('#priv-box').addClass('is-active')
        })
        
    }
}
</script>