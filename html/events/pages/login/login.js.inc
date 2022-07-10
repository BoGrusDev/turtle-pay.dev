<script>

var LoginTime = 360;


var MessageBankIdProblem = "Inloggning misslyckades, försök igen<br>eller kontakta Turtle Pay AB på telefon 08-806220<br>eller e-post info@turtle-pay.com."

var TokenId;

$(document).on('click', '#eLogin', function(event) {
    event.preventDefault();
   
    Validate = Date.now();
    var personal_id_number = $('#personal-id-number').val();
    if (personal_id_number && personal_id_number.length != 12  ) {
        $('#message-text-modal').html('Personnummer är inte gilltigt');
        $('#message-modal').addClass('is-active');
        return;
    }
    if (Helper.isValidSwedishSSN(personal_id_number) == false) {
        $('#message-text-modal').html('Personnummer är inte gilltigt');
        $('#message-modal').addClass('is-active');
        return;
    }
   
    var param = {};
    param._group = "User";
    param._action = "Login";
    param._personal_id_number = personal_id_number;
    $.ajax({ type: "POST", url: 'service/index2.php', data: param,
        success: function(result) {
            
            var reply = jQuery.parseJSON(result);
            if (reply.code == '1') {
                TokenId = reply.token_id;
                if (document.getElementById("BankIDCheckBox").checked == true) {
                    var url = "";
                    if (Browser == "Safari") {
                        url = "bankid:///?autostarttoken=" + reply.auto_start_token + "&redirect=https://www.turtle-pay.com/events";
                    }
                    else if (Browser == "Chrome") {
                        url = "bankid:///?autostarttoken=" + reply.auto_start_token + "&redirect=googlechrome:///";
                    }
                    else if (Browser == "Firefox") {
                        url = "bankid:///?autostarttoken=" + reply.auto_start_token + "&redirect=firefox:///";
                    }
                    else {
                        url = "bankid:///?autostarttoken=" + reply.auto_start_token + "&redirect=null";
                    }
                }
                if (isMobile == "yes") {
                    document.cookie = "turtlepayetoid=" + reply.token_id + ';sameSite=lax;path=/';
                    initMobile();
                    document.cookie = "turtlepayeip=yes" + ';sameSite=lax;path=/';
                    if (document.getElementById("BankIDCheckBox").checked == true) {
                        window.location.href = url;
                    }
                }
                else {
                    $('#login-wait-modal').addClass('is-active');

                    if (document.getElementById("BankIDCheckBox").checked == true) {
                        window.location.href = url;
                    }
                   
                    var param = {};
                    param._group = "User";
                    param._action = "Connect";
                    param._token_id = reply.token_id;
                   
                    $.ajax({ type: "POST", url: 'service/index2.php', data: param,
                        success: function(result) {
                            var reply = jQuery.parseJSON(result);
                            if (reply.code == '1') {
                               var date = new Date();
                                date.setTime(date.getTime()+(LoginTime*60*1000));
                                expires = "; expires=" + date.toGMTString();
                                //document.cookie = "turtlepaylist=" + reply.token + expires + ';path=/';
                                document.cookie = "turtlepayevents=" + reply.token + expires + ';sameSite=lax;path=/';
                                setTimeout(function () {
                                    $('#login-wait-modal').removeClass('is-active');
                                    //CheckPr(reply.token);
                                }, 4000);
                                location.reload();
                                //window.location.href = Site;  // Reload page
                            }
                            else {
                                $('#login-wait-modal').removeClass('is-active');
                                $('#message-text-modal').html(messageBankId(reply.denied_code));
                                $('#message-modal').addClass('is-active');
                            }
                        },
                        error: function(result) {
                            $('#message-text-modal').html(MessageBankIdProblem);
                            $('#message-modal').addClass('is-active');
                        }
                    });
                }
            }
            else {
                $('#message-text-modal').html(MessageBankIdProblem);
                $('#message-modal').addClass('is-active');
            }
        },
        error: function(result) {
            if (isMobile == "no") {
                alert("First: ");
            }
        }
        
    });
});

