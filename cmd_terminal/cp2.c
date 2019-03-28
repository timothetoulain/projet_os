/**
* \file cp2.c
* \brief Copy file
* \author BERANGER Claire (50%) - TOULAIN Timothe (50%)
* \version 6
* \date 28 march 2019
*
* Program to copy file : Command cp
*
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>

/* size of the read/written bloc */
#define BSIZE 512
#define ARRAY_SIZE 255

/**
* \fn int isDirectory(const char *path)
* \brief Determine if a given path is a directory
* \param path 
* \return S_ISDIR(statbuf.st_mode)
*/
int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

/**
* \fn int main(int argc, char** argv)
* \brief Main program to copy file
* \param argc file to copy
* \param argv destination file (not existing)
* \return int : 0 if copy done else return an error
*/
int main(int argc, char** argv) {
	int fd1, fd2; /* file descriptors */
	int count; /* nb of bytes per transfert */
	char buf[BSIZE]; /* transfert buffer */
	char nameFileCopied[ARRAY_SIZE];
	memset(buf,0,BSIZE);
	memset(nameFileCopied,0,ARRAY_SIZE);

	if (argc != 3) { /* incorrect number of parameters */
		fprintf(stderr, "use: %s <source> <dest>\n", *argv);
		return 1;
	}
	fd1 = open(argv[1], O_RDONLY);
	if (fd1==-1) { 
		perror(argv[1]);
		return 2;
	}

	strcpy(nameFileCopied,argv[2]);

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
