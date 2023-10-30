#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_special_character(char ch) {
        return ch == '(' ||
                ch == ')' ||
                ch == '<' ||
                ch == '>' ||
                ch == ';' ||
                ch == '|' ||
                ch == '"';
}

// Function for reading words
int read_nonspecial_string(const char *input, char *output) {
  int i = 0;
  // while we have input and the character is not a space or special character
  while (input[i] != '\0' && input[i] != ' ' && (! is_special_character(input[i]))) {
    output[i] = input[i]; // copy character to output buffer
    ++i;
  }
  output[i] = '\0'; // add the terminating byte

  return i; // return the length of the string
}

// Function for reading words
int read_quote_string(const char *input, char *output) {
  int i = 0;
  // while we have input and the input is not the end quote
  while (input[i] != '\0' && input[i] != '"') {
    output[i] = input[i]; // copy character to output buffer
    ++i;
  }
  output[i] = '\0'; // add the terminating byte

  return i + 1; // return the length of the string
}

//check if the pointer is NULL and if it is log the error and exit
void checkMalloc(void* ptr) {
  if (ptr == NULL) {
    fprintf(stderr, "Memory allocation failed. Exiting...\n");
    exit(1);
  }
}

/* Convert the input string to an array of tokens where each token is one of:
 * (, ), <, >, ;, |, "somestuffintquotes 898|>(", somegroupofnonsp3cialcharacters
 * Allocates memory for an array of 256 strings and allocates memory to hold each token
 */
char** tokenize(char* inputString) {
  //allocate memory for array of up to 256 tokens of up to 256 bytes each
  char** output = calloc(256, sizeof(char*));
  checkMalloc(output);
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
    checkMalloc(output[tokenNum]);
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
  checkMalloc(inputString);
  fgets(inputString, 256, stdin);
  //remove trailing newline from gets
  inputString[strcspn(inputString, "\r\n")] = 0;

  //tokenize string
  char** tokens = tokenize(inputString);
  free(inputString);
  return tokens;
}
