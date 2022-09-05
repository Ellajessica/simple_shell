#include "shell.h"

void shell_loop(shell_i *vary)
{
	char *line, *op;
	char **args, **logic_cmd;
	int i = 0;

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
			if (isatty(STDIN_FILENO))
				break;
		comment_remover(line);
		args = tokenize(line, ";");
		while (args[i])
		{
			logic_cmd = logic_token(args[i++]);
			op = logic_cmd[1];
			execute_logic(logic_cmd[0], vary);
			vary->cmd_counter += 1;
			if (!op)
				continue;
			if (_strcmp(op, AND_DELIM) == 0)
			{
				if (vary->error_status != 0)
					logic_cmd = logic_token(logic_cmd[2]);
				else
					break;
			}
			else if (_strcmp(op, OR_DELIM) == 0)
			{
				if (vary->error_status == 0)
					logic_cmd = logic_token(logic_cmd[2]);
				else
					break;
			} free(op);
		} free_tokenized(args);
	} free(line);
}

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
			execute_logic(logic_cmd[0], p);
			p->cmd_counter += 1;
			if (!op)
				continue;
			if (_strcmp(op, AND_DELIM) == 0)
			{
				if (p->error_status != 0)
					logic_cmd = logic_token(logic_cmd[2]);
				else
					break;
			}
			else if (_strcmp(op, OR_DELIM) == 0)
			{
				if (p->error_status == 0)
					logic_cmd = logic_token(logic_cmd[2]);
				else
					break;
			}
			free(op);
		}
		free_tokenized(args);
		free_tokenized(environ);
		free(line);
	}
}

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
	i = 0;
	while (int_cmd[i])
	{
		if (_strcmp(command, int_cmd[i]) == 0)
			return (INTERNAL_CMD);
		i++;
	}
	if (path)
	{
		free(path);
		return (PATH_CMD);
	}
	return (INVALID_CMD);
}

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
			perror("failed to call fork");
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


char *_strcpy(char *dest, char *src)
{
	int i;

	for(i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';

	return (dest);
}
