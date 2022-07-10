<script>

const App = {};
App.isMobile = isMobile;
App.browser = Browser
App.loginTime = 360;
// var LoginTime = 360;
App.messageBankIdProblem = "Inloggning misslyckades, försök igen<br>eller kontakta Turtle Pay AB på telefon 08-806220<br>eller e-post info@turtle-pay.com."
//var MessageBankIdProblem = "Inloggning misslyckades, försök igen<br>eller kontakta Turtle Pay AB på telefon 08-806220<br>eller e-post info@turtle-pay.com."
App.tokenId;
//var TokenId;

App.bankIdThisUnit = false;
//    if (document.getElementById("BankIDCheckBox").checked == true) {


class LoginModel {
    validatePersonalId (personalIdNumber) {
        let errCode = 0;
        if (personalIdNumber && personalIdNumber.length != 12  ) {
            errCode = 1;
        }
        else if (_.isValidSwedishSSN(personalIdNumber) == false) {
            errCode = 1;
        }
        return errCode;
    }

    async login(personalIdNumber) {
        var param = {};
        param._group = "User";
        param._action = "Login";
        param._personal_id_number = personalIdNumber;
        let response = await fetch('service/', { method: 'post', body: JSON.stringify(param) })
        return response;
    }

    bankIdUrl() {
        let url = '';
        if (App.browser == "Safari") {
            url = "bankid:///?autostarttoken=" + data.auto_start_token + "&redirect=https://www.turtle-pay.com/events";
        }
        else if (App.browser == "Chrome") {
            url = "bankid:///?autostarttoken=" + data.auto_start_token + "&redirect=googlechrome:///";
        }
        else if (App.rowser == "Firefox") {
            url = "bankid:///?autostarttoken=" + data.auto_start_token + "&redirect=firefox:///";
        }
        else {
            url = "bankid:///?autostarttoken=" + data.auto_start_token + "&redirect=null";
        }
        return url;
    }

    async connect() {
        var param = {};
        param._group = "User";
        param._action = "Connect";
        param._token_id = App.tokenId;
        let response = await fetch('service/', { method: 'post', body: JSON.stringify(param) })
        return response;
    }
}
        

class LoginView {
    constructor() {
        /*
        this.error = [
            [1, 'Personnummer är inte gilltigt']
        ];
        */
    }
    init() {
        if (App.isMobile == 'y') {
            document.getElementById("BankIDCheckBox").checked = true;
        }
    }
    initMobile() {
        $('#login-mobile-modal-text').html("Väntar på BankID");
        $('#eMobileLogin').show();
        $('#login-mobile-modal').addClass('is-active');
    }
}

class LoginController {
    init() {
        View.init();
        this.inProgress = _.getCookie('turtlepayip');
        if (this.inProgress == 'yes' && App.isMobile == "yes" && App.browser  == "Safari") {
            document.cookie = "turtlepayip=no" + ';sameSite=lax;path=/';
            View.initMobile();
        }
        else {
            document.cookie = "turtlepayip=no" + ';sameSite=lax;path=/';   
        }
        if (document.getElementById("BankIDCheckBox").checked == true) {
            App.bankIdThisUnit = true;
        }
        else {
            App.bankIdThisUnit = false;
        }
    }
    eLogin(personalIdNumber) {
        // Validate = Date.now();
        let url = '';
        let retCode = Model.validatePersonalId(personalIdNumber);
        if (retCode > 0 ) {
            _.messageBox('Personnummer är inte gilltigt');
            return;
        }
        Model.login(personalIdNumber)
        .then(response => response.json())
		.then(function(data) {   
            if (data.code == '1') {
                App.tokenId = data.token_id;
                if (App.bankIdThisUnit) {
                    url = Model.bankIdUrl()
                }
                
                if (App.isMobile == "yes") {
                    /*
                    document.cookie = "turtlepaytoid=" + reply.token_id + ';sameSite=lax;path=/';
                    initMobile();
                    document.cookie = "turtlepayip=yes" + ';sameSite=lax;path=/';
                    if (document.getElementById("BankIDCheckBox").checked == true) {
                        window.location.href = url;
                    }
                    */
                }
                else {
                    
                    $('#login-wait-modal').addClass('is-active');

                    if (App.bankIdThisUnit) {
                        window.location.href = url;
                    }
                    Model.connect()
                    .then(response => response.json())
		            .then(function(data) {   
                        if (data.code == '1') {
                            var date = new Date();
                            date.setTime(date.getTime()+(App.loginTime * 60 * 1000));
                            expires = "; expires=" + date.toGMTString();
                            document.cookie = "turtlepayevents=" + data.token + expires + ';sameSite=lax;path=/';
                            setTimeout(function () {
                                $('#login-wait-modal').removeClass('is-active');
                            }, 4000);
                            alert('Reload');
                            location.reload();
                        }
                        else {
                            $('#login-wait-modal').removeClass('is-active');
                            $('#message-text-modal').html(messageBankId(data.denied_code));
                            $('#message-modal').addClass('is-active');
                        }
                    })
                }
            }
            else {
                $('#message-text-modal').html(App.messageBankIdProblem);
                $('#message-modal').addClass('is-active');
            }
        })
    }
}

const Model = new LoginModel();
const View = new LoginView();
const Controller = new LoginController(); 

$(document).on('click', '#eLogin', function(event) {
    event.preventDefault();
    let personalIdNumber = $('#personal-id-number').val();
    Controller.eLogin(personalIdNumber);
});


/*

    var param = {};
    param._group = "User";
    param._action = "Login";
    param._personal_id_number = personal_id_number;
    $.ajax({ type: "POST", url: 'service/', data: param,
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
                    document.cookie = "turtlepaytoid=" + reply.token_id + ';sameSite=lax;path=/';
                    initMobile();
                    document.cookie = "turtlepayip=yes" + ';sameSite=lax;path=/';
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
                   
                    $.ajax({ type: "POST", url: 'service/', data: param,
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
    var TokenId = getCookie('turtlepaytoid');
    var param = {};
    param._group = "User";
    param._action = "Connect";
    param._token_id = TokenId;
                   
    $.ajax({ type: "POST", url: 'service/', data: param,
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
    $.ajax({ type: "POST", url: 'service/', data: param,
        success: function(result) {
            var reply = jQuery.parseJSON(result);
            if (reply.length > 0) {
                document.cookie = "turtlepaya=" + reply[0].company_id + ';sameSite=lax;path=/';
            }
            else {
                document.cookie = "turtlepaya=0" + ';sameSite=lax;path=/';
            }

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

*/

</script>
