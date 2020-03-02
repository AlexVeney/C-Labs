/* 
 * Alexandra Veney G0677630
 * CS 262, Lab Section 201
 * Lab 10
 *
 */


#include <stdio.h>
#include <stdlib.h>

typedef struct Node{

	int number;
	struct Node* next;

}Node;

// Insert a node into list sorted by number
void insertNodeSorted(Node** head, Node* new);

// Print node values of list
void printList(Node* head);

// Delete each node of list
void deleteList(Node* head);

int main(int argc, char* argv[]){


	if(argc !=4){

		printf("%s <key> <N> <MAX_VALUE>\n",argv[0]);
		exit(1);
	}


	int S = atoi(argv[1]);
	srandom(S);

	int N = atoi(argv[2]);

	int V =  atoi(argv[3]);

	Node* head;
	head = NULL;

	for(int i = 0; i < N; i++){

		int randNum;
		randNum = random() % (V + 1);

		if(i == 0){
			printf("Random Number : \n");
		}

		printf("%3d ", randNum);		

		Node* new;
		new = (Node*)malloc(sizeof(Node));

		if(new == NULL){
			printf("Malloc failed\n");
			exit(1);
		}

		new->number = randNum;
		new->next = NULL;

		//insert node sorted
		insertNodeSorted(&head, new);	

	}

	//print nodes
	printList(head);


	//delete nodes
	deleteList(head);
}

// Insert a node into list sorted by number
void insertNodeSorted(Node** head, Node* new){

	Node* current;
	Node* previous;
	current = *head;

	if(current == NULL){	

		// Set NEW as first node if list is empty
		*head = new;

	}else if(new->number < current->number){

		// Insert NEW at front of list
		new->next = current;
		*head = new;
	}else{	
		// Insert NEW in sorted order
		while(new->number >= current->number){

			if(current->next == NULL){
				current->next = new;
				new->next = NULL;	
				break;

			}else{	
				previous = current;
				current = current->next;
			}	

			if(new->number < current->number){
				previous->next = new;
				new->next = current;
				break;
			}
		}
	}
}

// Print node values of list
void printList(Node* head){

	printf("\n");

	printf("Linked List   : \n");

	while(head != NULL){
		printf("%3d ", head->number);
		head = head->next;
	}

	printf("\n");

}

// Delete each node of list
void deleteList(Node* head){

	while(head != NULL){
		Node* temp = head;
		head = head->next;
		free(temp);
	}




}


