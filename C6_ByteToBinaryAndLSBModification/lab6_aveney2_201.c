/* 
 * Alexandra Veney 
 * 
 * 
*
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"

#define BYTETOBINARY(byte) \
	(byte & 0x80 ? 1 : 0), \
	(byte & 0x40 ? 1 : 0), \
	(byte & 0x20 ? 1 : 0), \
	(byte & 0x10 ? 1 : 0), \
	(byte & 0x08 ? 1 : 0), \
	(byte & 0x04 ? 1 : 0), \
        (byte & 0x02 ? 1 : 0), \
        (byte & 0x01 ? 1 : 0)

#define PRINTBIN(x) printf(BYTETOBINARYPATTERN, BYTETOBINARY(x));

#define SIZE 8

void setlsbs(unsigned char *p, unsigned char b0);

unsigned char getlsbs(unsigned char *p);

void displayarray(unsigned char *p);

void displaybyte(unsigned char byte0);

int main (int argc, char* argv[]){


	// Initialize byte0 with a random number seeded by 
	// command line input
	
	int seed = 0;
	
	seed = atoi(argv[1]);
	
	srandom(seed);
	
	unsigned char byte0 =  random() % 256;


	// Initialize p with random numbers
	
	unsigned char p[SIZE];

	for (int i = 0; i < SIZE ; i++){

		p[i] = random() % 256;
	}	



	// Display decimal and binary values
	printf("\n  	 ORIGINAL VALUES	  \n");
	printf("----------------------------------------\n");
	displayarray(p);
	printf("\n");
	printf("byte0: ");
	displaybyte(byte0);

	//Set lsbs of p to bits of byte0
	setlsbs(p, byte0);	
	
	// Display array after lsbs changes	
	printf("\n	ARRAY AFTER SETLSBS	\n");
	printf("----------------------------------------\n");
	displayarray(p);

	// Display byte after getting lsbs of p to create new byte
	printf("\n	BYTEO AFTER GETLSBS	\n");
	printf("----------------------------------------\n");
	printf("\n");

	// Display return value of getlsbs and original value
	printf("Original BYTE0 is: \n\n");
	displaybyte(byte0);
	printf("\nNew BYTE0 is: \n\n");
	displaybyte(getlsbs(p));
	printf("\n");

	return 0;

}


void setlsbs(unsigned char *p, unsigned char b0){

	int arrayBit = 0;
	int byteBit = 0;
	int position = 0;
	
	for(int i = 0; i < 8; i++){
		
		// Get lsb of value at index i
		arrayBit = (p[i] & 0x01)? 1 : 0;
	
		// Get desired bit of byte0
		position = pow(2,i);
		byteBit = (b0 & position)? 1 : 0;
	
		//only toggle bit if they arent the same
		if(arrayBit != byteBit){
		
			p[i] = (p[i] ^ 0x01);
		}

	}
	
}


unsigned char getlsbs(unsigned char *p){
	
	unsigned char newbyte0 = 0;
	int lsb = 0;
	int mask = 0;
	
	for(int i = 0; i < 8; i++){
		
		// Get lsb of value at index i
		lsb = (p[i] & 0x01)? 1 : 0;
			
		// Create mask to add one to newbyte0
		mask = (lsb << i);

		newbyte0 = (newbyte0 | mask);
	}

	return newbyte0;


}

void displayarray(unsigned char *p){
	// Print values of p in decimal and in binary 
	for(int j = 0; j < SIZE; j++){
		printf("p[%d]	Decimal: %3d	Binary: ",j , p[j]);
		PRINTBIN(p[j]);
		printf("\n");	
	}	


}

void displaybyte(unsigned char byte0){
	// Print values of byte0 in decimal and in binary
	printf("	Decimal: %3d	Binary: ", byte0);
	PRINTBIN(byte0);	
	printf("\n");

}

