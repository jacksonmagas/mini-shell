#include <tokenize_all.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Convert the input string to an array of tokens where each token is one of:
 * (, ), <, >, ;, |, "somestuffintquotes 898|>(", somegroupofnonsp3cialcharacters
 * Allocates memory for 256 strings of length 256, it is the responsability of callers of tokenize to free the memory.
 */
char** tokenize(char* inputString) {
  //allocate memory for array of up to 256 tokens of up to 256 bytes each
  char** output = calloc(256, sizeof(char*));
  for (int i = 0; i < 256; i++) {
    output[i] = calloc(256, sizeof(char));
  }
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
    while (buf[j] != '\0') {
      output[tokenNum][j] = buf[j];
      ++j;
    }
    output[tokenNum][j+1] = '\0';
    ++tokenNum;
  }
  output[tokenNum+1] = NULL;
  return output;
}


int main(int argc, char **argv) {
  //get up to 256 characters of input from stdin
  char* inputString = calloc(256, sizeof(char));
  fgets(inputString, 256, stdin);
  //remove trailing newline from gets
  inputString[strcspn(inputString, "\r\n")] = 0;
  
  //tokenize string
  char** tokens = tokenize(inputString);
  //print each token on a new line
  int i = 0;
  while (tokens[i] != NULL) {
    if (i > 0) { puts("");}
    printf("%s", tokens[i]);
    ++i;
  }
  //free all memory
  for (int j = 0; j < 256; j++) {
    free(tokens[j]);
  }
  free(tokens);
  free(inputString);
}
