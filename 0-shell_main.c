#include "shell.h"

/**
 * main - function for the shell
 * @argc: argument count passed to attribute unused
 * @argv: character array passed to the main function
 *
 * Return: 1 on success
 */
int main(int argc __attribute__((unused)), char **argv)
{
	shell_i vary;

	init_shell(&vary);
	vary.shell_name = argv[0];

	shell_loop(&vary);
	free_tokenized(environ);
	free_tokenized(vary.aliases);
	return (EXIT_SUCCESS);
}

/**
 * init_shell - iniitialise shell
 *
 * @vary: shel global variable
 * Return: shell vary
 */
shell_i *init_shell(shell_i *vary)
{
	int i;
	char **tmp;

	vary->shell_name = NULL;
	vary->old_pwd = NULL;
	vary->error_status = 0;
	vary->cmd_counter = 1;

	for (i = 0; environ[i]; i++)
		;

	tmp = malloc(sizeof(char *) * (i + 1));
	vary->aliases = malloc(sizeof(char *));
	vary->aliases[0] = NULL;

	for (i = 0; environ[i]; i++)
	{
		tmp[i] = _strdup(environ[i]);
	}
	tmp[i] = NULL;
	environ = tmp;

	return (vary);
}

