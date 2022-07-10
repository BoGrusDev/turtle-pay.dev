<script>

/*
	settings.js
*/

var Action = {};
var Session = {};
Session.Settings = {};

Action.settingsLoad = function() {

	var param = {};
	param._group = 'Setting';
	param._action = 'GetGlobal';

	$.ajax({ type: "POST", url: 'Service.php', data: param,
		success: function(result) {

			var dataObj = jQuery.parseJSON(result);
			Session.Settings.settingId =  dataObj['setting_id'];
			Helper.bindForm('settings', dataObj);
			Helper.setValue('start-date', dataObj['startdate']);
			Helper.disableForm('settings');
		}
	});
}

$(document).on('click', '.eSettings', function(event) {
	event.preventDefault();
	var action = $(this).attr('action');

	if (action == 'edit') {
		Helper.enableForm('settings');
		$('#start-date').prop('disabled', true);
		Helper.hide('#eSettingsEdit');
		Helper.show('#eSettingsSave');
		Helper.show('#eSettingsCancel');
	}

	else if (action == 'cancel') {
		Helper.disableForm('settings');
		Helper.show('#eSettingsEdit');
		Helper.hide('#eSettingsSave');
		Helper.hide('#eSettingsCancel');
	}

	else if (action == "save") {

		var param = $('#settings-form').serializeArray();
		//if(Helper.validateForm('settings')) {
			param .push(
				{ name: '_group', value: 'Setting'},
				{ name: '_action', value: 'GlobalUpdate'});

			$.ajax({ type: "POST", url: 'Service.php', data: param,
				success: function(result) {
					Action.settingsLoad();
					Helper.show('#eSettingsEdit');
					Helper.hide('#eSettingsSave');
					Helper.hide('#eSettingsCancel');
				}
			});
		//}
	}

});

$(document).ready(function() {
	Action.settingsLoad();
});

</script>
