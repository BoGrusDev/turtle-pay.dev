<?php
// remove all session variables
session_unset(); 

// destroy the session 
session_destroy(); 
setcookie("cp-prod", "", time()-3600, '/','www.turtle-pay.com', false);

header('Location: https://www.turtle-pay.com/cp-prod');

?>
