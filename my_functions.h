#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>

void copy_dir(char *source, char *destination);
void insertCharPrev(char *buf);
void insertCharSlash(char *buf);
int isDirectory(const char *path);

void deleteNCar(char *destination,int lenDest,int len);
int analyseInput(char *input,char *command, char *argument,char *param1,char *param2, int currentSize);
void deleteSpaces(char *input);
int readInput(char *input, int length);
void deleteMultipleSpaces(char *str);
void calculateSize(char *dirName, int level, int *currentSize);





