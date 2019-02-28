/* delete a directory
* param1: name of the directory
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <errno.h>

int main (int argc, char **argv){
	int res;
	struct stat info;
 	if(argc==1){
 		printf("missing parameter\n");
 		exit(1);
 	}
 	else if(argc==2){
		if (stat(argv[1], &info) == 0) {
			//we check if the mode allows us to delete
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