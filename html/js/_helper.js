/*
    wh - web helper
*/
var Helper = {};

/*
Helper.show = function (tag) {
    document.getElementById(tag).style.display="block";
}
Helper.hide = function (tag) {
    document.getElementById(tag).style.display="none";
}
Helper.setValue = function (tag, value) {
    document.getElementById(tag).value = value;
}
Helper.getValue = function (tag) {
    return document.getElementById(tag).value;
}
Helper.setHtml = function (tag, html) {
    document.getElementById(tag).innerHTML = html;
}
Helper.getHtml = function (tag) {
    return document.getElementById(tag).innerHTML;
}
Helper.onClick = function (tag, action) {
    document.getElementById(tag).addEventListener("click", action);
}
Helper.onClassClick = function (class_name, action) {
     var classes = document.getElementsByClassName(class_name);
     for (var i = 0; i < classes.length; ++i) {
         classes[i].addEventListener("click", action);
     }
 }

 Helper.addClass = function (tag, className) {
    var element = document.getElementById(tag);
    element.classList.add(className);
}

Helper.removeClass = function(tag, className) {
    var element = document.getElementById(tag);
    element.classList.remove(className);
}
*/

Helper.onClick = function (tag, action) {
    document.getElementById(tag).addEventListener("click", action);
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

/*
Helper.validateEmail = function(email) {
    var re = /^(([^<>()[]\\.,;:\s@\"]+(\.[^<>()[]\\.,;:\s@\"]+)*)|(\".+\"))@(([[0-9]{1,3}\‌​.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/; 
    return re.test(email); 
}
*/

Helper.validateEmail = function(mail) {
    if (/^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/.test(mail)) {
        return true;
    } 
    else {     
        return false;
    }
}

Helper.getCookie = function(name) {
    var v = document.cookie.match('(^|;) ?' + name + '=([^;]*)(;|$)');
      return v ? v[2] : null;
}

Helper.isValidSwedishSSN = function(ssnInput) {

    if (ssnInput.length !=12) {
        return false;
    }
    let century = ssnInput.substring(0, 2);
    //if (century.includes("19") || century.includes("20")) {
    if (century == "19" || century =="20") {
        ssnInput = ssnInput.substring(2);
    } else {
        return false;
    }
    let ssn = ssnInput
        .replace(/\D/g, "")     // strip out all but digits
        .split("")              // convert string to array
        .reverse()              // reverse order for Luhn
        .slice(0, 10);          // keep only 10 digits (i.e. 1977 becomes 77)
     // verify we got 10 digits, otherwise it is invalid
    if (ssn.length != 10) {
        return false;
    }

    let sum = ssn
    // convert to number
    .map(function(n) {
        return Number(n);
    })
    // perform arithmetic and return sum
    .reduce(function(previous, current, index) {
        // multiply every other number with two
        if (index % 2) current *= 2;
        // if larger than 10 get sum of individual digits (also n-9)
        if (current > 9) current -= 9;
        // sum it up
        return previous + current;
    });

    // sum must be divisible by 10
    return 0 === sum % 10;
}

Helper.onYesNoShowHide = function(value, element) {
    //alert(element + ' : ' + value);
    if (value == 'n') {
        $(element).hide();
    }
    else {
        $(element).show();
    }
}

Helper.getDate = function () {
    var date = new Date();
    var d = new Date(date),
    month = '' + (d.getMonth() + 1),
    day = '' + d.getDate(),
    year = d.getFullYear();

    if (month.length < 2) month = '0' + month;
    if (day.length < 2) day = '0' + day;

    return [year, month, day].join('-');
}
