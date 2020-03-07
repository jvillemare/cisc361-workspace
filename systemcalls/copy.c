#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int main(int argc, char *argv[]) {
	int fd1, fd2;
    char buffer[1024];
    struct stat   buf;
    long int n1;

    if (stat(argv[1], &buf) < 0) {
		perror("stat error");
		exit(1);
	}

	if (access(argv[1], W_OK) < 0) {
		printf("W_OK access error for %s\n", argv[1]);
		perror("W_OK");
	} else
		printf("write W_OK access OK\n");

	umask(0); 

    if(((fd1 = open(argv[1], O_RDONLY)) == -1) || 
    	((fd2 = open(argv[2],O_CREAT|O_WRONLY|O_TRUNC, 0700)) == -1)) {
        perror("file problem");
        exit(1);
    }

    while((n1 = read(fd1, buffer, 1024)) > 0) {
        if(write(fd2, buffer, n1) != n1){
            perror("writing problem ");
            exit(3);
        }
    }

    close(fd1);
    close(fd2);

	/*
	struct stat   buf;

	// umask(0);   // UMASK

	printf("copy: %s %s ", argv[1], argv[2]);
	if (stat(argv[1], &buf) < 0) {
		perror("stat error");
		exit(1);
	}
	printf("source mode [%o]\n", buf.st_mode);
	open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, buf.st_mode);
	*/
}