/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
 * StegoExtract.c: A program for manipulating images                    *
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <string.h>
#include "image.h"
#include <math.h>
// randperm function
void randomperm(int *array, int size);


// unscramble function
void unscramble(int a[], struct Buffer in, struct Buffer out);



int main(int argc, char *argv[])
{  
	int i, j, k, cover_bits, bits;
	struct Buffer b = {NULL, 0, 0}, ub = {NULL, 0, 0};   // need to buffers
	struct Image img = {0, NULL, NULL, NULL, NULL, 0, 0};
	byte b0;

	if (argc != 4) 
	{
		printf("\n%s <key> <stego_file> <file_to_extract> \n", argv[0]);
		exit(1);
	}

	// convert key from string to integer
	int seed = atoi(argv[1]);

	// use key to initialize random number generator
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

	// extract four size bytes for the Buffer's size field
	for(int i = 31; i >= 0; i--){

		int lsb = 0;
		// Get LSB of cover byte
		lsb  = (GetGray(i) & 0x01)? 1 : 0;

		// Add lsb to size 
		b.size = ((b.size << 1) |lsb);


	}

	printf("\n");
	printf("BSIZE is %d \n", b.size);



	// Set this to b.size
	b.data = malloc(sizeof(byte) *b.size); // Allocates room for the output data file

	if(b.data == NULL){
		printf("Not enough memory, malloc failed\n");
		exit(1);
	}	




	int gnumber =0;

	// extract the eight digits of your G# using 4 bits per digit
	for(int c = 7; c >= 0; c--){

		static int index = 32;	 //  index/counter of cover byte [32,63]
		long decPlace;
		int digit = 0;
		int lsb;

		for(int d = 0; d <= 3; d++){

			// Get lsb of cover byte
			lsb = (GetGray(index)& 0x01)? 1:0;

			// Combine add lsb to end of digit
			digit = ((digit << 1) | lsb);

			// Move to next cover byte 
			index++;
		}

		decPlace = pow(10, c);
		digit *=  decPlace;
		gnumber +=  digit;	
	}

	printf("GNUMBER: %d \n", gnumber);

	for (i=0; i<b.size; i++)
	{
		static int index = 64;
		// here you extract information from the image one byte at the time

		for(int j = 0; j <=7; j++){

			int lsb = 0;
			static byte payloadByte; 

			if( j == 0){

				payloadByte = 0;
			}
			// Get lsb of stego image byte
			lsb = (GetGray(index++) & 0x01)? 1 : 0;



			//printf("LSB of byte %d\n", lsb);
			payloadByte <<= 1;

			if(0 != lsb){

				payloadByte ^= 0x01;
			}
			/*		
					printf("running payload byte  \n");
					printf("%d ", (payloadByte & 128)? 1: 0);
					printf("%d ", (payloadByte & 64)? 1: 0);
					printf("%d ", (payloadByte & 32)? 1: 0);
					printf("%d ", (payloadByte & 16)? 1: 0);
					printf("%d ", (payloadByte & 8)? 1: 0);
					printf("%d ", (payloadByte & 4)? 1: 0);
					printf("%d ", (payloadByte & 2)? 1: 0);
					printf("%d \n\n\n ", (payloadByte & 1)? 1: 0);
					*/
		}

	}

	
	// move image data to buffer data
	
	for(int i = 0; i< b.size; i++){

	
		b.data[i]=GetGray(i);
	

	}



	// Array of index
	int *a = (int*)malloc(sizeof(int)*b.size);
	if (a == NULL){
		printf("Not enough memory, malloc failed\n");
		exit(1);	
	}

	for(int c = 0; c < b.size; c++){
		a[c] = c;
	}	

	randomperm(a, b.size);


	// Unscramble the data:   b to ub
	ub.size = b.size;

	ub.data = (byte*)malloc(sizeof(byte)*ub.size);
	if(ub.data == NULL){
		printf("Not enough memory, malloc failed\n");
		exit(1);	

	}

	unscramble(a, b, ub);

	WriteBinaryFile(argv[3],ub);  // output payload file
}



void randomperm(int *array, int size){


	for (int e = (size-1); e >= 0 ; e--){

		int k;
		int temp;
		k = random() % (e + 1);

		temp = array[e];
		array[e] = array[k];
		array[k] = temp;



	} 


	printf(" 0 = %d\n", array[0]);

	printf(" 1 = %d\n", array[1]);

}


void unscramble(int a[], struct Buffer in, struct Buffer out){


	for(int i = 0; i < in.size; i++){

		out.data[a[i]] = in.data[i];

	} 


}













