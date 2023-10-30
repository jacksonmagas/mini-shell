#include <tokenize_all.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv) {
  
  // Prints welcome message
  printf("Welcome to mini-shell.\nshell $ ");
  
  // Obtains intial input
  char** input = getInputTokens();

  // Loops shell until exit
  while (input[0] != NULL && strcmp(input[0], "exit") != 0) {
    char* myargv[16];
    char* src = calloc(256, sizeof(char));
    char* dest = calloc(256, sizeof(char));

    // Processes the tokens as arguments
    for (int i = 0; i <= sizeof(input); i++) {
      if (i == 0) {
        strcpy(src, input[0]);
        strcpy(dest, "/bin/");
        strcat(dest, src);
        myargv[0] = dest;
      } else if (i == sizeof(input)) {
        myargv[i] = NULL;
      } else {
        myargv[i] = input[i];
      }
    }

    // Runs the arguments
    if (fork() == 0) {
      execve(myargv[0], myargv, NULL);
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
  }

  // Prints exit message
  if (input[0] == NULL) {
    printf("\n");
  }
  printf("Bye bye.\n");

  return 0;
}
