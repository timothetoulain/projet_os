#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
/* la taille des blocs lus/ecrits */
#define BSIZE 512
#define ARRAY_SIZE 255

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

/***************************************************************************
* arguments :
* - le fichier source (a copier)
* - un fichier destination (qui ne doit pas deja exister)
*
***************************************************************************/
int main(int argc, char** argv) {
	int fd1, fd2; /* les descripteurs pour les 2 fichiers */
	int count; /* le nb d’octets par transfert */
	char buf[BSIZE]; /* le buffer de transfert */
	char nameFileCopied[ARRAY_SIZE];
	memset(buf,0,BSIZE);
	memset(nameFileCopied,0,ARRAY_SIZE);

	if (argc != 3) { /* nb incorrect de parametres: erreur */
		fprintf(stderr, "usage: %s <source> <dest>\n", *argv);
		return 1;
	}
	fd1 = open(argv[1], O_RDONLY);
	if (fd1==-1) { /* ouverture source impossible */
		perror(argv[1]);
		return 2;
	}

	strcpy(nameFileCopied,argv[2]);

	if(isDirectory(argv[2])){
		printf("is dir\n");
		if(strstr(argv[2],"../")!=NULL || strstr(argv[2],"./")!=NULL ){
			printf("test\n");
			char *sub;
			char temp[ARRAY_SIZE];
			sub = strtok(argv[1],"/");
			while(sub!=NULL){
				strcpy(temp,sub);
				sub = strtok(NULL,"/");
			}
			printf("fin while: %s\n",temp);
			strcat(nameFileCopied,temp);
		}
		else{
			strcat(nameFileCopied,"/");
			strcat(nameFileCopied,argv[1]);
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