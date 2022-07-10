<script>

var Current = {};
Current.siteUrl = Site;
const Model = new CompanyModel();
const View = new CompanyView();
const Controller = new CompanyController();

document.addEventListener('DOMContentLoaded', function() {
	//alert('Company');
	Controller.init();
	Controller.load();
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
