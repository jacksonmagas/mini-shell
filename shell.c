#include <tokenize_all.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

char** tokenize(char* inputString) {
  //allocate memory for array of up to 256 tokens of up to 256 bytes each
  char** output = calloc(256, sizeof(char*));
  int charNum = 0;
  int tokenNum = 0;
  //iterate through the string adding each token to the output
  while (inputString[charNum] != '\0') {
    char buf[256];
    if (inputString[charNum] == '"') {
      //precrement charNum to pass first quote
      ++charNum;
      int len = read_quote_string(&inputString[charNum], buf);
      //add length of the quote string to index to avoid double reading
      charNum += len;
    } else if (is_special_character(inputString[charNum])) {
      //for special characters simply add the character and a null character to the buffer
      buf[0] = inputString[charNum];
      buf[1] = '\0';
      charNum++;
    } else if (inputString[charNum] != ' ') {
      //if it's none of the above and not a space read the string into the buffer
      int len = read_nonspecial_string(&inputString[charNum], buf);
      charNum += len;
    } else {
      //if it's a space just move on to the next letter.
      charNum++;
      continue;
    }
    int j = 0;
    output[tokenNum] = calloc(strlen(buf) + 1, sizeof(char));
    while (buf[j] != '\0') {
      output[tokenNum][j] = buf[j];
      ++j;
    }
    ++tokenNum;
  }
  output[tokenNum + 1] = NULL;
  return output;
}

char** getInputTokens() {
  //get up to 256 characters of input from stdin
  char* inputString = calloc(256, sizeof(char));
  fgets(inputString, 255, stdin);
  //remove trailing newline from gets
  inputString[strcspn(inputString, "\r\n")] = 0;
  //tokenize string
  char** tokens = tokenize(inputString);
  return tokens;
}

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
