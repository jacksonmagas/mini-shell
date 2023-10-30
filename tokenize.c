#include <tokenize_all.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


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

int main(int argc, char **argv) {
  char** tokens = getInputTokens();
  //print each token on a new line and then free the token
  int i = 0;
  while (tokens[i] != NULL) {
    printf("%s\n", tokens[i]);
    free(tokens[i]);
    ++i;
  }
  free(tokens);
  printf("\n");
}
