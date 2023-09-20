#include "shell.h"

/**
 * history_file - Generate history file path.
 * @in: Pointer to the shell information struct.
 *
 * Return: Pointer to the generated history file path or NULL on failure.
 */

char *history_file(infocmd *in)
{
	char *bf, *d;

	d = get_var_env(in, "HOME=");
	if (!d)
		return (NULL);
	bf = malloc(sizeof(char) * (str_length(d) + str_length(HIST_FILE) + 2));
	if (!bf)
		return (NULL);
	bf[0] = 0;
	str_copy(bf, d);
	str_cat(bf, "/");
	str_cat(bf, HIST_FILE);
	return (bf);
}

/**
 * create_history - Create history file.
 * @in: Pointer to the shell information struct.
 *
 * Return: 1 on success, -1 on failure.
 */
int create_history(infocmd *in)
{
	ssize_t file;
	char *nm = history_file(in);
	liststr *c = NULL;

	if (!nm)
		return (-1);

	file = open(nm, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(nm);
	if (file == -1)
		return (-1);
	for (c = in->history; c; c = c->next)
	{
		puts_file2(c->s, file);
		put_file('\n', file);
	}
	put_file(BUF_FLUSH, file);
	close(file);
	return (1);
}

/**
 * read_history - Read history from file and populate list.
 * @in: Pointer to the shell information struct.
 *
 * Return: Number of history entries read and added to the list.
 */
int read_history(infocmd *in)
{
	int i, lt = 0, lcount = 0;
	ssize_t file, lenght, size = 0;
	struct stat str;
	char *bf = NULL, *nm = history_file(in);

	if (!nm)
		return (0);

	file = open(nm, O_RDONLY);
	free(nm);
	if (file == -1)
		return (0);
	if (!fstat(file, &str))
		size = str.st_size;
	if (size < 2)
		return (0);
	bf = malloc(sizeof(char) * (size + 1));
	if (!bf)
		return (0);
	lenght = read(file, bf, size);
	bf[size] = 0;
	if (lenght <= 0)
		return (free(bf), 0);
	close(file);
	for (i = 0; i < size; i++)
		if (bf[i] == '\n')
		{
			bf[i] = 0;
			build_history_list(in, bf + lt, lcount++);
			lt = i + 1;
		}
	if (lt != i)
		build_history_list(in, bf + lt, lcount++);
	free(bf);
	in->histcount = lcount;
	while (in->histcount-- >= HIST_MAX)
		del_node_index(&(in->history), 0);
	renum_history(in);
	return (in->histcount);
}

/**
 * build_history_list - Build command history list.
 * @in: Pointer to the shell information struct.
 * @bf: Command string to be added to history.
 * @lcount: Line number of the command in the history file.
 *
 * Return: 0 on success.
 */
int build_history_list(infocmd *in, char *bf, int lcount)
{
	liststr *str = NULL;

	if (in->history)
		str = in->history;
	add_end_node(&str, bf, lcount);

	if (!in->history)
		in->history = str;
	return (0);
}

/**
 * renum_history - Renumber history list entries.
 * @in: Pointer to the shell information struct.
 *
 * Return: New history count after renumbering.
 */
int renum_history(infocmd *in)
{
	liststr *str = in->history;
	int i = 0;

	while (str)
	{
		str->n = i++;
		str = str->next;
	}
	return (in->histcount = i);
}
