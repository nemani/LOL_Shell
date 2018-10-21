#include "lol_shell.h"


int read_line(){
	char * a = printprompt();
	char *line = readline(a); 
	
	if (line == NULL){
		// Ctrl+D recieved exiting
		printf("\n");
		return 0;
	}

	add_history (line);

	const char delim[2] = ";";
	int temp = 0;
	commands[temp] = strtok(line, delim); // Breaking line into commands

	while( commands[temp] != NULL )     {
		commands[++temp] = strtok(NULL, delim);
	}

	return temp; // Returning number of commands
}

char** split_commands_into_tokens(char* command){

	int temp = 0;
	ssize_t bufsize = 1024;

	char **tokens = malloc(bufsize * sizeof( char* ));
	char **temp_tokens;

	if (!tokens){
		fprintf(stderr, "LOL SHELL: Memory Allocation Error");
		exit(3);
	}

	tokens[temp] = strtok(command, " \t\r\n\a");    

	while( tokens[temp] != NULL )   {
		tokens[++temp] = strtok(NULL, " \t\r\n\a");
		if (temp >= bufsize){
			bufsize += 1024;
			temp_tokens = tokens;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens) {
				free(temp_tokens);
				fprintf(stderr, "LOL SHELL: Memory Allocation Error");
				exit(3);
			}
		}
	}
	
	tokens[temp] = NULL;
	return tokens;
}
