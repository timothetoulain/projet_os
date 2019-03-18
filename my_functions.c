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


//Determine if a path is a directory
int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

//Replace multiple spaces by a single space
void deleteMultipleSpaces(char *str){
    char *dest = str;  /* Destination to copy to */

    /* While we're not at the end of the string, loop... */
    while (*str != '\0'){
        /* Loop while the current character is a space, AND the next
         * character is a space
         */
        while (*str == ' ' && *(str + 1) == ' ')
            str++;  /* Just skip to next character */
       /* Copy from the "source" string to the "destination" string,
        * while advancing to the next character in both
        */
       *dest++ = *str++;
    }
    /* Make sure the string is properly terminated */    
    *dest = '\0';
}

//Read the input on the command line 
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
//Delete the spaces of a string
//Can be use to deal more easily with the user's input
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

//Analyse the input
int analyseInput(char *input,char *command, char *argument,char *param1,char *param2){
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
						printf("not a valid path -l\n");
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
					printf("not a valid path\n");
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
			printf("not enough param\n");
			//param1=NULL;
			return -1;
		}
		int i,j;
		//We copy the parameter into param1, which is supposed to be a path or directory name
		for(i=6,j=0;i<len;j++,i++){
			param1[j]=input[i];
		}
		return 0;
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
			printf("not enough param\n");
			//param1=NULL;
			return -1;
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
		
		printf("move detected\n");
		//There is no argument for this function
		argument[0]='0';
		argument[1]='0';
		printf("before %s\n",input);
		deleteMultipleSpaces(input);
		printf("after %s\n",input);	

		strcpy(command,"mv2");
		int len=strlen(input);
		if(len==2){
			printf("not enough param\n");
			return -1;
		}
		char *sub;
		sub = strtok(input," ");
		sub = strtok(NULL," ");
		strcpy(param1,sub);
		sub = strtok(NULL," ");
		if(sub==NULL){
			printf("null arg2\n");
			return -1;
		}
		strcpy(param2,sub);

		printf("param1 %s\n",param1);
		printf("param2 %s\n",param2);
	
		return 0;
	}

//TODO
/**************Check if storage is available******************/
	//If we detect mkdir
	else if(input[0]=='m' && input[1]=='k' && input[2]=='d' && input[3]=='i' && input[4]=='r'){
		//No second parameter expected
		strcpy(param2,"no param2");
		printf("mkdir detected\n");
		//There is no argument for this function
		argument[0]='0';
		argument[1]='0';
		deleteSpaces(input);
		strcpy(command,"mkdir2");
		int len=strlen(input);
		if(len==5){
			printf("not enough param\n");
			//param1=NULL;
			return -1;
		}
		int i,j;
		//We copy the parameter into param1, which is supposed to be a path or directory name
		for(i=5,j=0;i<len;j++,i++){
			param1[j]=input[i];
		}
		return 0;
	}
	
	//If we detect cp
	else if(input[0]=='c' && input[1]=='p'){
		
		printf("cp detected\n");
		//There is no argument for this function
		argument[0]='0';
		argument[1]='0';
		printf("before %s\n",input);
		deleteMultipleSpaces(input);
		printf("after %s\n",input);

		

		strcpy(command,"cp2");
		int len=strlen(input);
		if(len==2){
			printf("not enough param\n");
			return -1;
		}
		char *sub;
		sub = strtok(input," ");
		sub = strtok(NULL," ");
		strcpy(param1,sub);
		sub = strtok(NULL," ");
		if(sub==NULL){
			printf("null arg2\n");
			return -1;
		}
		strcpy(param2,sub);

		printf("param1 %s\n",param1);
		printf("param2 %s\n",param2);

	
		return 0;
	}

	
	//If we detect touch
	else if(input[0]=='t' && input[1]=='o' && input[2]=='u' && input[3]=='c' && input[4]=='h'){
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
			printf("not enough param\n");
			return -1;
		}
		deleteSpaces(input);
		int i,j;
		//We copy the parameter into param1, which is supposed to be a path or a file name
		for(i=5,j=0;i<len;j++,i++){
			param1[j]=input[i];
		}
		return 0;
	}
	//If the input is not a valid command
	else{
		return -1;
	}
}














/************************ The functions below are meant to be used in C program, not on the command line****************/


