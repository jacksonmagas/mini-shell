#include <tokenize_all.h>
#include <stdio.h>

/* Convert the input string to an array of tokens where each token is one of:
 * (, ), <, >, ;, |, "somestuffintquotes 898|>(", somegroupofnonsp3cialcharacters
 */
char** tokenize(char* inputString) {
  int i = 0;
  char** output[256];
  while (inputString[i] != '\0') {
    char* buf[256];
    if (inputString[i] == '"') {
      ++i;
      int len = read_quote_string(&inputString[i], buf);
      i += len;
    } else if (is_special_character(inputString[i])) {
      buf[0] = inputString[i];
      buf[1] = '\0'
    } else if (inputString[i] != ' ') {
      read_nonspecial_string(&inputString[i], buf);
    }
    ++i;
    output[i] = &buf;
  }
  output[i+1] = null;
  return output;
}

int main(int argc, char **argv) {
  char* inputString = argv[1];
  char** tokens = tokenize(inputString);
  int i = 0;
  while (tokens[i] != null) {
    fprintf("%s\n", tokens[i]);
  }

}
