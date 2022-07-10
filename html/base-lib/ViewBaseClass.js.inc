<?php
/*
    Front-end Priv

*/
?>
<script>
class ViewBaseClass {

    addClass(tag, className) {
        document.getElementById(tag).classList.add(className);
    }

    addChange(tag, method) {
        document.getElementById(tag).addEventListener("change", method);
    }

    addClick(tag, method) {
        document.getElementById(tag).addEventListener("click", method);
    }

    append(tag, html) {
        $('#' + tag).append(html);
    }

    attr(element, name, value = false ) {
        if (value) {
            //e.setAttribute(value);
        }
        else {
            return element.getAttribute(name);
        }
    }

    check(tag) {
        $('#' + tag).prop('checked', true);
    }

    checkbox(tag) {
        if ($('#' + tag).prop('checked')) {
            return true;
        }
        else {
            return false;
        }
    }

    disabled(tag) {
        let elementsId = tag.split(',');
        for (let i=0; i<elementsId.length; i++) {
            document.getElementById(elementsId[i]).disabled = true;
        }
    }

    enabled(tag) {
        let elementsId = tag.split(',');
        for (let i=0; i<elementsId.length; i++) {
            document.getElementById(elementsId[i]).disabled = false;
        }
    }

    hide(tag) {
        document.getElementById(tag).style.display="none";
    }

    hideClass(tag) {
        let elementsId = tag.split(',');
        for (let i=0; i<elementsId.length; i++) {
            $('.' + elementsId[i]).hide();
        }
    }

    html(tag, html = false) {
        document.getElementById(tag).innerHTML = html;
    } 
    
    initIsNumeric() {
        $(document).on('keypress', '.is-numeric', function (e) {
            var keyCode = e.which ? e.which : e.keyCode ; 
            if (!(keyCode >= 48 && keyCode <= 57)) {
                return false;
            }
        });
    }

    initNoSpecial() {
        $(document).on('keypress', '.no-special', function (e) {
            var keyCode = e.which ? e.which : e.keyCode     
            if (!(keyCode == 34 || keyCode == 39)) {
                
            }
            else {
                return false;
            }
        });
    }

    isPersonalIdNumberValid (ssnInput) {
        if (ssnInput.length !=12) {
            return false;
        }
        let century = ssnInput.substring(0, 2);
        if (century == "19" || century =="20") {
        //if (century.includes("19") || century.includes("20")) {
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

    message(message) {
        View.html('message-box-text', message);
        View.addClass('message-box','is-active');
    }

    removeClass(tag, className) {
        document.getElementById(tag).classList.remove(className);
    }

    show(tag) {
        document.getElementById(tag).style.display="block";
    }

    showClass(tag) {
        let elementsId = tag.split(',');
        for (let i=0; i<elementsId.length; i++) {
            $('.' + elementsId[i]).show();
        }
    }

    uncheck(tag) {
        $('#' + tag).prop('checked', false);
    }

    validateEmail(mailAdress) {
        let mailformat=/(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])/;
        if(mailAdress.match(mailformat)) {
            return true;
        }
        else {
            return false;
        }
    }

    value(tag, value ) {
        if (typeof value !== 'undefined') {
            document.getElementById(tag).value = value;
        }
        else {
            return document.getElementById(tag).value
        } 
    }

    valueRadio(tag, value) {
        if (typeof value !== 'undefined') {  
            $("input[name=" + tag  + "][value=" + value + "]").prop('checked', true);
        }
        else {
            return $("input[name=" + tag  + "]:checked").val();
        }
    }
}
</script>