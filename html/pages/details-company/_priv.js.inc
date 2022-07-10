<?php
/*
    Front-end Priv

*/
?>
<script>

/*
class ViewBaseClass {

    addClass(tag, className) {
        document.getElementById(tag).classList.add(className);
    }
    addClick(tag, method) {
        document.getElementById(tag).addEventListener("click", method);
    }
    attr(element, name, value = false ) {
        if (value) {
            //e.setAttribute(value);
        }
        else {
            return element.getAttribute(name);
        }
    }
    hide(tag) {
        document.getElementById(tag).style.display="none";
    }
    html(tag, html = false) {
        document.getElementById(tag).innerHTML = html;
    } 
    initIsNumeric() {
        $(document).on('keypress', '.is-numeric', function (e) {
	        var keyCode = e.which ? e.which : e.keyCode ; 
  	        if (!(keyCode >= 48 && keyCode <= 57)) {
		        return false;
	        }
        });
    }
    isPersonalIdNumberValid (ssnInput) {
        if (ssnInput.length !=12) {
            return false;
        }
        let century = ssnInput.substring(0, 2);
        if (century == "19" || century =="20") {
        //if (century.includes("19") || century.includes("20")) {
            ssnInput = ssnInput.substring(2);
        } else {
            return false;
        }
        let ssn = ssnInput
            .replace(/\D/g, "")     // strip out all but digits
            .split("")              // convert string to array
            .reverse()              // reverse order for Luhn
            .slice(0, 10);          // keep only 10 digits (i.e. 1977 becomes 77)
        // verify we got 10 digits, otherwise it is invalid
        if (ssn.length != 10) {
            return false;
        }
        let sum = ssn
        // convert to number
        .map(function(n) {
            return Number(n);
        })
        // perform arithmetic and return sum
        .reduce(function(previous, current, index) {
            // multiply every other number with two
            if (index % 2) current *= 2;
            // if larger than 10 get sum of individual digits (also n-9)
            if (current > 9) current -= 9;
            // sum it up
            return previous + current;
        });
        // sum must be divisible by 10
        return 0 === sum % 10;
    }

    removeClass(tag, className) {
        document.getElementById(tag).classList.remove(className);
    }
    show(tag) {
        document.getElementById(tag).style.display="block";
    }
    value(tag, value ) {
        if (typeof value !== 'undefined') {
            document.getElementById(tag).value = value;
        }
        else {
            return document.getElementById(tag).value
        } 
    } 
    valueRadio(tag, value) {
        if (typeof value !== 'undefined') {  
            $("input[name=" + tag  + "][value=" + value + "]").prop('checked', true);
        }
        else {
            return $("input[name=" + tag  + "]:checked").val();
        }
    }
}
*/

class PrivView extends ViewBaseClass {
    init() {
        this.initIsNumeric();
        
        this.addClick('ePrivAdd', privView.ePrivAdd);
        this.addClick('ePrivCancel', privView.ePrivCancel);
        this.addClick('ePrivInsert', privView.ePrivInsert);
        this.addClick('ePrivUpdate', privView.ePrivUpdate);
        this.addClick('ePrivClose', privView.ePrivClose);
    }

    checkSuperuserComplete(status) {
        if (status) {
            document.getElementById('ePrivOpen').style.display="inline-flex";
        }
        else {
            privView.html('priv-box', '');
        }
    }

    ePrivClose() {
        privView.removeClass('priv-box', 'is-active')
    }

    ePrivAdd() {
        privView.hideClass('priv-list-container');
        privView.html('priv-warning-text', '')
        privView.hide('priv-personal-id-number-text');
        privView.valueRadio('priv', 'sp');
        privView.hide('priv-name-label');
        privView.hide('priv-name-text');
        privView.hide('priv-personal-id-number');
        privView.value('priv-personal-id-number', '');
        privView.show('priv-personal-id-number');
        privView.showClass('priv-update-container');
        privView.hide('ePrivAdd');
        privView.show('ePrivCancel');
        privView.show('ePrivInsert');
        privView.hide('ePrivClose');
    }

    ePrivCancel() {
        privView.hideClass('priv-update-container');
        privView.hide('ePrivCancel');
        privView.hide('ePrivUpdate');
        privView.show('ePrivAdd');
        privView.hide('ePrivInsert');
        privView.show('ePrivClose');
        privView.showClass('priv-list-container');
    }

    ePrivEdit(e) { 
        privView.hideClass('priv-list-container');
        privView.html('priv-warning-text', '')
        Current.privIndex = this.attr(e, 'index');
        privView.html('priv-personal-id-number-text', Current.privList[Current.privIndex].personal_id_number);
        privView.html('priv-name-text', Current.privList[Current.privIndex].people_name);
        privView.valueRadio('priv', Current.privList[Current.privIndex].priv);
        privView.hide('priv-personal-id-number');
        privView.show('priv-personal-id-number-text');
        privView.show('priv-name-label');
        privView.show('priv-name-text');
        privView.showClass('priv-update-container');

        privView.hide('ePrivAdd');
        privView.show('ePrivCancel');
        privView.hide('ePrivInsert');
        privView.show('ePrivUpdate');
        privView.hide('ePrivClose');
    }

