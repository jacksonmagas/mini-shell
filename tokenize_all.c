#include <stdio.h>
#include <string.h>

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
  // while we have input and the character is a digit,
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
  // while we have input and the character is a digit,
  while (input[i] != '\0' && input[i] != '"') {
    output[i] = input[i]; // copy character to output buffer
    ++i;
  }
  output[i] = '\0'; // add the terminating byte

  return i + 1; // return the length of the string
}


