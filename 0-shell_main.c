#include "shell.h"

int main(int argc __attribute__((unused)), char **argv)
{
	shell_i vary;

	init_shell(&vary);
	vary.shell_name = argv[0];

	shell_loop(&vary);
	free_tokenized(environ);

	return (EXIT_SUCCESS);
}

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

	for (i = 0; environ[i]; i++)
	{
		tmp[i] = _strdup(environ[i]);
	}
	tmp[i] = NULL;
	environ = tmp;

	return(vary);
}

