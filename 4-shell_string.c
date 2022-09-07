#include "shell.h"

/**
 * _strlen - return the lenght of a string
 * @s: string pointer
 *
 * Return: string lenght
 */

int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (-1);
	for (i = 0; s[i]; i++)
		;
	return (i);
}
/**
 * _strcmp - compare two string
 * @str1: first string to be compared
 * @str2: second string to be compared
 *
 * Return: the diffrence of the two strings
 */

int _strcmp(char *str1, char *str2)
{
	int i = 0;

	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			break;
		i++;
	}
	return (str1[i] - str2[i]);
}
/**
 * _strcat - concatenate src to dest
 * @src: pointer to the source string
 * @dest: pointer to the destination
 * Return: dest
 */

char *_strcat(char *dest, char *src)
{
	int x = 0, y = 0;

	if (!dest || !src)
		return (dest);

	while (dest[y])
		y++;
	while (src[x])
	{
		dest[y++] = src[x];
		x++;
	}
	dest[y] = '\0';
	return (dest);
}

/**
 * _strdup - duplicate a string
 *
 * @s: pointer to string
 * Return: pointer to duplicate
 */

char *_strdup(char *s)
{
	int i;
	char *res;

	if (!s)
		return (0);
	res = malloc(_strlen(s) + 1);
	i = 0;
	while (s[i])
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

/**
 * _strndup - duplicates a string
 *
 * @s: pointer to string
 * @n: number to characters to duplicate
 * Return: pointer to duplicate
 */

char *_strndup(char *s, int n)
{
	int i, len;
	char *res;

	if (!s || n < 0)
		return (0);
	len = _strlen(s);
	if (n > len)
		n = len;
	res = malloc(n + 1);
	i = 0;
	while (s[i] && i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
