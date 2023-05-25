#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <stdarg.h>
#include <errno.h>

extern char **environ;

/**
 * struct formating - types of data and their function
 * @ltr: data type
 * @type: pointer to data type
 */

typedef struct formating
{
	char *ltr;
	int (*type)();
} formating;

char *_strdup(char *);
char *_strcat(char *, char *);
int _strcmp(char *, char *);
int _strncmp(char *, char *, int);
char *_strcpy(char *, char *);

int _printf(const char *, ...); 

int parsing_input(char *, int, char *[], int);
int exe(char *, char **, char *, char **, char **, int);
void modfree(char *, char **, char *, char **);
int checkbltin(char *, char **, char *, char **);
int tokcount(char *);
int findpath(char *, char **);
int findonpath(char **);
void exepath(char *, char **);
int formatMod(va_list *, const char *, int);
int print_string(va_list *);
int print_digit(va_list *);
void getdigits(int);
void changedir(char **);

#endif
