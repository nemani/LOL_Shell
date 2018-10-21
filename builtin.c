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
	return 0;
}

int lols_pwd (int argc, char** args) {
	printf("%s\n",pwd);
	return 0;
}

int lols_echo (int argc, char** args) {
	for (int i = 1; i < argc; ++i)  {
		printf("%s", args[i]);
	}
	printf("\n");
	return 0;
}

int lols_exit (int argc, char** args) {
	printf("exit\n");
	exit(1);
}

int lols_ls (int argc, char** args) {
	
	DIR *curDir;
	struct dirent* info_archivo;
	struct stat fileStat;
	
	char fullpath[256];
	
	int flag_long = 0;
	int flag_no_hidden = 1;
	int flag_filename = 0;

	for (int i = 1; i < argc; ++i){
		if (strcmp(args[i], "-l") == 0 ){
			flag_long = 1;
		}
		else if (strcmp(args[i], "-a") == 0 ){
			flag_no_hidden = 0;
		}
		else if ( strcmp(args[i], "-la") == 0 || strcmp(args[i], "-al") == 0 ){
			flag_no_hidden = 0;
			flag_long = 1;
		}
		else{
			flag_filename = i;
		}
	}

	if (flag_filename == 0){
		flag_filename = 1;
		args[1] = ".";
	}

	curDir = opendir(args[flag_filename]);

	if (curDir == NULL){
		perror("Error in opening: ");
		printf("filename: %s\n", args[flag_filename]);
		return 0;
	}

	while ((info_archivo = readdir(curDir)) != 0) {
		if (flag_no_hidden && info_archivo->d_name[0] == '.'){
			continue;
		} 
		
		strcpy (fullpath, args[flag_filename]);
		
		strcat (fullpath, "/");
		
		strcat (fullpath, info_archivo->d_name);

		if (flag_long){
			if (!stat(fullpath, &fileStat)) {
				struct passwd* user = getpwuid(fileStat.st_uid);
				struct group* group = getgrgid(fileStat.st_gid);
				time_t now;
				time(&now);
				int year = localtime(&now)->tm_year;
				struct tm* strtime = localtime(&fileStat.st_ctime);
				unsigned char mod[13];

				printf((S_ISDIR(fileStat.st_mode))  ? "d" : "-");
				printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
				printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
				printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
				printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
				printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
				printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
				printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
				printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
				printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
				printf("\t%d\t",(int) fileStat.st_nlink);
				printf("\t%s", user->pw_name);
				printf("\t%s", group->gr_name);
				printf("\t%lld",(long long)fileStat.st_size);
				if(strtime->tm_year == year)
					strftime(mod,13,"%b %e %R",strtime);
				else
					strftime(mod,13,"%b %e %Y",strtime);
				printf("\t%s",mod );        
				printf("\t%s\n",info_archivo->d_name);
			}
			else{
				perror("Error in stat");
			}
		}
		else{
			printf ("%s ", info_archivo->d_name);
		}
		printf("\n");

	}
	closedir(curDir);
	return 0;
}
