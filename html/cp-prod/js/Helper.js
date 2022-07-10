/*
    Helpers.js
*/

var Helper = {};

/**
    jQuery based
*/

Helper.setHtml = function (id, text) {
    $('#' + id).html(text);
}

Helper.setText = function (id, text) {
    $('#' + id).text(text);
}

Helper.setValue = function (id, val) {
    $('#' + id).val(val);
}

Helper.getValue = function (id) {
    return $('#' + id).val();
}

Helper.hide = function (id) {
	$(id).hide();
}

Helper.show = function (id) {
	$(id).show();
}

Helper.bind = function (tag, data) {
	$(tag).each(function(){
		$(this).text(data[$(this).attr('bind')]);
        //$(this).text(data[$(this).attr('bind')]);
        //var index  = $(this).attr('bind');
        //$(this).text(data[index]);
        //$(this).text('Hello');
        //alert(data[index]);
	});
}

Helper.bindClassByID = function (group, data) {
	$('.' + group).each(function(){
        var itemField = $(this).attr('field');
        //alert(data[itemField]);
        $(this).text(data[itemField]);

		//$(this).val(data[$(this).attr('id')]);
	});
}

Helper.bindForm = function (form, data) {

	$('#' + form + '-form input').each(function(){
		$(this).val(data[$(this).attr('name')]);
	});
	$('#' + form + '-form select').each(function(){
		$(this).val(data[$(this).attr('name')]);
	});
	$('#' + form + '-form textarea').each(function(){
		$(this).val(data[$(this).attr('name')]);
	});
	$('#' + form + '-form checkbox').each(function(){
		$(this).val(data[$(this).attr('name')]);
	});
}

Helper.clearForm = function (form) {
	$('#' + form + '-form input').each(function(){
		$(this).val("");
	});
	$('#' + form + '-form select').each(function(){
		$(this).val("");
	});
	$('#' + form + '-form textarea').each(function(){
		$(this).val("");
	});
	$('#' + form + '-form checkbox').each(function(){
		$(this).val("");
	});
}

Helper.enableForm = function (form) {
	$('#' + form + '-form input').each(function(){
		$(this).prop('disabled', false);
    });
}

Helper.disableForm = function (form) {
	$('#' + form + '-form input').each(function(){
		$(this).prop('disabled', true);
    });
}

Helper.validateForm = function (form) {
	var validation = true;
	var zxcv = '';
	$('#' + form + '-form .mess').remove();
	$('#' + form + '-form input').each(function(index) {
		var input = $(this);
		if (input.attr('require') == 'yes') {

			var attrMinLength = $(this).attr('minlength');
			if (typeof attrMinLength !== typeof undefined && attrMinLength !== false) {
				var minLength = attrMinLength;
			} else {
				var minLength = 1;
			}
			if (input.val().length < minLength) {
				validation = false;
				//$(input).parent().parent().append('<p class="mess" style="margin: 0!important">' + $(this).attr('message') + '</p>');
                $(input).parent().append('<p class="mess">required</p>');
			}
		}
		if (input.attr('email') == 'yes') {
			var re = /\S+@\S+\.\S+/;
		    if (re.test(input.val()) == false) {
				validation = false;
				$(input).parent().parent().append('<p class="mess">' + $(this).attr('message') + '</p>');
			}
		}
		if (input.attr('zxcv') == 'yes') {
			zxcy = input.val();
		}
		if (input.attr('zxcv') == 'match') {
			if (input.val() != zxcy) {
				validation = false;
				$(input).parent().parent().append('<p class="mess">' + $(this).attr('message') + '</p>');
			}
		}

		if (input.attr('date') == 'yes') {
			var dateToCheck = input.val();
			if (dateToCheck.length !== 10 ) {
				validation = false;
				$(input).parent().parent().append('<p class="mess">' + $(this).attr('message') + '</p>');
			} else {
				if (Date.parse(dateToCheck)) {
				} else {
					validation = false;
					$(input).parent().parent().append('<p class="mess">' + $(this).attr('message') + '</p>');
				}
			}
		}
	});

	$('#' + form + '-form select').each(function(index) {
		if($(this).val() == '-') {
			validation = false;
			$(this).parent().parent().append('<p class="mess">' + $(this).attr('message') + '</p>');
		}
	});
	return validation;
}

Helper.validateFormClear = function (form) {
	$('#' + form + '-form .mess').remove();
}

Helper.convertDate = function(date) {
  var yyyy = date.getFullYear().toString();
  var mm = (date.getMonth()+1).toString();
  var dd  = date.getDate().toString();

  var mmChars = mm.split('');
  var ddChars = dd.split('');

  return yyyy + '-' + (mmChars[1]?mm:"0"+mmChars[0]) + '-' + (ddChars[1]?dd:"0"+ddChars[0]);
}

Helper.gridAddRow = function(title, form) {
    Helper.hide('.modal-grid-add-form');
    Helper.show('#modal-grid-add-row-' + form);
	$('#modal-grid-add-row-insert').attr('action', form);
	var modal = UIkit.modal('#modal-grid-add-row');
	modal.show();
}

$( document ).on( 'click', '.modal-grid-add-row-cancel', function (event) {
	event.preventDefault();
	$('#modal-grid-add-row .uk-close').trigger('click');
});

/*
    JavaScrip and DOM
*/

Helper.addClass = function (tag, className) {
   var element = document.getElementById(tag);
   element.classList.add(className);
}

Helper.removeClass = function(tag, className) {
   var element = document.getElementById(tag);
   element.classList.remove(className);
}

Helper.removeComma = function (numberString) {
    return numberString.split(',').join('');
  }