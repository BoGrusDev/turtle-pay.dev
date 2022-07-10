<?php
/*
    Front-end Company

*/
?>
<script>

class TdbView extends ViewBaseClass{
 
    init() {
       
        View.initIsNumeric();
        View. initNoSpecial(); 
        View.addClick('eConfirm', View.eConfirm); 
        View.addChange('ePeopleCompanyOn', View.ePeopleCompanyOn);
        View.addClick('eBankIdBoxContinue', View.eBankIdBoxContinue); 
        if (Current.isMobile == 'yes') {
            View.check('BankIDCheckBox');
        }
        View.addClick('eKycCancel', View.eKycCancel);
        View.addClick('eKycComplete', View.eKycComplete);
        Current.inProgress = false;
	}

    testData() {
        View.value('personal_id_number', '195711040054');
        View.value('email', 'bo.grus@yahoo.com');
        View.value('mobile', '0729427977');
        View.value('people_company', 'Snabb data AB');
        View.value('people_company_address', 'Box 9811');
        View.value('people_company_postcode', '11220');
        View.value('people_company_city', "Stockholm");
    }

    ePeopleCompanyOn() {
        if (this.checked) {
            View.show('company-adress-panel');
        }
        else {
            View.hide('company-adress-panel');
        }
    }

    eKycCancel() {
        Current.inProgress = false;
    }

    eKycComplete() {
        Current.inProgress = false;
        let el = document.getElementById('eConfirm');
        el.click();
    }

    specShow() {
        let html = '<h2 style="padding-top: 6px; margin-bottom:4px" class="title is-5">Specifikation</h2>';
        html += '<table class="table" style="width:100%;max-width: 640px">';
        for (let i=0; i<Current.Participant.length; i++) {
            html += '<tr class="bold">';
                html += '<td style="padding: 4px 0;">' + Current.Participant[i].first_name + ' ' + Current.Participant[i].last_name + '</td>';
                html += '<td style="padding: 4px 0;" class="has-text-right">' + Current.Participant[i].horse_name + '</td>';
            html += '</tr>';
            
            for (let j=0; j<Current.Participant[i].option.length; j++) {
                html += '<tr>';
                    html += '<td style="padding: 4px 0;">' + Current.Participant[i].option[j].text + '</td>';
                    html += '<td style="padding: 4px 0;" class="has-text-right">' + Current.Participant[i].option[j].value + 'kr </td>';
                html += '</tr>';
            }
        }
        html += '<tr>';
                    html += '<td class="bold" style="padding: 6px 0;">Totalt:</td>';
                    html += '<td style="padding: 6px 0;" class="has-text-right">' + Current.total.toLocaleString('se-SE', 0) + 'kr </td>';
                html += '</tr>';
        html += '</table>';
        View.html('specification', html);
    }

    async eConfirm() {

        if (Current.previewOn == 'yes') {
            View.message('Detta är en förhandsgranskning!');
            return false;
        }

        if (Current.inProgress) {
            return;
        }
        Current.inProgress = true;
        

        //View.addClass('kyc-box','is-active');
        //return;
        Current.personal_id_number = View.value('personal_id_number');
        Current.email = View.value('email');
        
        if (Current.items.mobile_on == 'y') {
            Current.mobile = View.value('mobile');
        }
        if (View.isPersonalIdNumberValid(Current.personal_id_number) == false) {
            View.message('Personnummer är inte giltigt!');
            Current.inProgress = false
            return false;
        }
        if (View.validateEmail(Current.email) == false) {
            View.message('E-postaddress är inte giltigt');
            Current.inProgress = false
            return false;
        }

        if (View.checkbox('ePeopleCompanyOn')) {
            Current.people_company_on = 'y';
            Current.people_company = View.value('people_company');
            Current.people_company_address = View.value('people_company_address');
            Current.people_company_postcode = View.value('people_company_postcode');
            Current.people_company_city  = View.value('people_company_city');
        }

        Current.isInternalBankId = View.checkbox('BankIDCheckBox');

        if (await Controller.eConfirm()) {
            if (Current.confirmStatus == 'overdue-yes') {
                alert('denied');
                return;
            }

            View.html('bankid-box-text', 'Väntar på BankID signering');
            View.addClass('bankid-box', 'is-active');

            if (Current.visitor.browser == 'Safari' && Current.visitor.cookie_on == 'y') {
                //alert('firefox');
                var date = new Date();
                date.setTime(date.getTime()+(3*60*1000));
                var expires = "; expires="+date.toGMTString();	
                document.cookie = "tpsafari=" + Current.orderRef + expires + ';sameSite=lax;path=/';
            }

            if (Current.isInternalBankId) {
                // window.location.href = Current.redirectUrl;
            }
        }   
    }

    eBankIdBoxContinue () {
        View.removeClass('bankid-box','is-active');
        View.processRedirect()
    }

    processRedirect(){
        window.location.href = SITE_URL + Current.items.wa_url + '?tp=' + Current.approvedCode;
    }
                        
}

class TdbModel {

