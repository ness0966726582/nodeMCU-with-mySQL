<?php

$host       = "localhost";		 // host = localhost because database hosted on the same server where PHP files are hosted
$dbname     = "id20306897_demo";          // Database name
$username   = "id20306897_ness";		  // Database username
$password   = "g6#KzFCo4=5mL2x1";	      // Database password


// Establish connection to MySQL database
$conn = new mysqli($host, $username, $password, $dbname);


// Check if connection established successfully
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

else { echo "Connected to mysql database. "; }

   
// Get date and time variables
    date_default_timezone_set('Asia/Taipei');  // for other timezones, refer:- https://www.php.net/manual/en/timezones.asia.php
    $d = date("Y-m-d");
    $t = date("H:i:s");
    
// If values send by NodeMCU are not empty then insert into MySQL database table

  if(!empty($_POST['value1']))
    {		$id         = $_POST['value1'];
            $area_id    = $_POST['value2'];
		    $sensor_id  = $_POST['value3'];
            $buzzer     = $_POST['value4'];
            $sensor1    = $_POST['value5'];
            $sensor2    = $_POST['value6'];


// Update your tablename here
	        
	        //SQL插入語法改寫到網頁上直接新增
	        //$sql = "INSERT INTO iot (id,area_id,sensor_id,buzzer,sensor1, sensor2, date, time) VALUES ('".$id."','".$area_id."','".$buzzer."','".$id."','".$sensor1."','".$sensor2."', '".$d."', '".$t."')"; 
            
            //SQL更新語法
            $sql = "UPDATE iot SET id='".$id."', area_id ='".$area_id."', sensor_id='".$sensor_id."', buzzer='".$buzzer."', sensor1='".$sensor1."', sensor2 ='".$sensor2."', date ='".$d."', time ='".$t."' WHERE id='".$id."' ";
            
		if ($conn->query($sql) === TRUE) {
		    echo "Values inserted in MySQL database table.";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}


// Close MySQL connection
$conn->close();



?>