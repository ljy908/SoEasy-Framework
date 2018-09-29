<?php
/* ****************** Page for receiving Timer values and saving them to the database ***************** */

// Receive data value via POST method.
$timerList = $_POST['timerList'];
// timer 데이터베이스 경로
$fp = "/var/www/project_os/DB/Time_DB/timer";

// timer database path
$fp = fopen($fp, "r+");
fputs($fp, $timerList);
fclose($fp);

echo "<meta http-equiv = 'Refresh' content='0; URL=test.php'>";
?>