/* delete a file
* param1: name of the file
*/
void my_unlink(char *filename){
	struct stat info;
	if (stat(filename, &info) ==0) {
  		int status=unlink(filename);
  		if(status!=0){
  			perror(filename);
  			return;
  		}
	}
	else{
		perror(filename);
		return;
	}
} 

/* delete a directory
* param1: name of the directory
*/
void my_rmdir (char *filename){
	int res;
	struct stat info;
	if (stat(filename, &info) == 0) {
		//we check if the mode allows us to delete
		char mode[1];
		mode[0]=((info.st_mode & S_IWUSR) ? '-' : 'w');
		if(strcmp(mode,"-")==0){
			int status=rmdir(filename);
	  		if(status!=0){
	  			perror("Couldn't remove the directory\n");
	  			return;
	  		}
		}
		else{
			perror("permission denied\n");
			return;
		}
	}
	else{
		perror(filename);
		return;
	}
}


/*create a new directory
* param1: name of the directory
*/
void my_mkdir(char *dirname){
	int res;
	struct stat info;
 		
	if (stat(dirname, &info) == -1) {
  		int status=mkdir(dirname, 0700);
  		if(status!=0){
  			perror(dirname);
  			return;
  		}
	}
	else{
		printf("Directory already exists\n");
		return;
	}
}

/*copy content from a file  into another non existing*/
int my_cp(char *source, char *destination) {
	int fd1, fd2; /* descriptors for the files */
	int count; /* nb of octets by transfert */
	char buf[BSIZE]; /* transfert buffer */
	char nameFileCopied[ARRAY_SIZE];
	memset(buf,0,BSIZE);
	memset(nameFileCopied,0,ARRAY_SIZE);
	
	fd1 = open(source, O_RDONLY);
	if (fd1==-1) { /* impossible to open source */
		perror(source);
		return 1;
	}
	strcpy(nameFileCopied,destination);

	if(isDirectory(destination)){
		printf("is dir\n");
		if(strstr(destination,"../")!=NULL || strstr(destination,"./")!=NULL ){
			printf("test\n");
			char *sub;
			char temp[ARRAY_SIZE];
			sub = strtok(source,"/");
			while(sub!=NULL){
				strcpy(temp,sub);
				sub = strtok(NULL,"/");
			}
			printf("fin while: %s\n",temp);
			strcat(nameFileCopied,temp);
		}
		else{
			strcat(nameFileCopied,"/");
			strcat(nameFileCopied,source);
		}
	}
	printf("file: %s\n",nameFileCopied);

	/* ouverture second fichier ssi il n’existe pas */
	fd2 = open(nameFileCopied, O_WRONLY | O_CREAT | O_EXCL,00644);
	if (fd2==-1) { /* ouverture destination impossible */
		perror(nameFileCopied);
		close(fd1);
		return 3;
	}
	/* lecture/ecriture par blocs de BSIZE octets */
	/* on s’arrete au premier bloc incomplet (EOF de source) */
	do {
		count = read(fd1,buf, BSIZE);
		write(fd2,buf, count);
	} while (count==BSIZE);
	
	/* fermeture des deux fichiers */
	close(fd1);
	close(fd2);
	return 0;
}

/*display information on file and directory
*param1: indicates if we want a long listing format: 0 for no, 1 for yes
*		(same than ls -l)
*param2: path of the directory to explore: can be NULL
*/
void my_ls(int l, char *path) {
	DIR * curDir;
	struct dirent * cur;
	struct stat buf;
	int full = 0;
	if (l== 1 ) {
		full = 1;
	}
	/* opening of the chosen directory */
	if (path!=NULL) {
		chdir(path);
	}
	curDir = opendir(".");
	if (!curDir) {
		perror("impossible to open");
		
		return;
	}
	/* browse the entries of the directory */
	while (1) {
		/* get entry of the current directory */
		cur = readdir(curDir);
		/* end of the directory, we quit */
		if (!cur) break;

		/* read attributs of the current file */
		stat(cur->d_name, &buf);
		if (!full) {
		/* display inode,name (and "/" if it's a directory */
			printf("(%d) %s",(int)buf.st_ino,cur->d_name);
			if (S_ISDIR(buf.st_mode)) {
				puts("/");
			}
			else putchar('\n');
		} 
		else {
			/* display like 'ls -l'
			* type, permissions, nb links, size, name
			*/
			printf("%c%c%c%c%c%c%c%c%c%c ",
			S_ISDIR(buf.st_mode) ?  'd' : '-',
			buf.st_mode & S_IRUSR ? 'r' : '-',
			buf.st_mode & S_IWUSR ? 'w' : '-',
			buf.st_mode & S_IXUSR ? 'x' : '-',
			buf.st_mode & S_IRGRP ? 'r' : '-',
			buf.st_mode & S_IWGRP ? 'w' : '-',
			buf.st_mode & S_IXGRP ? 'x' : '-',
			buf.st_mode & S_IROTH ? 'r' : '-',
			buf.st_mode & S_IWOTH ? 'w' : '-',
			buf.st_mode & S_IXOTH ? 'x' : '-');
			printf("%3ld %10ld %s\n",
			buf.st_nlink,
			(long)buf.st_size,
			cur->d_name);
		}
	}
	closedir(curDir);
}

