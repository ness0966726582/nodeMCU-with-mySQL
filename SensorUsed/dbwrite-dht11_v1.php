<?php

    $host = "localhost";		         // host = localhost because database hosted on the same server where PHP files are hosted
    $dbname = "id20264456_iot";              // Database name
    $username = "id20264456_ness";		// Database username
    $password = "sed0yPVAnzElKy@$";	        // Database password


// Establish connection to MySQL database
$conn = new mysqli($host, $username, $password, $dbname);


// Check if connection established successfully
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

else { echo "Connected to mysql database. "; }

   
// Get date and time variables
    date_default_timezone_set('Asia/Kolkata');  // for other timezones, refer:- https://www.php.net/manual/en/timezones.asia.php
    $d = date("Y-m-d");
    $t = date("H:i:s");
    
// If values send by NodeMCU are not empty then insert into MySQL database table

  if(!empty($_POST['nodeMCU_id']))
    {		$id = $_POST['nodeMCU_id'];
            $area_id = $_POST['area_id'];
		    $val1 = $_POST['sendval1'];
            $val2 = $_POST['sendval2'];


// Update your tablename here
	        
	        //SQL插入語法
	        //$sql = "INSERT INTO bbi_nodemcu (id,area_id,val1, val2, date, time) VALUES ('".$id."','".$area_id."','".$val1."','".$val2."', '".$d."', '".$t."')"; 
            
            //SQL更新語法
            $sql = "UPDATE bbi_nodemcu SET id='".$id."', area_id ='".$area_id."', val1='".$val1."', val2 ='".$val2."', date ='".$d."', time ='".$t."' WHERE id=1";
            
		if ($conn->query($sql) === TRUE) {
		    echo "Values inserted in MySQL database table.";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}


// Close MySQL connection
$conn->close();



?>