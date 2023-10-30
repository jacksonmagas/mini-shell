//Header File for tokenizer
#ifndef _TOKENIZER_H
#define _TOKENIZER_H

//reads a string until the next quote
//returns the length of the output string
int read_quote_string(char* input, char* output);

//read a string until the next special character or space
//returns the length of the output string
int read_nonspecial_string(char* input, char* output);

//determines if the character is one of:
//(, ), <, >, ;, |
int is_special_character(char input);

/* Convert the input string to an array of tokens where each token is one of:
 * (, ), <, >, ;, |, "somestuffintquotes 898|>(", somegroupofnonsp3cialcharacters
 * Allocates memory for an array of 256 strings and allocates memory to hold each token
 */
char** tokenize(char* inputString);

char** getInputTokens();


#endif /*#ifndef _TOKENIZER_H */
