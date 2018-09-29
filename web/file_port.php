<html>
<head>
<title>so</title>
</head>
<body>

<table width = 800  border = 1 cellpadding='3' cellspacing='1' frame = 'void' align = center><tr bgcolor=000000 >
<td align = center>	<font color = white size = 2><b>Pin Number</b></font></td>
<td align = center>	<font color = white size = 2><b>Pin Configue</b></font></td>
<td align = center>	<font color = white size = 2><b>Set Port</b></font></td></tr><tr>
<br>

<form action='file_run.php' method='post'>

<?php
$array;
$i=0;

while ($i <= 40) {
    
    $analogLocation = "./DB/gpio_analog/";
    $fp_config = "./DB/gpio_config_DB/";
    $fp_config .= $i;
    
    $config_open = fopen($fp_config, "r+");
    $config_index = fread($config_open, 1);
    
    // Setting value is 0: Disabled :: No output
    if ($config_index == 0) {
        $i ++;
        continue;
    }
    
    // Read GPIO data value.
    $fp_gpio = "./DB/gpio/";
    $fp_gpio .= $i;
    
    $gpio_open = fopen($fp_gpio, "r+");
    $gpio_index = fread($gpio_open, 255);
    
    // Edit link
    echo "<td bgcolor=white><p align = center>$i</a></p></td>";
    echo "<td bgcolor=white><p align = center>";
    
    

    if ($i <= 40) {
        if ($config_index == 1) {
            echo "Digital Output (1)</p></td>";
        }else if ($config_index == 2){
            echo "Digital Input (2)</p></td>";
        }else if ($config_index == 3){
            echo "Analog Input (3)</p></td>";
        }else if ($config_index == 4){
            echo "PWM Output (4)</p></td>";
        }else if ($config_index == 5){
            echo "UART RX (5)</p></td>";
        }else if ($config_index == 6){
            echo "UART TX (6)</p></td>"; }                       
    }
    
    echo "<td bgcolor=white>";
    
    echo "<label>". substr($_GET['file'] ,0 ,7) ." [".$i."] ==> Rasp_Pi </label>";
   
?>

<input type='hidden' name='pinArray[]' value='<?php echo $i;?>'/>
<input type='text' name='setArray[]' value='<?php echo $i;?>'/>
</td></tr>

<?php 
    $i ++;
}
?>

</table>
<center><input type='submit' value='Submit'/></center>
</form>


</body>

</html>
