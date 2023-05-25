#include "main.h"
/**
 * checkbltin - verify if command is builtin
 * @line: input entered by user
 * @ar: array that can be handled by execve
 * @newline: duplicate of line
 * @array: Tokens to check
 * Return: Return depends upon if the built-in was found
 */
int checkbltin(char *line, char **ar, char *newline, char **array)
{
	int i = 0;

	if (_strcmp(ar[0], "exit") == 0)
	{
		modfree(line, ar, newline, array);
		_exit(errno);
	}
	else if (_strcmp(ar[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			while (*environ[i] != '\0')
				write(1, environ[i], 1), environ[i]++;

			write(1, "\n", 1);
		}
		return (2);
	}
	else if (_strcmp(ar[0], "cd") == 0)
	{
		changedir(ar);
		return (2);
	}
	return (0);
}
/**
 * changedir - changes directory to ar
 * @ar: the directory to change to or nothing
 */
void changedir(char **ar)
{
	char *homeval = ar[1];
	int i = 0;

	if (homeval == NULL)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			if (_strncmp("HOME=", environ[i], 5) == 0)
			{
				homeval = environ[i] + 5;
				break;
			}
		}
	}
	chdir(homeval);
}