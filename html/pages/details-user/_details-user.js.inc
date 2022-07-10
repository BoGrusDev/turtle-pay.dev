<script>

function DetailsLoad() {
	var param = {};
	param._group = "People";
	param._action = "Details";
	param._token = Token;

	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var data = jQuery.parseJSON(result);
			if (data.code == '1') {
				$("#dName").html(data.first_name + " " +  data.last_name);
				$("#dPersonalId").html(data.personal_id_number);
				$("#dAddress").html(data.address);
				$("#dPostAddress").html(data.postcode + ' ' + data.city);

				$("#dEmail").html(data.email);
				$("#dMobile").html(data.mobile);
				$('#dClearingNo').html(data.clearing_no);
				$('#dBankAccount').html(data.bank_account);
				$('#editEmail').val(data.email);
				$('#editMobile').val(data.mobile);
				$('#editClearingNo').val(data.clearing_no);
				$('#editBankAccount').val(data.bank_account);

				$("#dOcrno").html(data.ocrno);
				//Helper.setHtml("dCreditLimit", data.settings.customer_credit_limit);
			}
			else {
				alert('Fail: '  + data.message);
			}
		},
        error: function(result) {
            //alert("Error Person");
        }
	});
}

$(document).on('click', '#eEditModeOn', function(event) {
	event.preventDefault();

	$('.edit-off').hide();
	$('.edit-on').show();
});

$(document).on('click', '#eEditModeCancel', function(event) {
	event.preventDefault();
	$('.edit-on').hide();
	$('.edit-off').show();
});

$(document).on('click', '#eEditUpdate', function(event) {
	event.preventDefault();
	var email = $('#editEmail').val();
	var mobile = $('#editMobile').val();
	var clearingNo = $('#editClearingNo').val();
	var bankAccount = $('#editBankAccount').val();
	if (email.length < 5) {
       $('#message-text-modal').html('E-postadress är inte giltigt.');
        $('#message-modal').addClass('is-active');
        return;
    }
    if (Helper.validateEmail(email) == false) {
        $('#message-text-modal').html('E-postadress är inte giltigt');
        $('#message-modal').addClass('is-active');
        return;
    }
    if ( mobile.length < 8) {
        $('#message-text-modal').html('Telefonr inte komplett.');
        $('#message-modal').addClass('is-active');
        return;
    }

	var param = {};
	param._group = "People";
	param._action = 'DetailsUpdate';
	param.email = email;
	param.mobile = mobile;
	param.clearing_no = clearingNo;
	param.bank_account = bankAccount;
	param._token = Token;
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var reply = jQuery.parseJSON(result);
			if (reply.code == "1") {
					/// OK
			} else {
				$('#message-text-modal').html('Detaljer kunde inte sparas.');
		        $('#message-modal').addClass('is-active');
				return;
			}
			$('.edit-on').hide();
			$('.edit-off').show();
			DetailsLoad();
		}
	});
});


document.addEventListener('DOMContentLoaded', function() {
	$('#navbar-user-details').addClass('is-active');
	DetailsLoad();
	//CheckPr();
});


</script>
