#include "shell.h"

/**
 * **strtow -  It splits a string in 2 words, repeated delimiters ignored
 * @str: The string input
 * @d:  Delimeter string
 * Return: a NULL on failure, or pointer to an array of strings
 */

char **strtow(char *str, char *d)
{
	int a, b, c, n, wordnum = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			wordnum++;

	if (wordnum == 0)
		return (NULL);
	s = malloc((1 + wordnum) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < wordnum ; b++)
	{
		while (is_delim(str[a], d))
			a++;
		c = 0;
		while (!is_delim(str[a + c], d) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < c; n++)
			s[b][n] = str[a++];
		s[b][n] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the string input
 * @d:  delimeter
 * Return: a NULL on failure, or pointer to an array of strings
 */
char **strtow2(char *str, char d)
{
	int a, b, c, n, wordnum = 0;

	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			wordnum++;
	if (wordnum == 0)
		return (NULL);
	s = malloc((1 + wordnum) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < wordnum ; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		c = 0;
		while (str[a + c] != d && str[a + c] && str[a + c] != d)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < c; n++)
			s[b][n] = str[a++];
		s[b][n] = 0;
	}
	s[b] = NULL;
	return (s);
}
