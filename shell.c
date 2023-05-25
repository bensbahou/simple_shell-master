#include "main.h"

/**
 * parsing_input - convert input to token
 * @line: input to be converted
 * @num_tokens: tokens count
 * @argv: argument vector
 * @cmdcount: command count
 * Return: return 0 on success
 */

int parsing_input(char *line, int num_tokens, char **argv, int cmdcount)
{
	int i = 0, bltin, exval = 0;
	char *p = NULL, *newline = NULL, **array = NULL, **ar = NULL;
	char *del = " \t\r\n\f\v";

	array = malloc(sizeof(char *) * num_tokens);
	newline = _strdup(line);
	p = strtok(newline, del);
	if (p == NULL)
	{
		modfree(line, ar, newline, array);
		return (0);
	}
	for (; p != NULL; p = strtok(NULL, del))
		array[i++] = p;
	ar = malloc(sizeof(char *) * (num_tokens + 1));
	for (i = 0; i < num_tokens; i++)
		ar[i] = _strdup(array[i]);
	ar[i] = NULL;
	bltin = checkbltin(line, ar, newline, array);
	if (bltin == 0)
		exval = exe(line, ar, newline, array, argv, cmdcount);
	modfree(line, ar, newline, array);
	return (exval);
}

/**
 * modfree - function to free up memory
 * @line: line to free up
 * @ar: array to free up
 * @newline: line to free up
 * @array: array to free up
 */

void modfree(char *line, char **ar, char *newline, char **array)
{
	int i = 0;

	if (ar != NULL)
		while (ar[i] != NULL)
			free(ar[i++]);
	free(ar);

	if (newline != NULL)
		free(newline);
	if (line != NULL)
		free(line);
	if (array != NULL)
		free(array);
}

/**
 * tokcount - token count to be created
 * @line: data
 * Return: number of tokens to create
 */

int tokcount(char *line)
{
	int num_tokens = 0, i, check = 1;

	for (i = 0; line[i]; i++)
		if (line[i] == ' ' || line[i] == 10 || line[i] == '\t')
			check = 1;
		else if (check == 1)
			check = 0, ++num_tokens;
	return (num_tokens);
}

/**
 * main - the entry of the shell program
 * @argc: argument count
 * @argv: argument vetor
 *
 * Return: 0 if the program exits properly
 */

int main(int argc, char *argv[])
{
	size_t bufsize = 0;
	char *line = NULL;
	int i, num_tokens = 0, cmdcount = 1, shell_interaction;

	signal(SIGINT, SIG_IGN);
	shell_interaction = isatty(STDIN_FILENO);
	if (shell_interaction == 0 && argc == 1)
	{
		while (getline(&line, &bufsize, stdin) > 0)
		{
			num_tokens = tokcount(line);
			parsing_input(line, num_tokens, argv, cmdcount);
			line = NULL;
		}
		free(line);
		return (0);
	}
	while (shell_interaction)
	{
		write(1, ">> ", 4);
		num_tokens = 0;
		i = getline(&line, &bufsize, stdin);
		if (i < 0)
		{
			free(line);
			write(1, "\n", 1);
			break;
		}
		num_tokens = tokcount(line);
		parsing_input(line, num_tokens, argv, cmdcount);
		cmdcount++;
		line = NULL;
	}
	return (0);
}
