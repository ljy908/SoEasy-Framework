<?php

function comfile()
{
    /**
     * **************컴파일 하기위한 페이지****************
     */
    
    // 컴파일 명령어
    $fileLocation = "gcc -o add uart_test.c gpioCompare.c filepointer.c main.c init.c output_DB.c programExec. output_analog.c insert_DB.c wiringSerial.c";
    //$fileLocation = "make all";
    // 명령어를 실행하기 위한 함수
    $t = exec($fileLocation, $output);
    
    //window . open('./console.html', 'popup', 'width=600,height=600,top=100,left=100');
    echo "<script>alert(\"Done\");</script>";
}

?>