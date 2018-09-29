#include "index.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

/********************************************************************
  The GPIO configuration file is read into the main part of the control program,
  Call the function to run. The called function is divided into each C code file.
  At the top of each code, I added comments as comments.

  The main part of the main part is the while statement, through the loop, the numbers 1 to 14, or 1 to 20
  It works as a loop statement.
 ********************************************************************/

//#define DEBUG1
char* data_sprintf(int number) {
	static char data[100];
	sprintf(data, "%d", number);
	return data;
}

void functionApacheLog() {
	//apache2 Variable to delete the log
	struct stat accessBuf, errorBuf;
	int fpAccess;
	int accessVolume, errorVolume;

	// apache2 LOG path
	char *accessLocation = "/var/log/apache2/access.log";
	char *errorLocation = "/var/log/apache2/error.log";

	stat(accessLocation, &accessBuf);
	stat(errorLocation, &errorBuf);

	if ((int) accessBuf.st_size > 500000000) {
		fpAccess = open(accessLocation, O_WRONLY | O_TRUNC);
		close(fpAccess);
	}
	if ((int) errorBuf.st_size > 500000000) {
		fpAccess = open(accessLocation, O_WRONLY | O_TRUNC);
		close(fpAccess);
	}

}

int main(void) {
	int status = 0;
	// File descriptor
	int gpio_file, gpio_config_file, gpio_unexport, gpio_pair;

	// child process
	int pid, childPid, childPidTemp;

	// Temporary variable for reading GPIO
	int i = 0;
	int temp = 0;

	// GPIO number
	int gpio_number = -1, gpio_config_number = -1;

	// Save the value read from DB
	char gpio_config_str[255] = { 0 };
	char gpio_result_str[2]; // Store the value read from DB.
	char gpio_value_str[40];

	// DB path
	char *pwd_temp = "/var/www/project_os/DB/gpio";
	char *pwd_config_temp = "/var/www/project_os/DB/gpio_config_DB/";
	char *pwd_value_temp = "/sys/class/gpio/gpio";

	char* test[3] = { "nohup", "/var/www/project_os/c_program/uart/uart", "&" };

	char pwd[50] = { 0 };

	/*
	 Implement low-level file I / O
	 If you set GPIO first on the web

	 **************************************************
	 1. gpio_DB.txt: Store the value read from the GPIO in the database.
	 2. gpio_config_DB.txt: Determine whether GPIO is input or output. (Set it on the web and read it from a C program.)
	 **************************************************

	 */
	pid = fork(); // Initialize Galileo Level Shifter
	while (gpio_config_number++ < 40) {
		functionApacheLog();
		// Create a child UART process
		strcpy(gpio_config_str, pwd_config_temp);
		strcat(gpio_config_str, data_sprintf(gpio_config_number));

		gpio_config_file = open(gpio_config_str, O_RDONLY, S_IRUSR); // O_RDONLY, S_IRUSR

		if (gpio_config_file == -1) // Go back to the beginning of the program if there is an error opening the DB
				{
			perror("config_file error");
			close(gpio_config_file);

			continue; // For the first time
		}

		read(gpio_config_file, gpio_result_str, 2); // Read GPIO setting value.

		close(gpio_config_file);

		gpio_number++; // Numeric position of GPIO

		/*
		 ***************************
		 1. HTML input (button in HTML) - value must be read and sent to GPIO
		 2. Digital Input - External Button Input: Saved in DB
		 3. Digital output - Read out the DB value. (HIGH / LOW)
		 4. Analog input - Read analog value and save it to DB
		 5. Analog output - Read out DB value
		 ***************************
		 */

		// Part for storing or reading GPIO data
		strcpy(pwd, pwd_temp); // Copy the path (/project_os/DB/gpio/)
		strcat(pwd, "/");
		strcat(pwd, data_sprintf(gpio_config_number)); // Add the GPIO number.

		if ((gpio_file = open(pwd, O_RDWR, S_IRUSR)) == -1) // Open the GPIO DB file.
				{
			perror("open_gpio_file");
			continue;
		}

		/*
		 output_DB (int data): Read the value stored in DB.
		 insert_DB (int data): Inserts a value into the DB.
		 */

		switch (gpio_result_str[0]) {
		case '0': // not used
			printf("not used\n");
			break;
		case '1': // Digital output
			output_DB(gpio_file, gpio_config_number);
			break;
		case '2': // Digital input
			insert_DB(gpio_file, gpio_config_number); // 10000 ���떊�뿉 GPIO�뿉�꽌 �씫�뼱�삤�뒗 媛믪쑝濡� 蹂�寃쏀븯湲�
			break;
		case '3': // Rx_insert.
			if (pid == -1) {
				perror("fork error");
			} else if (pid == 0) {

				//Rx_rasb(gpio_file, gpio_config_number);
				childPid = getpid();
				status = 1;

				//insertUart();
				if (execlp(test[1], test[1], (char *) NULL) == 0) {
					perror("execlp");
					exit(0);
				}
			} else {
				printf("pid = %d, %d", childPid, pid);
			}

			break;
		case '4': //Tx_outed
			if (pid == -1) {
				perror("fork error");
			} else if (pid == 0) {
				//Rx_rasb(gpio_file, gpio_config_number);
				//printf("pid = %d", pid);
				status = 1;
				//insertUart();
				if (execlp(test[1], test[1], (char *) NULL) == 0) {
					perror("execlp");
					exit(0);
				}

			} else {
				printf("pid = %d", pid);
				//break;
			}
			break;
		default: // exception handling
			break;
		}
		close(gpio_file);

		close(gpio_config_file);

		i = 0; // reset
		gpio_number = -1;
		printf("AAA");

		if (gpio_config_number == 40) {
			gpio_config_number = -1;
		}
		sleep(0.5);
	}
}
