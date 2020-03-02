// Alexandra Veney 
// 
// Lab 3

#include <stdio.h>

//function declaration/prototype
//accepts address or character as param
void menu(char *input);

char changeChar();

int changeNum();

void recFill(int x, char y);

void recBord(int x, char y);


int main(){

	//User menu selection, number and character
	char choice;
	int N = 0;
	char C =' ';
	
	// Print menu and prompt for input
	do{
		menu(&choice);
	
		switch(choice){
	
			case 'C':
			case 'c':
				C = changeChar();
				printf("C is %c\n", C);
				break;
			case 'N':
			case 'n':
				N = changeNum();
				printf("N is %d\n", N);
				break;
			case '1':
				recBord(N, C);
				break;
                        case '2':
				recFill(N, C);
                                break;	
		}
		
	}while(choice != 'Q' && choice != 'q');

}
//function accepts address of char variable 
void menu(char *input){
	
	//print menu
	printf("\n --------------------------------------------------------\n");
	printf("| Menu Choice			Valid User Input Choices |\n");
	printf("|------------------------------------------------------- |\n");
	printf("| Enter/Change Character    |  	'C' or 'c'		 |\n");
	printf("| Enter/Change Number	    |   'N' or 'n'		 |\n");
	printf("| Print Rectangle Type 1    |   '1'			 |\n");
        printf("|        (Border Only)      |                            |\n");
	printf("| Print Rectangle Type 2    |   '2'		 	 |\n");
	printf("|	(Filled in)	    |    			 |\n");
	printf("| Quit Program		    |   'Q' or 'q'		 |\n");
	printf(" -------------------------------------------------------- \n");

	char fromKeyboard [2];
	printf("Enter menu choice: \n");
	
	fgets(fromKeyboard,24,stdin);
	//place info from keyboard into address of input	
	sscanf(fromKeyboard, "%c", input);

}

char changeChar(){
	//prompt for new character
	printf("Enter new character: \n");
	char tempChar[2];
	char newChar;
	fgets(tempChar, 24, stdin);
	sscanf(tempChar, "%c", &newChar);

	return newChar;
}	

int changeNum(){
	// Prompt for new number
	int newNum = 0;
	do{
		printf("Enter new number: \n");
		char tempNum[3];
		fgets(tempNum, 24, stdin);
		sscanf(tempNum, "%d", &newNum);

	}while(newNum < 1 || newNum > 15);

	return newNum;
}

void recFill(int x, char y){
	// Print character for each position in rectangle
	for(int i = 0; i < x; i++){
		printf("\n");

		for(int j = 0; j < x; j++){
			printf("%c ", y);
		}
	}
}

void recBord(int x, char y){
	// Print character for border of rectangle
	for(int i = 1; i <= x; i++){
		printf("\n");
	
		for(int j = 1; j <= x; j++){
			if( (j > 1 && j < x) && (i > 1 && i < x) ){
				printf("  ");
			}else{
				printf("%c ", y);
			}
		}

	}

}
