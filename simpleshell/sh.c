#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "sh.h"
#define MAXLINE 128

int sh( int argc, char **argv, char **envp ) {
	char *prompt = calloc(PROMPTMAX, sizeof(char));
	char *commandline = calloc(MAX_CANON, sizeof(char));
	char *command, *arg, *commandpath, *p, *pwd, *owd;
	char **args = calloc(MAXARGS, sizeof(char*));
	int uid, i, status, argsct, go = 1;
	struct passwd *password_entry;
	char *homedir;
	struct pathelement *pathlist;

	char *token;

	uid = getuid();
	password_entry = getpwuid(uid);		/* get passwd info */
	homedir = password_entry->pw_dir;	/* Home directory to start out with*/
		 
	if( (pwd = getcwd(NULL, PATH_MAX+1)) == NULL ) {
		perror("getcwd");
		exit(2);
	}
	owd = calloc(strlen(pwd) + 1, sizeof(char));
	memcpy(owd, pwd, strlen(pwd));
	prompt[0] = ' '; prompt[1] = '\0';

	/* Put PATH into a linked list */
	pathlist = get_path();

	char cmdBuffer[MAXLINE];

	while( go ) {
		/* print your prompt */
		printf("%s>>> ", pwd);

		/* get command line and process */
		fgets(cmdBuffer, MAXLINE, stdin);
		int len = strlen(cmdBuffer);
		cmdBuffer[len - 1] = '\0';

		token = strtok(cmdBuffer, " ");

		int argsIndex = 0;
		while(token != NULL) {
			args[argsIndex] = token;
			argsIndex++;
			token = strtok(NULL, " ");
		}
		args[argsIndex] = NULL;

		/* check for each built in command and implement */

		if(strcmp(args[0], "exit") == 0) { // exit
			go = 0;
		} else if(strcmp(args[0], "which") == 0) { // which
			printf("\n to be implemented \n");
			continue;
		} else if(strcmp(args[0], "where") == 0) { // where
			printf("\n to be implemented \n");
			continue;
		} else if(strcmp(args[0], "cd") == 0) { // cd
			printf("\n to be implemented \n");
			continue;
		} else if(strcmp(args[0], "pwd") == 0) { // pwd
			printf("\n to be implemented \n");
			continue;
		} else if(strcmp(args[0], "ls") == 0) { // list
			list(args);
			continue;
		} else if(strcmp(args[0], "pid") == 0) { // pid
			printf("\n to be implemented \n");
			continue;
		} else if(strcmp(args[0], "kill") == 0) { // kill
			printf("\n to be implemented \n");
			continue;
		} else if(strcmp(args[0], "prompt") == 0) { // prompt 
			printf("\n to be implemented \n");
			continue;
		} else if(strcmp(args[0], "printenv") == 0) { // printenv
			printf("\n to be implemented \n");
			continue;
		} else if(strcmp(args[0], "setenv") == 0) { // setenv
			printf("\n to be implemented \n");
			continue;
		} else {
			/* find it */
			/* do fork(), execve() and waitpid() */

			/*

			pid = fork();
			if (pid == 0) {                 // child
				execve(command, arg, envp);
			} else {                          // parent
				waitpid(pid, NULL, WNOHANG); 
			}

			else
				fprintf(stderr, "%s: Command not found.\n", args[0]);

			*/
		}

		/* else program to exec */
	}
	return 0;
} /* sh() */

char *which(char *command, struct pathelement *pathlist ) {
	 /* loop through pathlist until finding command and return it.  Return
	 NULL when not found. */

} /* which() */

char *where(char *command, struct pathelement *pathlist ) {
	/* similarly loop through finding all locations of command */
} /* where() */

void list(char **args) {
	/* see man page for opendir() and readdir() and print out filenames for
	the directory passed */
	struct dirent *de;  // Pointer for directory entry 

	// opendir() returns a pointer of DIR type.  
	DIR *dr;

	if(args[1] == NULL)
		dr = opendir("."); 
	else
		dr = opendir(args[1]);

	if(dr == NULL) {
		printf("could not open current directory, or it's a file\n");
		return;
	}

	while((de = readdir(dr)) != NULL) 
		printf("%s\n", de->d_name); 

	closedir(dr);
} /* list() */



 