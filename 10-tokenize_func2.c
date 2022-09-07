#include "shell.h"

/**
 * tokenize - split a string
 * @str: pointer to string to be splitted
 * @delim: caracter to split string
 * Return: pointer to new or NULL
 */

char **tokenize(char *str, const char *delim)
{
	int k = 0, j = 0, i = 0, size = 0, lens[1200];
	char **arr;

	if (str == NULL || !(*str))
		return (NULL);

	for (i = 0; str[i]; i++)
	{
		if (is_delimeter(delim, str[i]))
			continue;
		j = i;
		while (!is_delimeter(delim, str[i]) && str[i])
			i++;
		if (i > j)
			lens[size++] = i - j;
		if (!str[i])
			break;
	}
	if (!size)
		return (NULL);

	arr = malloc((size + 1) * sizeof(char *));
	for (i = 0; str[i]; i++)
	{
		if (is_delimeter(delim, str[i]))
			continue;

		arr[k] = malloc((lens[k] + 1) * sizeof(char));
		j = 0;
		while (!is_delimeter(delim, str[i]) && str[i])
			arr[k][j++] = str[i++];
		arr[k++][j] = '\0';

		if (!str[i])
			break;
	}
	arr[size] = NULL;
	return (arr);
}

/**
 * is_delimeter - checks if a character is in delimeter
 * @delimeters: pointer to delimeter
 * @c: character to check
 *
 * Return: 1 for true 0 for false
 */

int is_delimeter(const char *delimeters, char c)
{
	int i = 0;

	if (!delimeters)
		return (0);
	while (delimeters[i])
	{
		if (delimeters[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/**
 * startsWith - check if s starts with ndl
 * @s: the string to check
 * @ndl: the string searched
 * Return: 0 if false
 *        else returns the next index after ndl in s
 */

int startsWith(char *s, char *ndl)
{
	int i = 0;

	if (!s || !ndl)
		return (0);
	while (ndl[i])
	{
		if (ndl[i] != s[i])
			return (0);
		i++;
	}
	return (i);
}

/**
 * endsWith - check if s ends with ndl
 * @s: the string to check
 * @ndl: the string searched
 * Return: 0 if false
 *        else retuens the index before ndl in s
 */

int endsWith(char *s, char *ndl)
{
	int i, j;

	if (!s || !ndl)
		return (0);
	i = _strlen(s);
	j = _strlen(ndl);
	if (j > i)
		return (0);
	for (j--, i--; j >= 0; j--, i--)
		if (ndl[j] != s[i])
			return (0);
	return (i);
}
