//Header File for tokenize driver
#ifndef _TOKENIZE_H
#define _TOKENIZE_H

/* Convert the input string to an array of tokens where each token is one of:
 * (, ), <, >, ;, |, "somestuffintquotes 898|>(", somegroupofnonsp3cialcharacters
 * Allocates memory for an array of 256 strings and allocates memory to hold each token
 */
char** tokenize(char* inputString);

char** getInputTokens();

#endif /*#ifndef _TOKENIZE_H */
