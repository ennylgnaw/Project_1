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

/* Takes a char * line and separates it by spaces into a char * array. Returns the array.*/
char ** parse_args(char * line) {
  char ** arrP = calloc(5, sizeof(char *));
  for(int i = 0; line; i++)
    arrP[i] = strsep(&line, " ");
  return arrP;
}

/* Takes a char * line which contains two commands separated by a semicolon and separates it into a char * array.
 * Returns the array. */
char ** sep_cmds(char * line) {
  char ** arrP = calloc(5, sizeof(char *));
  for(int i = 0; line; i++) arrP[i] = strsep(&line, ";");
  return arrP;
}


/* Finds the current working directory and returns it as a string. */
char * findDir() {
    char cwd[PATH_MAX];
    char * dir;
    getcwd(cwd, sizeof(cwd));
    dir = cwd;
    return dir;
}

/* Changes directory. If successful, returns 0; else, returns 1. */
int cd(char * path) {
    if (chdir(path)) return 0;
    else return 1;
}
