/* 
 * Alex Veney 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){

	if(argc != 3){
		printf("%s <ASCII_FILE> <BINARY_FILE>\n", argv[0]);
		exit(1);

	}

	// Open ascii for reading
	FILE *fp1;
	fp1 = fopen(argv[1], "r");

	if(fp1 == NULL){
		printf("Error opening %s\n", argv[1]);
		exit(1);
	}

	// Open binary for writing
	FILE *fp2;
	fp2 = fopen(argv[2], "wb");

	if(fp2 == NULL){
		printf("Error opening %s\n", argv[2]);
		exit(1);
	}

	// Read info from ASCII file and place into Binary file
	// Read 10 double values
	for(int i = 0; i < 10; i++){	
		double number;
		char buffer[40];

		fgets(buffer, 55, fp1);
		sscanf(buffer, "%lf", &number);
		fwrite(&number, sizeof(double), 1, fp2);
	}



	// Read 10 lines of characters 
	for(int i = 0; i < 10; i++){	
		char buffer[40];

		fgets(buffer,40, fp1);
		fwrite(buffer, sizeof(char), 40, fp2);

	}


	// Read 10 int values 
	for(int i = 0; i < 10; i++){	
		int number;
		char buffer[50];

		fgets(buffer, 51, fp1);
		sscanf(buffer, "%d", &number);
		fwrite(&number, sizeof(int), 1, fp2);
	}



	// Close both files
	fclose(fp1);
	fclose(fp2);

}










