#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>


void main(int argc, char *argv[]) {

	FILE *cfp, *rfp, *wfp;
	DIR *dir1, *dir2;
	struct dirent *ent;
	char buffer[BUFSIZ];

	int n;
	int i = 0, j = 0;
	int tmp_org, tmp_set;
	char s1[10], s2[10];

	char *org_dir = (char*)malloc(sizeof(char) * 100);
	char *tmp_dir = (char*)malloc(sizeof(char) * 100);

	char *gpio[] = { "", "/gpio", "/gpio_analog", "/gpio_compare", "/gpio_config_DB", "/gpio_pair",
		"/gpio_pwm", "/gpio_variable" };

	char *web[] = {"/homepage", "/web_variable"};
	if ((cfp = fopen("./config.txt", "rt")) == NULL) {
		perror("fopen:config.txt");
		exit(1);
	}

	mkdir("../DB", 0777);

	while ((n = fscanf(cfp, "%d %d", &tmp_org, &tmp_set)) != EOF)
	{

		printf("%d : %d , %d\n", j, tmp_org, tmp_set);
		sprintf(s1, "%d", tmp_org);
		sprintf(s2, "%d", tmp_set);
		printf("\n------%d-----%d-------- \n", s1, s2);

		for (i = 0; i < sizeof(gpio) / sizeof(gpio[0]); i++) {
			strcpy(org_dir, "./DB");
			strcat(org_dir, gpio[i]);
			printf("\n-------------%s------------ \n", org_dir);
			dir1 = opendir(org_dir);

			if (dir1 != NULL) {
				while ((ent = readdir(dir1)) != NULL) {
					printf("%s\n", ent->d_name);

					if (!strcmp(s1, ent->d_name)) {
						strcat(org_dir, "/");
						strcat(org_dir, s1);
						printf("\nopen file: %s\n", org_dir);

						if ((rfp = fopen(org_dir, "rt")) == NULL) {
							perror("fopen:read");
						}

						else {
							fgets(buffer, sizeof(buffer), rfp);
							printf("%s\n", buffer);

							strcpy(tmp_dir, "../DB");
							strcat(tmp_dir, gpio[i]);
							printf("\nopen dir: %s \n", tmp_dir);
							dir2 = opendir(tmp_dir);
							mkdir(tmp_dir, 0777);

							if (dir1 != NULL) {
								strcat(tmp_dir, "/");
								strcat(tmp_dir, s2);
								printf("\nsave file: %s\n", tmp_dir);

								if ((wfp = fopen(tmp_dir, "wt")) == NULL) {
									perror("fopen:write");
								}

								else {
									fputs(buffer, wfp);
									printf("-- %s -- \n", buffer);


									printf("\n --Change Value-- \n");
								}
							}

							else {
								perror("TMP error");

							}

							dir2 = NULL;
							memset(tmp_dir, 0, sizeof(char) * 100);

						}
					}
				}

			}
			else {
				perror("DB error");

			}
			memset(org_dir, 0, sizeof(char) * 100);
			dir1 = NULL;
		}
		j++;
	}












	printf(" --------- close dir --------- \n");

	closedir(dir1);
	closedir(dir2);

	printf(" --------- free memory --------- \n");
	free(org_dir);
	free(tmp_dir);

	printf(" --------- close file --------- \n");
	fclose(cfp);
	fclose(wfp);
	fclose(rfp);
}





























/*
while ((n = fscanf(cfp, "%d %d", &tmp_org, &tmp_set)) != EOF)
{
printf("%d : %d , %d\n", i, tmp_org, tmp_set);
//sprintf(org[i], "%d", tmp_org);
//sprintf(set[i], "%d", tmp_set);
//printf("%d : %s , %s\n", i, org[i], set[i]);
i++;
}


for (i = 0; i < sizeof(gpio) / sizeof(gpio[0]); i++) {
strcpy(org_dir, "./DB");
strcat(org_dir, gpio[i]);
printf("%s \n", org_dir);
dir = opendir(org_dir);

if (dir != NULL) {
while ((ent = readdir(dir)) != NULL) {
printf("%s\n", ent->d_name);

}
closedir(dir);
}
else {
perror("error");
}
memset(org_dir, 0, sizeof(char) * 100);
dir = NULL;
}

*/
/*
for (i = 0; i < sizeof(gpio) / sizeof(gpio[0]); i++) {

strcpy(org_dir, "./DB");

char *path = strcat(org_dir, gpio[i]);
printf("%s \n", path));
if ((count = scandir(path, &namelist, NULL, alphasort)) == -1) {
fprintf(stderr, "%s Directory Scan Error: %s\n", path, strerror(errno));
exit(0);
}

for (idx = 0; idx < count; idx++) { printf("%s\n", namelist[idx]->d_name); }
for (idx = 0; idx < count; idx++) { free(namelist[idx]); }

free(namelist);
memset(org_dir, 0, sizeof(char) * 100);
dir = NULL;

}
*/