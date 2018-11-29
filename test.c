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
    char * cmd1 = cmd2;
    cmd2 = strsep(&cmd1, "|");
    if ( cmd1) { 
        pipe_cmds(cmd2, cmd1); 
    }   //executes the command, but with a pipe
    else {
        execr(cmd2); //executes the command
    }
  }
  return 0;
}
