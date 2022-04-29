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

table,tr,td,tx{
border: 5px solid #bcbcbc;
width: 450px;
height: 150px;

    margin-left: auto;
    margin-right: auto;
margin-bottom: 30pt;	
text-align : center;

font-size:30pt;
color : white;

}

th{
text-align : auto;
font-size:30pt;
color : white;

}


</style>

<body>

	<h1> Purdue study spot tracker </h1>

<?php
$conn = mysqli_connect("localhost","root","Rlawngud11@!","study");
$sql = "Select * from deskinfo where deskID between 1 and 12";
$result = mysqli_query($conn,$sql);



if($conn->connect_error) {


    die("Connection failed: " . $conn->connect_error);
}
else {

$sql = "Select * from deskinfo where deskID between 1 and 12";
$result = mysqli_query($conn,$sql);
//$row = mysqli_fetch_array($result);
//var_dump($row);
for($i = 1; $i <= 12; $i++){
$row = mysqli_fetch_array($result);
$deskIDlst[$i] = $row["deskID"];
$distancelst[$i] = $row["dis"];
$timelst[$i] = $row["TIME"];

}

echo '<div style="width:50%;float:left;">';
echo '<table>';
echo '<tr>';
echo '<td bgcolor= "#000" colspan = "3">Thermal Sensor</td>';
echo '</tr >';
echo '<tbody>';
echo '<tr >';



echo '</div>';


$crit = 1; //!!!!!10cm 이상 이면 empty!!!!

if(floatval($distancelst[12]) ==$crit){

echo '<td bgcolor= "#808080" >N/A</td>';
}else{
echo '<td bgcolor= "#808080" >N/A</td>';
}

if(floatval($distancelst[7])==$crit){
echo '<td bgcolor= "#DC143C" >1<br>Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >1<br>Empty</td>';
}

echo '</tr>';
echo '<tr>';

if(floatval($distancelst[11]) ==$crit){
echo '<td bgcolor= "#DC143C" >5<br>Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >5<br>Empty</td>';
}

if(floatval($distancelst[8]) ==$crit){
echo '<td bgcolor= "#DC143C" >2<br>Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >2<br>Empty</td>';
}

echo '</tr>';
echo '<tr>';

if(floatval($distancelst[10]) ==$crit){
echo '<td bgcolor= "#DC143C" >4<br>Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >4<br>Empty</td>';
}

if(floatval($distancelst[9])==$crit){
echo '<td bgcolor= "#DC143C" >3<br>Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >3<br>Empty</td>';
}

//echo '</tr>';
echo '</tbody>';
echo '</table>';
echo '</div>';

echo '<div width:50%;float:right;">';
echo '<table>';
echo '<tr align ="center">';
echo '<p><td bgcolor= "#000" colspan = "3">PIR+USS</td></p>';
echo '</tr >';
echo '<tbody>';
echo '<tr >';

$crit = 1; //!!!!!10cm 이상 이면 empty!!!!

if(floatval($distancelst[3]) ==$crit){
echo '<td bgcolor= "#DC143C" >3<br>Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >3<br>Empty</td>';
}

if(floatval($distancelst[4])==$crit){
echo '<td bgcolor= "#DC143C" >4<br>Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >4<br>Empty</td>';
}

echo '</tr>';
echo '<tr>';

if(floatval($distancelst[2]) ==$crit){
echo '<td bgcolor= "#DC143C" >2<br>Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >2<br>Empty</td>';
}

if(floatval($distancelst[5]) ==$crit){
echo '<td bgcolor= "#DC143C" >5<br>Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >5<br>Empty</td>';
}

echo '</tr>';
echo '<tr>';

if(floatval($distancelst[1]) ==$crit){
echo '<td bgcolor= "#DC143C" >1<br>Occupied</td>';
}else{
echo '<td bgcolor= "##bee9b4" >1<br>Empty</td>';
}

if(floatval($distancelst[6])==$crit){
echo '<td bgcolor= "#808080" >N/A</td>';
}else{
echo '<td bgcolor= "##808080" >N/A</td>';
}

}
?>



</body>
</html>