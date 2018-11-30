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

#define READ 0
#define WRITE 1

void pipe_cmds(char * first_pipe, char * second_pipe);

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

void execr( char * cmd) {
    char ** cmds = sep_cmds(cmd); //separates by semicolon 
    for (int i = 0; cmds[i]; i++) {
        
        char * cmd1 = cmds[i];
        char * cmd2 = strsep(&cmd1, "|");
        if ( cmd1) { 
            pipe_cmds( cmd2, cmd1 );
            return;
        }   //executes the command, but with a pipe
    
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
    }
}

void pipe_cmds(char * first_pipe, char * second_pipe) {
    if (!fork()) {
        int desc[2];
        pipe( desc);
        if ( !fork()) { //the child
            close( desc[READ]);
            dup2( desc[WRITE], STDOUT_FILENO);
            char ** args = parse_args( first_pipe);
            execvp(args[0], args);
            close( desc[WRITE]);
        }
        else {
            char ** args = parse_args( second_pipe);
            close(READ);
            dup(desc[READ]);
            close(desc[WRITE]);
            execvp(args[0], args);
        }   
    }
    wait(0);
}
