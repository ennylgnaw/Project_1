/* If you're looking for function descriptions, check out helper_functions.c. */

char ** sep_cmds(char * line); 

char ** parse_args(char * line);

char * findDir();

int cd(char * path);

void execr( char * cmd);

int pipe_cmds(char * first_pipe, char * second_pipe);
