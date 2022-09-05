#include "shell.h"

void *_realloc(void *ptr, int old, int new)
{
	void *tmp;
	unsigned int i, min;

	if (!ptr)
		return (malloc(new));
	else if (!new)
	{
		free(ptr);
		return (NULL);
	}
	else if (new == old)
		return (ptr);
	min = (old > new) ?
		new :
		old;
	tmp = malloc(new);
	if (tmp == NULL)
		return (NULL);
	for (i = 0; i < min; i++)
		((char *)tmp)[i] = ((char *)ptr)[i];
	free(ptr);
	return (tmp);
}

void free_tokenized(char **tokens)
{
	int i = 0;

	if (!tokens)
		return;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

