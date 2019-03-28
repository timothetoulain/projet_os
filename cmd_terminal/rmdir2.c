/**
* \file rmdir2.c
* \brief Remove directory
* \author BERANGER Claire (50%) - TOULAIN Timothe (50%)
* \version 6
* \date 28 march 2019
*
* Program to remove directory : Command rmdir
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
* \brief Main program to remove directory
* \param argc directory to remove
* \param argv destination directory (not existing)
* \return int : 0 if remove done else return an error
*/
int main (int argc, char **argv){
	struct stat info;
	/* the parameter is mandatory*/
 	if(argc==1){
 		printf("missing parameter\n");
 		exit(1);
 	}
 	else if(argc==2){
 		/* check if the directory exists*/
		if (stat(argv[1], &info) == 0) {
			/* check if the mode allows us to delete*/
			char mode[1];
			mode[0]=((info.st_mode & S_IWUSR) ? '-' : 'w');
			if(strcmp(mode,"-")==0){
				int status=rmdir(argv[1]);
		  		if(status!=0){
		  			perror("Couldn't remove the directory\n");
		  			exit(1);
		  		}
			}
			else{
				printf("permission denied\n");
				exit(1);
			}
		}
		else{
			printf("directory doesn't exist\n");
			exit(1);
		}
	}

	else{
		printf("Error, too many parameters\n");
		exit(1);
	}
  return 0;
}
