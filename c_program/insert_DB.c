#include "index.h"
#include <fcntl.h>

extern int RB_pinMap[27][27];

void insert_DB(int fp, int gpio_number) {
	int fp2;
	char data[2]; // read DB Data (ON / OFF)
	char fpData[100];
	char temp[100];
	char gpioChar[10];
	char test[10] = "1";
	char result[3], gpio_pair[3];
	int i = 0, readResult;

	// I will use GPIO.

	while (i < 27) {
		if (gpio_number == RB_pinMap[i][0]) {
			break;
		} else {
			i++;
		}
	}

	sprintf(gpioChar, "%d", RB_pinMap[i][1]);
	printf("\n\n %s \n", gpioChar);

	gpioExport(gpioChar);
	// Copy the path to fpData.
	gpioDirection(gpioChar, "in");

	// Set the GPIO type
	// gpioDrive (gpioChar, "strong");

	// Check GPIO values

	// When i is 0, set Level Shifter GPIO to 0.

	// First we read the value of gpio_pair. If it is 0, it is not used. If it is different value, it is used (it must be corrected)

	readResult = gpioPair(data_sprintf(gpio_number), gpio_pair);

	if (readResult != 3) {
		gpio_pair[readResult] = '\0';
	}
	close(fp2);

	printf("GPIO_PAIR ::::::::::: %s", gpio_pair);

	if (gpio_pair[0] == '0') {
		printf("**************************NOPAIR\n");
	} else if (gpio_pair[0] > 0) {
		printf("**************************SUCCESS\n");
	}

	// Load the GPIO value. (Whether or not the button is pressed)

	printf("\n\nHello : %s %s \n\n", gpioValueRead(gpioChar), gpioChar);
	strcpy(result, gpioValueRead(gpioChar));

	DBWrite(data_sprintf(gpio_number), result);
	printf("result : %s", result);

	// Send to GPIO PAIR (pair) value. (Currently fixed at 13): Testing

	// DBWrite (gpio_pair, result);

	if (result[0] == '0') // when the button is not pressed
			{
		printf("----------------------------------------off \n\n");

		DBWrite(gpio_pair, "0");
	} else // when pressed
	{
		printf("----------------------------------------on \n\n");
		printf("%s\n", result);

		DBWrite(gpio_pair, "1");
	}

}
