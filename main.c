#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>
#include "helper_functions.h"


/* Main function: asks for a command, executes the command, and loops. Returns 0.
 * All of the other functions are in helper_functions.c, with the headers in helper_functions.h. */
int main() {
  while (1) {
    char cmd[256];
    cmd[0] = 0;
    printf("\x1b[36m\n%s $ \x1b[0m", findDir() );
    fgets(cmd, 256, stdin); // input through fgets
    char *cmd2 = cmd;
    cmd2 = strsep(&cmd2, "\n"); // removing the newline from the fgets input
    char ** cmds = sep_cmds(cmd2);
    for (int i = 0; cmds[i]; i++) {
        char ** args = parse_args(cmds[i]); // creating an array of string from the fgets input, calling parse_args
        if (! (strcmp(cmds[i], "exit") == 0 || strcmp(cmds[i], "cd") == 0)) {
            int f = fork();
            if (! f) {
                execvp(args[0], args); // executes any command that is not exit or cd.
            }
            int status;
            wait(&status);
        }
        else if (strcmp(cmds[0], "exit") == 0) // EXIT implementation
            exit(0);
            else if (strcmp(cmds[0], "cd") == 0) { //CD implementation 
                if (!cd(args[1]) ) printf("\x1b[31mNo directory %s found.\n\x1b[0m", args[1]); // CD implementation
            }
            else printf("\x1b[31mCommand %s not found.\n\x1b[0m", cmds[0]);
    }
  }
  return 0;
}
