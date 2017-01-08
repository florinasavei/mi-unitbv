#include <stdio.h>
void main(){
	FILE *fl;
	char filename[100];
	char answer;
	puts("Creating new file");
	puts("File name:");
	gets(filename);
	fl = fopen(filename, "r");
	if (fl){
		printf("The file allready exists! Do you want to delete it? (y/n)");
		answer = getchar();
		if (answer == 'n' || answer == 'N'){
			printf("\nterminating program\n");
			return; //this terminates the program
			}
			else 
			if (answer == 'y' || answer == 'Y'){
				fl = fopen(filename, "w");
				fputs(filename, fl); //writes the name of the file in the file itself
				fclose(fl);
			}
			else
				printf("\ninvalid input\n");
	}
	else {
		fl = fopen(filename, "w");
		fputs(filename, fl); //writes the name of the file in the file itself
		fclose(fl);
	}
}