    specCreate() {
       for (let i=0; i<Current.selections.people.spec.length; i++) {
            Current.Participant[i] = {};
            Current.Participant[i].first_name =  Current.selections.people.spec[i].first_name;
            Current.Participant[i].last_name = Current.selections.people.spec[i].last_name;
            Current.Participant[i].horse_name = Current.selections.people.spec[i].horse_name;
            Current.Participant[i].option = [];
            
            for (let j=0; j<Current.selections.people.spec[i].part.length; j++) {
                Current.Participant[i].option[j] = {};
                Current.Participant[i].option[j].event_option_setting_id = Current.selections.people.spec[i].part[j].event_option_setting_id;
                Current.Participant[i].option[j].text = Current.selections.people.spec[i].part[j].text;
                Current.Participant[i].option[j].value = Current.selections.people.spec[i].part[j].total;
                Current.Participant[i].option[j].status = 'a';
                Current.Participant[i].option[j].tdb_eco_id =Current.selections.people.spec[i].part[j].tdb_eco_id
                Current.total =  Current.total + parseInt(Current.selections.people.spec[i].part[j].total); //  Current.total +
            }
       }
    }

    async overdueCheck() {
        let param = {};
        param._group = "App"
        param._action = "OverdueCheck";
        param._personal_id_number = Current.personal_id_number;
        let promise = await $.ajax({ type: "POST", url: '/webapp-service/', data : JSON.stringify(param), contentType : 'application/json',
		    success: function(result) {
                let data = result;        
                if (data.code == '1') {
                    //Current.orderRef = 'aaaa-bbbb-cccc-dddd';
                    //Current.autoStartToken = '1111-2222-3333-4444';
                    Current.confirmStatus = 'overdue-no';
                    return true;
                }
                else {
                    Current.confirmStatus = 'overdue-yes';
                    return false;
                        // window.location.href = SITE_URL + '?m=denied';
                }
            }
        });
        return promise;
    }

    // async request() {
    request() {
        //var reply;
        Current.eBankIdInternal = View.checkbox('eBankIdInternal');
        let param = {};
        param._group = 'Tdb';
        param._action = "Request";
        param.personal_id_number = Current.personal_id_number;
        param.amount = Current.amount;
        param.receipt_number = Current.items.ref;
        param.email = Current.email;
        if (Current.items.mobile_on == 'y') {
            param.mobile = Current.mobile; 
        }
        
        param.participant_on = 'y';
        param.participant = Current.Participant;
        param.amount = Current.total;
        
        if (Current.items.infobox_1_on == 'y') {
            param.infobox_1 = $('#infobox_1').val();
        }
        if (Current.items.infobox_2_on == 'y') {
            param.infobox_2 = $('#infobox_2').val();
        }
        
        if (Current.people_company_on == 'y') {
            param.people_company_on = 'y';
            param.people_company = Current.people_company;
            param.people_company_address = Current.people_company_address;
            param.people_company_postcode = Current.people_company_postcode;
            param.people_company_city  = Current.people_company_city;
        } 
        else {
            param.people_company_on = 'n';
        }
    
        param.company_id = Current.items.company_id;
        param._invoice_event_id = Current.items.invoice_event_id; 
        param._invoice_event_item_id = Current.items.invoice_event_item_id; 
        param.event_id = Current.items.event_id;

        param._visitor = ''; // Current.visitor;
        param._web_app_tdb_log_id = Current.webAppTdbLogId;

        //console.log(JSON.stringify(param));
        //return;

        $.ajax({ type: "POST", url: '/webapp-service/', data : JSON.stringify(param), contentType : 'application/json',
		    success: function(result) {
                let data = result;
                if (data.code == '1') {   
                    Current.approvedCode = data.approved_code;
                    Current.autoStartToken = data.auto_start_token;
                    if (Current.isMobile == 'yes' && Current.eBankIdInternal) {
                        Model.bankIdMobileAutoStart();
                        View.addClass('bankid-box', 'is-active');
                    }
                    else if (Current.isMobile == 'yes') {
                        View.addClass('bankid-box', 'is-active');
                    }
                    else {
                        View.processRedirect();
                    }
                }
                else if (data.code == '6') {
                    KycController.load(data.people_id, Current.personal_id_number, true, 'y'); 
                    View.addClass('kyc-box', 'is-active');
                return;
            }
                else if (data.code == '8') {
                    //Current.Form._people_id = data.people_id;
                    //$('#uc-box').addClass('is-active');
                }
                else if (data.code == '7') {
                    // alreadyInProgress)
                    View.message('BankID är upptagen, försök igen om en stund!');
                    return;
                }
                else if (data.code == '0') {

                    if (data.denied_code == 'age_under_18') {
                        View.message('Fakturamottagare får ej vara minderårig!');
                         return;
                    }
                    else if (data.denied_code == 'alreadyInProgress') {
                        View.message('BankID är upptagen, försök igen om en stund!');
                        return;
                    }
                   
                    /*
                        if (data.denied_code == 'no_credit_limit') {
                            if (INVOICE_EVENT_ITEM_ID == '0') {
                                window.location.href = SITE_URL + '?m=denied';
                            }
                            else {
                                window.location.href = SITE_URL + '?m=denied&id=' + INVOICE_EVENT_ITEM_ID;
                            }
                            return;
                        }
                        else {
                            if (INVOICE_EVENT_ITEM_ID == '0') {
                                window.location.href = SITE_URL + '?m=denied';
                            }
                            else {
                                window.location.href = SITE_URL + '?m=denied&id=' + INVOICE_EVENT_ITEM_ID;
                            }
                            // $('#message-box-text').html('Medges ej' + message['turtle']);
                            // $('#message-box').addClass('is-active');
                            return;
                        }
                        }
                        else {
                    */

                    View.message('Ett BankID fel har inträttats, försök igen om en stund!');
                    return;
                }
                
            }
        });
    }

