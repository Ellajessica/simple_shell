#include "shell.h"

int _strlen(char *s)
{
	int i = 0;

	for (i = 0; s[i]; i++)
		;
	return (i);
}

int _strcmp(char *str1, char *str2)
{
	int len1 = _strlen(str1);
	int len2 = _strlen(str2);
	int i = 0;

	if (len1 != len2)
		return (-1);

	while(str1[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	return (0);
}

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
