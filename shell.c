#define _GNU_SOURCE
#include <tokenize_all.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <shell.h>

#define HELP_MESSAGE "Mini-shell supports 4 built-in commands.\nThe first command is cd \"path\" which sets the current working directory to the driectory specified by path.\nThe next command is source \"filename\" which executes each line of the given file as if it were a shell command.\n The fourth command is prev which prints the previous command and executes it again.\nThe final supported command is help, which prints this message."

#define MAX_NUM_TOKENS 16

//Globals:
char* prev[MAX_NUM_TOKENS];

//gets the number of elements in a null terminated string array
int getNumElements(char** arr) {
  int numElements = 0;
  while (arr[numElements] != NULL) {
    numElements++;
  }

  return numElements;
}

void handleGeneralCase(char* myargv[MAX_NUM_TOKENS], char* src, char* filename) {
  if (fork() == 0) {
    if (strcmp(filename, "") != 0) {
      int file_desc = open(filename, O_WRONLY | O_APPEND | O_TRUNC | O_CREAT, 0644);
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

void runArgs(char* myargv[MAX_NUM_TOKENS], char* src, char* filename) {
  char* command = myargv[0];
  if (strcmp(command, "cd") == 0) {
    chdir(myargv[1]);
  } else if (strcmp(command, "source") == 0) {
    FILE *fptr = fopen(myargv[1], "r");
    char cmds[256];
    while (fgets(cmds, 256, fptr)) {
      parseInput(tokenize(cmds));
    }
  } else if (strcmp(command, "prev") == 0) {
    parseInput(prev);
  } else if (strcmp(command, "help") == 0) {
    printf("%s", HELP_MESSAGE);
  } else {
    handleGeneralCase(myargv, src, filename);
  }

  if (strcmp(command, "prev") != 0) {
    for (int i = 0; i < getNumElements(myargv); i++) {
      strcpy(prev[i], myargv[i]);
    }
  }
}

void nextArgs(char** input, char** newInput, int i, int jump) {
  int n = 0;
  for (int j = i + jump; j < getNumElements(input); j++) {
    newInput[n] = input[j];
    n++;
  }
}

void getFileInput(char** input, int i, char** myargv) {
  FILE* file = fopen(input[i + 1], "r");
  char* buffer = NULL;
  size_t len;
  ssize_t bytes_read = getdelim(&buffer, &len, '\0', file);
  if (bytes_read != -1) {
    myargv[i] = buffer;
  }
}

void parseInput(char** input) {
  char** myargv = calloc(256, sizeof(char*));
  char* src = calloc(256, sizeof(char));
  char** newInput = calloc(256, sizeof(char*));
  char* filename = "";
  // Processes the tokens as arguments
  for (int i = 0; i <= getNumElements(input); i++) {
    if (i == 0) {
      strcpy(src, input[0]);
      myargv[0] = src;
    } else if (i == getNumElements(input)) {
      myargv[i] = NULL;
      runArgs(myargv, src, filename);
    } else if (strcmp(input[i], ";") == 0) {
      myargv[i] = NULL;
      runArgs(myargv, src, filename);
      if (i < getNumElements(input) - 1) {
        nextArgs(input, newInput, i, 1);
        parseInput(newInput);	
      }
      break;
    } else if (strcmp(input[i], ">") == 0) {
      filename = input[i + 1];
      i++;
    } else if (strcmp(input[i], "<") == 0) {
      if (i < getNumElements(input) - 1) {
        getFileInput(input, i, myargv);
        myargv[i + 1] = NULL;	
	runArgs(myargv, src, filename);
      }
      if (i < getNumElements(input) - 3 && strcmp(input[i + 2], ";") == 0) {
        nextArgs(input, newInput, i, 3);
        parseInput(newInput);
      }
      break;
    } else if (strcmp(input[i], "|") == 0) {
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
  for (int i = 0; i < MAX_NUM_TOKENS; i++) {
    prev[i] = calloc(256, sizeof(char*));
  }
  strcpy(prev[0], "echo");
  strcpy(prev[1], "no");
  strcpy(prev[2], "previous");
  strcpy(prev[3], "command");
  // Prints welcome message
  printf("Welcome to mini-shell.\nshell $ ");
  
  // Obtains intial input
  char** input = getInputTokens("");

  // Loops shell until exit
  while (input[0] != NULL && strcmp(input[0], "exit") != 0) {
    char* filenameList = "";
    
    // Reacts to user input if not only a newline
    if (strcmp(input[0], "\n") != 0) {
      parseInput(input);
    }

    // Prepares the shell for next input arguments
    printf("shell $ ");
    input = getInputTokens("");
  }

  // Prints exit message
  if (input[0] == NULL) {
    printf("\n");
  }
  printf("Bye bye.\n");
  
  for (int i = 0; i < MAX_NUM_TOKENS; i++) {
    free(prev[i]);
  }
  return 0;
}
