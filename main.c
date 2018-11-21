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

int main() {
  while (1) {
    char cmd[256];
    cmd[0] = 0;
    printf("\n%s $ ", findDir() );
    fgets(cmd, 256, stdin);
    char *cmd2 = cmd;
    cmd2 = strsep(&cmd2, "\n");
    char ** args = parse_args(cmd2);
    if (! (strcmp(cmd2, "exit") == 0 || strcmp(cmd2, "cd") == 0)) {
      int f = fork();
      if (! f) {
	execvp(args[0], args);
	exit(0);
      }
      int status;
      wait(&status);
    }
    else if (strcmp(cmd2, "exit") == 0)
      exit(0);
  }
}
