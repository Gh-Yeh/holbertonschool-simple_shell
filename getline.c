#include "shell.h"

/**
 * input_buf - the buffer input chain
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t rt_inp = 0;
	size_t length_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rt_inp = getline(buf, &length_p, stdin);
#else
		rt_inp = _getline(info, buf, &length_p);
#endif
		if (rt_inp > 0)
		{
			if ((*buf)[rt_inp - 1] == '\n')
			{
				(*buf)[rt_inp - 1] = '\0';
				rt_inp--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = rt_inp;
				info->cmd_buf = buf;
			}
		}
	}
	return (rt_inp);
}

/**
 * get_input - to get a line
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, length;
	ssize_t rt_inp = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	rt_inp = input_buf(info, &buf, &length);
	if (rt_inp == -1)
		return (-1);
	if (length)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, length);
		while (j < length)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (rt_inp);
}

/**
 * read_buf - interpret a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * Return: sizeofbuffer if not NULL
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t size_r = 0;

	if (*i)
		return (0);
	size_r = read(info->readfd, buf, READ_BUF_SIZE);
	if (size_r >= 0)
		*i = size_r;
	return (size_r);
}

/**
 * _getline - hold the next input line
 * @info: parameter struct
 * @ptr: address of pointer to buffer
 * @length: size of ptr
 * Return: size if not NULL
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t siz_k;
	ssize_t rt_size = 0, t_size = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		t_size = *length;
	if (i == len)
		i = len = 0;

	rt_size = read_buf(info, buf, &len);
	if (rt_size == -1 || (rt_size == 0 && len == 0))
		return (-1);

	c = func_strchr(buf + i, '\n');
	siz_k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, t_size, t_size ? t_size + siz_k : siz_k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (t_size)
		_strncat(new_p, buf + i, siz_k - i);
	else
		_strncpy(new_p, buf + i, siz_k - i + 1);

	t_size += siz_k - i;
	i = siz_k;
	p = new_p;

	if (length)
		*length = t_size;
	*ptr = p;
	return (t_size);
}

/**
 * sigintHandler - stops ctrl-c
 * @sig_num: sign number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
