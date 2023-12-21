#include "shell.h"

/**
 * func_erratoi - converts from string to an integer
 * @s: the string to be processed
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int func_erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @info: the parameter and return type
 * @errstr: string containing error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *errstr)
{
	func_eputs(info->fname);
	func_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	func_eputs(": ");
	func_eputs(info->argv[0]);
	func_eputs(": ");
	func_eputs(errstr);
}

/**
 * print_d - function prints a decimal base 10 number
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, counter = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = func_eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			counter++;
		}
		current %= i;
	}
	__putchar('0' + current);
	counter++;

	return (counter);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function that replaces '#' with '\0'
 * @buf: address of the string to be replaced
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
