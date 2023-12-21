#include "shell.h"

/**
 **_memset - register memory with a constant byte
 *@s: pointer to the memory area
 *@byte: byte that occupy
 *@n: number of bytes to be registered
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char byte, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = byte;
	return (s);
}

/**
 * ffree - frees a pointer to a string
 * @ps: pointer to string
 */
void ffree(char **ps)
{
	char **a = ps;

	if (!ps)
		return;
	while (*ps)
		free(*ps++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to prevoius block
 * @prev_size: size of previous block
 * @new_size: size of new block
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == prev_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
		p[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (p);
}
