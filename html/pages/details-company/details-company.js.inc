<script>

var Current = {};
Current.siteUrl = Site;
const Model = new CompanyModel();
const View = new CompanyView();
const Controller = new CompanyController();

// IF ys su
const privView = new PrivView();
const privModel = new PrivModel();
const privController = new PrivController();
Current.token = Token;
Current.userId = UserId;
// Current.KAPI = 'https://turtle-pay.grusit/service2/';
Current.API_HEADER = {
    'Accept': 'application/json',
    'Content-Type': 'application/json'
};

document.addEventListener('DOMContentLoaded', function() {
	//alert('Company');
	Controller.init();
	Controller.load();
	// Superuser
	privController.init();
});

$(document).on('click', '.eAccountRemove', function(event) {
	event.preventDefault();
	var index = $(this).attr('index');
	$(this).parent().parent().parent().hide();
	Controller.accountRemove(index);
});

/*
$(document).on('click', '#eAccountNew', function(event) {
	event.preventDefault();
	alert('AccountNew');
	// -- prevent double insert
	if (Current.accountList.length > 0) {
		let index = Current.accountList.length - 1;
		let accountName =  $('#account-no-' + index).val();
		let accountNo =  $('#account-name-' + index).val();
		if (accountName.length != 0 || accountNo.length != 0) {			
			Controller.accountNew();
		}	
	}
	else {
		Controller.accountNew();
	}
});
*/

</script>
