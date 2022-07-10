<script>
class BankIdClass {

    init(orderRef, autoStartToken, browser, visitor, siteUrl ) {
        alert(browser.name);
        let redirectUrl = '';
        switch (browser.name) {
            case 'Safari':
                if (visitor.dg == 'y') {
                    // Duck and Go
                    let redirect =  siteUrl + '?p=' + orderRef;
                    redirectUrl = "bankid:///?autostarttoken=" + autoStartToken + "&redirect=" + redirect;
                }
                else if (visitor.cookie_on == 'y') {
                    let redirect = window.location.href;
                    redirectUrl = "bankid:///?autostarttoken=" + autoStartToken + "&redirect=" + redirect;
                }
                else {
                    let redirect = siteUrl + '?p=' + orderRef;
                    redirectUrl = "bankid:///?autostarttoken=" + autoStartToken + "&redirect=" + redirect;
                }
                if (Current.visitor.cookie_on == 'y') {
                    let date = new Date();
                    date.setTime(date.getTime()+(3*60*1000));
                    let expires = "; expires="+date.toGMTString();	
                    document.cookie = "tpsafari=" + orderRef + expires + ';sameSite=lax;path=/';
                }
                break;
            case 'Chrome':
                let redirect = siteUrl + '?p=' + orderRef;
                redirectUrl = "bankid:///?autostarttoken=" + autoStartToken + "&redirect=googlechrome:///";
                break;
            case 'Firefox':
                redirectUrl = "bankid:///?autostarttoken=" + autoStartToken + "&redirect=firefox:///";
                break;
            default:
                redirectUrl = "bankid:///?autostarttoken=" + autoStartToken;
                break;
        }
        return redirectUrl;
    }    
}
</script>