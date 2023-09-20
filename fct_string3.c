#include "shell.h"

/**
 * **str_to_words - splits a string without repeated delimiter
 * @strin: the input string
 * @tds: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **str_to_words(char *strin, char *tds)
{
	int i, j, k, m, nbr = 0;
	char **s;

	if (strin == NULL || strin[0] == 0)
		return (NULL);
	if (!tds)
		tds = " ";
	for (i = 0; strin[i] != '\0'; i++)
		if (!fct_delim(strin[i], tds) && 
			(fct_delim(strin[i + 1], tds) || !strin[i + 1]))
			nbr++;

	if (nbr == 0)
		return (NULL);
	s = malloc((1 + nbr) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nbr; j++)
	{
		while (fct_delim(strin[i], tds))
			i++;
		k = 0;
		while (!fct_delim(strin[i + k], tds) && strin[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = strin[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * str_to_words2 - Split a string into an array of words using a delimiter.
 * @s: Input string to be split.
 * @tds: Delimiter character to split the string.
 *
 * Return: an array of strings extracted from the input string or NULL if fails
 */
char **str_to_words2(char *s, char tds)
{
	int i, j, k, m, nbr = 0;
	char **res;

	if (s == NULL || s[0] == 0)
		return (NULL);
	for (i = 0; s[i] != '\0'; i++)
		if ((s[i] != tds && s[i + 1] == tds) ||
		    (s[i] != tds && !s[i + 1]) || s[i + 1] == tds)
			nbr++;
	if (nbr == 0)
		return (NULL);
	res = malloc((1 + nbr) * sizeof(char *));
	if (!res)
		return (NULL);
	for (i = 0, j = 0; j < nbr; j++)
	{
		while (s[i] == tds && s[i] != tds)
			i++;
		k = 0;
		while (s[i + k] != tds && s[i + k] && s[i + k] != tds)
			k++;
		res[j] = malloc((k + 1) * sizeof(char));
		if (!res[j])
		{
			for (k = 0; k < j; k++)
				free(res[k]);
			free(res);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			res[j][m] = s[i++];
		res[j][m] = 0;
	}
	res[j] = NULL;
	return (res);
}
