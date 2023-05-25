#include "main.h"

/**
 * _puts - print string to terminal
 * @str: string to write
 */

void _puts(char *str)
{
	while (*str  != '\0') 
		write(1, str, 1), str++; 
}

/**
 * print_string - print argument
 * @args: ponter to arg
 *
 * Return: printed char
 */
int print_string(va_list *args)
{
	int x = 0;
	char *ar = va_arg(*args, char *);

	while (*ar != '\0') 
		_putchar(*ar), x++, ar++; 
	return (x);
}

/**
 * _putchar - write char to terminal
 * @c: character to be printed
 *
 * Return: On success 1, -1 on error.
 */
int _putchar(char c)
{
	return (write(2, &c, 1));
}
