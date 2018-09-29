<?php

/* ***************** Delete GroupControl ******************* */

// Get the name of the GroupControl.
$name = $_GET['name'];

// Add the GroupControl path
$web_variable_location = "/var/www/project_os/DB/web_variable/";
$web_variable_location .= $name;

// Delete GroupControl
unlink($web_variable_location);

echo "<meta http-equiv = 'Refresh' content='1; URL=test.php'>";
?>
