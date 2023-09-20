#include "shell.h"

/**
 * unset_info - initializes info_t struct
 * @inf: struct address
 */
void unset_info(infocmd *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_info - init struct infocmd
 * @inf: struct info cmd
 * @a: init values
 */
void set_info(infocmd *inf, char **a)
{
	int i = 0;

	inf->fname = a[0];
	if (inf->arg)
	{
		inf->argv = str_to_words(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = str_duplicate(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i;

		rep_alias(inf);
		rep_vars(inf);
	}
}

/**
 * lib_info - free infocmd struct
 * @inf: pointer to struct
 * @a: true if ok
 */
void lib_info(infocmd *inf, int a)
{
	str_free(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (a)
	{
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->env)
			free_list(&(inf->env));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		str_free(inf->environ);
			inf->environ = NULL;
		free_mem((void **)inf->cmd_buf);
		if (inf->readfd > 2)
			close(inf->readfd);
		_put_char(BUF_FLUSH);
	}
}
