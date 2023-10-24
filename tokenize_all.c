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

int main(int argc, char **argv) {
  char expr[256];
  for (int i = 0; i < argc; i++) {
	  strcat(expr, argv[i]);
	  if (i != argc - 1) {
		  strcat(expr, " ");
	  }
  }
  char buf[256]; // temp buffer

  int i = 0; // current position in string
  while (expr[i] != '\0') { // while the end of string is not reached
    // check if the current char is a quote
    if (expr[i] == '"') {
      // read the integer from the output AND
      // advance the current position by the length of the string
      i += read_quote_string(&expr[i], buf);
      // could convert it here...
      printf("%s\n", buf);
      continue; // skip the rest of this iteration
    }
    // check if the current char is a nonspecial char
    if ((! is_special_character(expr[i])) && expr[i] != ' ') {
      // read the integer from the output AND
      // advance the current position by the length of the string
      i += read_nonspecial_string(&expr[i], buf);
      // could convert it here...
      printf("%s\n", buf);
      continue; // skip the rest of this iteration
    }

    // if not number, consider the current character and print its type
    switch (expr[i]) {
      case '(':
        printf("(\n");
        break;
      case ')':
        printf(")\n");
        break;
      case '<':
        printf("<\n");
        break;
      case '>':
        printf(">\n");
        break;
      case ';':
        printf(";\n");
        break;
      case '|':
        printf("|\n");
        break;
      case ' ':
        // skip spaces
        break;
      default:
        printf("ERROR: Unknown token '%c'.\n", expr[i]);
    }

    ++i; // advance to the next character
  }

  return 0;
}
