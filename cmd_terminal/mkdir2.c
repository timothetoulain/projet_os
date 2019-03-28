/**
* \file mkdir2.c
* \brief Create directory
* \author BERANGER Claire (50%) - TOULAIN Timothe (50%)
* \version 6
* \date 28 march 2019
*
* Program to make a new directory : Command mkdir
*
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <errno.h>
/**
* \fn int main(int argc, char** argv)
* \brief Main program to create a new directory
* \param argc name of new directory
* \param argv destination file (not existing)
* \return int : 0 if mkdir done else return an error
*/
int main (int argc, char **argv){
	struct stat info;
	/* the parameter is mandatory*/
 	if(argc==1){
 		printf("missing parameter\n");
 		exit(1);
 	}
 	else if(argc==2){
 		/* check if the directory doesn't already exist*/
		if (stat(argv[1], &info) == -1) {
	  		int status=mkdir(argv[1], 0777);
	  		if(status!=0){
	  			perror("Couldn't create the directory\n");
	  			exit(1);
	  		}
		}
		else{
			printf("directory already exists\n");
			exit(1);
		}
	}
	/* we need only one parameter*/
	else{
		printf("Error, too many parameters\n");
		exit(1);
	}
  return 0;
}
