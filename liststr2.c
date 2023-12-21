#include "shell.h"

/**
 * list_len - get the length of a linked list
 * @ptr: pointer to first node
 * Return: size of list
 */
size_t list_len(const list_t *ptr)
{
	size_t i = 0;

	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings
 * @p_head: pointer to first node
 * Return: array of strings
 */
char **list_to_strings(list_t *p_head)
{
	list_t *node = p_head;
	size_t i = list_len(p_head), j;
	char **arr_s;
	char *str;

	if (!p_head || !i)
		return (NULL);
	arr_s = malloc(sizeof(char *) * (i + 1));
	if (!arr_s)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(arr_s[j]);
			free(arr_s);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		arr_s[i] = str;
	}
	arr_s[i] = NULL;
	return (arr_s);
}


/**
 * print_list - prints linked list elements
 * @ptr_head: pointer to first node
 * Return: size of list
 */
size_t print_list(const list_t *ptr_head)
{
	size_t i = 0;

	while (ptr_head)
	{
		_puts(convert_number(ptr_head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(ptr_head->str ? ptr_head->str : "(nil)");
		_puts("\n");
		ptr_head = ptr_head->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_func - gets a prefix of a node
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_starts_func(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - stores the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
