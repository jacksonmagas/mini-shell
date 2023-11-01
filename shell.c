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

void runArgs(char* myargv[16], char* src) {
  if (fork() == 0) {
    //int file_desc = open("out.txt", O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0644);
    //dup2(file_desc, 1) ;
    execvp(myargv[0], myargv);
    strcat(src, ": command not found\n");
    printf("%s", src);
    exit(1);
  }
  else {
    wait(NULL);
  }
}

void parseInput(char** input) {
  char** myargv = calloc(256, sizeof(char*));
  char* src = calloc(256, sizeof(char));
  char** newInput = calloc(256, sizeof(char*));
  // Processes the tokens as arguments
  for (int i = 0; i <= getNumElements(input); i++) {
    if (i == 0) {
      strcpy(src, input[0]);
      myargv[0] = src;
    } else if (i == getNumElements(input)) {
      myargv[i] = NULL;
      runArgs(myargv, src);
    } else if (strcmp(input[i], ";") == 0) {
      myargv[i] = NULL;
      runArgs(myargv, src);
      if (i != getNumElements(input) - 1) {
        int n = 0;
        for (int j = i + 1; j < getNumElements(input); j++) {
          newInput[n] = input[j];
          n++;
        }
        parseInput(newInput);
      }
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
