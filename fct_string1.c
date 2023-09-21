#include "shell.h"

/**
 * str_copy - Copy a string to another.
 * @ds: Destination string.
 * @sc: Source string.
 *
 * Return: Pointer to the destination string 'ds'.
 */
char *str_copy(char *ds, char *sc)
{
	int i = 0;

	if (ds == sc || sc == 0)
		return (ds);
	while (sc[i])
	{
		ds[i] = sc[i];
		i++;
	}
	ds[i] = 0;
	return (ds);
}

/**
 * str_duplicate - Create a duplicate of a string.
 * @std: Source string to be duplicated.
 *
 * Return: Pointer to the duplicated string, or NULL on failure.
 */
char *str_duplicate(const char *std)
{
	int lg = 0;
	char *r;

	if (std == NULL)
		return (NULL);
	while (*std++)
		lg++;
	r = malloc(sizeof(char) * (lg + 1));
	if (!r)
		return (NULL);
	for (lg++; lg--;)
		r[lg] = *--std;
	return (r);
}

/**
 * str_puts - Print a string to stdout.
 * @s: Source string to be printed.
 *
 * Return: None.
 */
void str_puts(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_put_char(s[i]);
		i++;
	}
}

/**
 * _put_char - Write a character to stdout or flush buffer.
 * @st: Character to be written or BUF_FLUSH to flush.
 *
 * Return: 1 after writing or flushing.
 */
int _put_char(char st)
{
    static int i;
    static char buffer[WRITE_BUF_SIZE];

    if (i >= WRITE_BUF_SIZE || st == BUF_FLUSH)
    {
        write(1, buffer, i);
        i = 0;
    }
    if (st != BUF_FLUSH)
        buffer[i++] = st;
    return (1);
}
