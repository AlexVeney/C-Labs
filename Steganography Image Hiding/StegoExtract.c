// Alex Veney 
// 
// Project 2

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
 * StegoExtract.c: A program for manipulating images                    *
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <string.h>
#include "image.h"
#include <math.h>



// Creates permutation of array of ints
void randperm(int *a, int n);

// Unscrambles data according to random permutation
void unscramble(int a[], struct Buffer in, struct Buffer out);

// Allocates memory and checks success
void* allocate(int s, int opt);

// Gets LSBs of stego file 
int getlsbs(byte cover);


int main(int argc, char *argv[]){ 
	int i, j, k, cover_bits, bits;
	struct Buffer b = {NULL, 0, 0}, ub = {NULL, 0, 0};   // need to buffers
	struct Image img = {0, NULL, NULL, NULL, NULL, 0, 0};
	byte b0;

	if (argc != 4) 
	{
		printf("\n%s <key> <stego_file> <file_to_extract> \n", argv[0]);
		exit(1);
	}


	//READ FILES/SEED RNG----------------------------------------------------//
	// Initialize random number generator
	int seed = atoi(argv[1]);
	srandom(seed);


	ReadImage(argv[2],&img);       // read image file into the image buffer img
	// the image is an array of unsigned chars (bytes) of NofR rows
	// NofC columns, it should be accessed using provided macros

	// hidden information 
	// first four bytes is the size of the hidden file
	// next 4 bytes is the G number (4 bits per digit)
	if (!GetColor)
		cover_bits = img.NofC*img.NofR;
	else 
		cover_bits = 3*img.NofC*img.NofR;    

	b.size = 0;

	//EXTRACT SIZE----------------------------------------------------------//
	// Extract four size bytes for the Buffer's size field
	for(int i = 31; i >= 0; i--){

		// Get LSB of cover byte
		// Add lsb to size 
		b.size = ((b.size << 1) | getlsbs(GetGray(i)));

	}

	printf("Size of %s: %d \n", argv[2], b.size);

	// Allocates memory and checks success
	b.data = allocate(b.size, 2);



	//EXTRACT GNUMBER------------------------------------------------------//
	int gnumber =0;

	// Extract the eight digits of your G# using 4 bits per digit
	for(int c = 7; c >= 0; c--){

		static int index = 32;	 // index/counter of cover byte [32,63]
		long decPlace;		 // *used to place gnumber digit in correct position
		int digit = 0;		 // the digit extracted from bytes
		int lsb;

		for(int d = 0; d <= 3; d++){

			// Get lsb of cover byte
			// Add lsb to end of digit
			digit = ((digit << 1) | getlsbs(GetGray(index)));

			// Move to next cover byte 
			index++;
		}

		decPlace = pow(10, c);
		digit *=  decPlace;
		gnumber +=  digit;	
	}

	printf("GNUMBER: %d \n", gnumber);

	//EXTRACT PAYLOAD  BYTES------------------------------------------------------//
	for (i=0; i<b.size; i++)
	{
		static int index = 64;
		// here you extract information from the image one byte at the time
		static byte payloadByte;

		payloadByte = 0;
		for(int j = 0; j <=7; j++){

			// Get lsb of stego image byte
			//printf("LSB of byte %d\n", lsb);
			payloadByte <<= 1;

			if(getlsbs(GetGray(index)) != 0){

				payloadByte ^= 0x01;
			}

			index++;

		}

		b.data[i] = payloadByte;


	}

	//PERM------------------------------------------------------------------------------//
	// Array of index (0 to size)
	int *a = NULL;
	a = allocate(b.size, 1);


	for(int c = 0; c < b.size; c++){
		a[c] = c;
	}	

	randperm(a, b.size);

	//UNSCRAMBLE------------------------------------------------------------------------//
	// Unscramble the data:   b to ub
	ub.size = b.size;
	ub.data = allocate(b.size, 1);


	unscramble(a, b, ub);

	WriteBinaryFile(argv[3],ub);  // output payload file




}


// Creates permutation of array of ints
void randperm(int *a, int n){

	for (int y = (n-1); y >= 0 ; y--){

		int temp;
		int randomIndex;

		temp = a[y];;
		randomIndex = random() % (y + 1);
		a[y] = a[randomIndex];
		a[randomIndex] = temp;
	} 


}

// Unscrambles data according to random permutation
void unscramble(int a[], struct Buffer in, struct Buffer out){

	for(int i = 0; i < in.size; i++){

		out.data[a[i]] = in.data[i];
	} 
}


// Allocates memory and checks success
void* allocate(int s, int opt){

	void* location = NULL;

	// Cast void* based on opt
	// opt 1: int   opt 2:byte	
	if(opt == 1){
		location = (int*)malloc(sizeof(int)*s);
	}else if(opt == 2){
		location = (byte*)malloc(sizeof(byte)*s);
	}

	if(location == NULL){
		printf("Not enough memory, malloc failed\n");
		exit(1);
	}
	return location;
}


// Get  LSBs of stego file 
int  getlsbs(byte cover){

	int lsb;         // lsb of cover byte

	// Get lsb byte
	lsb = (cover & 0x01)? 1 : 0;

	return lsb;


}








