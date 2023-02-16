<body>

<a href="https://bbi2023.000webhostapp.com/home/iot/index.php">首頁<br></a>

</body>


<?php
//若使用_GET 參數-->將會顯示於URL上
echo $_POST['value1'];
echo "<br>";
echo $_POST['value2'];
echo "<br>";
echo $_POST['value3'];
echo "<br>";
echo $_POST['value4'];
echo "<br>";
echo $_POST['value5'];
echo "<br>";
echo $_POST['value6'];
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
    {	$id         = $_POST['value1'];
	    $area_id    = $_POST['value2'];
	    $sensor_id  = $_POST['value3'];
	    $buzzer     = $_POST['value4'];
	    $sensor1     = $_POST['value5'];
	    $sensor2     = $_POST['value6'];

        // Update your tablename here 
	    $sql = "INSERT INTO iot (id, area_id, sensor_id, buzzer, sensor1, sensor2, date, time) VALUES ('".$id."','".$area_id."','".$sensor_id."','".$buzzer."','".$sensor1."','".$sensor2."', '".$d."', '".$t."')"; 
            
    
		if ($conn->query($sql) === TRUE) {
		    echo "Values inserted in MySQL database table.";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}


// Close MySQL connection
$conn->close();
?>