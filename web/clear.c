#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>


int main (){

	FILE *fp;
	DIR *dir;
	struct dirent *ent;
	char buffer[BUFSIZ];

	int n;
	char s[10];
	int i = 0, j = 0;
	char *dir_buf = (char*)malloc(sizeof(char) * 100);
	char *gpio[] = {"/gpio", "/gpio_analog", "/gpio_compare", "/gpio_config_DB", "/gpio_pair",
		"/gpio_pwm", "/gpio_variable" };


	for (i = 0; i < sizeof(gpio) / sizeof(gpio[0]); i++) {
		strcpy(dir_buf, "../DB");
		strcat(dir_buf, gpio[i]);
		dir = opendir(dir_buf);

		memset(dir_buf, 0, sizeof(char) * 100);
		for (j = 0; j < 50; j++) {
			sprintf(s, "%d", j);
			if (dir != NULL) {
					strcpy(dir_buf, "../DB");
					strcat(dir_buf, gpio[i]);
					strcat(dir_buf, "/");
					strcat(dir_buf, s);
					printf("\n open file: %s\n", dir_buf);

					if ((fp = fopen(dir_buf, "w+t")) == NULL) {
						perror("fopen:read");
					}
					else {
						fputs("0", fp);
					}
					memset(dir_buf, 0, sizeof(char) * 100);
				
			}
			else 
			perror("DB error");
		}
	}
	closedir(dir);
	free(dir_buf);
	fclose(fp);
	return 0;
}




