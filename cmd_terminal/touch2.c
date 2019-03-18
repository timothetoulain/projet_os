/*create a new file
* param1: name of the file
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main (int argc, char **argv){
	printf("touch function\n");
	int res;
	struct stat info;
 	if(argc==1){
 		printf("missing parameter\n");
 		exit(1);
 	}
 	else if(argc==2){
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