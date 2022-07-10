<script>
class VisitorClass {

    info(browser, isDuckAndGo) {
	    let visitor = {};
        visitor.browser = browser.name;
        visitor.version = browser.version;
        visitor.osname = browser.osname;
        visitor.osversion = browser.osversion;      
		visitor.cookie_on = this._checkCookie(); 
	    visitor.dg = isDuckAndGo;
        return visitor;
    }
        	
	_checkCookie() {
        let cookieEnabled = navigator.cookieEnabled;
        if (!cookieEnabled){ 
            document.cookie = "testcookie";
            cookieEnabled = document.cookie.indexOf("testcookie")!=-1;
        }
        if (cookieEnabled) {
                return 'y';
        }
        else {		
            return 'n';
        }
    }
}
</script>