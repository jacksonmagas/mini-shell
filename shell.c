#include <tokenize_all.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

//gets the number of elements in a null terminated string array
int getNumElements(char** arr) {
  int numElements = 0;
  while (arr[numElements] != NULL) {
    numElements++;
  }

  return numElements;
}

int main(int argc, char **argv) {
  
  // Prints welcome message
  printf("Welcome to mini-shell.\nshell $ ");
  
  // Obtains intial input
  char** input = getInputTokens();

  // Losrcops shell until exit
  while (input[0] != NULL && strcmp(input[0], "exit") != 0) {
    char* myargv[16];
    char* src = calloc(256, sizeof(char));

    // Processes the tokens as arguments
    for (int i = 0; i <= getNumElements(input); i++) {
      if (i == 0) {
        strcpy(src, input[0]);
        myargv[0] = src;
      } else if (i == getNumElements(input)) {
        myargv[i] = NULL;
      } else {
        myargv[i] = input[i];
      }
    }

    // Runs the arguments
    if (fork() == 0) {
      execvp(myargv[0], myargv);
      strcat(src, ": command not found\n");
      printf("%s", src);
      exit(1);
    }
    else {
      wait(NULL);
    }

    // Prepares the shell for next input arguments
    printf("shell $ ");
    input = getInputTokens();
    free(src);
  }

  // Prints exit message
  if (input[0] == NULL) {
    printf("\n");
  }
  printf("Bye bye.\n");
  

  return 0;
}
