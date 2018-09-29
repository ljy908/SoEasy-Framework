<?php

exec("tar -zcvf Rasp_Pi_" . $_GET['backup'] . ".tar.gz ../DB", $output, $error);
if ($error == "0") {
    echo "Rasp_Pi_" . $_GET['backup'] . ".tar.gz";
} else {
    echo "$error";
}

?>