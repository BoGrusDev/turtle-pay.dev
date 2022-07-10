<script>

var budget;
var StatusNew =false

function BudgetLoad() {
	var param = {};
	param._group = "People";
	param._action = "BudgetGet";
	param._token = Token;
	$.ajax({ type: "POST", url: 'service2/', data: param,
		success: function(result) {
			var reply = jQuery.parseJSON(result);
			if (reply.code == "1") {
				budget = reply;
				setShow();
				setEdit();
				$('.edit-off').hide();
				$('.edit-on').show();
			}
			else {
				StatusNew = true;
				budget = {};
				budget.ipm_sum = 0;
				budget.ipm_arbete = 0;
				budget.ipm_pension = 0;
				budget.ipm_form = 0;
				budget.bpm_sum = 0;
				budget.bpm_hyra = 0;
				budget.bpm_ranta = 0;
				budget.bpm_amor = 0;
				budget.bpm_el = 0;
				budget.bpm_vatten = 0;
				budget.bpm_sop = 0;
				budget.bpm_rep = 0;
				budget.lpm_sum = 0;
				budget.lpm_ranta = 0;
				budget.lpm_amor = 0;
				budget.fpm_sum = 0;
				budget.fpm_ranta = 0;
				budget.fpm_skatt = 0;
				budget.fpm_besikt = 0;
				budget.fpm_fors = 0;
				budget.fpm_rep = 0;
				budget.fpm_bransle = 0;
				budget.fpm_parking = 0;
				budget.hpm_sum = 0;
				budget.hpm_livs = 0;
				budget.hpm_klader = 0;
				budget.hpm_sport = 0;
				budget.hpm_mobil = 0;
				budget.hpm_forbruk = 0;
				budget.hpm_hemutr = 0;
				budget.omk_sum = 0;
				budget.omk_rest = 0;
				budget.omk_kollek = 0;
				budget.omk_lakare = 0;
				budget.sum_att_leva = 0;
				setShow();
				setEdit();
				$('.edit-off').hide();
				$('.edit-on').show();
			}
			//$('.edit-on').hide();
			//$('.edit-off').show();
		}
	});
}

function setShow() {
	for (var key in budget) {
		$("#show_" + key).html(budget[key]);
	}
}

function setEdit() {
	for (var key in budget) {
		$("#" + key).val(budget[key]);
	}
}

function endEdit() {
	for (var key in budget) {
		budget[key] = $("#" + key).val();
	}

}

function calculateSum() {

	budget.ipm_sum = Number(budget.ipm_arbete) + Number(budget.ipm_pension) + Number(budget.ipm_form) ;
	budget.bpm_sum = Number(budget.bpm_hyra) + Number(budget.bpm_ranta) + Number(budget.bpm_amor) + Number(budget.bpm_el) + Number(budget.bpm_vatten) + Number(budget.bpm_sop) + Number(budget.bpm_rep);
	budget.lpm_sum = Number(budget.lpm_ranta) + Number(budget.lpm_amor);
	budget.fpm_sum = Number(budget.fpm_ranta) + Number(budget.fpm_skatt) + Number(budget.fpm_besikt) + Number(budget.fpm_fors) + Number(budget.fpm_rep) + Number(budget.fpm_bransle) + Number(budget.fpm_parking);
	budget.hpm_sum = Number(budget.hpm_livs) + Number(budget.hpm_klader) + Number(budget.hpm_sport) + Number(budget.hpm_mobil) + Number(budget.hpm_forbruk) + Number(budget.hpm_hemutr);
	budget.omk_sum = Number(budget.omk_rest) + Number(budget.omk_kollek) + Number(budget.omk_lakare);

	budget.sum_att_leva = budget.ipm_sum - budget.bpm_sum - budget.lpm_sum - budget.fpm_sum - budget.hpm_sum - budget.omk_sum;

	$('#show_sum_att_leva').html(budget.sum_att_leva);

}

$(document).on('focusout', '.w-budget', function(event) {
	event.preventDefault();
	var value = $(this).val();
	var result = Number(value);
	if (isNaN(result) || result == 0) {
		 $(this).val('0');
	}
	if (result < 0) {
		result = result * -1;
		$(this).val(result);
	}
	endEdit();
	calculateSum();
	$('#show_ipm_sum').html(budget.ipm_sum);
	$('#show_bpm_sum').html(budget.bpm_sum);
	$('#show_lpm_sum').html(budget.lpm_sum);
	$('#show_fpm_sum').html(budget.fpm_sum);
	$('#show_hpm_sum').html(budget.hpm_sum);
	$('#show_omk_sum').html(budget.omk_sum);
	$('#show-budget.sum_att_leva').html(budget.sum_att_leva);
});

/*

$(document).on('click', '#eEditModeOn', function(event) {
	event.preventDefault();
	setEdit();
	$('.edit-off').hide();
	$('.edit-on').show();
});
*/

$(document).on('click', '#eEditModeCancel', function(event) {
	event.preventDefault();
	//$('.edit-on').hide();
	//$('.edit-off').show();
	BudgetLoad();
});


$(document).on('click', '#eEditUpdate', function(event) {
	event.preventDefault();
	endEdit();
	calculateSum();
	//setShow();
	//$('.edit-on').hide();
	//$('.edit-off').show();
	//console.log(budget);
	budget._group = "People";
	if (StatusNew) {
		budget._action = "BudgetNew";
		StatusNew = false;
	}
	else {
		budget._action = "BudgetUpdate";
	}
	budget._token = Token;
	$.ajax({ type: "POST", url: 'service2/', data:budget,
		success: function(result) {
			var reply = jQuery.parseJSON(result);
			if (reply.code == "1") {
				$('#message-text-modal').html('Sparat!');
		        $('#message-modal').addClass('is-active');
			} else {
				alert('Error');
			}
		}
	});

});


$(document).ready(function() {

	$('#navbar-user-budget').addClass('is-active');
	BudgetLoad();

	//setEdit();
	//$('.edit-off').hide();
	//$('.edit-on').show();

	//$('.budget-edit-on').hide();
	//$('.budget-edit-off').show();
	//$('#eEditModeOn').trigger('click');
});




</script>
