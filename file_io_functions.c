#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 * Return: string if success
 */

char *get_history_file(info_t *info)
{
	char *buf, *env_dir;

	env_dir = _getenv(info, "HOME=");
	if (!env_dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(env_dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, env_dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - intialize or append a file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_put_func_sfd(node->str, fd);
		func_putfd('\n', fd);
	}
	func_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - gets the history from a file
 * @info: the parameter struct
 * Return: history number on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, his_count = 0;
	ssize_t fd, readlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	readlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (readlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, his_count++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, his_count++);
	free(buf);
	info->histcount = his_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - hisory linked lists entry point
 * @info: Structure holding arguments
 * @buf: buffer
 * @his_count: the history linecount.
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int his_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, his_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - edit the history linked list anumber
 * @info: Structure holding arguments
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
