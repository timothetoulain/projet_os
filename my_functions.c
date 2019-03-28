/**
* \file my_functions.c
* \brief Run commands
* \author BERANGER Claire (50%) - TOULAIN Timothe (50%)
* \version 6
* \date 28 march 2019
*
* Program to traduce and run commands of main program
* Commands ls, cp, mkdir, rmdir, touch, unlink, mv, cpdir et size are traduce with analyseInput function
*
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include"my_functions.h"
#define BSIZE 512
#define ARRAY_SIZE 80
#define MAXLEN 500
extern int storage;

/**
* \fn int isDirectory(const char *path)
* \brief Determine if a path is a directory
* \param path 
* \return S_ISDIR(statbuf.st_mode)
*/
int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

/**
* \fn void deleteMultipleSpaces(char *str)
* \brief Replace multiple spaces by a single space
* \param str character string
*/
void deleteMultipleSpaces(char *str){
    char *dest = str;  /* Destination to copy to */

    /* While we're not at the end of the string, loop... */
    while (*str != '\0'){
        /* Loop while the current character is a space, AND the next character is a space */
        while (*str == ' ' && *(str + 1) == ' ')
            str++;  /* Just skip to next character */
       /* Copy from the "source" string to the "destination" string, while advancing to the next character in both */
       *dest++ = *str++;
    }
    /* Make sure the string is properly terminated */    
    *dest = '\0';
}

/**
* \fn int readInput(char *input, int length)
* \brief Read the input on the command line 
* \param input character string contain command name
* \param length int contain length of command name
* \return boolean
*/
int readInput(char *input, int length){
    char *position = NULL;
    // We read on the standard input
    if(fgets(input, length, stdin) != NULL){  
        position = strchr(input, '\n'); // We look for the '\n'
        if(position != NULL){ // If we've found it
            *position = '\0'; // We delete it
        }
        return 0; 
    }
    else{
        return 1; 
    }
}

/**
* \fn void deleteSpaces(char *input)
* \brief Delete the spaces of a string. Can be use to deal more easily with the user's input
* \param input character string contain command name
*/
void deleteSpaces(char *input){
        int i;
		int j = -1;
		for (i = 0; input[i]; i++){
			if (input[i] != ' '){
		    	input[++j] = input[i];
			}
		}
		input[++j] = '\0';
}

