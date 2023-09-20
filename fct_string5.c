#include "shell.h"

/**
 **str_ncopy - make a copy of a string
 *@d: string 1
 *@s: string 2
 *@number: number of characters to be copied in d
 *Return: string
 */
char *str_ncopy(char *d, char *s, int number)
{
	int i, j;
	char *r = d;

	i = 0;
	while (s[i] != '\0' && i < number - 1)
	{
		d[i] = s[i];
		i++;
	}
	if (i < number)
	{
		j = i;
		while (j < number)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (r);
}

/**
 **str_ncat - concatenates two strings
 *@d: string 1
 *@src: string 2
 *@number: number of characters to be used
 *Return: the concatenated string
 */
char *str_ncat(char *d, char *src, int number)
{
	int i, j;
	char *s = d;

	i = 0;
	j = 0;
	while (d[i] != '\0')
		i++;
	while (src[j] != '\0' && j < number)
	{
		d[i] = src[j];
		i++;
		j++;
	}
	if (j < number)
		d[i] = '\0';
	return (s);
}

/**
 * str_find_char - find a character in a string
 * @strin: string
 * @f: character
 * Return: pointer
 */
char *str_find_char(char *strin, char f)
{
	do {
		if (*strin == f)
			return (strin);
	} while (*strin++ != '\0');

	return (NULL);
}
