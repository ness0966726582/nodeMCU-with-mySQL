<?php

$host = "localhost";		 // host = localhost because database hosted on the same server where PHP files are hosted
$dbname = "id20306897_demo";              // Database name
$username = "id20306897_ness";		// Database username
$password = "g6#KzFCo4=5mL2x1";	        // Database password

// 建立連線
$conn = mysqli_connect($host, $username, $password, $dbname);
// Check connection
if (!$conn) {
    die("連線失敗: " . mysqli_connect_error());
}
 
$sql = "SELECT id, name, val1, date, time FROM demo ";		//注意表選擇 "欄位" 與 "資料表" 的正確!
$result = mysqli_query($conn, $sql);
 
if (mysqli_num_rows($result) > 0) {
    // 輸出資料
    while($row = mysqli_fetch_assoc($result)) {
        echo "id: " . $row["id"]. " -name : " . $row["name"]. " - val1: " . $row["val1"]. " - date: " . $row["date"]. " - time: " . $row["time"]. "<br>";
    }
} else {
    echo "0 結果";
}
 
mysqli_close($conn);
?>