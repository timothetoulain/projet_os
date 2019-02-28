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



int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

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

	tree(source,destination);
}
char tmp_name[ARRAY_SIZE];
void tree(char *dirName, char *destination){
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
			//char conca[ARRAY_SIZE];
			strcat(destination,tmp_name);
			printf("conca desti:%s\n",destination);

			my_cp(cur->d_name,destination);
			printf("(%d) %s\n",(int)buf.st_ino,cur->d_name);
		}
		if(S_ISDIR(buf.st_mode)&&strcmp(cur->d_name,".")&& strcmp(cur->d_name,"..")){
			counter++;
			printf("directory detected\n");
			/*if(counter>1)*/ 
			insertCharPrev(destination);
			strcpy(cur->d_name,tmp_name);
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
