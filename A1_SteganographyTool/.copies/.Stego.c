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


byte modifylsbs(int other , int pos, byte cover);

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



//READ FILES/SEED RNG----------------------------------------------------------------------------------GOOD//


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


//EMBED SIZE----------------------------------------------------------------------------------------GOOD-//


	// Embed size of payload into bytes [0,31] of cover
	// Implementation: lsb of payload size embded cb[0] 2nd lsb cb[1] ...	
	for(int i = 0; i < 32; i++){
/*		int sizeBit;	 // bit from b.size to embed
		int lsb;	 // lsb of cover byte
		long  position;
		byte coverByte;	
		byte newByte;		

		// Get sizebit from b.size
		position = pow(2,i); // 1, 2, 4, 8, 16 ....
		sizeBit = (b.size & position)? 1 : 0;


		// Get lsb of cover byte
		coverByte = GetGray(i);
		lsb = (coverByte & 0x01) ? 1 : 0;


		//Set newByte for cover
		newByte  = (sizeBit != lsb)? (coverByte ^ 0x01): coverByte;		
*/
//               printf("LSB of coverbyte[%d]: %d \n",i,(GetGray(i) & 0x01)? 1 : 0);
                                              //DEBUGGIN

       		byte newByte;
		newByte = modifylsbs( b.size, i, GetGray(i));		
 

 //             printf("        Newbyte lsb: %d \n\n",(newByte & 0x01)? 1: 0);


		// Embed byte into cover
		SetGray(i, newByte);
	


	}


//EMBED G#----------------------------------------------------------------------------------------GOOD//

	// Embed the eight digits of your G# using 4 bits per digit
	// From position [7,0]
	for(int c = 7 ; c >= 0 ; c--){

		static int index = 32;  // index/counter for coverbyte [32,63]
		int gDigit;		// gnumber digit being embedded 
		int gBit;		// bit of gnumber digit
		int lsb;		// lsb of cover byte
		int decPlace;		// *used to help select whole numbers from gnumber)
		int binPlace;  		// *used to help select bits from gnumber ditits
		byte coverByte;
		byte newByte;


		// Get digit of gnumber
		decPlace = pow(10, c);
		gDigit =(GNUMBER / decPlace) % 10;

		// Get bits from digit 
		for(int d = 3; d >= 0 ; d--){
			binPlace = pow(2, d);
			gBit = (gDigit & binPlace)? 1 : 0;

			// Set newByte for stego image
			// Get Coverbyte [32,63]
			coverByte = GetGray(index);

			// Get lsb of Coverbyte
			lsb = (coverByte & 0x01)? 1 : 0;

			newByte = (gBit != lsb)? (coverByte ^ 0x01) : coverByte;
		
			// Set newbyte
			SetGray(index, newByte);

			index++;
		}
	}


//PERM----------------------------------------------------------------------------------------GOOD//


	// Create permutation of array of indexs [0,(b.size-1)]
	int n = b.size;
	int *a = (int*)malloc(sizeof(int)*n);

	if(a == NULL){
		printf("Not enough memory, malloc failed\n");
		exit(1);
	}

	for(int i = 0; i < n; i++){
		a[i] = i;
	}



	// Rand perm of a[]
	randperm(a, n);	



//SCRAMBLE----------------------------------------------------------------------------------------GOOD//


	// Allocate space and initialize sizefor scramble buffer (sb)
	sb.data = (byte*)malloc(sizeof(byte)*b.size);
	
	if(sb.data == NULL){
		printf("Not enough memory, malloc failed\n");
		exit(1);
	}

	sb.size = b.size;

	
	// Scrambled payload bytes
	
	scrambledata(a, b, sb);


//EMBED REMAINING BYTES----------------------------------------------------------------------------GOOD//


	// Embed information into the image one byte at the time
	for (int i = 0; i<sb.size; i++)
	{		
		static int index = 64; 	// index/counter for coverbyte [64,last byte needed]
		byte payloadByte;
		
		payloadByte = sb.data[i];
		
		// Embed bit of payload into lsb of each coverbyte	
		for (int j = 7; j >= 0; j--){

			byte coverByte;  // Byte from cover image (img)
			byte newByte;	 // Modified byte to be embeded
			int coverlsb;	 // LSB of coverbyte
			int payloadBit;	 // Bit from payload byte
			int position;	 // *used to select bit from payload byte

			// Get coverbyte
			coverByte = GetGray(index);

			// Get lsb of coverbyte
			coverlsb =  (coverByte & 0x01)? 1 : 0;

			// Get desired bit from payload byte
			position = pow (2, j);	
			payloadBit = (payloadByte & position)? 1 : 0;


			// Create newByte to replace current coverByte
			newByte = (coverlsb != payloadBit)? (coverByte ^ 0x01): coverByte;
			
			// Set newByte as coverByte at current
			SetGray(index,newByte);
			
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





byte modifylsbs(int other , int pos, byte cover){

		int bit;	 // bit from other to embed
		int lsb;	 // lsb of cover byte
		long  position;
		byte newByte;		

		// Get sizebit from b.size
		position = pow(2,pos); // 1, 2, 4, 8, 16 ....
		bit = (other & position)? 1 : 0;
		printf("sizebit %d\n", bit);

		// Get lsb of cover byte
		lsb = (cover & 0x01) ? 1 : 0;


		//Set newByte for cover
		newByte  = (bit != lsb)? (cover ^ 0x01): cover;		

		return newByte;	


}
