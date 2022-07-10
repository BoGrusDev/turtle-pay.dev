<?php
/*
    Front-end Company

*/
?>
<script>


class KycBaseView extends ViewBaseClass{
 
    peopleId = '';
    personalIdNumber = '';
    pepSet = true;
    pep = '';

    init() {
        KycView.addClick('eMedborgareAndraLander', KycView.eMedborgareAndraLander); 
        KycView.addClick('eSkattAnnatLand', KycView.eSkattAnnatLand); 

        KycView.addChange('eSysselsattning', KycView.eSysselsattning);
        KycView.addChange('ePengarnaKommerFran', KycView.ePengarnaKommerFran);
        KycView.addChange('eUtlandskaMedel', KycView.eUtlandskaMedel);
        KycView.addChange('eUtlandskaKommerFran', KycView.eUtlandskaKommerFran);
        
        KycView.addClick('eKycSave', KycView.eKycSave); 
        KycView.addClick('eKycCancel', KycView.eKycCancel); 
        KycView.addClick('eKycComplete', KycView.eKycComplete);
        KycView.check('eMedborgareSverige');
        KycView.check('eSkattSverige');
	}

    load(peopleId, personalIdNumber, pepSet, pep) {
        KycView.peopleId = peopleId;
        KycView.personalIdNumber = personalIdNumber;
        if (KycView.pep == 'n') {
            KycView.check('ePep');
        } 
    }

    eMedborgareAndraLander() {
        if (this.checked) {
            KycView.showClass('medborgare_andra_lander-block');
        } else {
            KycView.hideClass('medborgare_andra_lander-block');
            KycView.value('medborgare_andra_lander', '');
        }
    }    
    
    eSkattAnnatLand() {
        if (this.checked) {
            KycView.showClass('skatt_andra_lander-block');
        } else {
            KycView.hideClass('skatt_andra_lander-block');
        }
    }   

    eSysselsattning() {
        if (this.value == 1) {
            KycView.showClass('arbetsgivare-block');
        } else {
            KycView.hideClass('arbetsgivare-block');
            KycView.value('arbetsgivare', '');
        }
    }

    eUtlandskaMedel() {
        if (this.checked) {
            KycView.showClass('utlandska_medel-block');
        } else {
            KycView.hideClass('utlandska_medel-block');
            KycView.value('utlandska_medel','');
        }
    }

    ePengarnaKommerFran() {
        if (this.value == 9) {
            KycView.showClass('pengarna_annat-block');
        } else {
            KycView.hideClass('pengarna_annat-block');
            KycView.value('pengarna_annat', '');
        }
    }

    eUtlandskaKommerFran() {
        if (this.value == 9) {
            KycView.showClass('utlandska_medel_annat-block');
        } else {
            KycView.hideClass('utlandska_medel_annat-block');
            KycView.value('utlandska_medel_annat', '');
        }
    }
   
    eKycSave() {
        // Controll form
        var param = {};
        
        if (KycView.checkbox('eMedborgareSverige')) {
            param.medborgare_sverige = 'y';
        } else {
            param.medborgare_sverige = 'n';
        }
        
        if (KycView.checkbox('eMedborgareAndraLander')) {
            param.medborgare_annat_land = 'y';
            param.medborgare_andra_lander = KycView.value('medborgare_andra_lander');
        } else {
            param.medborgare_annat_land = 'n';
            param.medborgare_andra_lander = '';
        }

        if (KycView.checkbox('eSkattSverige')) {
            param.skatt_sverige = 'y';
        } else {
            param.skatt_sverige = 'n';
        }
        
        if (KycView.checkbox('eSkattAnnatLand')) {
            param.skatt_annat_land = 'y';
            param.skatt_andra_lander = KycView.value('skatt_andra_lander');
        } else {
            param.skatt_annat_land = 'n';
            param.skatt_andra_lander = '';
        }

        param.sysselsattning =  KycView.value('eSysselsattning');
        if (param.sysselsattning == 1) {
            param.arbetsgivare = KycView.value('arbetsgivare');
        } else {
            param.arbetsgivare = '';
        }
        param.pengarna_kommer_fran = KycView.value('ePengarnaKommerFran');
        if (param.pengarna_kommer_fran == 9) {
            param.pengarna_annat = KycView.value('pengarna_annat');
        } else {
            param.pengarna_annat = KycView.value('pengarna_annat');
        }
        
        if (KycView.checkbox('eUtlandskaMedel')) {
            param.utlandska_medel = 'y';
        } else {
            param.utlandska_medel = 'n';
        }
        param.utlandska_kommer_fran = KycView.value('eUtlandskaKommerFran');
        
        if (param.utlandska_kommer_fran == 9) {
            param.utlandska_medel_annat = KycView.value('utlandska_medel_annat');
        } else {
            param.utlandska_medel_annat = '0';
        }
      
        if (KycView.validateForm(param)) {
            param.people_id = KycView.peopleId;
            param.personal_id_number = KycView.personalIdNumber;
        
            if (KycView.checkbox('ePep')) {
                param.pep = 'y';
            } else {
                param.pep = 'n';
            }
            // console.log(JSON.stringify(param));
            KycController.save(param);

        }
       
    }

