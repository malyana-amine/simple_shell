#include "shell.h"

/**
 * str_length - get the length of a string
 * @strin: a string
 *
 * Return: int
 */
int str_length(char *strin)
{
	int i = 0;

	if (!strin)
		return (0);

	while (*strin++)
		i++;
	return (i);
}

/**
 * str_comparison - lexicogarphic comparison
 * @strin1: string 1
 * @strin2: string 2
 *
 * Return: <0 if (strin1 < strin2) and >0 if (strin1 > strin2) and 0 if (s1 == s2)
 */
int str_comparison(char *strin1, char *strin2)
{
	while (*strin1 && *strin2)
	{
		if (*strin1 != *strin2)
			return (*strin1 - *strin2);
		strin1++;
		strin2++;
	}
	if (*strin1 == *strin2)
		return (0);
	else
		return (*strin1 < *strin2 ? -1 : 1);
}

/**
 * starts_with - checks if a string starts with a string
 * @strin: string
 * @subst: substring
 *
 * Return: pointer or NULL
 */
char *starts_with(const char *strin, const char *subst)
{
	while (*subst)
		if (*subst++ != *strin++)
			return (NULL);
	return ((char *)strin);
}

/**
 * str_cat - concatenates two strings
 * @d: the first string
 * @s: the second string
 *
 * Return: pointer to destination buffer
 */
char *str_cat(char *d, char *s)
{
	char *res = d;

	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (res);
}
