/*create a new directory
* param1: name of the directory
* param2(optionnal):mode
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
		if (stat(argv[1], &info) == -1) {
	  		int status=mkdir(argv[1], 0700);
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
	//TODO:mode est en octal
/*
	else if(argc==3){
		if (stat(argv[1], &info) == -1) {
			printf("%s\n",argv[2]);

			char mode[]=argv[2];
			//memset(mode,0,4);
			//strcpy(mode,argv[2]);
			for(int i=0;i<4;i++){
				printf("i=%d and mode=%c\n",i,mode[i]);
			}
   char *ptr;

			long k = strtol(mode, &ptr, 0);
			printf("k= %ld\n",k);
			int status=mkdir(argv[1], k);
	  		if(status!=0){
	  			perror("Couldn't create the directory\n");
	  		}
			int mode=atoi(argv[2]);
			int tmp=mode;
			int count=0;
			printf("mode= %d\n",mode);

			//count the number of digits
			while(tmp != 0){
        		tmp /= 10;
        		count++;
    		}
    		//if we don't have 3 digits, mode takes the default value 700
    		if(count!=3){
    			printf("incorrect mode indicated, default ->700\n");
    			mode=700;
    		}
    		printf("count=%d\n",count);

			printf("mode= %d\n",mode);
	  		int status=mkdir(argv[1], mode);
	  		if(status!=0){
	  			perror("Couldn't create the directory\n");
	  		}
		}
		else{
			printf("directory already exists\n");
			exit(1);
		}
	}*/


	else{
		printf("Error, too many parameters\n");
		exit(1);
	}
  return 0;
}