/* 
 * Alex Veney 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Item structure
typedef struct{

	char name[25];
	size_t quantity;
	double price;
}Item;


char menuOptions();

void addItem(Item Cart[], int index);

void printCart(Item Cart[], int numOfItems);

void ResizeArray(Item **Cart, int size);



int main(int argc, char *argv[]){

	// Get size from user and allocate initial cart size 
	printf("Please input the number of items-> ");
	char Buffer[25];
	fgets(Buffer,24 , stdin);
	int number;
	sscanf(Buffer, "%d", &number);

	printf("\nThe number of items you input is %d\n\n", number);

	Item *ShoppingCart;
	ShoppingCart = (Item*)malloc(sizeof(Item)*number);

	if(ShoppingCart == NULL){

		printf("Malloc failed\n");
		exit(1);
	}


	char selection;
	static int counter = 0;

	do{	

		// Prompt user for menu option selection
		selection = menuOptions();

		// Based on menu option selected perform operations
		switch(selection){
			case 'a':
				// Resize Shopping Cart if full
				if(counter >= number){
					ResizeArray(&ShoppingCart, number);
					number *= 2;
				}

				// Get Item information from user
				addItem(ShoppingCart, counter);
				counter++;
				break;
			case 'p':
				// Print information for cart items
				printCart(ShoppingCart, counter);
				break;

			case 'q':
				printf("Exiting program\n");
				break;
			default: 
				printf("Invalid option\n");
				break;
		}
	}while(selection != 'q');


	// Release cart memory
	free(ShoppingCart);

}



// Display menu option and get desired selection from user
char menuOptions(){

	printf("---------------------------------------------------\n");
	printf("Select option below:\n");
	printf("a - Add an item to Shopping Cart\n");
	printf("p - Print items in Shopping Cart\n");
	printf("q - Quit \n\n");
	printf("->");
	char option;
	char Buffer[20];

	fgets(Buffer, 4, stdin);
	sscanf(Buffer, "%c", &option);

	printf("\n");
	return option;

}

// Add item to cart
void addItem(Item Cart[], int index){

	Item new;

	char Buffer[100];

	printf("Input item  details below\n");
	printf("Name:");
	fgets(Buffer, 24, stdin);
	sscanf(Buffer,"%[^\n]", new.name);

	printf("Quantity:");
	fgets(Buffer, 24, stdin);
	sscanf(Buffer,"%lu", &new.quantity);

	printf("Price:");
	fgets(Buffer, 24, stdin);
	sscanf(Buffer, "%lf", &new.price );

	Cart[index] = new;

}

// Print information for each item in cart
void printCart(Item Cart[], int numOfItems){

	for(int i = 0; i < numOfItems; i++){
		printf("Item #%d:", i+1);
		printf("| Name: %12s ", Cart[i].name);
		printf("| Quantity: %4zd ", Cart[i].quantity);
		printf("| Price: %.2f \n", Cart[i].price);

	}


}

// Resize cart to double its size to hold more items
void ResizeArray(Item **Cart, int size){

	// Allocate new cart memory to hold more items
	Item *NewCart = (Item*)malloc(sizeof(Item) * (2*size));

	if(NewCart == NULL){
		printf("Malloc failed\n");
		exit(1);	
	}

	NewCart = memcpy(NewCart, *Cart, sizeof(Item)*size);

	// Release old(smaller) cart memory
	free(*Cart);
	*Cart = NewCart;

	NewCart = NULL;
}















