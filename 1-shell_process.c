#include "shell.h"

/**
 * shell_loop - read a line from user input
 *              check if the shell be ran interactively
 *              remove comments from line if any
 *              parse or tokenize the _getline
 *              execute the parsed command
 *              runs infinitfely unless user types exit or CTRL-D
 * @vary: shell global variable
 */

void shell_loop(shell_i *vary)
{
	char *line;

	signal(SIGINT, ctrl_C);
	while (1)
	{
		non_interractive(vary);
		print(" ($) ", STDOUT_FILENO);
		line = _getline();
		if (!_strlen(line))
		{
			free(line);
			if (isatty(STDIN_FILENO))
				continue;
		}
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				break;
		}
		logic_token_help(line, vary);
		free(line);
	}
}

/**
 * non_interractive - shell run in non interactive mode
 * @p: shell global variable
 */

void non_interractive(shell_i *p)
{
	char **args, **logic_cmd;
	char *line, *op;
	int i = 0;

	if (isatty(STDIN_FILENO) == 0)
	{
		line = _getline();
		comment_remover(line);
		args = tokenize(line, ";");
		while (args[i])
		{
			logic_cmd = logic_token(args[i++]);
			op = logic_cmd[1];
			while (logic_cmd[0])
			{
				execute_logic(logic_cmd[0], p);
				p->cmd_counter += 1;
				if (!logic_cmd[2])
					break;
				if (_strcmp(op, AND_DELIM) == 0)
				{
					if (p->error_status == 0)
						logic_cmd = logic_token(logic_cmd[2]);
					else
						break;
				}
				else if (_strcmp(op, OR_DELIM) == 0)
				{
					if (p->error_status != 0)
						logic_cmd = logic_token(logic_cmd[2]);
					else
						break;
				}
			}
		}
		free_tokenized(args);
		free_tokenized(environ);
		free(line);
	}
}
/**
 * check_command - determine the command type inputted
 * @command: command to be checked
 *
 * Return: constant variable representing the type of command
 */
int check_command(char *command)
{
	int i = 0;
	static char *int_cmd[] = {"exit", "cd", "env", "setenv",
		"unsetenv", "alias", "help", NULL};
	char *path = NULL;

	while (command[i])
	{
		if (command[i++] == '/')
			return (EXTERNAL_CMD);
	}
	for (i = 0; int_cmd[i]; i++)
	{
		if (_strcmp(command, int_cmd[i]) == 0)
			return (INTERNAL_CMD);
	}
	path = check_path(command);
	if (path)
	{
		free(path);
		return (PATH_CMD);
	}
	return (INVALID_CMD);
}

/**
 * shell_execute - launches the command to be executed
 * @command: command to be launched
 * @cmd_type: type of the command to be executed
 * @vary: struct for old path and shell name
 *
 * Return: 1 always
 */

void shell_execute(char **command, int cmd_type, shell_i *vary)
{
	int state;
	pid_t PID, W_PID __attribute__((unused));

	if (cmd_type == EXTERNAL_CMD || cmd_type == PATH_CMD)
	{
		PID = fork();

		if (PID == 0)
		{
			execute(command, cmd_type, vary);
		}
		else if (PID < 0)
		{
			perror("Error Creating fork");
			return;
		}
		else
		{
			do {
				W_PID = waitpid(PID, &state, WUNTRACED);
			} while (!WIFEXITED(state) && !WIFSIGNALED(state));
		}
	}
	else
		execute(command, cmd_type, vary);
	vary->error_status = state / 256;
}

/**
 * _strcpy - copy string from the source to another destination
 * @dest: pointer to the string destination
 * @src: Pointer to the source
 *
 * Return: 1 always
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';

	return (dest);
}
