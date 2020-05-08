#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define row 10
char line[10][256];
const char replacement[] = "^I";

void
expand(int fp)
{
	int lineNum = 0;
	int i=0;
	int j;
	int total=0;
	int index=0;

	// int row = sizeof(line) / sizeof(line[0]);
	while(fgets(line[lineNum], row, fp)) {
		line[lineNum][strlen(line[lineNum]) - 1] = '\0';
		lineNum++;
	}

	total = lineNum;
	char temp[512];

	for(i=0;i<=total;i++)
	{
		strcpy(temp,line[i]);
		int length = strlen(temp);
                char *new_string = (char *)malloc(sizeof(char) * (length + 2));
		for(j=0;j<=length;j++)
		{
			if(temp[j] == '\t')
			{
				new_string[index++] = replacement[0];
				new_string[index++] = replacement[1];
				j += 1;
				break;
			}
			else{
				new_string[index++] = temp[j];
			}
		}

		for(;j<length;j++)
		{
			new_string[index++] = temp[j];
		}
		printf(1, "%s\n", new_string);
	}
}

void
expand2(int fp) {
	int lineNum = 0;
	int i=0;
	int j;
	int total=0;

	while(fgets(line[lineNum], row, fp)) {
		line[lineNum][strlen(line[lineNum]) - 1] = '\0';
		lineNum++;
	}

	total = lineNum;
	char temp[512];

	for(i=0;i<=total;i++)
	{
		strcpy(temp,line[i]);
		int length = strlen(temp);
		for(j=0;j<=length;j++)
		{
			if((temp[j] == '^') && (temp[j+1] == 'I')
			{
			        char strr[] = "";
                                temp[j] = strr[0];
				temp[j+1] = '\t';
			}
		}
		
		for(j=0;j<=length;j++)
		{
			printf(1, "%s\n",temp[j]);
		}
	}
}

int main(int argc, char *argv[]) {
	int fp;

	if((argc == 3)&&(strcmp("-A",*(argv+1))==0)) {
		// read in file
		fp = open(argv[2], 0);
		if(fp < 0) {
			printf(1, "Error: Cannot open file %s\n", argv[2]);
			exit();
		}
		expand(fp);
	}
	else if ((argc == 4)&&(strcmp("-A",*(argv+1))==0)){
		fp = open(argv[2], 0);
		if(fp < 0) {
			printf(1, "Error: Cannot open file %s\n", argv[2]);
			exit();
		}
		expand2(fp);
	}
	else {
		printf(1, "Error: Bad command line parameters\n");
		exit();
	}
	close(fp);
	exit();
}
