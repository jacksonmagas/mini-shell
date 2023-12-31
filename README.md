# Project 1: Shell

This repository was the first project for my computer systems class, a shell written in c using system calls.

The shell supports piping, sequencing, input and output redirection, and a few built in functions, as well as support for running external binaries such as echo or any other binary.

There are two main parts to the project, the tokenizer which gets user input and splits it into lexical tokens, and the shell which takes a list of tokens and makes the correct system calls and forks and joins the required processes to execute the command.

This project was written in collaboration with Ben Aranow.
