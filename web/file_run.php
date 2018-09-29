<?php
// print_r($_POST['pinArray']) ;
// print_r($_POST['setArray']) ;
$myfile = fopen("config.txt", "w") or die("Unable to open file!");

$i = 0;
while ($_POST['pinArray'][$i] != null) {
    echo "<br>";
    
    echo $_POST['pinArray'][$i];
    echo "-";
    echo $_POST['setArray'][$i];
    
    $txt=$_POST['pinArray'][$i]." ".$_POST['setArray'][$i]."\n";
    fwrite($myfile, $txt);
    $i ++;
}
fclose($myfile);
system ("./clear");
system ("./porting");
system ("./chmod.sh");


?>
 
 