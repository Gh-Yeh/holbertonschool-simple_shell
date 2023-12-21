#include "shell.h"

/**
 * get_environ - returns array of string
 * @info: Structure holding arguments.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - delete an environment variable
 * @info: Structure holding potential arguments
 * @varb: string environ variable
 *  Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *varb)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !varb)
		return (0);

	while (node)
	{
		p = starts_with(node->str, varb);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Creates a new environment variable
 * @info: Structure holding arguments
 * @varb: string environ variable
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *varb, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!varb || !value)
		return (0);

	buf = malloc(_strlen(varb) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, varb);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, varb);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}