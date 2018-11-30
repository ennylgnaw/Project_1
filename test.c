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
    char cmds[256];
    cmds[0] = 0;
    printf("\x1b[36m\n%s $ \x1b[0m", findDir() );
    fgets(cmds, 256, stdin); // input through fgets
    char *cmd = cmds;
    cmd = strsep(&cmd, "\n"); // removing the newline from the fgets input
    execr( cmd); //executes the command
  }
  return 0;
}
