#include "shell.h"

/**
 * _myhistory - function to show the history.
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - To unset an alias
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int strret;

	p = func_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	strret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_func(info->alias, str, -1)));
	*p = c;
	return (strret);
}

/**
 * set_alias - To set an alias
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = func_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - display an alias
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *al = NULL;

	if (node)
	{
		p = func_strchr(node->str, '=');
		for (al = node->str; al <= p; al++)
			_putchar(*al);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics an alias.
 * @info: Structure holding arguments.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = func_strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_func(info->alias, info->argv[i], '='));
	}

	return (0);
}
