#include "shell.h"

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

void quit(char **command, shell_i *p)
{
	int num_token = 0, arg;

	for (; command[num_token] != NULL; num_token++)
		;
	if (num_token == 1)
	{
		free_tokenized(command);
		free_tokenized(environ);
		exit(1);
	}
	else if (num_token == 2)
	{
		arg = _atoi(command[1]);
		if (arg < 0)
		{
			print(p->shell_name, STDERR_FILENO);
			print(": 1: exit: Illegal number: ", STDERR_FILENO);
			print(command[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			p->error_status = 2;
		}
		else
		{
			free_tokenized(command);
			free_tokenized(environ);
			exit(arg);
		}
	}
	else
	{
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);
	}
}

#define SETPWD(V) (V = _strdup(_getenv("OLDPWD")))

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
				exit (EXIT_FAILURE);
		}
		else
		{
			SETPWD(vary->old_pwd);
			if (chdir(vary->old_pwd) < 0)
				exit (EXIT_FAILURE);
		}
		print(vary->old_pwd, STDOUT_FILENO);
		print("\n", STDOUT_FILENO);
	}
	else
	{
		SETPWD(vary->old_pwd);
		if (chdir(command[1]) < 0)
		{
			print_error(command, vary);
			vary->error_status = 2;
			return;
		}
	}
	vary->error_status = 0;
}

#define GETCWD

void display_help(char **command __attribute__((unused)), shell_i *p __attribute__((unused)))
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
		"\nEvery other shell builtin are all supported\t",
		"\nThanks for using our shell\t",
		NULL
	};
	int i = 0;

	while (texts[i])
	{
		print(texts[i], STDIN_FILENO);
		i++;
	}
}
