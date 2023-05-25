#include "main.h"
/**
 * _printf - like standard printf
 * @format: string to print with formating
 *
 * Return: printed char count
 */
int _printf(const char *format, ...)
{
	int i = 0, chk = 0, retcount = 0;
	va_list args;
	formating fmtspec[] = {
		{"%", formatMod},
		{"\\", formatMod},
		{NULL, NULL}};

	va_start(args, format);

	while (format != NULL && format[i] != '\0')
	{
		if (format[i] == *(fmtspec[0].ltr))
		{
			chk += fmtspec[0].type(&args, format, i);
			if (chk == -1)
				return (-1);
			retcount += chk;
			i++;
			while (format[i] == ' ')
				i++;
			chk = 1;
		}
		if (!chk)
		{
			_putchar(format[i]);
			retcount++;
		}
		chk = 0;
		i++;
	}

	va_end(args);
	return (retcount);
}

/**
 * formatMod - checks the format modifer
 * @args: argument pointer
 * @format: the string
 * @i: the location of the modifer
 *
 * Return: count of anything printed
 */
int formatMod(va_list *args, const char *format, int i)
{
	int j = 0, x = 0;
	formating fmtmods[] = {
		{"s", print_string},
		{"d", print_digit},
		{"i", print_digit},
		{NULL, NULL}};

	i++;
	if (format[i] == ' ')
		while (format[i] == ' ')
			i++;
	if (format[i] == '%')
	{
		_putchar('%');
		return (1);
	}
	if (format[i] == 'n')
	{
		_putchar('\n');
		return (1);
	}
	while (fmtmods[j].type != NULL && *(fmtmods[j].ltr) != format[i])
		j++;
	if (fmtmods[j].type == NULL)
		return (-1);
	x = fmtmods[j].type(args);
	return (x);
}

/**
 * getdigits - gets digits
 * @n: int to get digits from
 */
void getdigits(int n)
{
	if (n > 0)
		getdigits((n / 10));
	if (n)
		_putchar('0' + (n % 10));
}
/**
 * print_digit - prints digit passed from _printf
 * @args: argument pointer
 *
 * Return: count of digits and signs printed
 */
int print_digit(va_list *args)
{
	int rc = 0, n = va_arg(*args, int), x = n, ld = 1;

	x = (x < 0) ? -x : x;
	while (x > 0)
		x /= 10, rc++;

	if (n < 0)
	{
		_putchar('-'), rc++;
		ld = n % 10;
		n = n / -10;
	}
	else if (n == 0)
	{
		_putchar('0');
		return (rc);
	}
	getdigits(n);
	if (ld < 0)
		_putchar('0' - ld);
	return (rc);
}
