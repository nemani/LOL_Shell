#include "lol_shell.h"


int lols_cd (int argc, char** args) {
	if (argc == 1 || strcmp(args[1], "~") == 0){
		chdir(home);
	}
	else{
		int k = chdir(args[1]);
		if (k < 0){
			perror("cd : Error");
		}
	}
	return 1;
}

int lols_pwd (int argc, char** args) {
	printf("%s\n",pwd);
	return 1;
}

int lols_echo (int argc, char** args) {
	for (int i = 1; i < argc; ++i)  {
		printf("%s", args[i]);
	}
	printf("\n");
	return 1;
}

int lols_exit (int argc, char** args) {
	printf("exit\n");
	exit(1);
	return 0;
}

int lols_builtin (int argc, char** args){
	printf("%s", "The following builtins exists in lol_shell");
	for (int i = 0; i < count_of_inbuild_commands; ++i){
		printf("%s ", builtin_function_names[i]);
	}
	printf("\n");
	return 1;
}