#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>

#define BSIZE 512
#define ARRAY_SIZE 255


int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}
int my_cp(char *source, char *destination) {
	int fd1, fd2; /* les descripteurs pour les 2 fichiers */
	int count; /* le nb d’octets par transfert */
	char buf[BSIZE]; /* le buffer de transfert */
	char nameFileCopied[ARRAY_SIZE];
	memset(buf,0,BSIZE);
	memset(nameFileCopied,0,ARRAY_SIZE);

	
	fd1 = open(source, O_RDONLY);
	if (fd1==-1) { /* ouverture source impossible */
		perror(source);
		return 2;
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


/***************************************************************************
* arguments :
* - le fichier source (a copier)
* - un fichier destination (qui ne doit pas deja exister)
*
***************************************************************************/
int main(int argc, char** argv) {
	if (argc != 3) { /* nb incorrect de parametres: erreur */
		fprintf(stderr, "usage: %s <source> <dest>\n", *argv);
		return 1;
	}
	//we save the value of argv[1] because it could be modified in my_cp
	char temp[ARRAY_SIZE];
	strcpy(temp,argv[1]);
	int status=my_cp(argv[1], argv[2]);
	//if the file has been successfully copied, we can delete the source
	if(status==0){
		unlink(temp);
	}
	return 0;
}