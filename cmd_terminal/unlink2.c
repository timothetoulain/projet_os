/* 
* delete a file
* param1: name of the file
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){
	struct stat info;

	/* the parameter is mandatory*/
	if(argc==1){
 		printf("missing parameter\n");
 		exit(1);
 	}
 	else if(argc==2){
 		/* check if the file exists*/
		if (stat(argv[1], &info) ==0) {
	  		int status=unlink(argv[1]);
	  		if(status!=0){
	  			perror("Couldn't delete the file\n");
	  			exit(1);
	  		}
		}
		/*if the file doesn't exist*/
		else{
			perror("Couldn't delete the file\n");
			exit(1);
		}
	}
	else{
		printf("Error, too many parameters\n");
		exit(1);
	}

	return 0; 
} 