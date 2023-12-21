#include "shell.h"

/**
 * is_chain - checks a character stored in buffer
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: buffer address
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t ind_b = *p;

	if (buf[ind_b] == '|' && buf[ind_b + 1] == '|')
	{
		buf[ind_b] = 0;
		ind_b++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[ind_b] == '&' && buf[ind_b + 1] == '&')
	{
		buf[ind_b] = 0;
		ind_b++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[ind_b] == ';')
	{
		buf[ind_b] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = ind_b;
	return (1);
}

/**
 * check_chain - test the chaining proccess
 * @info: the parameter struct
 * @buf: the character buff
 * @p: current position address
 * @i: buffer start
 * @length: length of buf
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t length)
{
	size_t ind_buf = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			ind_buf = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			ind_buf = length;
		}
	}

	*p = ind_buf;
}

/**
 * replace_alias - subtitutes the aliases
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_func(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = func_strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - subtitutes vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_func(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(func_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - subtitutes string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
