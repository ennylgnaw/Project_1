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

char ** parse_args(char * line) {
  char ** arrP = calloc(5, sizeof(char *));
  for(int i = 0; line; i++)
    arrP[i] = strsep(&line, " ");
  return arrP;
}

char * findDir() {
    char cwd[PATH_MAX];
    char * dir;
    getcwd(cwd, sizeof(cwd));
    dir = cwd;
    return dir;
}

int cd(char * path) {
    chdir(path);
}

int main() {
  while (1) {
    char cmd[256];
    cmd[0] = 0;
    printf("\n%s $ ", findDir() );
    fgets(cmd, 256, stdin);
    char *cmd2 = cmd;
    cmd2 = strsep(&cmd2, "\n");
    char ** cmds = sep_cmds(cmd2);
    for (int i = 0; cmds[i]; i++) {
        char ** args = parse_args(cmds[i]);
        if (! (strcmp(cmds[i], "exit") == 0 || strcmp(cmds[i], "cd") == 0)) {
            int f = fork();
            if (! f) {
                execvp(args[0], args);
                exit(0);
            }
            int status;
            wait(&status);
        }
        else if (strcmp(cmds[i], "exit") == 0)
        exit(0);
        else cd(args[1]);
    }
  }
  return 0;
}
