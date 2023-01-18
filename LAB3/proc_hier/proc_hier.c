//*****
//Andrew Lockwood
//COMP362L
//9/13/2022
//LAB3
//*****

#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <unistd.h>
#include    <errno.h>
#include    <sys/types.h>
#include    <sys/wait.h>

#define oops(m) {perror(m); exit(EXIT_FAILURE);}

int main(){

   pid_t pid;

   pid = fork();//fork to 1.1-----------------------------------------------

   if (pid < 0){ // error occurred
   oops("Fork Failed!");
   } 
   else if(pid == 0){ //check if fork for process 1.1 exists
   
      printf("I am process 1.1\n"); 
      printf("pid = %d | ppid = %d \n", getpid(), getppid());  
      
      //fork to 1.1.1-----------------------------------------------
      pid = fork();
      if (pid < 0){ // error occurred
         oops("Fork 1.1.1 Failed!");
      }
      else if(pid == 0){//check for fork for process 1.1.1
         printf("I am process 1.1.1\n"); 
         printf("pid = %d | ppid = %d \n", getpid(), getppid());
         //1.1.1
         if(execlp("./iam", "iam", "1.1.1", NULL) < 0){
            oops("execlp Failed!");
         }
      
      }
      
      
      //fork to 1.1.2-----------------------------------------------
      pid = fork();
      if (pid < 0){ // error occurred
         oops("Fork Failed!");
      }
      else if(pid == 0){//check for fork for process 1.1.2
         printf("I am process 1.1.2\n");
         printf("pid = %d | ppid = %d \n", getpid(), getppid());
         //1.1.2   
         if(execlp("./iam", "iam", "1.1.2", NULL) < 0){
            oops("execlp Failed!");
         }
      }             

      //1.1
      if(execlp("./iam", "iam", "1.1", NULL) < 0){
         oops("execlp Failed!");
      }
     
   }
   

   //fork to 1.2-----------------------------------------------   
   pid = fork();
   if (pid < 0){ // error occurred
      oops("Fork 1.2 Failed!");
   }    
   else if(pid == 0){ //check if fork for process 1.2 exists
      printf("I am process 1.2\n");
      printf("pid = %d | ppid = %d \n", getpid(), getppid());
      
      
      //fork to 1.2.1-----------------------------------------------
      pid = fork();
      if (pid < 0){ // error occurred
         oops("Fork 1.2.1 Failed!");
      }
      else if(pid == 0){//check for fork for process 1.2.1
         printf("I am process 1.2.1\n");
         printf("pid = %d | ppid = %d \n", getpid(), getppid());
         
         if(execlp("./iam", "iam", "1.2.1", NULL) < 0){
            oops("execlp Failed!");
         }
      
      }
      //fork to 1.2.2-----------------------------------------------
      pid = fork();
      if (pid < 0){ // error occurred
         oops("Fork 1.2.2 Failed!");
      }
      else if(pid == 0){//check for fork for process 1.2.2
         printf("I am process 1.2.2\n");
         printf("pid = %d | ppid = %d \n", getpid(), getppid());
             
         if(execlp("./iam", "iam", "1.2.2", NULL) < 0){
            oops("execlp Failed!");
         }
      }

      if(execlp("./iam", "iam", "1.2", NULL) < 0){
         oops("execlp Failed!");
      }
         
    }         
     
     
    // pid > 0 ==> must be parent
  
    /* parent will wait for the child to complete */
    printf("I am process 1\n");
    printf("pid = %d | ppid = %d \n", getpid(), getppid());
    if (waitpid(-1, NULL, 0) < 0){
        printf("-1 from wait() with errno = %d\n", errno);
    }
    
    printf("Child terminated; parent exiting\n");
    
    
    exit(EXIT_SUCCESS);
    
}
 



