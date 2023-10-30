#include <tokenize_all.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
