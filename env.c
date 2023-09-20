#include "shell.h"

/**
 * cur_env - prints the environment
 * @info: Struct containing potential arguments
 *
 * Return: Always 0
 */
int cur_env(infocmd *info)
{
	print_list(info->env);
	return (0);
}

/**
 * get_var_env - gets the value of an environ variable
 * @info: Structure containing potential arguments
 * @nm: environ name
 *
 * Return: the environ value
 */
char *get_var_env(infocmd *info, const char *nm)
{
	liststr *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->s, nm);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env_val - set a environment variable
 * @i: Structure containing potential arguments
 *
 *  Return: 0 if ok 1 if fails
 */
int set_env_val(infocmd *i)
{
	if (i->argc != 3)
	{
		er_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(i, i->argv[1], i->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_env_val - unset env variable
 * @info: Structure containing arguments
 *  Return: 0 if ok 1 if fails
 */
int unset_env_val(infocmd *info)
{
	int i;

	if (info->argc == 1)
	{
		er_puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unset_env(info, info->argv[i]);

	return (0);
}

/**
 * init_env_list - init list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int init_env_list(infocmd *info)
{
	liststr *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_end_node(&node, environ[i], 0);
	info->env = node;
	return (0);
}
