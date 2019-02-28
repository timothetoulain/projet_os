#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include"my_functions.h"
#define ARRAY_SIZE 80
char dirname[ARRAY_SIZE];
char source[ARRAY_SIZE];
char destination[ARRAY_SIZE];


int main(){
	//create a directory named dirtest
	memset(dirname,0,ARRAY_SIZE);
	strcpy(dirname,"dirtest");
	my_mkdir(dirname);

	//delete a directory named todel
	memset(dirname,0,ARRAY_SIZE);
	strcpy(dirname,"todel");
	my_rmdir(dirname);

	//delete a file named f.txt
	memset(dirname,0,ARRAY_SIZE);
	strcpy(dirname,"f.txt");
	my_unlink(dirname);

	//copy content of file a.txt into file b.txt
	memset(source,0,ARRAY_SIZE);
	memset(destination,0,ARRAY_SIZE);
	strcpy(source,"a.txt");
	strcpy(destination,"b.txt");
	my_cp(source,destination);

	//display information about content of a directory
	my_ls(0,NULL);

	// move/rename a file
	my_move("b.txt","c.txt");
/*
	memset(source,0,ARRAY_SIZE);
	memset(destination,0,ARRAY_SIZE);
	strcpy(source,"dirtest");
	strcpy(destination,"testdirec");
	copy_dir(source,destination);
*/
	
	return 0;
}
