/* delete a file
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
	if(argc==1){
 		printf("missing parameter\n");
 		exit(1);
 	}
 	else if(argc==2){
		if (stat(argv[1], &info) ==0) {
	  		int status=unlink(argv[1]);
	  		if(status!=0){
	  			perror("Couldn't delete the file\n");
	  			exit(1);
	  		}
		}
		else{
			perror("Couldn't delete the file\n");
			printf("file doesn't exist\n");
			exit(1);
		}
	}
	else{
		printf("Error, too many parameters\n");
		exit(1);
	}

	return 0; 
} 