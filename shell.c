#include <tokenize_all.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

//gets the number of elements in a null terminated string array
int getNumElements(char** arr) {
  int numElements = 0;
  while (arr[numElements] != NULL) {
    numElements++;
  }

  return numElements;
}

//fork a child and execute argv[0] with argv as arguments, src as input file, and filename as output file
void runArgs(char* myargv[16], char* src, char* filename) {
  if (fork() == 0) {
    if (strcmp(filename, "") != 0) {
      //open the given file as write only, if the file needs to be created create it as rw-r--r--
      int file_desc = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
      dup2(file_desc, 1);
    }
    execvp(myargv[0], myargv);
    strcat(src, ": command not found\n");
    printf("%s", src);
    exit(1);
  }
  else {
    wait(NULL);
  }
}

//makes newInput contain the all the elements of input after element i + jump - 1
void nextArgs(char** input, char** newInput, int i, int jump) {
  int n = 0;
  for (int j = i + jump; j < getNumElements(input); j++) {
    newInput[n] = input[j];
    n++;
  }
}

//runs the given input string in the shell
void parseInput(char** input) {
  char** myargv = calloc(256, sizeof(char*));
  char* src = calloc(256, sizeof(char));
  char** newInput = calloc(256, sizeof(char*));
  char* filename = "";
  //copy first element into input list
  strcpy(src, input[0]);
  myargv[0] = src;
  // Processes the tokens as arguments
  for (int i = 0; i <= getNumElements(input); i++) {
    if (i == getNumElements(input)) {
      //when you reach the end of the input null terminate and try to run
      myargv[i] = NULL;
      runArgs(myargv, src, filename);
    } else if (strcmp(input[i], ";") == 0) {
      //handle sequencing: null terminate and run the first command
      myargv[i] = NULL;
      runArgs(myargv, src, filename);
      //handle sequencing: get the rest of the input after the ; and recursively call parseinput on that
      if (i < getNumElements(input) - 1) {
        nextArgs(input, newInput, i, 1);
        parseInput(newInput);	
      }
      break;
    } else if (strcmp(input[i], ">") == 0) {
      //handle output redirection by updating filename
      filename = input[i + 1];
      i++;
    } else if (strcmp(input[i], "<") == 0) {
      //handle input redirection by updating src
      
    } else if (strcmp(input[i], "|") == 0) {
      //handle piping
      break;
    } else {
      myargv[i] = input[i];
    }
  }
  free(myargv);
  free(src);
  free(newInput);
}

int main(int argc, char **argv) {
  
  // Prints welcome message
  printf("Welcome to mini-shell.\nshell $ ");
  
  // Obtains intial input
  char** input = getInputTokens();

  // Loops shell until exit
  while (input[0] != NULL && strcmp(input[0], "exit") != 0) {
    
    // Reacts to user input if not only a newline
    if (strcmp(input[0], "\n") != 0) {
      parseInput(input);
    }

    // Prepares the shell for next input arguments
    printf("shell $ ");
    input = getInputTokens();
  }

  // Prints exit message
  if (input[0] == NULL) {
    printf("\n");
  }
  printf("Bye bye.\n");
  

  return 0;
}
