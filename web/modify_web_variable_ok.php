<?php

/* ***************** Page for modifying the GroupControl. The pinData that is actually used is stored. ******************* */

	$name			= $_POST['name'];
	$gpioNumber		= $_POST['gpioNumber'];
	$gpioValue		= $_POST['gpioValue'];
	$name			= $_POST['name'];
	$variableName	= $_POST['variableName'];
	$variableIndex	= $_POST['variableIndex'];

	$size			= sizeof($variableIndex);

	$fpGpio			= "/var/www/project_os/DB/gpio/";

	// In the GroupControl field, it is stored as a floating unit so that it can be stored including flooding.
	for($i = 0 ; $i < $size ; $i++)
	{
		$list .= $variableName[$i];
		$list .= " ";
		$list .= $variableIndex[$i];
		$list .= "\n";
		$fpGpio .= $variableName[$i];
	}

	$fp				= "/var/www/project_os/DB/web_variable/";
	$fp			   .= $name;
	$fp				= fopen($fp, "w+");

	$test			= fwrite($fp , $list);

	fclose($fp);

	echo "<meta http-equiv = 'Refresh' content='0; URL=test.php'>";

?>
