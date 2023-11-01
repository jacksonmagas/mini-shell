#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <tokenize_all.h>
#include <shell.h>

#define HELP_MESSAGE "Mini-shell supports 4 built-in commands.\nThe first command is cd \"path\" which sets the current working directory to the driectory specified by path.\nThe next command is source \"filename\" which executes each line of the given file as if it were a shell command.\n The fourth command is prev which prints the previous command and executes it again.\nThe final supported command is help, which prints this message."

void execWithBuiltIns(char* command, char** argv) {
  if (strcmp(command, "cd") == 0) {
    chdir(argv[1]);
  } else if (strcmp(command, "source") == 0) {
    FILE *fptr = fopen(argv[1], "r");
    char cmds[256];
    while (fgets(cmds, 256, fptr)) {
      parseInput(tokenize(cmds));
    }
  } else if (strcmp(command, "prev") == 0) {
    
  } else if (strcmp(command, "help") == 0) {
    printf("%s", HELP_MESSAGE);
  } else {
    execvp(command, argv);
  }
}
