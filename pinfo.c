#include "lol_shell.h"


int lols_pinfo (int argc, char** args) {

	char procpath[1024];
	char statpath[1024];
	int pid; 
	char status; 
	char name[20];

	printf("pinfo\n");

	strcpy(procpath, "/proc/");

	if(argc > 1){ // if we know the pid
		strcat(procpath, args[1]);
	}
	else{ // else pinfo self
		strcat(procpath, "self");
	}

	strcpy(statpath, procpath);
	strcat(statpath, "/stat");

	FILE *stat = fopen(statpath, "r"); 
	// open stat file of process in read mode
	if( stat == NULL ){ // No stat file found
		perror("lol Shell: ");
		return 0;
	}

	fscanf(stat, "%d (%s) %c", &pid, &name, &status); 

	name[strlen(name) - 1] = '\0'; // removing the last char from name. Couldn't remove the parentheses in fscanf

	fprintf(stdout, "pid: %d\n", pid);
	fprintf(stdout, "Name: %s\n", name);
	fprintf(stdout, "Process Status: %c\n", status);
	
	fclose(stat);

	strcpy(statpath, procpath); 
	strcat(statpath, "/statm");
	// open statm file of process in read mode
	FILE *mem = fopen(statpath, "r");
	
	if(mem == NULL){ // No statm file found
		perror("LOL Shell: ");
		return 0;
	}

	int memsize;

	fscanf(mem, "%d", &memsize);
	fprintf(stdout, "Memory: %d\n", memsize);
	fclose(mem);
	// closing statm
	char exepath[1024];
	
	strcpy(statpath, procpath);
	strcat(statpath, "/exe");

	// procpath/exe is link to the executable
	
	readlink(statpath, exepath, sizeof(exepath));
	
	char relpath[1024];

	if (strlen(exepath) > strlen(home) && strncmp(pwd, home, strlen(home)) == 0){
		strcpy(relpath, "~");
		strcat(relpath, exepath + strlen(home));
	}
	else{
		strcpy(relpath, exepath);
	}
	// clearing exepath
	int i = 0;

	while(exepath[i]){
		exepath[i] = '\0';
		i++;
	}

	fprintf(stdout, "Executable Path: %s\n", relpath);
	return status;
}
