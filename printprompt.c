#include "lol_shell.h"


char* printprompt() {
	// Get UID of user
	int uid = getuid();
	
	// Get data about current User
	struct passwd *currUser = getpwuid(uid);
	
	// Get Name of current User
	char *name = currUser -> pw_name;
	
	//Get the hostname
	char hostname[31];
	gethostname(hostname, 30);

	char ret[1000];
	char ret2[1000];

	sprintf(ret, "<\e[96m%s\e[39m@\e[95m%s\e[39m:\e[96m", name, hostname);

	// Get Current Working Directory
	getcwd(pwd, sizeof(pwd));
	
	if (strcmp(pwd, home) == 0){
		strcat(ret, "~>\e[39m");
	}
	else {

		if (strlen(pwd) > strlen(home) && strncmp(pwd, home, strlen(home)) == 0){
			sprintf(ret2, "~%s>\e[39m",pwd + strlen(home));
			strcat(ret, ret2);
		}
		else{
			sprintf(ret2, "%s>\e[39m", pwd);
			strcat(ret, ret2);
		}
	}
	// printf("%s", ret);
	strcpy(prompt, ret);
	return prompt;
} 
