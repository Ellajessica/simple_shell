#include "shell.h"

int print(char *var, int fd)
{
	if (!var)
		return (-1);
	return (write(fd, var, _strlen(var)));
}

void comment_remover(char *input)
{
	int i = 0;

	if (input[i] == '#')
		input[i] = '\0';
	while (input[i] != '\0')
	{
		if (input[i] == '#' && input[i - 1] == ' ')
			break;
		i++;
	}
	input[i] = '\0';
}

int _putchar(char c)
{
	return (write(1, &c, 1));
}

int _atoi(char *s)
{
	unsigned int n = 0;

	do {
		if (*s == '-')
			return (-1);
		else if ((*s < '0' || *s > '9') && *s != '\0')
			return (-1);
		else if (*s >= '0' && *s <= '9')
			n = (n * 10) + (*s - '0');
		else if (n > 0)
			break;
	} while(*s++);
	return (n);
}


char *_itoa(int num)
{
	char *res;
	int tmp = num, len = 0;

	if (tmp < 0)
	{
		len++;
		tmp *= -1;
	}

	do {
		tmp /= 10;
		len++;
	} while (tmp);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	*(res + len) = '\0';

	if (num < 0)
	{
		res[0] = '-';
		num *= -1;
	}
	len--;
	do {
		*(res + len) = (num % 10) + '0';
		num /= 10;
		len--;
	} while (num);

	return (res);
}