    bankIdMobileAutoStart() {
        console.log('init');          
        var url = "";
        if (Current.browser.name == "Safari") { 
            if (Current.visitor.dg == 'y') {
                let redirect =  SITE_URL + '?p=' + Current.approvedCode;
                url = "bankid:///?autostarttoken=" + Current.autoStartToken + "&redirect=" + redirect;
            }
            else if (Current.visitor.cookie_on == 'y') {
                let redirect = window.location.href;
                url = "bankid:///?autostarttoken=" + Current.autoStartToken + "&redirect=" + redirect;
            }
            else {
                let redirect =  SITE_URL + '?p=' + Current.approvedCode;
                url = "bankid:///?autostarttoken=" + Current.autoStartToken + "&redirect=" + redirect;
            }
            let date = new Date();
            date.setTime(date.getTime()+(3*60*1000));
            let expires = "; expires="+date.toGMTString();	
            document.cookie = "tpsafari=" + Current.approvedCode + expires + ';sameSite=lax;path=/';
        }
        else if (Current.browser.name == "Chrome") {
            let redirect =  SITE_URL + '?p=' + Current.approvedCode;
            url = "bankid:///?autostarttoken=" + Current.autoStartToken + "&redirect=googlechrome:///";
        }
        else if (Current.browser.name == "Firefox") {
            url = "bankid:///?autostarttoken=" + Current.autoStartToken + "&redirect=firefox:///";
        }
        else {
            url = "bankid:///?autostarttoken=" + Current.autoStartToken;
        }
        console.log('url: ' + url);
        window.location.href = url;
        return;
    }
}

class TdbController  {
	
	init() {
        Current.visitor = Visitor.info(Current.browser, Current.isDuckAndGo);
        Current.Participant = [];
        Current.total = 0;
        View.init();
        this.itemsLoad();
	}
    
	itemsLoad() {
        let param = {};
		param._group = "Tdb";
		param._action = "ItemsLoad";
		param._item_code = Current.itemCode;
        param._web_app_tdb_log_id = Current.webAppTdbLogId;
        param._selection_on = 'y';
        param._preview_on = Current.previewOn;
        $.ajax({ type: "POST", url: '/webapp-service/', data : JSON.stringify(param), contentType : 'application/json',
		    success: function(result) {
                let data = result;
			    if (data.code == '1') {     
                    Current.items = data;
                    let paramTdb = {};
                    paramTdb._group = "Tdb";
                    paramTdb._action = "SelectionsLoad";
                    paramTdb._item_code = Current.itemCode;
                    $.ajax({ type: "POST", url: '/webapp-service/', data : JSON.stringify(paramTdb), contentType : 'application/json',
		                success: function(result) {
			                var data =result;
                            if (data.code == '1') { 
                                Current.selections = data;
                                Model.specCreate();
                                View.specShow();
                            }
                        }
                    });
                    
			    }
			    else if (data.code == '0') {
                    alert('inget finns');
                    //location.reload();
			    }
			    else {	
				    alert('error');
				 //   // View.message('Updatera foretagsdetaljer är för tillfället inte möjligt!');
			    }
            }
		});
	}
    
    async eConfirm() {

        Current.confirmStatus = 'overdue';
        let promiseOverdue = await Model.overdueCheck();

        if (Current.confirmStatus == 'overdue-yes') {
            return promiseOverdue;
        }
        Model.request();
        
    }
}

var Current = {};
Current.siteUrl = SITE_URL;
// Current.WebAppApiUrl = 'https://turtle-pay.tp2/webapp-service/';
Current.itemCode = ITEM_CODE;
Current.webAppTdbLogId = WEB_APP_TDB_LOG_ID;
Current.isMobile = IS_MOBILE;
Current.browser = BROWSER;
Current.isDuckAndGo = IS_DUCK_AND_GO;
Current.previewOn = PREVIEW_ON;

const View = new TdbView();
const Model = new TdbModel();
const Controller = new TdbController();
const Visitor = new VisitorClass();
const BankId = new BankIdClass();

const KycView = new KycBaseView();
const KycModel = new KycBaseModel();
const KycController = new KycBaseController();

document.addEventListener('DOMContentLoaded', function() {
    KycController.init();
    Controller.init();
});

</script>

