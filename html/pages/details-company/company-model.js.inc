<script>
class CompanyModel {

	async service(param) {
        let promise = await fetch('service2/', {
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
}
</script>