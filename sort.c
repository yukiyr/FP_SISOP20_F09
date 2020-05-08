#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define MAX_LEN 	512
char line[200][200] = {0};
// global variable

void
sort(int fp)
{
	int lineNum = 0;
	int i=0;
	int j;
	int total=0;

	int row = sizeof(line) / sizeof(line[0]);
	while(fgets(line[lineNum], row, fp)) {
		line[lineNum][strlen(line[lineNum]) - 1] = '\0';
		lineNum++;
	}

	total = lineNum;
	char temp[512];

   	for (i = 1; i <= total; i++) {
      		for (j = i+1; j <= total; j++) {
         		if ((strcmp(line[i], line[j])) > 0) {
            			strcpy(temp,line[i]);
            			strcpy(line[i],line[j]);
            			strcpy(line[j],temp);
         		}
      		}
	}

	for(i = 1; i <= total; ++i) {
		printf(1," %s\n", line[i]);
	}
	printf(1,"\n");
}

int main(int argc, char *argv[]) {
	int fp;

	if(argc == 2) {
		// read in file
		fp = open(argv[1], 0);
		if(fp < 0) {
			printf(1, "Error: Cannot open file %s\n", argv[1]);
			exit();
		}
		sort(fp);
	}
	// get the number of words to be sorted by
	else if (argc == 3){
		fp = open(argv[2], 0);
		if(fp < 0) {
			printf(1, "Error: Cannot open file %s\n", argv[2]);
			exit();
		}
		sort(fp);
	}
	else {
		printf(1, "Error: Bad command line parameters\n");
		exit();
	}
	close(fp);
	exit();

}
