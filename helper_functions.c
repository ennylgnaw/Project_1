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
#include <fcntl.h>

#define READ 0
#define WRITE 1

void pipe_cmds(char * first_pipe, char * second_pipe); 
void redirect_cmd_file(char * cmd, char * file);
void redirect_file_cmd(char * cmd, char * file);

/* Helper function for parse_args.
 * Fixes up the bad array (passed from parse_args)
 * And returns a good array (with no null elements)
 */
char ** remove_nulls(char ** badArr) {
    char ** goodArr = calloc(sizeof(badArr), sizeof(char *));
    int index = 0;
    for(int i = 0; badArr[i]; i++) {
        if (strcmp(badArr[i], "") && strcmp(badArr[i], " ")) {
            goodArr[index] = badArr[i];
            index++;
        }
    }
    return goodArr;
}

/* Takes a char * line and separates it by spaces into a char * array. Returns the array.*/
char ** parse_args(char * line) {
  char ** arrP = calloc(strlen(line), sizeof(char *));
  for(int i = 0; line; i++) {
    arrP[i] = strsep(&line, " ");
    char * buf = arrP[i];
    if (!strsep(&buf, " ")) arrP[i] = parse_args(buf)[0];
  }
  return remove_nulls(arrP);
}

/* Takes a char * line which contains two commands separated by a semicolon and separates it into a char * array.
 * Returns the array. */
char ** sep_cmds(char * line) {
  char ** arrP = calloc(strlen(line), sizeof(char *));
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


/* Takes a char * cmd and separates it, first by semicolon.
 * Checks if there is any pipe nonsense involved - if so, redirects the command into pipe_cmds.
 * Then, separates by spaces.
 * Returns void; prints the results of executing the command.
 */
void execr( char * cmd) {
    char ** cmds = sep_cmds(cmd); //separates by semicolon 
    for (int i = 0; cmds[i]; i++) {
        char * cmd1 = cmds[i];
        char * cmd2 = strsep(&cmd1, "|"); //checks if there's a pipe in the comand; if yes, redirects the command to pipe_cmds
        if ( cmd1) { 
            pipe_cmds( cmd2, cmd1 );
            return;
        }   //executes the command, but with a pipe
        
        char * cmd3 = strsep(&cmd2, "<");
        if ( cmd2) {
            redirect_file_cmd( cmd3, cmd2);
            return;
        }  
        
        char * cmd4 = strsep(&cmd3, ">");
        if ( cmd3) {
            redirect_cmd_file( cmd4, cmd3);
            return;
        }
        
        char ** args = parse_args(cmds[i]); // separates by spaces
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

/* Takes a char * first_pipe command and a char * second_pipe command.
 * Redirects the output from executing first_pipe into the input of second_pipe. 
 * Returns void; prints the results of executing the command.
 */

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

/* Redirects the output of a command into a file.
 * Takes a char * cmd and a char * file. Return type void.
 * Prints the results of executing the command.
 */

void redirect_cmd_file(char * cmd, char * file) {
    if (!fork()) {
        char ** files = parse_args( file);
        int f = open( files[0], O_CREAT|O_EXCL, 0644 );
        close(f);
        f = open( files[0], O_WRONLY );
        dup2(f, STDOUT_FILENO);
        char ** args = parse_args( cmd);
        execvp(args[0], args);
    }
    wait(0);
}

/* Redirects a file into the input of a command. Not to bbe confused with redirect_cmd_file.
 * Takes a char * cmd and a char * file. Return type void.
 * Prints the results of executing the command.
 * Handles multiple redirects (ex. tr a-z A-Z < wholist > foo)
 */

void redirect_file_cmd(char * cmd, char * file) {
    if (!fork()) {
        char * file2 = file;
        file = strsep(&file2, ">");
        char ** files = parse_args( file);
        int f = open( files[0], O_RDONLY );
        dup2(f, STDIN_FILENO);
        char ** args = parse_args( cmd);
        
        if (file2) {
            file2 = parse_args(file2)[0];
            int f = open( file2, O_CREAT|O_EXCL, 0644 );
            close(f);
            f = open( file2, O_WRONLY );
            dup2(f, STDOUT_FILENO);
        }
        execvp(args[0], args);

    }
    wait(0);
}
