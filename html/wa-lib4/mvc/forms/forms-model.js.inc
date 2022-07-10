<script>
class FormsModel {

	async service(param) {
        let promise = await fetch('/wa-lib4/service/', {
            method: 'POST',
            headers: {
            'Accept': 'application/json',
            'Content-Type': 'application/json'
            },
            body: JSON.stringify(param) }
        )
        return promise;
    }
    
	
	/*
		async AccoutListUpdate(param) {
			param._group = "Company";
			param._action = 'AccountUpdate';
			param.accounts =  Current.AccountList;
			param._user_id = UserId;
			param._token = Token;
			let response = await fetch('servic22/', { method: 'post', body: JSON.stringify(param) })
			return response;
		}
	*/

    
    calculateTotal() {
        var total = 0;
        for (var i = 0; i < Current.Participant.length; i++) {
            if (Current.Participant[i].status == "a") {
                for (var j = 0; j < Current.Webform.selection.length; j++) {
                    if(isNaN(Current.Participant[i].option[j].value)) {
                        // do nothing
                    }
                    else {
                        if(Current.Webform.selection[j].calculate_on == 'y') {
                            total = total + Number(Current.Participant[i].option[j].value);
                        }
                    }  
                }
            }
        }
        if (Current.Webform.amount_on == 'y') {
            var amount = $('#amount').val();
            if (Number(amount) == false || Number(amount) == NaN) {
                // Skip no value
            }
            else {
                total = total + Number(amount);
            }
        } 
        Current.total = total;
        return;
    }

}
</script>