function mobileLogin() {
    //alert('Login');
    var TokenId = getCookie('turtlepayetoid');
    var param = {};
    param._group = "User";
    param._action = "Connect";
    param._token_id = TokenId;
                   
    $.ajax({ type: "POST", url: 'service/index2.php', data: param,
        success: function(result) {
            var reply = jQuery.parseJSON(result);
            if (reply.code == '1') {
                var date = new Date();
                date.setTime(date.getTime()+(LoginTime*60*1000));
                expires = "; expires=" + date.toGMTString();
                document.cookie = "turtlepayevents=" + reply.token + expires + ';sameSite=lax;path=/';
                setTimeout(function () {
                    $('#login-mobile-modal').removeClass('is-active');
                    //CheckPr(reply.token);
                }, 4000);
                location.reload();
                //window.location.href = Site;  // Reload page
            }
            else {
                $('#login-mobile-modal').removeClass('is-active');
                $('#message-text-modal').html(messageBankId(reply.denied_code));
                $('#message-modal').addClass('is-active');
            }
        },
        error: function(result) {
            $('#message-text-modal').html(MessageBankIdProblem);
            $('#message-modal').addClass('is-active');
        }
    });

    
}

function CheckPr(token) {
    var param = {};
    param._group = "People";
    param._action = "CheckPr";
    param._token = token;
    $.ajax({ type: "POST", url: 'service/index2.php', data: param,
        success: function(result) {
            var reply = jQuery.parseJSON(result);
            /*
            if (reply.length > 0) {
                document.cookie = "turtlepaya=" + reply[0].company_id + ';sameSite=lax;path=/';
            }
            else {
                document.cookie = "turtlepaya=0" + ';sameSite=lax;path=/';
            }
            */
            if (reply.length > 0) {
                window.location.href = Site;
            }
            else if (BudgetExist == '0') {
                $('#budget-check-modal').addClass('is-active');
            }
            else if (KycExist == '0') {
                $('#kyc-check-modal').addClass('is-active');
            }
            else {
                window.location.href = Site;
            }
        },
        error: function(result) {
            //Helper.setHtml('message-text-modal', MessageBankIdProblem);
            //Helper.addClass('message-modal', 'is-active');
        }
    });
}

function initMobile() {
    $('#login-mobile-modal-text').html("Väntar på BankID");
    $('#eMobileLogin').show();
    $('#login-mobile-modal').addClass('is-active');
}

function waitMobile() {
    $('#login-mobile-modal-text').html("Vänta, inloggning pågår...");
    $('#eMobileLogin').hide();
}

$(document).on('click', '#eMobileLogin', function(event) {
    event.preventDefault();
    waitMobile();
    mobileLogin();
});

$(document).on('click', '#eLoginCancel', function(event) {
    event.preventDefault();
    $('#login-wait-modal').removeClass('is-active');
    $('#message-text-modal').html('Inloggning avbruten');
    $('#message-modal').addClass('is-active');
});

function closeLoginWaitModal() {
    $('#login-wait-modal').removeClass('is-active');
}

function messageBankId(deniedCode) {
    var message = "";
    switch(deniedCode) {
        case 'userCancel':
            message = "BankID-förfrågan är avbruten.";
            break;
        case 'cancelled':
            message = "BankID-förfrågan är avbruten.";
            break;
        default:
            message = "Något fel inträffade vid BankID signering, försök igen!";
    }
    return message;
}


document.addEventListener('DOMContentLoaded', function() {

    if (isMobile == "yes") {
        document.getElementById("BankIDCheckBox").checked = true;
    }

    var inProgress = getCookie('turtlepayeip');
    //alert(inProgress);
    if (inProgress == 'yes' && isMobile == "yes" && Browser  == "Safari") {
        document.cookie = "turtlepayeip=no" + ';sameSite=lax;path=/';
        initMobile();
    }
    else {
        document.cookie = "turtlepayeip=no" + ';sameSite=lax;path=/';
    }

});

function getCookie(name) {
    var v = document.cookie.match('(^|;) ?' + name + '=([^;]*)(;|$)');
    return v ? v[2] : null;
}


</script>
