#include "index.h"
#include <unistd.h>
#include <fcntl.h>

#define DEBUG

void insertCompare(char *index, char *gpioNumber) {
	char result[5];

	strcpy(result, gpioNumber);
	result[strlen(gpioNumber) - 1] = '\0';

	DBWrite(result, index);
}

int gpioCompare(int fp, int gpio_number) {
	char compare[255];
	char compareIndex[255];
	char compareResult[255];
	char gpioData[255];
	char gpioLocation[100];
	char fpCompareLocation[255]; // compare DB address is stored.
	char fpResult[100];
	char compareNumber[255];

	int fpCompare, resultTotal, counter = 0, i = 0, j = 0;
	int fpResultSize;

	// Copy the current gpio_compare.
	strcpy(fpCompareLocation, "/var/www/project_os/DB/gpio_compare/");
	strcat(fpCompareLocation, data_sprintf(gpio_number));

	printf("\n***********gpioCompare**************\n");
	printf("fpCompareLocation : %s", fpCompareLocation);

	//exit(0);

	fpCompare = open(fpCompareLocation, O_RDONLY, S_IRUSR);

	// if there is an open error
	if (fpCompare == -1) {
		perror("open : fpCompare");
		close(fpCompare);

		return 0;
	}

	// Read 255 bytes from gpio_compare. (gpio compare number, condition, value)
	resultTotal = read(fpCompare, fpResult, 100);
	fpResult[resultTotal] = '\0';

#ifdef DEBUG
	printf("--------------------fpResult\n%s", fpResult);
#endif
	close(fpCompare);

	// If the length is less than 2, it is judged to be stored in DB
	if (strlen(fpResult) < 5) {
		printf("DB Compare Error\n");
		return 0;
	} else {

		// If there are multiple conditions, it will fetch the condition data repeatedly.
		while (1) {
			i = 0;

			// gpio number
			while (1) {
				compareNumber[i++] = fpResult[j];

				if (fpResult[j++] == ' ') {
					compareNumber[i] = '\0';
#ifdef DEBUG
					printf("\n1. compareNumber %s\n", compareNumber);
#endif
					break;
				}
			}
			// comparison condition (==: 0,>: 1,> =: 2, <: 3, <=: 4)
			i = 0;
			while (1) {
				compare[i++] = fpResult[j]; // The comparison condition value is input.

				if (fpResult[j++] == ' ') {
					compare[i] = '\0';
#ifdef DEBUG
					printf("3. compareNumber %s \t Memory : %u \n",
							compareNumber, compareNumber);
					printf("4. compareNumber %s \n", compareNumber);
#endif
					break;
				}
			}
			i = 0;
			while (1) {
				gpioData[i++] = fpResult[j]; // The comparison condition value is input.

				if (fpResult[j++] == ' ') {
					gpioData[i - 1] = '\0';
#ifdef DEBUG
					printf("3. compareNumber %s \t Memory : %u \n",
							compareNumber, compareNumber);
					printf("4. compareNumber %s \n", compareNumber);
#endif
					break;
				}
			}
			i = 0;
			// comparison value

			while (1) {

#ifdef DEBUG
				printf("6. compare %s \n", compare);
#endif

				compareIndex[i++] = fpResult[j++];

				if (fpResult[j] == '\n' | fpResult[j] == '\0') {
					printf("success\n");
					compareIndex[i] = '\0';

#ifdef DEBUG3
					printf("HI!!\n");
					printf("6. compareIndex %s\n", compareIndex);
#endif			

					// Copy the GPIO DB address. To compare GPIO and compareIndex values
					strcpy(gpioLocation, "/var/www/project_os/DB/gpio/");
					strcat(gpioLocation, data_sprintf(gpio_number));

					// Open the copied address.
					fpCompare = open(gpioLocation, O_RDONLY, S_IRUSR);

					if (fpCompare == -1) {
						perror("fpCompare : ");
						exit(0);
					}

					// Read 100 bytes from the copied address.
					if ((resultTotal = read(fpCompare, compareResult, 20))
							== -1) {
						perror("resultTotal : ");
					}
					compareResult[resultTotal] = '\0';

					printf("\n\n Current value : %s", compareResult);
					close(fpCompare);

					if (compare[0] == '0') {
						printf("\n equivalence \n");
						printf("compareResult = %s \t compareIndex = %s",
								compareResult, compareIndex);

						if (atoi(compareResult) == atoi(compareIndex)) {
							printf("\n gpioData : %c, compareNumber : %s\n",
									gpioData[0], compareNumber);
							insertCompare(gpioData, compareNumber);
							gpioVariable(gpio_number);
						}
					} else if (compare[0] == '1') {
						if (atoi(compareResult) > atoi(compareIndex)) {
							printf("\n Greater than");
							insertCompare(gpioData, compareNumber);
							gpioVariable(gpio_number);
						}
					} else if (compare[0] == '2') {
						if (atoi(compareResult) >= atoi(compareIndex)) {
							printf("\n Is greater than or equal to");
							insertCompare(gpioData, compareNumber);
							gpioVariable(gpio_number);
						}
					} else if (compare[0] == '3') {
						printf("\n Less than ");
						if (atoi(compareResult) < atoi(compareIndex)) {
							insertCompare(gpioData, compareNumber);
							gpioVariable(gpio_number);
						}
					} else if (compare[0] == '4') {

						printf("\n Less than or equal to ");
						if (atoi(compareResult) <= atoi(compareIndex)) {
							insertCompare(gpioData, compareNumber);
							gpioVariable(gpio_number);
						}
					} else {
						printf("\n Nothing ");
					}

					if (fpResult[j] == '\0') {
						close(fpCompare);
						return;
					}
					if (fpResult[j] == '\n') {
						j++;
					}
					close(fpCompare);
					break;
				}
			}
		}
	}

	if (gpio_number == 0) {
		exit(0);
	}

	return 1;
}
