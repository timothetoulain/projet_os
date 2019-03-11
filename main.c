#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include <sys/wait.h>
#include"my_functions.h"
#define ARRAY_SIZE 255
//The constant PATH is the path to the directory where the functions are
#define PATH "cmd_terminal/"
//#define PATH "/bin/test/"


int main(){
	char argument[3];
	char param1[ARRAY_SIZE];
	char param2[ARRAY_SIZE];
	char command[ARRAY_SIZE];
	char path[ARRAY_SIZE];
	char input[ARRAY_SIZE];

	while(1){
		memset(input,0,ARRAY_SIZE);
		memset(command,0,ARRAY_SIZE);
		memset(param1,0,ARRAY_SIZE);
		memset(param2,0,ARRAY_SIZE);
		memset(argument,0,3);
		memset(path,0,ARRAY_SIZE);

		strcpy(path,PATH);
		//We read the user's input
		readInput(input,ARRAY_SIZE);
		
		//q is the command to quit the program
		if(strcmp(input,"q")==0){
			printf("Exit the program\n");
			return 0;
		}
		else{
			
		    //If the input is a valid command
		    if(analyseInput(input,command,argument,param1,param2)==0){
				
				strcat(path,command);
				//path contains the path to the directory that contains the functions
				//We need it to call the function execlp

				//We create a child process that will execute the command
				pid_t pid;
				switch(pid=fork()){
					case -1: perror("fork failed");exit(1);
					case 0: 
					//If the function only has 1 parameter (ls,mkdir)
					if(strcmp(param2,"no param2")==0){
						//if there is no argument
						if(strcmp(argument,"00")==0){
							execlp(path,command,param1,NULL);
						}
						else{
							execlp(path,command,argument,param1,NULL);
						}
					}
					//If the function has 2 parameters (cp)
					else{
						execlp(path,command,param1,param2,NULL);
					}
					exit(0);
				}
			}
			else{
				printf("Unknown command\n");
			}
		}
	}
	return 0;
}