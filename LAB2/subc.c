#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Function declaration
void displayHelpMenu(void);


int main ( int argc , char **argv ) {
	
	//Checking if we did not pass any arguments in the command line besides calling the program.
	//If so, we display the help menu.
	// ./subc
	
	if ( argc <= 1 ) {
		displayHelpMenu();
	}
	
	
	char *inputFile = NULL;
	char *outputFile = NULL;
	
	//Iterating through all the arguments we pass into the command line, besides te program call.
	//This is why argument starts at 1 and ends before enter key.
	
	for ( int argument = 1 ; argument < argc ; argument++ ) {

		/*		
		//Checking if the argument we are on is -h by using strcmp.
		//If so, we call on the function to display the menu.
		
		if ( strcmp ( argv[argument] , "-h" ) == 0 ) {
			displayHelpMenu();
		}
		*/
		
		//Checking if the argument we are on is -i by using equality operator.
		//We check that the first character in the string is a '-'
		//We check that the second character in the string is a 'i'
		//If so, print a message saying this works for now.
		
		/*		i
		if ( ( argv[argument][0] == '-' ) && ( argv[argument][1] == 'i' ) ) {
			
			printf("\n -i part works \n");
		}
		*/
		
		
		
		/*
		Checking if the first character in the string of the current argument is a '-'
		
		If true, then we implement switch case statements
		depending on what the second character in the string of the current argument is
		
		*/
		
		if ( argv[argument][0] == '-' ) {
			
			switch ( argv[argument][1] ) {
				
				case 'h':
					displayHelpMenu();
					break;
				
				case '-':
					printf("indicates all characters that will be replaced in the processed text \n");
					break;
				
				case '+':
					printf("indicates the characters that will be used to replace corresponding \n");
					break;
				
				case 'i':
					printf("This is where we will open either a txt file as input stream or std input \n");
					break;
				
				case 'o':
					printf("This is where we open either a txt file as output stream or std output \n");
					break;
				
				default:
					printf("The command is not complete \n");
					break;
				
			}
		}
	}

return 0;
}




/*
-- Help Menu --
Opens the file helpMenu.txt for reading.
Then gets each character from the file and prints each character.
Then closes the file.
Basically just a utility function which displays the help menu.
*/	
	
void displayHelpMenu(void) {
	
	FILE *fptr;
	char letter;
	
	fptr = fopen ( "helpMenu.txt" , "r" );
	
	letter = fgetc ( fptr );
	
	while ( letter != EOF ) {
		
		printf ( "%c" , letter );
		letter = fgetc ( fptr );
	}
	
	fclose ( fptr );
	
return;
}
