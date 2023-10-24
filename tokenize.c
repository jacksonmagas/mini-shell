#include <tokenize_all.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Convert the input string to an array of tokens where each token is one of:
 * (, ), <, >, ;, |, "somestuffintquotes 898|>(", somegroupofnonsp3cialcharacters
 * Allocates memory for 256 strings of length 256, it is the responsability of callers of tokenize to free the memory.
 */
char** tokenize(char* inputString) {
  char** output = calloc(256, sizeof(char*));
  for (int i = 0; i < 256; i++) {
    output[i] = calloc(256, sizeof(char));
  }
  int charNum = 0;
  int tokenNum = 0;
  while (inputString[charNum] != '\0') {
    char buf[256];
    if (inputString[charNum] == '"') {
      ++charNum;
      int len = read_quote_string(&inputString[charNum], buf);
      charNum += len;
    } else if (is_special_character(inputString[charNum])) {
      buf[0] = inputString[charNum];
      buf[1] = '\0';
      charNum++;
    } else if (inputString[charNum] != ' ') {
      int len = read_nonspecial_string(&inputString[charNum], buf);
      charNum += len;
    } else {
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
  char* inputString = calloc(256, sizeof(char));
  fgets(inputString, 256, stdin);
  inputString[strcspn(inputString, "\r\n")] = 0;
  char** tokens = tokenize(inputString);
  int i = 0;
  while (tokens[i] != NULL) {
    if (i > 0) { puts("");}
    printf("%s", tokens[i]);
    ++i;
  }
  for (int i = 0; i < 256; i++) {
    free(tokens[i]);
  }
  free(tokens);
  free(inputString);
}