/* move or rename a file
* param1: name of file to move/rename
* param2: new name for the file or destination
*/
void my_move(char *filename,char *destination){
	char temp[ARRAY_SIZE];
	strcpy(temp,filename);
	int status=my_cp(filename, destination);
	if(status==0){
		unlink(temp);
	}
}




//attempt do program "copy directory" function
//not working

int MAXLEN=15;
int INDENT=3;
void copy_dir(char *source, char *destination){
	my_mkdir(destination);
	char my_cwd[ARRAY_SIZE];
	strcpy(my_cwd,getcwd(my_cwd, sizeof(my_cwd)));
	insertCharSlash(destination);
	strcat(my_cwd,destination);
	tree(source,my_cwd);
}
char tmp_name[ARRAY_SIZE];
char *sub;
char tmp_desti[ARRAY_SIZE];

void tree(char *dirName, char *destination){
	printf("destination debut: %s\n",destination);
	memset(tmp_name,0,ARRAY_SIZE);
	int counter =0;
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
	//printf("we are in %s\n",strcmp(dirName,".")?dirName:cwd);
	while(cur=readdir(curDir)){
		lstat(cur->d_name, &buf);

		/* display inode,name (and "/" if it's a directory */
		if(!S_ISDIR(buf.st_mode)){
			strcpy(tmp_name,cur->d_name);
			
			insertCharSlash(tmp_name);

			int len=strlen(tmp_name);
			strcat(destination,tmp_name);
			printf("conca desti:%s\n",destination);
			int lenDest=strlen(destination);
			my_cp(cur->d_name,destination);
			deleteNCar(destination,lenDest,len);
			
		}
		if(S_ISDIR(buf.st_mode)&&strcmp(cur->d_name,".")&& strcmp(cur->d_name,"..")){
			memset(tmp_name,0,ARRAY_SIZE);
			memset(tmp_desti,0,ARRAY_SIZE);

			//counter++;
			printf("directory detected\n");
				strcpy(tmp_name,destination);
				strcpy(tmp_desti,cur->d_name);

				insertCharSlash(tmp_desti);
				strcat(tmp_name,tmp_desti);
				printf("makedir %s\n",tmp_name);
				my_mkdir(tmp_name);

			/*if(counter>1)*/ 
			//insertCharPrev(destination);
			//strcpy(cur->d_name,tmp_name);
			printf("bef recursion: %s   %s\n",cur->d_name,destination);
			tree(cur->d_name,destination);
			/*insertCharSlash(tmp_name);
			strcat(destination,tmp_name);
			tree(cur->d_name,destination);*/
		}
	}
	closedir(curDir);
	chdir("..");
}
void insertCharPrev(char *buf){
	printf("before %s\n",buf);
	int i, j=0;
	for(i=0;i<3;i++){
		for(int j=ARRAY_SIZE-2;j>=0;j--){
			buf[j+1]=buf[j];
		}
	}
	buf[0]='.';
	buf[1]='.';
	buf[2]='/';

	printf("after %s\n",buf);
}

void insertCharSlash(char *buf){
	printf("before slash %s\n",buf);
	int i, j=0;
		for(int j=ARRAY_SIZE-2;j>=0;j--){
			buf[j+1]=buf[j];
		}
	buf[0]='/';

	printf("after slash %s\n",buf);
}
void deleteNCar(char *destination,int lenDest,int len){
	int i;
	printf("before delete %s\n",destination);
	for(i=lenDest;i>=lenDest-len;i--){
		destination[i]='\0';

	} 
	printf("after delete %s\n",destination);

}
