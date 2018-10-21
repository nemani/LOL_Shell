#include "lol_shell.h"

// char *builtin_function_names[] = { "nightswatch", "cd", "pwd", "ls", "echo", "exit", "pinfo"};
// int count_of_inbuild_commands = 7;
// int (*builtin_function_pointers[]) (int, char **) = { &lols_nightswatch, &lols_cd, &lols_pwd, &lols_ls, &lols_echo, &lols_exit, &lols_pinfo};

int main(int argc, char const *argv[]){
	getcwd(home, sizeof(home));

	int number_of_commands;
	char **args;
	int status = 1;
	do {
		// printprompt(); // printpromt moved to read_line
		number_of_commands = read_line();
		for (int i = 0; i < number_of_commands; i++){
			args = split_commands_into_tokens(commands[i]);
			status = builtin_or_execute(args);
		}
	} while(status);
	return 0;
}
