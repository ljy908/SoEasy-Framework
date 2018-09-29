<?php

/*
 * ************** Page for compilation ****************
 */

// Initialize the compilation
system("make clean");
echo "<br><br>";

// $fileLocation = "gcc -o add uart_test.c gpioCompare.c filepointer.c main.c init.c output_DB.c programExec. output_analog.c insert_DB.c wiringSerial.c";
// $fileLocation = "make all";

// $t = shell_exec($fileLocation, $output);

// function to execute the command
system("make all");

// window.open('./console.html', 'popup', 'width=600,height=600,top=100,left=100');
echo "<script>alert(\"Compiled successfully.\");</script>";

echo "<meta http-equiv = 'Refresh' content='0; URL=console.php'>";
?>