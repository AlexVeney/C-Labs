/* 
 * Alexandra Veney
 * 
 * Lab 7
 *
 */

#include <stdio.h>
#include <stdlib.h>


#define MAX_NUM_LOOPS 10
#define END (arrayLength-1)
#define BEGINNING 1

void InitializeArray (int *numArray, const int arrayLength);
	
void ShuffleArray(int *numArray, const int arrayLength);

void PrintArray(int *numArray, const int arrayLength);

int compare(const void *a, const void*b);

int main(int argc, char *argv[]){
	
	printf("\nName: Alexandra Veney Lab Section: 201");
	printf("\nThis program will shuffle and sort a random integer array\n\n");

	// Declare integer array of size N	
	int N = atoi(argv[2]);
	
	int *numArray = NULL;
	
	numArray = (int*)malloc(sizeof(int) * N);
	
	// Verify proper memory allocation for array
	if(numArray == NULL){
		printf("Error allocating memory!\n");
		exit(1);
	}	

	// Initialize seed(S) from command line arg 	
	int S = atoi(argv[1]);
	srandom(S);


	for(int i = 1; i <= MAX_NUM_LOOPS; i++){

		printf("---------ITERATION  # %d---------------\n\n", i);

		// Initialize array from 1 to N
		InitializeArray(numArray, N);

		// Print original array values
		printf("Original Array:\n");
		PrintArray(numArray, N);	


		

		// Shuffle array
		ShuffleArray(numArray, N);

		// Print shuffled array values
		printf("Shuffled Array:\n");
		PrintArray(numArray, N);




		// Sort array (descending)
		qsort(numArray, N, sizeof(int), compare);
				
		// Print sorted numArray values
		printf("Sorted Array:\n");
		PrintArray(numArray, N);
		
	}


	
	// Free array memory space 
	free(numArray);
	numArray = NULL;	
	
	return 0;	

}	


void InitializeArray (int *numArray, const int arrayLength){
	// Initializes array from 1 to N
	
	for(int j = 0; j < arrayLength; j++){
		numArray[j] = j + 1;
	}
	
	
}
	
void ShuffleArray(int *numArray, const int arrayLength){
	// Shuffles array using Fisher-Yates / Perfect Sort alg.	
	
	int randomIndex = 0;
	int temp = 0;
	for(int currPosition = END; currPosition >= BEGINNING; currPosition--){
		
		// Represents random location in array
		// from index 0 to current position	
		randomIndex = random() % currPosition;
	
		// Holds value at current position
		temp = numArray[currPosition];
		
		// Swap values at current positon and random position
		numArray[currPosition] = numArray[randomIndex];
		numArray[randomIndex] = temp;

	}
	
}

void PrintArray(int *numArray, const int arrayLength){
	// Prints each element of the array to stdout
	
	for(int k = 0; k < arrayLength; k++){
	
		printf("%d ", numArray[k]);
	}
	
	printf("\n\n");
}

int compare(const void *a, const void *b){
	/*
	* Compares the elements and returns value to qsort
	* 1. If the first element is less than the second
	* 	it will be moved to a higher position
	* 2. If the first element is greater than the second
	* 	it will be moved to a lower position
	* 3. If the elements are equal it will not be moved
	*/
	int *aptr = (int *) a;
	int *bptr = (int *) b;
	
	int value = 0;
	
	if(*aptr < *bptr){
		value = 1;
	}else if(*aptr > *bptr){
		value = -1;
	}else{
		value = 0;
	}

	return value;

}


















