# Project_1

Shell by Ela Gulsen and Lynne Wang

# Features

- Displays current directory, and then prompts for command(s)
- Support for all commands, including cd and exit
- All commands and arguments can be separated by any number of spaces! Go wild! 
- Multiple commands can be separated by a single semicolon (Ex. cd .. ; ls)
- Pipe fun! Separate two commands by a pipe and see the input-output switcheroo magic happen before your very eyes! (Ex. ls -l | wc)
- Redirection! Use > and < to redirect commands and files! Multiple redirection works, but only with two redirections in the form of "command < file > file".
- Funky and unique color scheme!

# Unsuccessful Features
- True multiple direction - only added support for redirection in the format command < file > file
- Multiple pipes
- Keyboard shortcuts, ex. tab, up/down arrows
- Themes/user changing shell color

# Known Bugs
- Other than the stated limitations (see Unsuccessful Features), none... we think.

# Functions
#### 1) char ** remove_nulls(char ** badArr)
- Helper function for parse_arg
- Fixes up the bad array (passed from parse_args)
- Returns a good array (with no null elements)

#### 2) char ** parse_args(char * line)
- Takes a char * line and separates it by spaces into a char * array
- Returns the array

#### 3) char ** sep_cmds(char * line)
- Takes a char * line which contains two commands separated by a semicolon and separates it into a char * array
- Returns the array

#### 4) char * findDir()
- Changes directory
- If successful, returns 0; else, returns 1

#### 5) void execr( char * cmd)
- Takes a char * cmd and separates it, first by semicolon
- Checks if there is any pipe nonsense involved - if so, redirects the command into pipe_cmds
- Then, separates by spaces
- Returns void; prints the results of executing the command

#### 6) void pipe_cmds(char * first_pipe, char * second_pipe)
- Takes a char * first_pipe command and a char * second_pipe command
- Redirects the output from executing first_pipe into the input of second_pipe
- Returns void; prints the results of executing the command

#### 7) void redirect_cmd_file(char * cmd, char * file) 
- Redirects the output of a command into a file (>). Not to be confused with redirect_cmd_file.
- Takes a char * cmd and a char * file. Return type void.
- Prints the results of executing the command.

#### 8) void redirect_file_cmd(char * cmd, char * file) 
- Redirects a file into the input of a command (<). Not to be confused with redirect_cmd_file.
- Takes a char * cmd and a char * file. Return type void.
- Prints the results of executing the command.
- Handles multiple redirects (ex. tr a-z A-Z < wholist > foo)

#### 9) int main()
- Main function: asks for a command, executes the command, and loops. 
- Returns 0
- All of the other functions are in helper_functions.c, with the headers in helper_functions.h
