#include "shell.h"

/**
 * ctrl_C - handles the signal rasied by CTRL-C
 * @signum: signal number
 */

void ctrl_C(int signum)
{
	if (signum == SIGINT)
		print("\n ($) ", STDIN_FILENO);
}

/**
 * _getline - reads line from standard input
 *
 * Return: the line read
 */

char *_getline(void)
{
	int bufSize = READ_BUF, no_read, position = 0;

	char c, *buffer = malloc(bufSize * sizeof(char));

	if (buffer == NULL)
	{
		perror("Failed to allocate memory");
		free_tokenized(environ);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		no_read = read(STDIN_FILENO, &c, 1);
		if (c == EOF || !no_read)
		{
			if (isatty(STDIN_FILENO))
			{
				free(buffer), print("\n", STDIN_FILENO);
				return (NULL);
			}
		}
		else if (c == '\n' || !no_read)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else
			buffer[position] = c;
		position++;

		if (position >= bufSize)
		{
			bufSize += READ_BUF;
			buffer = _realloc(buffer, READ_BUF, bufSize);
			if (!buffer)
			{
				free_tokenized(environ);
				exit(EXIT_FAILURE); }
		}
	}
}

/**
 * execute - execute command based on it type
 * @commands: processed character array
 * @cmd_type: the type of command
 * @p: shell global variables
 */

void execute(char **commands, int cmd_type, shell_i *p)
{
	void (*func)(char **command, shell_i *vary);

	signal(SIGINT, SIG_DFL);
	switch (cmd_type)
	{
		case EXTERNAL_CMD:
			{
				if (execve(commands[0], commands, environ) == -1)
				{
					perror(p->shell_name);
				free_tokenized(environ);
				exit(2);
				}
				break;
			}
		case INTERNAL_CMD:
			{
				func = get_func(commands[0]);
				func(commands, p);
				break;
			}
		case PATH_CMD:
			{
				if (execve(check_path(commands[0]), commands,environ) == -1)
				{
					perror(p->shell_name);
						free_tokenized(environ);
					exit(2);
				}
				break;
			}
		case INVALID_CMD:
			{
				print_error(commands, p);
				p->error_status = 2;
			}
	}
	p->error_status = 0;
}

/**
 * get_func - retrieves a function based on the command given and a mapping
 * @command: string to check against the mapping
 *
 * Return: pointer to the proper function, or null on fail
 */

void (*get_func(char *command))(char **, shell_i *)
{
	int i;

	map_func map[] = {
		{"env", env},
		{"cd", ch_dir},
		{"exit", quit},
		{"help", display_help},
		{"alias", aliasFunc},
		{"setenv", handle_setenv},
		{"unsetenv", handle_unsetenv}
	};

	for (i = 0; i < 7; i++)
	{
		if (_strcmp(command, map[i].cmd_name) == 0)
			return (map[i].func);
	}
	return (NULL);
}
