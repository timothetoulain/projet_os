/****************************************************************************
*
* $Id: ls2.c 1897 2010-11-18 09:57:58Z phil $
* Ecriture d’une commande "ls" simplifiee
* Principe:
* - opendir() permet d’obtenir une reference sur le repertoire choisi
* (ici ".")
* - readdir() va permettre de naviguer dans le repertoire, chaque appel
45
* renvoyant une reference sur l’entree suivante
* - pour chaque entree, stat() permet de lire les informations du
* fichier courant.
* Dans cette version,
* - on ne prend le repertoire courant que par defaut.
* - integration d’une option "-l" proche de celle de "ls"
*
****************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include<string.h>
/***************************************************************************
* usage: ls2 [-l] [<dir>]
***************************************************************************/
int main(int argc, char ** argv) {
	DIR * curDir;
	struct dirent * cur;
	struct stat buf;
	int full = 0;
	if (argc > 1 && !strcmp(argv[1],"-l")) {
		full = 1;
		argc--; argv++;
		//l
	}
	/* ouverture du repertoire choisi */
	if (argc==2) {
		//chemin
		chdir(argv[1]);
	}
	curDir = opendir(".");
	if (!curDir) {
		perror("ouverture impossible");
		exit(1);
	}
	/* parcours des entrees de ce repertoire */
	while (1) {
		/* obtention de l’entree de repertoire courante */
		cur = readdir(curDir);
		/* fin de repertoire: on quitte */
		if (!cur) break;

		/* lecture des attributs du fichier courant */
		stat(cur->d_name, &buf);
		if (!full) {
		/* affichage de l’inode, du nom (et de "/" si c’est un repertoire */
			printf("(%d) %s",(int)buf.st_ino,cur->d_name);
			if (S_ISDIR(buf.st_mode)) {
				puts("/");
			}
			else putchar('\n');
		} 
		else {
			/* affichage ’a la ls -l’:
			* type, droits, nb de liens, taille, nom
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
	return 0;
}