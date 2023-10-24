//Header File for tokenizer
#ifndef _TOKENIZER_H
#define _TOKENIZER_H

//reads a string until the next quote
//returns the length of the output string
int read_quote_string(char* input, char* output);

//read a string until the next special character
//returns the length of the output string
int read_nonspecial_string(char* input, char* output);

//determines if the character is one of:
//(, ), <, >, ;, |
int is_special_character(char input);

#endif /*#ifndef _TOKENIZER_H */
