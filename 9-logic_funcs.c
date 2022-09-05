#include "shell.h"

void execute_logic(char *args, shell_i *vary)
{
	char **command;
	int command_type;

	command = tokenize(args, DELIM);
	if (!(command[0]))
	{
		free(command);
		return;
	}
	command_type = check_command(command[0]);
	shell_execute(command, command_type, vary);
	free_tokenized(command);
	free(args);
}

char **logic_token(char *str)
{
	int j = 0, i = 0;
	char **res;

	if (!str)
		return (0);
	res = malloc(3 * sizeof(char *));
	for (; str[i]; i++)
	{
		j = startsWith(str + i, "&&");
		if (j)
		{
			res[0] = _strndup(str, i);
			res[1] = _strdup("&&");
			res[2] = str + i + j;
			return (res);
		}
		j = startsWith(str + i, "||");
		if (j)
		{
			res[0] = _strndup(str, i);
			res[1] = _strdup("||");
			res[2] = str + i + j;
			return (res);
		}
	}
	res[0] = _strdup(str);
	res[1] = 0;
	res[2] = 0;
	return (res);
}
