#include "shell.h"

void handle_setenv(char **args, shell_i *p)
{
	int i = 0;

	(void)p;
	while (args[i])
		i++;
	if (i != 3)
	{
		print("setenv: wrong number of arguments\n", STDERR_FILENO);
		print("type help for more info\n", STDERR_FILENO);
		return;
	}
	i = _setenv(args[1], args[2]);
	if (i)
		print("setenv: invalid arguments\n", STDERR_FILENO);
}

void handle_unsetenv(char **args, shell_i *p)
{
	int i = 0;

	(void)p;
	while (args[i])
		i++;
	if (i != 2)
	{
		print("unsetenv: wrong number of arguments\n", STDERR_FILENO);
		print("type help for more info\n", STDERR_FILENO);
		return;
	}
	i = _unsetenv(args[1]);
	if (i)
		print("unsetenv: invalid arguments\n", STDERR_FILENO);
}

void aliasFunc(char **args, shell_i *p)
{
	(void)args;
	(void)p;
}