    ePrivInsert() {
        // privView.show('warning-container');
        let personalIdNumber =  privView.value('priv-personal-id-number');
        if (privView.isPersonalIdNumberValid(personalIdNumber) == false) {
           privView.html('priv-warning-text', 'Ej gilltigt personnr!')
           return false;
        }
        let priv = privView.valueRadio('priv');
        privController.ePrivInsert(personalIdNumber, priv);
    }

    insertComplete(status) {
        privView.hideClass('priv-update-container');
        privView.html('priv-warning-text', '');
        privView.show('ePrivAdd');
        privView.hide('ePrivCancel');
        privView.hide('ePrivInsert');
        privView.show('ePrivClose');
        privView.showClass('priv-list-container');
    }

    ePrivUpdate() {
        let priv = privView.valueRadio('priv');
        let cpId = Current.privList[Current.privIndex].cp_id;  
        privController.ePrivUpdate(cpId, priv);
    }

    updateComplete(status) {
        privView.hideClass('priv-update-container');
        privView.hide('ePrivCancel');
        privView.hide('ePrivUpdate');
        privView.show('ePrivAdd');
        privView.show('ePrivClose');
        privView.showClass('priv-list-container');
    }

    privListTable() {
		let html = '<table class="table" style="width:100%">';
	    html += '<tr>';
            html += '<th style="text-align:left;background-color: #ffffff">Personnr</th>';
            html += '<th style="text-align:left;background-color: #ffffff">Namn</th>';
            html += '<th style="text-align:left;background-color: #ffffff">Rättighet</th>';
            html += '<th style="background-color: #ffffff"> </th>';
	    html += '</tr>';
	    for (let i = 0; i < Current.privList.length; i++) {
		    html += '<tr>';
                html += '<td>' + Current.privList[i].personal_id_number + '</td>';
                html += '<td>' + Current.privList[i].people_name + '</td>';
                html += '<td>' + privView._privNameSet(Current.privList[i].priv) + '</td>';
				//html += '<td style="text-align:right;width:66px"><button index="' + i + '" class="button is-primary is-small eUserPrivEdit">Ändra</button></td>';
                html += '<td style="text-align:right;width:66px"><button onclick="privView.ePrivEdit(this)" index="' + i + '" class="button is-dark is-small ePrivEdit">Ändra</button></td>';
            html += '</tr>';
        }    
        privView.html('priv-list', html);
    }

    _privNameSet(priv) {
        let text = '';
        switch (priv) {
    	    case 'ac' :
                text = 'Ekonomiansvarig';
                break;
            case 'pr' :  
                text = 'Administratör';
                break;
            case 'sp' :  
                text = 'Funktionär';
                break;
        }
        return text;
    }
}

class PrivModel {

    checkSuperuser() {
        let param = {};
        param._group = 'Priv';
        param._action = 'Check';
        param._user_id = Current.userId;
        param._token = Current.token;
        $.ajax({ type: "POST", url: 'service2/', data : JSON.stringify(param), contentType : 'application/json',
		    success: function(result) {
                let data = result;        
                if (data.code == '1') {
                    if (data.priv == 'su') {
                        privController.checkSuperuserComplete(true);
                    }
                    else {
                        privController.checkSuperuserComplete(false);
                    }
                }
                else {
                    privController.checkSuperuserComplete(false);
                }
            }
        });
    }

    async privList() {
        let param = {};
        param._group = 'Priv';
        param._action = 'List';
        param._user_id = Current.userId;;
        param._token = Current.token;
        let promise = await fetch('service2/', {method: 'POST', headers: Current.API_HEADER, body: JSON.stringify(param) })
        return promise;
    }

    privInsert(personalIdNumber, priv) {
        let param = {};
        param._group = 'Priv';
        param._action = 'Add';
        param._user_id = Current.userId;
        param._token = Current.token;
        param._personal_id_number = personalIdNumber;
        param.priv = priv;
        $.ajax({ type: "POST", url: 'service2/', data : JSON.stringify(param), contentType : 'application/json',
		    success: function(result) {
                let data = result;        
                if (data.code == '1') {
                    privController.insertComplete(true);
                }
                else {
                    privController.insertComplete(false);
                }
            }
        });
    }
    
    privUpdate(cpId, priv) {
        let param = {};
        param._group = 'Priv';
        param._action = 'Update';
        param._user_id = Current.userId;
        param._token = Current.token;
        param._cp_id = cpId;
        param.priv = priv;
        $.ajax({ type: "POST", url: 'service2/', data : JSON.stringify(param), contentType : 'application/json',
		    success: function(result) {
                let data = result;        
                if (data.code == '1') {
                    privController.updateComplete(true);
                }
                else {
                    privController.updateComplete(false);
                }
            }
        });
    }
}

class PrivController {
    init() {
      privView.init();
      privModel.checkSuperuser();
    }

    checkSuperuserComplete(status) {
        privView.checkSuperuserComplete(status);
    }

    privList () {
        privModel.privList()
        .then(response => response.json())
		.then(function(data) {   
            Current.privList = data;
            privView.privListTable();
        })
    }
    ePrivInsert(personalIdNumber, priv) {
        privModel.privInsert(personalIdNumber, priv);
    }
    
    insertComplete(status) {
        privController.privList();
        privView.insertComplete(status);
    }

    ePrivUpdate(cpId, priv) {
        privModel.privUpdate(cpId, priv);
    }

    updateComplete(status) {
        privController.privList();
        privView.updateComplete(status);
    }

}

</script>