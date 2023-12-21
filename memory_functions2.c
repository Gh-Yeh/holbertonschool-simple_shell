#include "shell.h"

/**
 * byt_free - frees a pointer
 * @ptr: address of the pointer to free
 * Return: 1 if freed, otherwise 0.
 */
int byt_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
