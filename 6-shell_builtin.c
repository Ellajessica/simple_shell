#include "shell.h"

/**
 * env - prints the current environment
 * @command: the entered command
 *
 * @p: shell global variable
 */

void env(char **command __attribute__((unused)), shell_i *p)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		print(environ[i], STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
	p->error_status = 0;
}

/**
 * quit - exits the shell
 * @command: entered command
 *
 * @p: shell global variable
 *
 */

void quit(char **command, shell_i *p)
{
	int num_token = 0, arg;

	for (; command[num_token] != NULL; num_token++)
		;
	if (num_token == 1)
	{
		clear_memory(p);
		p->exit = p->error_status;
	}
	else if (num_token == 2)
	{
		arg = _atoi(command[1]);
		if (arg < 0)
		{
			print_error(command, p);
			p->error_status = 2;
		}
		else
		{
			clear_memory(p);
			p->exit = arg;
		}
	}
	else
	{
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
	}
}

#define SETPWD(V) (V = _strdup(_getenv("OLDPWD")))

/**
 * ch_dir - handles change directory command (cd)
 * @command: command entered
 * @vary: shell global variable
 */

void ch_dir(char **command, shell_i *vary)
{
	char *home;

	home = _getenv("HOME");
	if (command[1] == NULL)
	{
		SETPWD(vary->old_pwd);
		if (chdir(home) < 0)
		{
			print_error(command, vary);
			vary->error_status = 2;
			return;
		}
	}
	else if (_strcmp(command[1], "-") == 0)
	{
		if (vary->old_pwd == NULL)
		{
			SETPWD(vary->old_pwd);
			if (chdir(home) < 0)
				exit(EXIT_FAILURE);
		}
		else
		{
			SETPWD(vary->old_pwd);
			if (chdir(vary->old_pwd) < 0)
				exit(EXIT_FAILURE);
		}
		print(vary->old_pwd, STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
	else
	{
		SETPWD(vary->old_pwd);
		if (chdir(command[1]) < 0)
		{
			print_error(command, vary), vary->error_status = 2;
			return;
		}
	} vary->error_status = 0;
}

#undef GETCWD

/**
 * display_help - display help
 * @command: command passed
 * @p: shell global variable
 */

void display_help(char **command __attribute__((unused)),
		shell_i *p __attribute__((unused)))
{
	static char *texts[] = {
		"\n\t**Welcome to this Simple Shell Project**\n",
		"Copyright: @DannyRalph @Ellajessica\n",
		"\tcd\n",
		"\tenv\n",
		"\texit\n",
		"\tmkdir\n",
		"\trmdir\n",
		"\thelp\n",
		"\tclear\n",
		"\tsetenv\n",
		"\tunsetenv\n",
		"\nEvery other shell builtin are all supported\n",
		"\nThanks for using our shell\n",
		NULL
	};
	int i = 0;

	while (texts[i])
	{
		print(texts[i], STDIN_FILENO);
		i++;
	}
}
