/*
* Determine and display the storage still available for the user
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#define ARRAY_SIZE 80
#define MAXLEN 500

// 800Ko available
const int storage=800000;

//Go through all the directories and files to determine the whole size
void calculateSize(char *dirName, int level, int *currentSize){
	int i;
	DIR *curDir;
	struct stat buf;
	struct dirent *cur;
	char cwd[MAXLEN];
	chdir(dirName);
	getcwd(cwd,MAXLEN);
	curDir=opendir(".");
	if(!curDir){
		perror("opendir failed\n");
		exit(1);
	}
	while(cur=readdir(curDir)){
		lstat(cur->d_name, &buf);
		if((strcmp(cur->d_name,"..")!=0) && (strcmp(cur->d_name,".")!=0)){
			*currentSize=*currentSize+(int)buf.st_size;
		}
		if(S_ISDIR(buf.st_mode)&&strcmp(cur->d_name,".")&& strcmp(cur->d_name,"..")){
			 calculateSize(cur->d_name,level+1,currentSize);
		}
	}
	closedir(curDir);
	chdir("..");
}
int main(){
	char curDir[ARRAY_SIZE];
	getcwd(curDir, ARRAY_SIZE);
	int currentSize=0;
	calculateSize(curDir,0,&currentSize);
	printf("%d/%d Ko used (%d Ko remaining)\n",currentSize,storage,storage-currentSize);
	return 0;
}