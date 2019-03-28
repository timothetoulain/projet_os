#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* size of the read/written bloc */
#define BSIZE 512
#define ARRAY_SIZE 255

/* determine if a given path is a directory*/
int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

int my_cp(char *source, char *destination) {
	int fd1, fd2; /* file descriptors */
	int count; /* nb of bytes per transfert */
	char buf[BSIZE]; /* transfert buffer */
	char nameFileCopied[ARRAY_SIZE];
	memset(buf,0,BSIZE);
	memset(nameFileCopied,0,ARRAY_SIZE);

	
	fd1 = open(source, O_RDONLY);
	if (fd1==-1) { 
		perror(source);
		return 2;
	}
	

	strcpy(nameFileCopied,destination);

	/* open the second only if it doesn't already exist */
	fd2 = open(nameFileCopied, O_WRONLY | O_CREAT | O_EXCL,00644);
	if (fd2==-1) { 
		perror(nameFileCopied);
		close(fd1);
		return 3;
	}
	/* read/write by blocs of BSIZE bytes */
	/* we stop at the first incomplete bloc */
	do {
		count = read(fd1,buf, BSIZE);
		write(fd2,buf, count);
	} while (count==BSIZE);
	
	close(fd1);
	close(fd2);
	return 0;
}


/***************************************************************************
* parameters :
* - file to move
* - destination (not existing)
*
***************************************************************************/
int main(int argc, char** argv) {
	if (argc != 3) { /* incorrect number of parameters */
		fprintf(stderr, "use: %s <source> <dest>\n", *argv);
		return 1;
	}
	//we save the value of argv[1] because it could be modified in my_cp
	char temp[ARRAY_SIZE];
	strcpy(temp,argv[1]);
	int status=my_cp(argv[1], argv[2]);
	//if the file has been successfully copied, we can delete the source
	if(status==0){
		unlink(temp);
	}
	return 0;
}