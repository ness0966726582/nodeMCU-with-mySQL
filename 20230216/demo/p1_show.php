<?php
//若使用_GET 參數-->將會顯示於URL上
echo $_POST['value1'];
echo "<br>";
echo $_POST['value2'];
echo "<br>";
echo $_POST['value3'];
echo "<br>";

$host = "localhost";		 // host = localhost because database hosted on the same server where PHP files are hosted
$dbname = "id20306897_demo";              // Database name
$username = "id20306897_ness";		// Database username
$password = "g6#KzFCo4=5mL2x1";	        // Database password


// Establish connection to MySQL database
$conn = new mysqli($host, $username, $password, $dbname);


// Check if connection established successfully
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
else { echo "Connected to mysql database. "; }

   
// Get date and time variables
    date_default_timezone_set('Asia/taipei');  // for other timezones, refer:- https://www.php.net/manual/en/timezones.asia.php
    $d = date("Y-m-d");
    $t = date("H:i:s");
    
// If values send by NodeMCU are not empty then insert into MySQL database table

  if(!empty($_POST['value1']))
    {	$id     = $_POST['value1'];
	    $name   = $_POST['value2'];
	    $val1   = $_POST['value3'];

        // Update your tablename here 
	    $sql = "INSERT INTO demo (id, name, val1, date, time) VALUES ('".$id."','".$name."','".$val1."', '".$d."', '".$t."')"; 
            
    
		if ($conn->query($sql) === TRUE) {
		    echo "Values inserted in MySQL database table.";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}


// Close MySQL connection
$conn->close();
?>