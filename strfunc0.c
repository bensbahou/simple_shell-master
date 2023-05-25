#include "main.h"

/**
 * _strcpy - copy string
 * @src: source to copy from
 * @dest: destination to be filled with source content
 * Return: destination pointer
 */
char *_strcpy(char *dest, char *src)
{
	char *p = dest;
	while ((*p++ = *src++))
	{
	}
	return dest;
}

/**
 * _strdup - duplicates string
 * @str: the string to be duplicated
 *
 * Return: pointed to duplicated string
 */
char *_strdup(char *str)
{
	char *ar;
	unsigned int i, size;

	if (str == NULL)
		return (NULL);
	for (size = 0; *(str + size) != '\0'; size++)
		;
	ar = malloc((size + 1) * sizeof(char));
	if (ar == NULL)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		ar[i] = str[i];
	}
	ar[i] = '\0';
	return (ar);
}

/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 *
 * Return: 0 if strings are equal, -1 if not
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
		s1++, s2++;
	return ((*s1 == *s2) ? 0 : -1);
}

/**
 * _strncmp - function to compare strings
 * @s1: first string to compare
 * @s2: second string to compare
 * @len: length of string to compare
 * Return: 0 for success
 */

int _strncmp(char *s1, char *s2, int len)
{
	int i = 0;
	for (i = 0; i < len; i++)
	{
		if (s1[i] != s2[i])
		{
			return -1;
		}
		if (s1[i] == '\0')
		{
			break;
		}
	}
	return 0;
}
/**
 * _strcat - concatenates two strings
 * @dest: the destination string
 * @src: the source string
 *
 * Return: pointer to dest.
 */

char *_strcat(char *dest, char *src)
{
	char *p = dest;
	while (*p)
	{
		p++;
	}
	while (*src)
	{
		*p++ = *src++;
	}
	*p = '\0';
	return dest;
}