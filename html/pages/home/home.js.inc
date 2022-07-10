<script>


$(document).on('click', '#eSendContact', function(event) {
	event.preventDefault();
    // Check
    var param = {};
    param.orgno = $('#orgno').val();
    param.company  = $('#company').val();
    param.contact = $('#contact').val();
    param.email = $('#email').val();
    param.mobile = $('#mobile').val();


    if (param.orgno.length < 10  ) {
        $('#message-text-modal').html('Organisationsnummer är inte giltigt.');
        $('#message-modal').addClass('is-active');
        return;
    } 
    
    if ( param.company.length < 3) {
         $('#message-text-modal').html('Företagsnamn måste anges.');
         $('#message-modal').addClass('is-active');
        return;
    }

    if ( param.contact.length < 1) {
	 $('#message-text-modal').html('Kontaktperson måste anges.');
         $('#message-modal').addClass('is-active');
        return;
    }


    if (param.email.length < 5) {
        $('#message-text-modal').html('E-postaddress är inte giltigt.');
        $('#message-modal').addClass('is-active');
        return;
    } 
    if (Helper.validateEmail(param.email) == false) {
        $('#message-text-modal').html('E-postaddress är inte giltigt');
        $('#message-modal').addClass('is-active');
        return;
    } 
    if ( param.mobile.length < 8) {
        $('#message-text-modal').html('Telefonr inte komplett.');
        $('#message-modal').addClass('is-active');
        return;
    }
    param._group = "Email";
	param._action = "Contact";

    $.ajax({ type: "POST", url: 'service2/', data: param,
        success: function(result) {
            $('#message-text-modal').html('Registrering har skickats.');
            $('#message-modal').addClass('is-active');
			
			$('#orgno').val('');
			$('#company').val('');
			$('#contact').val('');
			$('#email').val('');
			$('#mobile').val('');
        }
    });

    
   return true;
});

/*
document.addEventListener('DOMContentLoaded', function() {
    Helper.onClick('eSendContact', emailTheForm);
});
*/

</script>
