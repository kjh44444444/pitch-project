<?php header("Content-Type: text/html;charset=UTF-8");
header("Content-Type: text/html;charset=UTF-8");

$host = 'localhost';
$user = 'root';
$pw = 'Rlawngud11@!';
$dbName = 'study';
$mysqli = new mysqli($host,$user,$pw,$dbName);

if($mysqli)
{
echo "MySQL successfully connected!<br/>";

$deskID = $_GET['deskID'];
$dis =  $_GET['distance'];

echo "<br> deskID = $deskID";
echo " Distance = $dis<br/>";

$query = "update deskinfo set dis = $dis where deskID = $deskID";
mysqli_query($mysqli,$query);

echo "</br>success!!"; 
} else{ echo "MySQL could not be connected"; 
} 

mysqli_close($mysqli); 

?>