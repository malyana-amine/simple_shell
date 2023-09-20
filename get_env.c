#include "shell.h"

/**
 * get_env - Retrieve environment variables as an array.
 * @inf: Pointer to infocmd structure with environment data.
 *
 * Return: Array of strings containing environment variables.
 */
char **get_env(infocmd *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_string(inf->env);
		inf->env_changed = 0;
	}

	return (inf->environ);
}

/**
 * unset_env - Remove an environment variable
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @v: the string env var property
 */
int unset_env(infocmd *inf, char *v)
{
	liststr *node = inf->env;
	size_t i = 0;
	char *p;

	if (!node || !v)
		return (0);

	while (node)
	{
		p = starts_with(node->s, v);
		if (p && *p == '=')
		{
			inf->env_changed = del_node_index(&(inf->env), i);
			i = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (inf->env_changed);
}



/**
 * set_env - Set or update an environment variable.
 * @inf: Pointer to infocmd structure with environment data.
 * @v: Variable name.
 * @val: Variable value.
 *
 * Return: 0 on success, 1 on memory allocation error.
 */
int set_env(infocmd *inf, char *v, char *val)
{
	char *buffer = NULL;
	liststr *node;
	char *p;

	if (!v || !val)
		return (0);

	buffer = malloc(str_length(v) + str_length(val) + 2);
	if (!buffer)
		return (1);
	str_copy(buffer, v);
	str_cat(buffer, "=");
	str_cat(buffer, val);
	node = inf->env;
	while (node)
	{
		p = starts_with(node->s, v);
		if (p && *p == '=')
		{
			free(node->s);
			node->s = buffer;
			inf->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_end_node(&(inf->env), buffer, 0);
	free(buffer);
	inf->env_changed = 1;
	return (0);
}
