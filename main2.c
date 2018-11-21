#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


char ** parse_args(char * line) {
  char ** arrP = calloc(5, sizeof(char *));
  for(int i = 0; line; i++)
    arrP[i] = strsep(&line, " ");
  return arrP;
}

char ** sep_cmds(char * line) {
  char ** arrP = calloc(5, sizeof(char *));
  for(int i = 0; line; i++)
    arrP[i] = strsep(&line, ";");
  return arrP;
}

int main() {
  while (1) {
    char cmd[256];
    cmd[0] = 0;
    printf("Enter a command$ ");
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
    }
  }
}
