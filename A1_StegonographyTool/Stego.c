// Alexandra Veney
// Project


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
 * Stego.c: A program for manipulating images                           *
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


#include <stdio.h>
#include <string.h>
#include "image.h"
#include <math.h>
#define  GNUMBER 677630 




// randperm function
void randperm(int a[], int n);

// scramble data function
void scrambledata(int a[], struct Buffer in, struct Buffer out);

// modify lsbs
byte setlsbs(void *other, int opt, byte cover, int pos);

// allocate memory and check success
void* allocate(int s, int opt);


int main(int argc, char *argv[]){

	int i, j, k, cover_bits, bits;
	struct Buffer b = {NULL, 0, 0}, sb = {NULL, 0, 0};
	struct Image img = {0, NULL, NULL, NULL, NULL, 0, 0};
	byte b0;

	if (argc != 5) 
	{
		printf("\n%s <key> <cover_file> <stego_file> <file_to_hide> \n", argv[0]);
		exit(1);
	}



	//READ FILES/SEED RNG-----------------------------------------------------//
	// Initialize RNG with command line seed 
	int  seed = atoi(argv[1]);	
	srandom(seed);

	// Read image file(cover) into the image buffer img
	ReadImage(argv[2],&img);     

	// Read binary data(payload)
	ReadBinaryFile(argv[4],&b);   


	// Hidden information 
	if (!GetColor)
		cover_bits = img.NofC*img.NofR;
	else 
		cover_bits = 3*img.NofC*img.NofR;    
	bits = (8 + b.size)*8;

	if (bits > cover_bits)
	{
		printf("Cover file is not large enough %d (bits) > %d (cover_bits)\n",bits,cover_bits);
		exit(1);
	}


	//EMBED SIZE----------------------------------------------------------------//
	// Embed size of payload into cover
	// Size bits from R to L are embedded into bytes [0,31] of cover
	for(int i = 0; i < 32; i++){

		int *size;
		size = &b.size;

		byte newByte;

		newByte = setlsbs(size, 1, GetGray(i), i);
		SetGray(i, newByte);
	}


	//EMBED G#------------------------------------------------------------------//
	// Embed G# into cover
	// Eight digit G# embedded (4 bits per digit) from L to R 
	for(int c = 7 ; c >= 0 ; c--){

		static int index = 32;  // counter for coverbyte index [32,63]
		int gDigit;		// gnumber digit being embedded 
		int decPlace;		// *used to help select whole numbers from gnumber
		byte newByte;

		// Get digit of gnumber
		decPlace = pow(10, c);
		gDigit =(GNUMBER / decPlace) % 10;

		// Get bits from digit 
		for(int d = 3; d >= 0 ; d--){

			int *digit;
			digit = &gDigit;

			byte newByte;	
			newByte = setlsbs(digit, 1, GetGray(index), d);

			SetGray(index, newByte);

			index++;

		}
	}



	//PERM---------------------------------------------------------------------//
	// Create permutation of array of indexs [0,(b.size-1)]
	int n = b.size;

	int *a = NULL;
	a = allocate(n, 1);

	for(int i = 0; i < n; i++){

		a[i] = i;
	}


	// Rand perm of a[]
	randperm(a, n);	


	//SCRAMBLE----------------------------------------------------------------//
	// Allocate space and initialize sizefor scramble buffer (sb)
	sb.data = allocate(b.size, 2);

	sb.size = b.size;



	// Scrambled payload bytes
	scrambledata(a, b, sb);


	//EMBED REMAINING BYTES-----------------------------------------------------//
	// Embed information into the image one byte at the time
	for (int i = 0; i<sb.size; i++){		

		static int index = 64; 	// counter for coverbyte index [64,last byte needed]

		byte payloadByte;
		payloadByte = sb.data[i];

		// Embed bit of payload into lsb of each coverbyte	
		for (int j = 7; j >= 0; j--){

			byte *plb;
			plb = &payloadByte;

			byte newByte;	
			// Modified byte to be embeded
			newByte = setlsbs(plb, 2, GetGray(index), j);

			// Set newByte at current index
			SetGray(index, newByte);

			// Increment counter to move to next cover byte
			index++;
		}	

	}

	WriteImage(argv[3],img);  // output stego file (cover_file + file_to_hide)

	// Free all dynamically allocated memory
	free(b.data);
	free(sb.data);
	free(img.gray);
	free(a);

}


// Creates permutation of array of ints
void randperm(int a[], int n){

	for(int y = n-1; y >= 0; y--){

		int temp;
		int randomIndex;

		temp = a[y];
		randomIndex= random() % (y + 1);
		a[y] = a[randomIndex];
		a[randomIndex] = temp; 
	}

}

// Scrambles data according to random permutation
void scrambledata(int a[], struct Buffer in, struct Buffer out){

	for(int i = 0; i < in.size; i++){
		out.data[i] = in.data[a[i]];
	}

}

// Sets the LSB of cover byte 
//other: info to be embedded
//opt  : cast options for comparison  int* or byte* 
//cover: orig. coverbyte 
//pos  : index of bit to be embedded
byte setlsbs(void *other, int opt, byte cover, int pos){

	int bit;	 // bit to embed
	int lsb;	 // lsb of cover byte
	long  position;
	byte newByte;		

	// Get specific bit at position
	position = pow(2,pos); // 1, 2, 4, 8, 16 ....

	// Cast void* based on opt
	// opt 1: int   opt 2:byte	
	if(opt == 1){
		bit = (*((int*)other) & position)? 1 : 0;
	}
	else if(opt == 2){
		bit = (*((byte*)other) & position)? 1 : 0;
	}

	// Get lsb of cover byte
	lsb = (cover & 0x01)? 1 : 0;

	//Set newByte for cover
	newByte  = (bit != lsb)? (cover ^ 0x01): cover;		

	return newByte;	


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

