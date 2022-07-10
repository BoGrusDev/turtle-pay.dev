<script>

var KycNew = false;

function kycLoad() {
	var param = {};
	param._group = "People";
	param._action = "KycGet";
	param._token = Token;
	$.ajax({ type: "POST", url: 'service2/', data:param,
		success: function(result) {
			var reply = jQuery.parseJSON(result);
			if (reply.code == "1") {
				setKyc(reply);
			} else {
				KycNew = true;
				$('#medborgare_sverige').prop('checked', true);
			}
		}
	});
}

function setKyc(data) {
	if (data.medborgare_sverige == "y") {
		$('#medborgare_sverige').prop('checked', true);
		$('.medborgare-block').hide();
	} else {
		$('#medborgare_sverige').prop('checked', false);
		$('#medborgare').val(data.medborgare);
		$('.medborgare-block').show();
	}
	if (data.medborgare_annat_land == 'n') {
		$('#medborgare_annat_land').prop('checked', false);
		$('.medborgare_andra_lander-block').hide();
	} else {
		$('#medborgare_annat_land').prop('checked', true);
		$('#medborgare_andra_lander').val(data.medborgare_andra_lander);
		$('.medborgare_andra_lander-block').show();
	}

	/*
	if (data.skatt_sverige == "y") {
		$('#skatt_sverige').prop('checked', true);
	}
	*/

	if (data.skatt_annat_land == 'n') {
		$('#skatt_annat_land').prop('checked', false);
		$('.skatt_andra_lander-block').hide();
	} else {
		$('#skatt_annat_land').prop('checked', true);

		$('#skatt_andra_lander').val(data.skatt_andra_lander);
		$('.skatt_andra_lander-block').show();
	}

	$('#sysselsattning').val(data.sysselsattning);
	if (data.sysselsattning == 1) {
		$('#arbetsgivare').val(data.arbetsgivare);
		$('.arbetsgivare-block').show();
	}

	$('#pengarna_kommer_fran').val(data.pengarna_kommer_fran);
	if (data.pengarna_kommer_fran == 9) {
		$('#pengarna_annat').val(data.pengarna_annat);
		$('.pengarna_annat-block').show();
	}

	if (data.utlandska_medel == "y") {
		$('#utlandska_medel').prop('checked', true);
		$('#utlandska_kommer_fran').val(data.utlandska_kommer_fran);
		$('.utlandska_medel-select').show();
		if (data.utlandska_kommer_fran == 9) {

			$('#utlandska_medel_annat').val(data.utlandska_medel_annat);
			$('.utlandska_medel_annat-block').show();
		} else {
			$('#utlandska_medel_annat').val('');
			$('.utlandska_medel_annat-block').hide();
		}
	} else {
		$('#utlandska_medel').prop('checked', false);
		$('.utlandska_medel-select').hide();
	}

	//$('#utlandska_medel').val(data.utlandska_medel);

	//alert(data.utlandska_medel);

	/*
	if (data.utlandska_medel) {
		$('.utlandska_medel-select').show();
		if (data.utlandska_kommer_medel == 9) {
			$('#utlandska_kommer_fran').val(data.utlandska_kommer_fran);
			$('.utlandska_medel-block').show();
		}
	}
	*/

	if (data.pep == 'n') {
		$('#pep').prop('checked', false);
	} else {
		$('#pep').prop('checked', true);
	}

}

