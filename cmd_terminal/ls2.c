/**
* \file ls2.c
* \brief List file
* \author BERANGER Claire (50%) - TOULAIN Timothe (50%)
* \version 6
* \date 28 march 2019
*
* Program to list file : Command ls
*
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include<string.h>
/***************************************************************************
* use: ls2 [-l] [<dir>]
***************************************************************************/
/**
* \fn int main(int argc, char** argv)
* \brief Main program to list file
* \param argc option to list
* \param argv destination file (not existing)
* \return int : 0 if copy done else return an error
*/
int main(int argc, char ** argv) {
	DIR * curDir;
	struct dirent * cur;
	struct stat buf;
	int full = 0;
	if (argc > 1 && !strcmp(argv[1],"-l")) {
		full = 1;
		argc--; argv++;
	}
	/* open the chosen directory */
	if (argc==2) {
		chdir(argv[1]);
	}
	curDir = opendir(".");
	if (!curDir) {
		perror("opening impossible");
		exit(1);
	}
	/* go through the directory */
	while (1) {
		/* get the current entry */
		cur = readdir(curDir);
		/* end of the directory */
		if (!cur) break;

		/* read the attributes of the current file */
		stat(cur->d_name, &buf);
		if (!full) {
		/* display inode and name (and "/" if it's a directory */
			if((strcmp(cur->d_name,"..")!=0) && (strcmp(cur->d_name,".")!=0)){
				printf("(%d) %s",(int)buf.st_ino,cur->d_name);
				if (S_ISDIR(buf.st_mode)) {
					puts("/");
				}
				else putchar('\n');
			}
		} 
		else {
			if((strcmp(cur->d_name,"..")!=0) && (strcmp(cur->d_name,".")!=0)){
				/* display like 'ls -l':
				* type, permission, nb of links, size, name
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
				printf("%3ld %10ld %s\n",buf.st_nlink,(long)buf.st_size,cur->d_name);
			}
		}
	}
	closedir(curDir);
	return 0;
}