/**
* \fn int analyseInput(char *input,char *command, char *argument,char *param1,char *param2, int currentSize)
* \brief Analyse the input
* \param input character string
* \param command character string
* \param argument character string
* \param param1 character string
* \param param2 character string
* \param currentSize int
* \return int if it's 0 the command is launch else a error message is returned in the main program
*/
int analyseInput(char *input,char *command, char *argument,char *param1,char *param2, int currentSize){
	//if we recognise the "ls" command
	if(input[0]=='l' && input[1]=='s'){

		//No second parameter expected
		strcpy(param2,"no param2");
		deleteSpaces(input);
		strcpy(command,"ls2");
		printf("ls analysed\n");
		int len=strlen(input);
		//If there is parameter(s)
		if(len>2){
			if(input[2]=='-' && input[3]=='l'){
				argument[0]='-';
				argument[1]='l';

				//We check if there is another parameter after -l
				if(len==4){
					printf("no path\n");
					param1=NULL;
					return 0;
				}
				else{
					int i,j;
					//We affect the parameter after -l to param1; it's supposed to be a path
					for(i=4,j=0;i<len;j++,i++){
						param1[j]=input[i];
					}
					printf("command: %s\n",command);
					printf("param1: %s\n",param1);
					printf("argument: %s\n",argument);

					//We check if param1 is a directory
					int status=isDirectory(param1);
					if(status!=1){
						//Not a valid path
						return -1;
					}
					else{
						return 0;
					}
				}
			}
			//If there is no argument
			else{
				//argument takes the default value '00'
				argument[0]='0';
				argument[1]='0';
				int len=strlen(input);
				int i,j;
				//param1 takes the value of the parameter, which is supposed to be a path
				for(i=2,j=0;i<len;j++,i++){
					param1[j]=input[i];
				}
				//We check if it's a directory
				int status=isDirectory(param1);
				if(status!=1){
					//Not a valid path
					return -1;
				}
				else{
					printf("command: %s\n",command);
					printf("param1: %s\n",param1);
					printf("argument: %s\n",argument);
					return 0;
				}
			}
		}
		//If there is no argument nor parameter
		else{
			param1=NULL;
			argument[0]='0';
			argument[1]='0';
			return 0;
		}
	}

	//If we detect unlink
	else if(input[0]=='u' && input[1]=='n' && input[2]=='l' && input[3]=='i' && input[4]=='n' && input[5]=='k'){
		//No second parameter expected
		strcpy(param2,"no param2");
		printf("unlink detected\n");
		//There is no argument for this function
		argument[0]='0';
		argument[1]='0';
		deleteSpaces(input);
		strcpy(command,"unlink2");
		int len=strlen(input);
		if(len==6){
			//Not enough parameters
			return -4;
		}
		int i,j;
		//We copy the parameter into param1, which is supposed to be a path or directory name
		for(i=6,j=0;i<len;j++,i++){
			param1[j]=input[i];
		}
		return 0;
	}

	//sizemem detected
	else if(input[0]=='s' && input[1]=='i' && input[2]=='z' && input[3]=='e' 
		&& input[4]=='m' && input[5]=='e'&& input[6]=='m'){
		//No second parameter expected
		strcpy(param2,"no param2");
		printf("sizemem detected\n");
		//There is no argument for this function
		argument[0]='0';
		argument[1]='0';
		deleteSpaces(input);
		strcpy(command,"sizemem");
		int len=strlen(input);
		if(len==7){
			param1=NULL;
			return 0;
		}
		else{
			//Too many parameters
			return -5;
		}
	}

	//If we detect rmdir
	else if(input[0]=='r' && input[1]=='m' && input[2]=='d' && input[3]=='i' && input[4]=='r'){
		//No second parameter expected
		strcpy(param2,"no param2");
		printf("rmdir detected\n");
		//There is no argument for this function
		argument[0]='0';
		argument[1]='0';
		deleteSpaces(input);
		strcpy(command,"rmdir2");
		int len=strlen(input);
		if(len==5){
			//not enough parameters
			return -4;
		}
		int i,j;
		//We copy the parameter into param1, which is supposed to be a path or directory name
		for(i=5,j=0;i<len;j++,i++){
			param1[j]=input[i];
		}
		return 0;
	}

	//If we detect move
	else if(input[0]=='m' && input[1]=='v'){
		
		//There is no argument for this function
		argument[0]='0';
		argument[1]='0';
		deleteMultipleSpaces(input);	

		//strcpy(command,"mv2");
		int len=strlen(input);
		if(len==2){
			//Not enough parameters
			return -4;
		}
		char *sub;
		sub = strtok(input," ");
		sub = strtok(NULL," ");
		strcpy(param1,sub);
		sub = strtok(NULL," ");
		if(sub==NULL){
			//Not enough parameters
			return -4;
		}
		strcpy(param2,sub);

		printf("param1 %s\n",param1);
		printf("param2 %s\n",param2);
		if(isDirectory(param1)){
			printf("dir detected, c++ program\n");
			strcpy(command,"mvdir");
		}
		else{
			strcpy(command,"mv2");
		}	
	
		return 0;
	}


/**************We need to check if storage is available for the following operations*****************/

	//If we detect mkdir
	else if(input[0]=='m' && input[1]=='k' && input[2]=='d' && input[3]=='i' && input[4]=='r'){
		//We need 4096 octets to create a directory
		if(currentSize<=storage-4096){	
			//No second parameter expected
			strcpy(param2,"no param2");
			//There is no argument for this function
			argument[0]='0';
			argument[1]='0';
			deleteSpaces(input);
			strcpy(command,"mkdir2");
			int len=strlen(input);
			if(len==5){
				//Not enough parameters
				return -4;
			}
			int i,j;
			//We copy the parameter into param1, which is supposed to be a path or directory name
			for(i=5,j=0;i<len;j++,i++){
				param1[j]=input[i];
			}
			return 0;
		}
		else{
			return -2;
		}
	}
	
	//If we detect cp
	else if(input[0]=='c' && input[1]=='p'){
		struct stat buf;
		printf("cp detected\n");
		//There is no argument for this function
		argument[0]='0';
		argument[1]='0';
		printf("before %s\n",input);
		deleteMultipleSpaces(input);
		printf("after %s\n",input);
		
		//strcpy(command,"cp2");
		int len=strlen(input);
		if(len==2){
			//Not enough parameters
			return -4;
		}
		char *sub;
		sub = strtok(input," ");
		sub = strtok(NULL," ");
		strcpy(param1,sub);
		sub = strtok(NULL," ");
		if(sub==NULL){
			//Not enough parameters
			return -4;
		}
		strcpy(param2,sub);

		printf("param1 %s\n",param1);
		printf("param2 %s\n",param2);
		if(isDirectory(param1)){
			printf("dir detected, c++ program\n");
			strcpy(command,"cpdir");
		}
		else{
			strcpy(command,"cp2");
		}	

		if(stat(param1,&buf) != 0) { 
		      printf("error!\n" ); 
		      return -3; 
		} 
 
   		printf("size %s= %ld\n",param1,buf.st_size); 
   		//We calculate the size of param1 to know if there is enough space to copy it
   		if(buf.st_size<=storage-currentSize){
			return 0;
   		}
   		else{
   			return -2;
   		}
	
	}

	
	//If we detect touch
	else if(input[0]=='t' && input[1]=='o' && input[2]=='u' && input[3]=='c' && input[4]=='h'){
		//We need at least one octet to create a file
		if(currentSize<=storage-1){	
			strcpy(param2,"no param2");
			printf("touch detected\n");
			//There is no argument for this function
			argument[0]='0';
			argument[1]='0';
			printf("before %s\n",input);
			deleteMultipleSpaces(input);
			printf("after %s\n",input);	

			strcpy(command,"touch2");
			int len=strlen(input);
			if(len==5){
				//Not enough parameters
				return -4;
			}
			deleteSpaces(input);
			int i,j;
			//We copy the parameter into param1, which is supposed to be a path or a file name
			for(i=5,j=0;i<len;j++,i++){
				param1[j]=input[i];
			}
			return 0;
		}
		else{
			return -2;
		}
	}
	//If the input is not a valid command
	else{
		return -6;
	}
}

/**
* \fn void calculateSize(char *dirName, int level, int *currentSize)
* \brief Calcule size of dir recursively
* \param dirName character string
* \param level int
* \param currentSize int
*/
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

