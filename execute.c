#include "lol_shell.h"


void child_exited(int num){

	pid_t wpid;
	int status;

	wpid = waitpid(-1, &status, WNOHANG);

	if(wpid > 0 && WIFEXITED(status)==0){
		printf("\nProcess with pid %d exited normally\n", wpid);
	}
	if(wpid > 0 && WIFSIGNALED(status)==0){
		printf("\nProcess with pid %d exited due to a user-defined signal\n", wpid);
	}
}


int execute(int redirect, int argc, char **args){

	pid_t pid;
	int status;
	int background_flag = 0;

	if (strcmp(args[argc - 1], "&")==0){
		background_flag = 1;
		argc--;
		args[argc] = NULL; 
	}

	pid = fork();

	if (pid == 0) {
	// Child
		
		if(background_flag){
			setpgid(0, 0);
		}
		if (redirect){
			args = check_redirect(argc, args);
		}
		int temp = execvp(args[0], args);

		if (temp == -1) {
			perror("lol shell: Error Executing >");
		}

		exit(EXIT_FAILURE);

	}
	else if (pid < 0) {
	// Error
		perror("lol shell: Error, cant create fork");
	}
	else {
	// Parent
		if (!background_flag){
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
		else{ // Background process
			signal(SIGCHLD, child_exited);
		}
	}
	return 1;
}

int builtin_or_execute(char **args){
	int argc = 0; // Number of Arguments
	int redirect = 0;

	while (args[argc] != NULL){
		if (!strcmp(args[argc], "<") || !strcmp(args[argc], ">") || !strcmp(args[argc], ">>")){
			redirect = argc;
		}
		argc++;
	}

	if (argc == 0){
		printf("\n");
		return 1;
	}

	// char* main_command = args[0];
	// int i = 0;

	// for (i = 0; i < count_of_inbuild_commands; ++i){
	// 	if (strcmp(main_command, builtin_function_names[i]) == 0){ // if main_command is in builtin command list
	// 		return (*builtin_function_pointers[i])(argc, args); // Call the builtin function
	// 	}
	// }

	return execute(redirect, argc, args);
}
