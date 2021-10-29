<?php
#Blake Lufkin
#Php database json encoding code
#Last Updated: 4/28/2020
header('context-type: text/json');

#acquire data from database
$db= new SQLite3('data.db');
$statement=$db->prepare("select * from hatdata");
$result=$statement->execute();

#fetch the data from the database with same date/time info but seperate values
while($row = $result->fetchArray()) {
    $data['hat1'][]=['t' => $row[0] . " " . $row[1],'y' => $row[2]];
	$data['hat2'][]=['t' => $row[0] . " " . $row[1],'y' => $row[3]];
	$data['hat3'][]=['t' => $row[0] . " " . $row[1],'y' => $row[4]];
	$data['hat4'][]=['t' => $row[0] . " " . $row[1],'y' => $row[5]];
	$data['hat5'][]=['t' => $row[0] . " " . $row[1],'y' => $row[6]];
	$data['hat6'][]=['t' => $row[0] . " " . $row[1],'y' => $row[7]];
	$data['hat7'][]=['t' => $row[0] . " " . $row[1],'y' => $row[8]];
	$data['hat8'][]=['t' => $row[0] . " " . $row[1],'y' => $row[9]];
}

#encode data in json format
echo json_encode($data);

$db->close();
?>   
