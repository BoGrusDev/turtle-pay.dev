<script>
	$('#navbar-contact-us').addClass('is-active');

	/*
	$(document).ready(function() {

	Helper.addClass('navbar-contact-us','is-active');

	$(document).on('click', '#send-contact', function(event) {
		event.preventDefault();
        $('#send-contact').hide();
        $('#contact-message').html("Vänta...");
        var param = {};
        param._group = "Email";
        param._action = 'Contact';
        param.name = $('#contact-name').val();
        param.email = $('#contact-email').val();
        param.mobile = $('#contact-mobile').val();
        param.desc = $('#contact-desc').val();
        //console.log(param);
        $.ajax({ type: "POST", url: 'service/index.php', data: param,
            success: function(result) {
                //console.log(result);
                $('#contact-message').html("Contact information sänt");
            }
        });
	});
});
	*/
</script>
