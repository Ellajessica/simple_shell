#include "shell.h"
/**
 * handle_setenv - sers an environment vary
 * @args: entered command
 * @p: shell global variable
 */

void handle_setenv(char **args, shell_i *p)
{
	int i = 0;

	while (args[i])
		i++;
	if (i != 3 || !args[1] || !args[2])
	{
		p->error_status = -1;
		print_error(args, p);
		return;
	}
	i = _setenv(args[1], args[2]);
	if (i)
		print("setenv: invalid arguments\n", STDERR_FILENO);
	p->error_status = 0;
}

/**
 * handle_unsetenv - unsets an environment vary
 * @args: entered command
 * @p: shell global variable
 */

void handle_unsetenv(char **args, shell_i *p)
{
	int i = 0;

	while (args[i])
		i++;
	if (i != 2 || !args[1])
	{
		p->error_status = -1;
		print_error(args, p);
		return;
	}
	i = _unsetenv(args[1]);
	if (i)
	{
		p->error_status = -1;
		print_error(args, p);
		return;
	}

	p->error_status = 0;
}

/**
 * aliasFunc - handles aliases for commands
 * @args: entred command
 * @p: shell global variable
 */

void aliasFunc(char **args, shell_i *p)
{
	int i = 0, j = 0;

	if (args[1] == NULL && p->aliases)
	{
		if (p->aliases[i] == NULL)
		{
			print("\n", STDOUT_FILENO);
			return;
		}
		while (p->aliases[i])
		{
			print(p->aliases[i++], STDOUT_FILENO);
			print("\n", STDOUT_FILENO);
		}
		p->error_status = 0;
		return;
	}
	for (i = 1; args[i]; i++)
	{
		if (is_delimeter(args[i], '=') == 0)
		{
			j = 0;
			while (p->aliases[j])
			{
				if (_strcmp(p->aliases[j], args[i]) == 0)
				{
					print(p->aliases[j], STDOUT_FILENO);
					print("\n", STDOUT_FILENO);
					break;
				} j++;
			}
			if (!p->aliases)
			{
				print_error(args, p);
				p->error_status = 1;
			}
		}
		else
			set_alias(args[i], p);
	} p->error_status = 0;
}

/**
 * set_alias - set aliase according to a key value pair
 * @key_val: key value pair to be set
 * @vary: global struct shell variables
 *
 */

void set_alias(char *key_val, shell_i *vary)
{
	char **tmp = tokenize(key_val, "="), **temp;
	char *key = tmp[0];
	int i = 0;

	while (vary->aliases && vary->aliases[i])
	{
		if (startsWith(vary->aliases[i], key))
		{
			free(vary->aliases[i]);
			vary->aliases[i] = _strdup(key_val);
			free_tokenized(tmp);
			return;
		}
		i++;
	}
	temp = malloc((i + 2) * sizeof(char *));
	if (!temp)
		return;
	for (i = 0; vary->aliases && vary->aliases[i]; i++)
		temp[i] = vary->aliases[i];
	temp[i++] = _strdup(key_val);
	temp[i] = NULL;
	free_tokenized(vary->aliases);
	vary->aliases = temp;
	free_tokenized(tmp);
	vary->error_status = 0;
}

/**
 * alias_error - print error message associated wirg alias
 * @cmd: list of arguments supplied
 * @vary: global struct shell variables
 *
 * Return: the error message
 */

char *alias_error(char **cmd, shell_i *vary __attribute__((unused)))
{
	char *res, *msg;
	int len;

	msg = " not found\n";
	len = _strlen(cmd[0]) + _strlen(msg) + _strlen(cmd[1]);
	res = malloc((len + 3) * sizeof(char));
	if (!res)
	{
		return (NULL);
	}

	_strcpy(res, cmd[0]);
	_strcat(res, ": ");
	_strcat(res, cmd[1]);
	_strcat(res, msg);

	return (res);
}
