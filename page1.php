<!DOCTYPE html>
<html>
<head>
	<title> Purdue study spot tracker </title>

<meta http-equiv="refresh" content="1">

</head>




<style>
	 
body{  
background: url('WALCstudy.jpg') no-repeat; 
background-size: cover;
		}

h1{
        background-color: rgba(0,0,0,0.8); color: #fff; 
        padding:40px;  text-align: center; font-size:30pt;
}

table,tr,td{
border: 5px solid #bcbcbc;
width: 600px;
height: 200px;
    margin-left: auto;
    margin-right: auto;
}

tr{
text-align : center;
font-size:30pt;
color : white;

}

</style>
<body>

	<h1> Purdue study spot tracker </h1>

<?php
$conn = mysqli_connect("localhost","root","Rlawngud11@!","study");
$sql = "Select * from deskinfo where deskID between 1 and 6";
$result = mysqli_query($conn,$sql);



if($conn->connect_error) {


    die("Connection failed: " . $conn->connect_error);
}
else {

$sql = "Select * from deskinfo where deskID between 1 and 6";
$result = mysqli_query($conn,$sql);
//$row = mysqli_fetch_array($result);
//var_dump($row);
for($i = 1; $i <= 6; $i++){
$row = mysqli_fetch_array($result);
$deskIDlst[$i] = $row["deskID"];
$distancelst[$i] = $row["dis"];
$timelst[$i] = $row["TIME"];

}

echo '<table>';
echo '<tbody>';
echo '<tr >';

$crit = 1; //!!!!!10cm 이상 이면 empty!!!!

if(floatval($distancelst[1]) ==$crit){
echo '<td bgcolor= "#DC143C" >Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >Empty</td>';
}

if(floatval($distancelst[2])==$crit){
echo '<td bgcolor= "#DC143C" >Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >Empty</td>';
}

echo '</tr>';
echo '<tr>';

if(floatval($distancelst[3]) ==$crit){
echo '<td bgcolor= "#DC143C" >Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >Empty</td>';
}

if(floatval($distancelst[4]) ==$crit){
echo '<td bgcolor= "#DC143C" >Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >Empty</td>';
}

echo '</tr>';
echo '<tr>';

if(floatval($distancelst[5]) ==$crit){
echo '<td bgcolor= "#DC143C" >Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >Empty</td>';
}

if(floatval($distancelst[6])==$crit){
echo '<td bgcolor= "#DC143C" >Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >Empty</td>';
}

echo '</tr>';
echo '</tbody>';
echo '</table>';

}
?>





</body>
</html>