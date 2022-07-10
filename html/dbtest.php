<?php  
$servername = "db";
//$servername = "host.docker.internal";
$username = "root";
$password = "password";
$dbname = "TP_prod";
$port = "3306";

try{
   //$conn = new PDO("mysql:host=$servername;port=$port;dbname=$dbname",$username,$password);
   $conn = new PDO("mysql:host=$servername;dbname=$dbname",$username,$password);
   $conn -> setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);
   echo "Connected succesfully";
} catch(PDOException $e){
   echo "Connection failed: " . $e -> getMessage();
}

/*
Connection failed: SQLSTATE[HY000] [2002] Connection refused 

Connection failed: SQLSTATE[HY000] [1045] Access denied for user 'root'@'172.27.0.4' (using password: YES) 
*/


?> 
