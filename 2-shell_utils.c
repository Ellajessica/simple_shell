#include "shell.h"

void ctrl_C(int signum)
{
	if (signum == SIGINT)
		print("\n ($) ", STDIN_FILENO);
}

char *_getline(void)
{
	int bufSize = READ_BUF, no_read, position = 0;

	char *buffer = malloc(bufSize * sizeof(char));
	char c;

	if (buffer == NULL)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		no_read = read(STDIN_FILENO, &c, 1);
		if (c == 0x05 || !no_read)
		{
			if (isatty(STDIN_FILENO))
			{
				free(buffer);
				print("\n", STDIN_FILENO);
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
				perror("Failed to re-allocate a space in the memory");
				exit(EXIT_FAILURE);
			}
		}
	}
}

void execute(char **commands, int cmd_type, shell_i *p)
{
	void (*func)(char **command, shell_i *vary);
	signal(SIGINT, SIG_DFL);
	switch (cmd_type)
	{
		case EXTERNAL_CMD:
			{
				if (execve(commands[0], commands, NULL) == -1)
				{
					perror(_getenv("PWD"));
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
				if (execve(check_path(commands[0]), commands, NULL) == -1)
				{
					perror(_getenv("PWD"));
						free_tokenized(environ);
					exit(2);
				}
				break;
			}
		case INVALID_CMD:
			{
				print_error(commands, p);
				p->error_status = 2;
				break;
			}
	}
	p->error_status = 0;
}


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
