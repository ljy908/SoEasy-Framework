<?php
// Restore
// Setting
echo "<script>alert(\"START\");</script>";
$uploaddir = '/var/www/html/project_os/backup/';
$uploadfile = $uploaddir . basename($_FILES['importFile']['name']);

if (move_uploaded_file($_FILES['importFile']['tmp_name'], $uploadfile)) {
    exec("tar xvf ../backup/".basename($_FILES['importFile']['name']) , $output, $error); 
?>
<script>
var file = '<?php echo (basename($_FILES['importFile']['name']));?>';
window.open('file_port.php?file='+file, '_blank', 'toolbar=yes, scrollbars=yes, resizable=yes, top=500, left=500, width=1000, height=500');
</script>
<?php 
} else {
    echo "<script>alert(\"ERROR\");</script>";
}


echo "<meta http-equiv = 'Refresh' content='0; URL=setting.php'>";



/*$uploads_dir = '/var/www/html/project_os/backup/';

//$allowed_ext = array('gz');

echo "<script>alert(\"START\");</script>";

// Variable organization
$error = $_FILES['importFile']['error'];
$ext = array_pop(explode('.', $name));

$name = $_FILES['importFile']['name'];
$dest = $uploads_dir . basename($name);


// Check Error
if ($error != UPLOAD_ERR_OK) {
    switch ($error) {
        case UPLOAD_ERR_INI_SIZE:
        case UPLOAD_ERR_FORM_SIZE:
            echo "<script>alert(\"The file is too large.\");</script>";
            break;
        case UPLOAD_ERR_NO_FILE:
            echo "<script>alert(\"The file is not attached.\");</script>";
            break;
        default:
            echo "<script>alert(\"The file was not uploaded properly.\");</script>";
    }
    exit;
}

// Confirm extension
if (! in_array($ext, $allowed_ext)) {
    echo "<script>alert(\"This is an unacceptable extension.\");</script>";
    exit;
}

// Move files
if(move_uploaded_file($_FILES['importFile']['tmp_name'], "$dest")){
    echo "<script>alert(\"DONE\");</script>";
}esle{
    echo "<script>alert(\"ERROR\");</script>";
}

//exec("tar -xvzf " . $uploads_dir . $name . " -C ../DB");
*/

?>