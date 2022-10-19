// C program to demonstrate use of fork() and pipe() 
// worked with Aster Smith on this lab 
#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
  
int main() 
{ 
    int fd1[2];  
    int fd2[2];  
    char input_str[100]; 
    pid_t p; 
  
    if (pipe(fd1)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
    if (pipe(fd2)==-1) 
    { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 
  
    printf("Enter a string to concatenate:");
    scanf("%s", input_str); 
    p = fork(); 
  
    if (p < 0) 
    { 
        fprintf(stderr, "fork Failed" ); 
        return 1; 
    } 
  
    // Parent process 
    else if (p > 0) 
    { 
      close(fd1[0]);  // Close reading end of pipes 
      close(fd2[1]);  // Close the writing end of pipe - recieves the message

      // Write input string and close writing end of first 
      // pipe. 
      write(fd1[1], input_str, strlen(input_str)+1); // www.geeks

      read(fd2[0], input_str, 100); //www.geekshoward.edu

      // Wait for child to send a string 
      wait(NULL); 

      strcat(input_str, "gobison.org"); // www.geekshoward.edugobison.org
      printf("Parent: Concatenated string %s\n", input_str);

      //close(fd2[0]); // Close writing end of pipes 
      //close(fd1[1]); 
    } 
    
    // child process 
    else
    { 
      close(fd1[1]);  // Close writing end of first pipes 
      close(fd2[0]);  // Close the reading end of the pipe 

      char concat_str[100]; 
      read(fd1[0], concat_str, 100);

      strcat(concat_str, "howard.edu"); // www.geekshoward.edu
      write(fd2[1], concat_str, strlen(concat_str)+1); // www.geekshoward.edu

      printf("Child: Concatenated string %s\n", concat_str);
      // Close both reading ends 
      exit(0); 
    }  
} 