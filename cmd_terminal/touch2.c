/**
* \file touch2.c
* \brief Create a new file
* \author BERANGER Claire (50%) - TOULAIN Timothe (50%)
* \version 6
* \date 28 march 2019
*
* Program to create new file : Command touch
*
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
/**
* \fn int main(int argc, char** argv)
* \brief Main program to create file
* \param argc directory to create file
* \param argv destination directory (not existing)
* \return int : 0 if create done else return an error
*/
int main (int argc, char **argv){
	struct stat info;

	/* the parameter is mandatory*/
 	if(argc==1){
 		printf("missing parameter\n");
 		exit(1);
 	}
 	else if(argc==2){
 		/* check if the file doesn't already exist*/
		if (stat(argv[1], &info) == -1) {
	  		int fd2 = open(argv[1], O_WRONLY | O_CREAT | O_EXCL,00777);
	  		if(fd2==-1){
	  			perror(argv[1]);
	  			exit(1);
	  		}
	  		close(fd2);
		}
		else{
			printf("file already exists\n");
			exit(1);
		}
	}
	else{
		printf("Error, too many parameters\n");
		exit(1);
	}
  return 0;
}
