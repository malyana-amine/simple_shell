#include "shell.h"

/**
 * lislength - Calculate the length of a linked list.
 * @poi: Pointer to the start of the linked list.
 *
 * Return: Number of elements in the linked list.
 */
size_t lislength(const liststr *poi)
{
	size_t i = 0;

	while (poi)
	{
		poi = poi->next;
		i++;
	}
	return (i);
}

/**
 * list_string - Convert linked list to array of strings.
 * @pstr: Pointer to the start of the linked list.
 *
 * Return: Array of strings converted from linked list.
 */
char **list_string(liststr *pstr)
{
	liststr *no = pstr;
	size_t i = lislength(pstr), j;
	char **c;
	char *st;

	if (!pstr || !i)
		return (NULL);
	c = malloc(sizeof(char *) * (i + 1));
	if (!c)
		return (NULL);
	for (i = 0; no; no = no->next, i++)
	{
		st = malloc(str_length(no->s) + 1);
		if (!st)
		{
			for (j = 0; j < i; j++)
				free(c[j]);
			free(c);
			return (NULL);
		}

		st = str_copy(st, no->s);
		c[i] = st;
	}
	c[i] = NULL;
	return (c);
}


/**
 * fct_list - Print a linked list of numbers and strings.
 * @plt: Pointer to the start of the linked list.
 *
 * Return: Number of elements printed.
 */
size_t fct_list(const liststr *plt)
{
	size_t i = 0;

	while (plt)
	{
		str_puts(conv_number(plt->n, 10, 0));
		_put_char(':');
		_put_char(' ');
		str_puts(plt->s ? plt->s : "(nil)");
		str_puts("\n");
		plt = plt->next;
		i++;
	}
	return (i);
}

/**
 * node_start - Find a linked list node that starts with a given string.
 * @st: Pointer to the start of the linked list.
 * @ch: String to search for at the beginning of a node's string.
 * @pstr: Character to match at the start of the found node's string.
 *
 * Return: Pointer to the found node or NULL if not found.
 */
liststr *node_start(liststr *st, char *ch, char pstr)
{
	char *k = NULL;

	while (st)
	{
		k = starts_with(st->s, ch);
		if (k && ((pstr == -1) || (*k == pstr)))
			return (st);
		st = st->next;
	}
	return (NULL);
}

/**
 * node_index - Find the index of a linked list node.
 * @in: Pointer to the start of the linked list.
 * @dex: Pointer to the node to find the index for.
 *
 * Return: Index of the found node or -1 if not found.
 */
ssize_t node_index(liststr *in, liststr *dex)
{
	size_t i = 0;

	while (in)
	{
		if (in == dex)
			return (i);
		in = in->next;
		i++;
	}
	return (-1);
}
