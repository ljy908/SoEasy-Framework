<meta http-equiv="content-type" content="text/html; charset=UTF-8">

<!-- 占쏙옙占쏙옙占� 占쏙옙占쏙옙占쏙옙 -->
<head>

<meta name = "viewport" content = "width=device-width, initial-scale=1"/>
<style>
	A:link 
	{
		COLOR: black; TEXT-DECORATION: none
	}
	A:visited 
	{
		COLOR: blue; TEXT-DECORATION: none
	}
	A:hover
	{	
		COLOR: orange; TEXT-DECORATION: underline 
	}
</style>
</head>


<?php

	$j = 0;
	$i = 0;
	
	$gpioFileList		=		array();
	$fileFp				=		dir("/var/www/project_os/DB/gpio_config_DB");

// 占쏙옙占썰리占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙트占쏙옙 처占쏙옙占쏙옙占쏙옙 占싻억옙쨈占�.
	while(($fileResult = $fileFp -> read()) == true)
	{
		if($fileResult == "." || $fileResult == "..")
		{
			continue;
		}
		$gpioFileList[$j++] = $fileResult;
	}

	for($k = 0 ; $k < sizeof($gpioFileList) - 1; $k++)
	{
		$least = $k;

		for($m = $k + 1 ; $m < sizeof($gpioFileList) ; $m++)
		{
			if($gpioFileList[$m] < $gpioFileList[$least])
			{
				$least = $m;
			}
		}
		$temp = $gpioFileList[$k];
		$gpioFileList[$k] = $gpioFileList[$least];
		$gpioFileList[$least] = $temp;
	}

	$i = 0;
	$imageLocation		=	"/var/www/project_os/DB/homepage/image";

// DB占쏙옙 占쏙옙占쏙옙퓸占� 占쌍댐옙 占쏙옙占쏙옙화占쏙옙 占쌓몌옙占쏙옙 占쌀뤄옙占승댐옙.
	$fpImageDown		=	fopen("/var/www/project_os/DB/homepage/image/imageWhere/down", "r");
	$fpImageResult		=	fread($fpImageDown, 255);
	$imageResult		=	$imageLocation . "/" . $fpImageResult;

	$imageSearch		=	strpos($imageResult, ".jpg");
	$imageResult		=	substr($imageResult, 0, $imageSearch + 4);

	echo "<body background	=	'$imageResult'>";

// DB占쏙옙 占쏙옙占쏙옙퓸占쏙옙獵占� 占쏙옙占싸곤옙침 占쏙옙占쏙옙 占시곤옙占쏙옙 占싻억옙쨈占�.
	$fpRefreshTime		=	fopen("/var/www/project_os/DB/homepage/refreshTime", "r");
	$refreshTimeResult	=	fread($fpRefreshTime, 255);

// DB占쏙옙 占쏙옙占쏙옙퓸占쏙옙獵占� 표 占쏙옙占쏙옙占쏙옙 占싻억옙쨈占�.
	$fpTableColor		=	fopen("/var/www/project_os/DB/homepage/tableColor", "r");
	$TableColorResult	=	fread($fpTableColor, 255);

// 占싣놂옙占싸깍옙 占쏙옙占쏙옙
	$analogLocation		=	"/var/www/project_os/DB/gpio_analog/";

// 占쏙옙占쏙옙(표)占쏙옙 占쏙옙쨉풔占� php占쏙옙 占쏙옙占쏙옙占승댐옙.
	require('./functionList.php');

	echo "<p align = center>";
	echo "<form action=modify_ok.php?no=$no method=post> "; 

// 占쌨댐옙 표 占쏙옙占쏙옙
	echo "<table width = 330 height = 40 align = center><tr bgcolor= $TableColorResult>";
	echo "<td><p align = center><a href = 'setting.php'  width = 10>	<font color = white size = 2>Setting<br></a></font></p></td>";
	echo "<td><p align = center><a href = 'new.php'  width = 10>		<font color = white size = 2>New<br></a></font></p></td></tr><tr  bgcolor= $TableColorResult>";
	echo "<td><p align = center><a href = 'new_numorus.php'>			<font color = white size = 2>GroupControl<br></a></p></font></td>";
	echo "<td><p align = center><a href = 'sourceSelect.html'><font color = white size = 2>Code Editing<br></a></p></font></td></tr></table>";

	tableList(330);
// GPIO 표 占쏙옙占쏙옙
	echo "<table width = 330  border = 1 cellpadding='3' cellspacing='1' frame = 'void' align = center><tr bgcolor=$TableColorResult >";
	echo "<td align = center >	<font color = white size = 2><b>#</b></font></td>";
	echo "<td align = center>	<font color = white size = 2><b>PinData</b></font></td>";
	echo "<td align = center>	<font color = white size = 2><b>Control</b></font></td></tr><tr>";		
	echo "<br>";

// while占쏙옙 0占쏙옙 占쏙옙占쏙옙 13占쏙옙 占쏙옙占쏙옙 占쏙옙占쏙옙 (占쌩곤옙占쌔야듸옙 : 占싣놂옙占싸깍옙)
	while($i < sizeof($gpioFileList))
	{

// GPIO 占쏙옙占쏙옙 占쏙옙占쏙옙 占싻억옙쨈占�.
		$fp_config		= "/var/www/project_os/DB/gpio_config_DB/";
		$fp_config	   .= $gpioFileList[$i];

// GPIO 占쏙옙占쏙옙 占쌔쏙옙트 占쏙옙占쏙옙 fopen
		$config_open	= fopen($fp_config, "r+");
		$config_index	= fread($config_open , 1);

// 占쏙옙占쏙옙 占쏙옙占쏙옙 0占싱몌옙 占쏙옙占쏙옙占쏙옙占� 占십댐옙 占쏙옙占쏙옙 : 占쏙옙쨉占쏙옙占� 占쏙옙占쏙옙
		if($config_index == 0)
		{
			$i++;
			continue;
		}

// GPIO 占쏙옙占쏙옙占쏙옙 占쏙옙占쏙옙 占싻억옙쨈占�.
		$fp_gpio		= "/var/www/project_os/DB/gpio/";
		$fp_gpio	   .= $gpioFileList[$i];

		$gpio_open		= fopen($fp_gpio, "r+");
		$gpio_index		= fread($gpio_open, 255);

// 占쏙옙占쏙옙 占쏙옙크
		echo "<td bgcolor=white><p align = center><a href = 'modify.php?number=$gpioFileList[$i]'><font size = 2>$gpioFileList[$i]</a></font></p></td>";
		echo "<td bgcolor=white><p align = center>$gpio_index</p></td><td>";
		
// 占쏙옙占쏙옙占� 占쏙옙占�
		if($config_index == 1)
		{

// GPIO 占쏙옙占승곤옙 HIGH 占쏙옙 占쏙옙占�
			if($gpio_index == 1)
			{
				echo "<p align = center><a href = 'control.php?power=off&number=$i'>OFF</a></p>";
			}
// GPIO 占쏙옙占승곤옙 LOW 占쏙옙 占쏙옙占�
			else
			{
				echo "<p align = center><a href = 'control.php?power=on&number=$i'>ON</a></p>";
			}
		}
		echo "</td></tr>";
		$i++;
	}
	echo "</table>";
	echo "<p align = center>";

	fileList("/var/www/project_os/DB/web_variable", 330);

	echo "</body>";
	echo "<meta http-equiv = 'Refresh' content=5; URL=test.php'>";
?>
