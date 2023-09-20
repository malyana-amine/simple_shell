#include "shell.h"

/**
 * fct_cmd - Check if a given path points to a regular file.
 * @pin: Pointer to the infocmd struct (not used pin this function).
 * @p: Path to be checked for regular file status.
 *
 * Return: 1 if the path points to a regular file, 0 otherwise.
 */
int fct_cmd(infocmd *pin, char *p)
{
	struct stat st;

	(void)pin;
	if (!p || stat(p, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * fct_duplicate - Create a duplicate substring from a given range in a string.
 * @pst: Pointer to the input string.
 * @tr: Starting index of the substring.
 * @tp: Ending index of the substring.
 *
 * Return: Pointer to the duplicated substring.
 */
char *fct_duplicate(char *pst, int tr, int tp)
{
	static char buffer[1024];
	int i = 0, j = 0;

	for (j = 0, i = tr; i < tp; i++)
		if (pst[i] != ':')
			buffer[j++] = pst[i];
	buffer[j] = 0;
	return (buffer);
}

/**
 * fct_path - Find and return the full path of a command.
 * @poin: Pointer to infocmd struct.
 * @pst: Colon-separated paths.
 * @cn: Command name.
 *
 * Return: Full path if found, else NULL.
 */
char *fct_path(infocmd *poin, char *pst, char *cn)
{
	int i = 0, position = 0;
	char *ph;

	if (!pst)
		return (NULL);
	if ((str_length(cn) > 2) && starts_with(cn, "./"))
	{
		if (fct_cmd(poin, cn))
			return (cn);
	}
	while (1)
	{
		if (!pst[i] || pst[i] == ':')
		{
			ph = fct_duplicate(pst, position, i);
			if (!*ph)
				str_cat(ph, cn);
			else
			{
				str_cat(ph, "/");
				str_cat(ph, cn);
			}
			if (fct_cmd(poin, ph))
				return (ph);
			if (!pst[i])
				break;
			position = i;
		}
		i++;
	}
	return (NULL);
}
