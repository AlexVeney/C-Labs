// Alex Veney
// 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(FILE *plainText, FILE *cypherText);

void decrypt(FILE *cypherText, FILE *plainText);

void checkIfOpen(FILE *file);

int charToCode(char p);

char codeToChar(int c1);

int main (int argc, char* argv[]){

	// Get key int from command line arg
	int key = 0;	
	int *keyPtr = &key; 
	sscanf(argv[1], "%d", keyPtr);	
	
	// Get mode string from command line arg
	char mode[8];
	sscanf(argv[2], "%s", mode);
	
	// Seed random function with key
	srandom(key);

	// Open source file for reading
	FILE *firstFile = fopen(argv[3],"r");	

		// Check if file is opened properly
		checkIfOpen(firstFile);

	// Open/Create destination file for writing
	FILE *secondFile = fopen(argv[4],"w");
		
		// Check if file is opened properly
		checkIfOpen(secondFile);

	// Check mode and perform ENCRYPT or DECRYPT
	if(strcmp(mode, "ENCRYPT") == 0){
		
		// ENCRYPTs file
		encrypt(firstFile, secondFile);	
	
	}else if(strcmp(mode, "DECRYPT") == 0){	
		
		// DECRYPTs file
		decrypt(firstFile, secondFile);

	}else{
		printf("An invalid mode has been entered\n");
		exit(1);
	}
	
	// Close both files	
	fclose(firstFile);
	fclose(secondFile);	
	return 0;
}

void encrypt(FILE *plainText, FILE *cypherText){
	// Encrypts characters from plain text file and places characters
	// into cypher text file
	
	int randomNumber;
	char letter;
	int charCode;
	int newCode;
	char newLetter;

	while((letter = fgetc(plainText)) != EOF){
		randomNumber = random() % 97;	

		// Change all displayable characters to range [0,96]
		charCode = charToCode(letter);
		
		// Randomize character code
		newCode = (charCode + randomNumber) % 97; // modular addition
		
		// Turn all output values into displayable characters
		newLetter = codeToChar(newCode);
	
		fputc(newLetter, cypherText);
	}	
}

void decrypt(FILE *cypherText, FILE *plainText){
	// Decrypts characters from cypher text file and places characters
	// into plain text file
	
	int randomNumber;
	char letter;
	int charCode;
	int newCode;
	char newLetter;

	while((letter = fgetc(cypherText)) != EOF){	
		randomNumber = random() % 97;	
		
		// Change all displayable characters to range [0,96]
		charCode = charToCode(letter);
		
		// Randomize character code
		newCode = (charCode + 97 - randomNumber) % 97; // modular addition
			
		// Turn all output values into displayable characters
		newLetter = codeToChar(newCode);

		fputc(newLetter, plainText);

	}

}

void checkIfOpen(FILE *file){
	// Check if file was opened successfully
	 
	if(file == NULL){
		printf("Something went wrong with opening file\n");
		exit(1);
		}
	
}

int charToCode(char p){
	// Change character to the corresponding code in range [0,96] 
	// FROM: Displayable Character   TO:Coded Number
	
	int p1;
	
	if(p == '\t'){
		p1 = 0;
	}else if(p == '\n'){
		p1 = 1;
	}else{
		p1 = p - 30;
	}

	return p1;

}

char codeToChar(int c1){

	// Change code  from [0,96] to the corresponding character
	// FROM: Coded Number          TO:Displayable Character	
	
	char c;
	
	if(c1 == 0){
		c = '\t';
	}else if(c1 == 1){
		c = '\n';
	}else{
		c = c1 + 30;
	}

	return c;

}
