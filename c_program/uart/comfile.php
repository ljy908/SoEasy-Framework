<?php

function comfile()
{
    /**
     * **************������ �ϱ����� ������****************
     */
    
    // ������ ��ɾ�
    $fileLocation = "gcc -o add uart_test.c gpioCompare.c filepointer.c main.c init.c output_DB.c programExec. output_analog.c insert_DB.c wiringSerial.c";
    //$fileLocation = "make all";
    // ��ɾ �����ϱ� ���� �Լ�
    $t = exec($fileLocation, $output);
    
    //window . open('./console.html', 'popup', 'width=600,height=600,top=100,left=100');
    echo "<script>alert(\"Done\");</script>";
}

?>