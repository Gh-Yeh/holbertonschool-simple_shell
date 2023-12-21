#include "shell.h"

/**
 * **func_strtow - divides a string into segments.
 * @string_str: the input string
 * @delim: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **func_strtow(char *string_str, char *delim)
{
	int i, j, k, m, numberword = 0;
	char **s;

	if (string_str == NULL || string_str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; string_str[i] != '\0'; i++)
		if (!is_delim(string_str[i], delim) &&
		(is_delim(string_str[i + 1], delim) || !string_str[i + 1]))
			numberword++;

	if (numberword == 0)
		return (NULL);
	s = malloc((1 + numberword) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numberword; j++)
	{
		while (is_delim(string_str[i], delim))
			i++;
		k = 0;
		while (!is_delim(string_str[i + k], delim) && string_str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = string_str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

