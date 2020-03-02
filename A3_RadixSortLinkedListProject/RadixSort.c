/* 
 * Alexandra Veney 
 * 
 * Project 
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define B 10


typedef struct Node{

	int num;
	struct Node* next;


}Node;


void insertNode(Node** head, Node* newNode);

Node* removeNode(Node** head);

int lengthList(Node* head);

void printList(Node* head);

void deleteList(Node* head);

void resetHTList(Node* array[]);

Node* createNode(int high, int low);


int main(int argc, char* argv[]){

	if(argc != 5){

		printf("%s <SEED> <N> <LOW> <HIGH> \n", argv[0]);
		exit(1);
	}



	// Initializing variables from CLI------------------------//
	int seed = atoi(argv[1]);
	int N = atoi(argv[2]);
	int low = atoi(argv[3]);
	int high = atoi(argv[4]);

	if(N < 0 || high < 0 || low < 0){
		printf("N, Low and High must be positive\n");
		exit(1);
	}

	if(high <= low){
		printf("High must be greater than Low\n");
		exit(1);
	}

	int M = floor(log10(high));	




	// Create original sequence-------------------------------//
	Node* sequence = NULL;
	srandom(seed);

	for(int i = 0; i < N; i++){
		//Create Node
		Node* newNode = createNode(high, low);

		// Insert Node into Initial list
		insertNode(&sequence, newNode);

	}

	// Print initial linked list
	printf("\nOriginal sequence: ");
	printf("\n---------------------------------------\n");
	printList(sequence);
	printf("\n---------------------------------------\n");



	
	// Initialize Array of bucket heads and tails-------------//
	Node* bucketHeads[B];
	resetHTList(bucketHeads);

	Node* bucketTails[B];
	resetHTList(bucketTails);
	


	// Radix Sort---------------------------------------------//
	for(int j = 0; j <= M; j++){

		Node* current;
		current = sequence;


		// Place node from sequence into corresponding bucket
		while(current != NULL){

			// Obtain proper bucket number
			int bucketNumber;
			bucketNumber = current->num % (int)(pow(10,j+1));
			bucketNumber /=  pow(10, j);

			Node* bucket;
			bucket = bucketTails[bucketNumber];	

			if(bucketHeads[bucketNumber] == NULL){
				bucketHeads[bucketNumber] = current;
				bucketTails[bucketNumber] = current;
			}else{
				bucketTails[bucketNumber] = current;
			}

			// Remove Node and shift current to next node
			Node* nodeToMove;
			nodeToMove = removeNode(&current);

			// Insert Node into proper bucket
			insertNode(&bucket, nodeToMove);


		}

		printf("BUCKETS\n");
		for(int i = 0; i < B; i++){
			printf("bucket %d: ", i);
			printList(bucketHeads[i]);
			printf("\n");
		}

		// Stitch together Buckets
		sequence = NULL;
		for(int i = 0; i < B; i++){

			while(bucketHeads[i] != NULL){

				Node* nodeToMove;
				nodeToMove = removeNode(&(bucketHeads[i]));
				insertNode(&sequence, nodeToMove);
			}

		}

		// Reset bucketHead and bucketTail array after stitching
		resetHTList(bucketHeads);
		resetHTList(bucketTails);
	
		printf("\nIntermediate sequence: ");
		printf("\n---------------------------------------\n");
		printList(sequence);
		printf("\n---------------------------------------\n");
	}



		printf("\nFinal sequence: ");
		printf("\n---------------------------------------\n");
		printList(sequence);
		printf("\n---------------------------------------\n");
	

	// Delete/Free list -----------------------------------------//
	deleteList(sequence);


}


// Links new node to end of list
//  Place Node at end of list 
void insertNode(Node** head, Node* newNode){

	Node* current = (*head);
	newNode->next = NULL;

	if(current == NULL){
		*head = newNode;

	}else{
		while(current->next != NULL){
			current =( current->next);
		}
		current->next = newNode;
	}
}

// Unlinks first node in list
Node* removeNode(Node** head){
	Node* nodeToRemove = *head;

	*head = (*head)->next;

	nodeToRemove->next = NULL;

	return nodeToRemove;	
}


// Frees the memory dynamically allocated for Linked List
void deleteList(Node* head){
	
	Node* temp;	
	while(head != NULL){
		temp = head;
		head = head->next;
		free(temp);
	}

}



// Determines length of list
int lengthList(Node* head){

	int length = 0;

	while(head != NULL){

		length++;

		head = head->next;

	}

	return length;
}

// Prints each node in list
void printList(Node* head){

	while(head != NULL){
		printf("%d ", head->num);
		head = head->next; 
	}


}

// Resets bucket head array for node distribution
void resetHTList(Node* array[]){

	for(int i = 0; i < B; i++){

		array[i] = NULL;

	}

}

// Creates new node within high-low range
Node* createNode(int high, int low){

	Node* newNode = (Node*)malloc(sizeof(Node));

	if(newNode == NULL){
		printf("Malloc failed\n");
		exit(1);
	}

	// Generates random #s [low, high] (incl) for newNode
	int randomNum; 
	randomNum = (random() % ((high - low) + 1)) + low;
	newNode->num = randomNum;
	newNode->next = NULL;

	return newNode;
}











