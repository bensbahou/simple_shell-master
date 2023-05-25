#include "main.h"

/**
 * exe - run new process
 * @line: data input
 * @ar: data to be executed by execve
 * @nln: duplicate of line
 * @arry: Tokens to check
 * @argv: arguments
 * @flcnt: failed command count
 * Return: 0 for success
 */

int exe(char *line, char **ar, char *nln, char **arry, char **argv, int flcnt)
{
	int status, onpath = -1;
	pid_t child;
	struct stat *statbuf;

	statbuf = malloc(sizeof(struct stat));
	if (stat(ar[0], statbuf) == -1)
	{
		onpath = findonpath(ar);
		if (onpath == 0)
		{
			free(statbuf);
			return (0);
		}
	}
	child = fork();
	if (child == 0)
	{
		if (execve(ar[0], ar, environ) == -1)
		{
			_printf("%s: %d: %s: not found\n", argv[0], flcnt, ar[0]);
			free(statbuf);
			modfree(line, ar, nln, arry);
			_exit(-1);
		}
	}
	else
		while (waitpid(-1, &status, 0) != child)
			;
	free(statbuf);
	errno = status == 0 ? 0 : status == 512 ? 2
						  : status == 65280 ? 127
											: errno;
	return (0);
}

/**
 * exepath - handle the PATH
 * @p: PATH dir
 * @tokens: tokens to look
 */
void exepath(char *p, char **tokens)
{
	int status, len = 0, len2 = 0;
	pid_t child;
	char *newp = NULL;

	while (*(p + len) != '\0')
		len++;
	while (tokens[0][len2] != '\0')
		len2++;
	newp = malloc(sizeof(char) * (len + len2 + 2));
	_strcpy(newp, p);
	_strcat(newp, "/");
	_strcat(newp, tokens[0]);
	newp[(len + len2 + 1)] = '\0';

	child = fork();

	if (child == 0)
	{
		if (access(newp, X_OK) == 0)
			execve(newp, tokens, environ);
	}
	else
		while (waitpid(-1, &status, 0) != child)
			;
	errno = (status == 0) ? 0 : errno;
	free(newp);
}

/**
 * findpath - function to search PATH
 * @p: part of PATH to search
 * @tokens: array of tokens
 * Return: 0 for success
 */

int findpath(char *p, char **tokens)
{
	struct dirent *de;
	int reached = 0, onpath = -1;

	p = strtok(p, ":");
	while (p != NULL && reached != 1)
	{
		DIR *dr = opendir(p);

		if (dr == NULL)
			return (0);
		while ((de = readdir(dr)) != NULL)
			if (_strcmp(de->d_name, tokens[0]) == 0)
			{
				exepath(p, tokens);
				onpath = 0;
				reached = 1;
				break;
			}

		closedir(dr);
		p = (reached == 0) ? strtok(NULL, ":") : p;
	}
	return (onpath);
}

/**
 * findonpath - find PATH in environ
 * @tokens: token to pass along to PATH
 * Return: 0 for success
 */

int findonpath(char **tokens)
{
	int i = 0, onpath;
	char *p = NULL, *path = NULL;

	for (i = 0; environ[i] != NULL; i++)
		if (_strncmp("PATH=", environ[i], 5) == 0)
		{
			path = _strdup(environ[i]);
			strtok(path, "=");
			p = strtok(NULL, "=");
			onpath = findpath(p, tokens);
			break;
		}

	free(path);
	return (onpath);
}