$(document).on('click', '#eSaveKyc', function(event) {
 	event.preventDefault();
	var param = {};

	if ($('#medborgare_sverige').is(":checked")) {
		param.medborgare_sverige = 'y';
	} else {
		param.medborgare_sverige = 'n';
	}

	if ($('#medborgare_annat_land').is(":checked")) {
		param.medborgare_annat_land = 'y';
		param.medborgare_andra_lander = $('#medborgare_andra_lander').val();
	} else {
		param.medborgare_annat_land = 'n';
		param.medborgare_andra_lander = '';
	}
	if ($('#skatt_annat_land').is(":checked")) {
		param.skatt_annat_land = 'y';
		param.skatt_andra_lander = $('#skatt_andra_lander').val();
	} else {
		param.skatt_annat_land = 'n';
		param.skatt_andra_lander = '';
	}
	param.sysselsattning = $('#sysselsattning').val();
	if (param.sysselsattning == 1) {
		param.arbetsgivare = $('#arbetsgivare').val();
	} else {
		param.arbetsgivare = $('#arbetsgivare').val();
	}
	param.pengarna_kommer_fran = $('#pengarna_kommer_fran').val();
	if (param.pengarna_kommer_fran == 9) {
		param.pengarna_annat = $('#pengarna_annat').val();
	} else {
		param.pengarna_annat = $('#pengarna_annat').val();
	}
	if ($('#utlandska_medel').is(":checked")) {
		param.utlandska_medel = 'y';
	} else {
		param.utlandska_medel = 'n';
	}

	if (param.utlandska_medel == 9) {
		param.utlandska_kommer_fran = $('#utlandska_kommer_fran').val();
	} else {
		param.utlandska_kommer_fran = $('#utlandska_kommer_fran').val();
	}
	if (param.utlandska_kommer_fran == 9) {
		param.utlandska_medel_annat = $('#utlandska_medel_annat').val();
	} else {
		param.utlandska_medel_annat = $('#utlandska_medel_annat').val();
	}
	if ($('#pep').is(":checked")) {
		param.pep = 'y';
	} else {
		param.pep = 'n';
	}

	if (KycNew == false) {
		param._group = "People";
		param._action = "KycUpdate";
		param._token = Token;
		$.ajax({ type: "POST", url: 'service2/', data:param,
			success: function(result) {
				var reply = jQuery.parseJSON(result);
				if (reply.code == "1") {
					$('#message-text-modal').html('Sparat!');
					$('#message-modal').addClass('is-active');
				} else {
					alert('Fail update');
				}
			}
		});
	} else {
		param._group = "People";
		param._action = "KycInsert";
		param._token = Token;
		$.ajax({ type: "POST", url: 'service2/', data:param,
			success: function(result) {
				var reply = jQuery.parseJSON(result);
				if (reply.code == "1") {
					$('#message-text-modal').html('Sparat!');
					$('#message-modal').addClass('is-active');
				} else {
					alert('Fail');
				}
			}
		});
	}
});



$(document).on('click', '.checkbox', function(event) {
	var id = $(this).attr('id');
	var value = $(this).prop('checked');
	switch(id) {
		/*
  		case 'medborgare_sverige' :
    		if (value) {
				$('.medborgare-block').hide();
				$('#medborgare').val('');
			} else {
				$('.medborgare-block').show();
			}
    		break;
		*/
		case 'medborgare_annat_land' :
    		if (value) {
				$('.medborgare_andra_lander-block').show();
			} else {
				$('.medborgare_andra_lander-block').hide();
				$('#medborgare_andra_lander').val('');
			}
    		break;

		case 'skatt_annat_land' :
    		if (value) {
				$('.skatt_andra_lander-block').show();
			} else {
				$('.skatt_andra_lander-block').hide();
				$('#skatt_andra_lander').val('');

			}
    		break;

		case 'utlandska_medel' :
    		if (value) {
				$('.utlandska_medel-select').show();
			} else {
				$('.utlandska_medel-select').hide();
				$('#utlandska_medel_annat').val('');
				$('#utlandska_kommer_fran').val('0');
				$('.utlandska_medel_annat-block').hide();
			}
    		break;


		default:
	}
});

$(document).on('change', '.selectbox', function() {
	var id = $(this).attr('id');
	var value = $(this).val() ;
	switch(id) {
  		case 'sysselsattning' :
    		if (value == '1') {
				$('.arbetsgivare-block').show();
			} else {
				$('.arbetsgivare-block').hide();
				$('#arbetsgivare').val('');
			}
    		break;

		case 'pengarna_kommer_fran' :
			//alert(value);
    		if (value == '9') {
				$('.pengarna_annat-block').show();
			} else {
				$('.pengarna_annat-block').hide();
				$('#pengarna_annat').val('');
			}
    		break;

		case 'utlandska_kommer_fran' :
    		if (value == '9') {
				$('.utlandska_medel_annat-block').show();
			} else {
				$('.utlandska_medel_annat-block').hide();
				$('#utlandska_medel_annat').val('');

			}
    		break;

		default:
	}

});

document.addEventListener('DOMContentLoaded', function() {
	kycLoad();
	$('.budget-edit-on').hide();
	$('.budget-edit-off').show();
});


</script>
