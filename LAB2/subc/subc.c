//*****
//Andrew Lockwood
//COMP362L
//LAB2
//*****



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>






void subcFUNC(FILE * infile, FILE * outfile, char * target, char * replace);
void openHELP();




//Start main program
int main (int argc, char **argv){

   FILE * INFILE = NULL;
   FILE * OUTFILE = NULL;
   char * target = NULL;
   char * replace = NULL;
   
   int i = 0;
   int j = 2;
   
   if(argc <= 1){
      openHELP();
   }
   else{
   
      while(i < argc){
         if (argv[i][0] == '-') {

            switch (argv[i][1] ) {

               //-----------------------------            
            
               case 'h'://help menu command
                  //open help menu
                  openHELP();
                  break;
               
               //-----------------------------
               
               case '-'://target menu command
                  //target characters

                  target = &argv[i][j];

                  break;
               
               //-----------------------------
               
               case '+'://replace menu command
                  //replace characters
  
                  replace = &argv[i][j];

                   break;
               
               //-----------------------------
               
               case 'i'://infile menu command
                  //assign infile
                  INFILE = freopen(argv[i+1], "r", stdin);
                  break;
	    
               //-----------------------------
               
               case 'o'://outfile menu command
                  //assign outfile
                  OUTFILE = freopen(argv[i+1], "w+", stdout);
                  break;
           
               //-----------------------------   
               
               default:
                  //print error
                  printf("The command is not complete.\n");
                  break;       

               //-----------------------------           
          
            }
         }
      i++;
      }
      
      if(target > replace){//check if there are more targets than replacements
         printf("ERROR : missing replacement character.\n");//error and exit if so
         exit(0);
      }
            
      //decide which streams to pass to subcFUNC based on user input      
      if(target != NULL && replace != NULL){
         if(INFILE != NULL && OUTFILE != NULL){
           //do stuff: infile & outfile
           subcFUNC(INFILE, OUTFILE, target, replace);
         }
         else if(INFILE != NULL && OUTFILE == NULL){
           //do stuff: infile & stdout
           subcFUNC(INFILE, stdout, target, replace);
         }
         else if(INFILE == NULL && OUTFILE != NULL){
            //do stuff: stdin & outfile
            subcFUNC(stdin, OUTFILE, target, replace);
         }
         else if(INFILE == NULL && OUTFILE == NULL){
            //do stuff: stdin & stdout
            subcFUNC(stdin, stdout, target, replace);
         }
      
      }
      else{
         printf("Error : target and/or replace characters not present.\n");
      }
      fclose(stdin);
      fclose(stdout);


   }//close main else
   
  return 0;
}//close main END PROGRAM

///**************************************************************************///

///void subcFUNC(FILE * infile, FILE * outfile, char * target, char * replace)
void subcFUNC(FILE * infile, FILE * outfile, char * target, char * replace){

   int i = 0;//index
   char c;//c
   bool flag = 0;//target found flag
   
   
   while((c = getc(infile)) != EOF){//outside: while c is not the end of file
      i = 0;//reset index
      flag = 0;//reset target found flag
      while(target[i] != '\0'){//inside: while target array is not a null character
      
         if(c == target[i]){//if this target char
            putc(replace[i], outfile);//then print this replace char to out
            flag = 1;//target char found
            break;
         }
         ++i;//increment index
         
      }//close inside while
      
      if(flag == 0){//if target char not found  
         putc(c, outfile);//print c 
      }
      
   }//close outside while
   if(replace[i] != '\0'){
      printf("WARNING - extraneous replacement character\n");
   }
	
}//END subcFUNC

///**************************************************************************///

//void openHELP(void)
void openHELP(){
	FILE *fileptr;//help file pointer
	char c;//c
	fileptr = fopen("helpMENU.txt", "r");//open help menu text file
	c = getc(fileptr);
	while(c != EOF){//while c is not end of file
		printf("%c", c);//print c to terminal
		c = getc(fileptr);//get next c
	}
	fclose (fileptr);//close file
return;
}//END openHELP

///**************************************************************************///
//END OF FILE
