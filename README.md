# Project_1

Shell by Ela Gulsen and Lynne Wang

# Features

Displays current directory, and then prompts for command(s)
Support for all commands, including cd and exit
All commands and arguments can be separated by any number of spaces! Go wild! 
Multiple commands can be separated by a single semicolon (Ex. cd .. ; ls)
Pipe fun! Separate two commands by a pipe and see the input-output switcheroo magic happen before your very eyes! (Ex. ls -l | wc)
Funky and unique color scheme!

# Unsuccessful Features
Could not get redirection to work

# Known Bugs

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

#### 7) int main()
- Main function: asks for a command, executes the command, and loops. 
- Returns 0
- All of the other functions are in helper_functions.c, with the headers in helper_functions.h

