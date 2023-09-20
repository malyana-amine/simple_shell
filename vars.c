#include "shell.h"

/**
 * fct_chain - Identify and set command chaining type.
 * @in: Pointer to the shell information struct.
 * @bfr: Command buffer containing the command and chaining symbol.
 * @pad: Pointer to the index where the chaining symbol is located.
 *
 * Return: 1 if a valid chaining symbol is found, 0 otherwise.
 */

int fct_chain(infocmd *in, char *bfr, size_t *pad)
{
	size_t j = *pad;

	if (bfr[j] == '|' && bfr[j + 1] == '|')
	{
		bfr[j] = 0;
		j++;
		in->cmd_buf_type = CMD_OR;
	}
	else if (bfr[j] == '&' && bfr[j + 1] == '&')
	{
		bfr[j] = 0;
		j++;
		in->cmd_buf_type = CMD_AND;
	}
	else if (bfr[j] == ';')
	{
		bfr[j] = 0;
		in->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pad = j;
	return (1);
}

/**
 * fct_check - Check and adjust command buffer based on chaining type.
 * @in: Pointer to the shell information struct.
 * @bfr: Command buffer containing the command and chaining symbol.
 * @pst: Pointer to the index tracking the position within the buffer.
 * @i: Current index position within the buffer.
 * @lg: Length of the buffer.
 *
 * Return: none
 */
void fct_check(infocmd *in, char *bfr, size_t *pst, size_t i, size_t lg)
{
	size_t j = *pst;

	if (in->cmd_buf_type == CMD_AND)
	{
		if (in->status)
		{
			bfr[i] = 0;
			j = lg;
		}
	}
	if (in->cmd_buf_type == CMD_OR)
	{
		if (!in->status)
		{
			bfr[i] = 0;
			j = lg;
		}
	}

	*pst = j;
}

/**
 * rep_alias - Replace command name with alias argument from the alias list.
 * @in: Pointer to the shell information struct.
 *
 * Return: 1 on success, 0 on failure.
 */
int rep_alias(infocmd *in)
{
	int i;
	liststr *st;
	char *padam;

	for (i = 0; i < 10; i++)
	{
		st = node_start(in->alias, in->argv[0], '=');
		if (!st)
			return (0);
		free(in->argv[0]);
		padam = str_find_char(st->s, '=');
		if (!padam)
			return (0);
		padam = str_duplicate(padam + 1);
		if (!padam)
			return (0);
		in->argv[0] = padam;
	}
	return (1);
}

/**
 * rep_vars - Replace variables in command arguments with their values.
 * @in: Pointer to the shell information struct.
 *
 * Return: 0 on successful replacement.
 */
int rep_vars(infocmd *in)
{
	int i = 0;
	liststr *strin;

	for (i = 0; in->argv[i]; i++)
	{
		if (in->argv[i][0] != '$' || !in->argv[i][1])
			continue;

		if (!str_comparison(in->argv[i], "$?"))
		{
			rep_string(&(in->argv[i]), str_duplicate(conv_number(in->status, 10, 0)));
			continue;
		}
		if (!str_comparison(in->argv[i], "$$"))
		{
			rep_string(&(in->argv[i]), str_duplicate(conv_number(getpid(), 10, 0)));
			continue;
		}
		strin = node_start(in->env, &in->argv[i][1], '=');
		if (strin)
		{
			rep_string(&(in->argv[i]), str_duplicate(str_find_char(strin->s, '=') + 1));
			continue;
		}
		rep_string(&in->argv[i], str_duplicate(""));

	}
	return (0);
}

/**
 * rep_string - Replace old string with a new one.
 * @oldstr: Pointer to the old string to be replaced.
 * @newstrnew: Pointer to the new string to replace with.
 *
 * Return: 1 to indicate successful replacement.
 */
int rep_string(char **oldstr, char *newstrnew)
{
	free(*oldstr);
	*oldstr = newstrnew;
	return (1);
}