    eKycCancel() {
        KycView.removeClass('kyc-box', 'is-active');
    }

    eKycComplete() {
        // Dummy for external call
    }

    validateForm(param) {
        if (param.medborgare_sverige == 'n' && param.medborgare_annat_land == 'n') {
            KycView.validateMessage('Medborgarskap måste anges');
            return false;
        }
        if (param.medborgare_annat_land == 'y' && param.medborgare_andra_lander.length < 4) {
            KycView.validateMessage('Medborgarskap måste anges');
            return false;
        }
        if (param.skatt_annat_land == 'y' && param.skatt_andra_lander < 4) {
            KycView.validateMessage('Skattehemvist måste anges');
            return false;
        }

        if (param.sysselsattning == '0') {
            KycView.validateMessage('Sysselsättning måste anges');
            return false;
        }

        if (param.sysselsattning == '1' && param.arbetsgivare.length < 4){
            KycView.validateMessage('Arbetsgivare måste anges');
            return false;
        }

        if (param.pengarna_kommer_fran == '0') {
            KycView.validateMessage('Var pengarna kommer från måste anges');
            return false;
        }

        if (param.pengarna_kommer_fran == '9' && param.pengarna_annat.length < 3) {
            KycView.validateMessage('Var pengarna kommer från måste anges');
            return false;
        }
        /*
        if (param.utlandska_medel = 'y' && param.utlandska_kommer_fran == '0') {
            KycView.validateMessage('Var pengar från utlandet från måste anges');
            return false;
        } 

        if (param.utlandska_medel = 'y' && param.utlandska_kommer_fran == '9' && param.utlandska_medel_annat.length < 3) {
            KycView.validateMessage('Var pengar från utlandet från måste anges');
            return false;
        }
        */
       return true;
    }
    validateMessage(message) {
        KycView.html('kyc-message', message);
        KycView.show('kyc-message-block');
    }
}

class KycBaseModel {
    async service(param, Url) {
        let promise = await fetch(Url, {
            method: 'POST',
            headers: {
            'Accept': 'application/json',
            'Content-Type': 'application/json'
            },
            body: JSON.stringify(param) }
        )
        return promise;
    }
}

class KycBaseController  {
	
	init() {
        //alert('init');
        KycView.init();
	}
    load(peopleId, personalIdNumber, pepSet, pep) {
        KycView.load(peopleId, personalIdNumber, pepSet, pep);
    }
    save(param) {
        param._group = 'People';
        param._action = 'KycInsert'

        $.ajax({ type: "POST", url: '/service2/', data : JSON.stringify(param), contentType : 'application/json',
		    success: function(result) {
                let data = result;        
                if (data.code == '1') {   
                    KycView.removeClass('kyc-box', 'is-active');
                    // Trigger for external call
                    let el =  document.getElementById('eKycComplete');
                    el.click();
                }
                else {
                    // alert('error');
                }
            }
        });

        /*
        KycModel.service(param, 'https://turtle-pay.com/service2/')
        .then(response => response.json())
        .then(function(data) {   
            if (data.code == '1') {   
                KycView.removeClass('kyc-box', 'is-active');
                // Trigger for external call
                let el =  document.getElementById('eKycComplete');
                el.click();
            }
            else {
                // alert('error');
            }
        });
        */
    }

}

</script>

