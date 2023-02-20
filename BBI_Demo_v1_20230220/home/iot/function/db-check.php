<body>
<a href="https://10.231.220.20/home/iot/index.php">首頁<br></a>

</body>

<?php

$host = "localhost";		 // host = localhost because database hosted on the same server where PHP files are hosted
$dbname = "iot";              // Database name
$username = "ness";		// Database username
$password = "itd123";	        // Database password

// 建立連線
$conn = mysqli_connect($host, $username, $password, $dbname);
// Check connection
if (!$conn) {
    die("連線失敗: " . mysqli_connect_error());
}
 
$sql = "SELECT id, area_id, sensor_id,buzzer,sensor1,sensor2, date, time FROM demo ";		//注意表選擇 "欄位" 與 "資料表" 的正確!
$result = mysqli_query($conn, $sql);
 
if (mysqli_num_rows($result) > 0) {
    // 輸出資料
    while($row = mysqli_fetch_assoc($result)) {
        echo "id: " . $row["id"]. " -area_id : " . $row["area_id"]. " - sensor_id: " . $row["sensor_id"]. " - buzzer: " . $row["buzzer"]." - sensor1: " . $row["sensor1"]." - sensor2: " . $row["sensor2"]." - date: " . $row["date"]. " - time: " . $row["time"]. "<br>";
    }
} else {
    echo "0 結果";
}
 
mysqli_close($conn);
?>