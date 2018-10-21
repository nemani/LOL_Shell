
#ifndef HEADER
#define HEADER 

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <pwd.h> 
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <fcntl.h>

#include <time.h>
#include <grp.h>
#include <sys/select.h>
#include <readline/history.h>
#include <readline/readline.h>

char home[1000];    //Home directory, globally declared
char pwd[1000];     //present working directory
char *commands[25]; // Array for ';' commands
char prompt[1000];

// extern char *builtin_function_names[];
// extern int count_of_inbuild_commands;
// extern int (*builtin_function_pointers[]) (int, char **);

void child_exited(int);
int execute(int, int, char **);
int builtin_or_execute(char **);
int read_line();
char** split_commands_into_tokens(char* );
char* printprompt();
char** check_redirect (int, char**);
// int lols_cd (int, char**);
// int lols_pwd (int, char**);
// int lols_echo (int, char**);
int lols_exit (int, char**);
// int lols_ls (int, char**);
// int lols_pinfo (int, char**);
// int lols_nightswatch (int, char**);
void intHandler(int);

#endif
