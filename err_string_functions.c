#include "shell.h"

/**
 *func_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void func_eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		func_eputchar(str[i]);
		i++;
	}
}

/**
 * func_eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int func_eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * func_putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int func_putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_put_func_sfd - prints an input string
 * @string: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _put_func_sfd(char *string, int fd)
{
	int i = 0;

	if (!string)
		return (0);
	while (*string)
	{
		i += func_putfd(*string++, fd);
	}
	return (i);
}
