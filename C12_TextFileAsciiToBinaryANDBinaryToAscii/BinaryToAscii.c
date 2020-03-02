/* 
 * Alexandra Veney G0677630
 * CS 262, Lab Section 201
 * Lab 12
 *
 */


#include <stdio.h>
#include <stdlib.h>

struct doubleBuffer{

	double num;

};

struct intBuffer{

	int num;

};


int main(int argc, char *argv[]){

	if(argc != 3){
		printf("%s <BINARY_FILE> <ASCII_FILE>\n", argv[0]);
		exit(1);

	}

	// Open binary file for reading
	FILE *fp1;
	fp1 = fopen(argv[1], "rb");

	if(fp1 == NULL){
		printf("Error opening %s\n", argv[1]);
		exit(1);
	}

	// Open ascii file for writing
	FILE *fp2;
	fp2 = fopen(argv[2], "w");

	if(fp2 == NULL){
		printf("Error opening %s\n", argv[2]);
		exit(1);
	}

	// Read info from binary file and place into ascii file	
/*	for(int i = 0; i < 10; i++){  
		struct doubleBuffer DB;
		fread(&DB, sizeof(struct doubleBuffer), 1, fp1);
		fprintf(fp2, "%.4lf\n", DB.num);
	}*/

	for(int i = 0; i < 10; i++){  
		double number;
		fread(&number, sizeof(double), 1, fp1);
		fprintf(fp2, "%.4lf\n", number);
	}


	// Read strings from file and write 
	for(int i = 0; i < 10; i++){
		char buffer[40];
		fread(buffer,sizeof(buffer), 1, fp1);
		fprintf(fp2, "%s", buffer);
	}

	for(int i = 0; i < 10; i++){  
		struct intBuffer IB;
		fread(&IB, sizeof(struct intBuffer), 1, fp1);
		fprintf(fp2, "%d\n", IB.num);
	}

	// Close both files
	fclose(fp1);
	fclose(fp2);

}
