#include "lol_shell.h"

char** check_redirect (int argc, char** args){
	int i = 0;
	int in = 0;
	int out_write = 0;
	int out_append = 0;

	for (i = 0; i < argc; ++i){
		if (!strcmp(args[i], "<")){
			in = i;
			args[i] = NULL;
		}
		else if (!strcmp(args[i], ">")){
			out_write = i;
			args[i] = NULL;
		}
		else if (!strcmp(args[i], ">>")){
			out_append = i;
			args[i] = NULL;
		}
	}

	if (in != 0){
		// Redirect for input 
		int fd_input = open(args[in + 1], O_RDONLY,0);

		if(fd_input < 0){
			perror("Could not open the input file");
			return 0;
		}
		
		args[in + 1] = NULL;

		dup2(fd_input, 0);
		close(fd_input);
	}
	
	if (out_write != 0){
		// Redirect for output for writing  
		int fd_write = open(args[out_write + 1],  O_WRONLY| O_TRUNC | O_CREAT, 0644);

		if(fd_write < 0){
			perror("Could not open the output file");
			return 0;
		}
		args[out_write + 1] = NULL;
		
		dup2(fd_write, 1);
		close(fd_write);
	}


	if (out_append != 0){
		// Redirect for output for appending
		int fd_append = open(args[out_append + 1], O_APPEND | O_RDWR | O_CREAT, 0644);

		if(fd_append < 0){
			perror("Could not open the output file");
			return 0;
		}
		args[out_append + 1] = NULL;
		dup2(fd_append, 1);
		close(fd_append);
	}

	return args;
}

