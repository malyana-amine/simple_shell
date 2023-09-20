#include "shell.h"

/**
 * er_puts - Print a string to stderr.
 * @sp: Source string to be printed.
 *
 * Return: None.
 */
void er_puts(char *sp)
{
	int i = 0;

	if (!sp)
		return;
	while (sp[i] != '\0')
	{
		e_put_char(sp[i]);
		i++;
	}
}

/**
 * e_put_char - Write a character to stderr or flush buffer.
 * @stri: Character to be written or BUF_FLUSH to flush.
 *
 * Return: 1 after writing or flushing.
 */
int e_put_char(char stri)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (stri == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (stri != BUF_FLUSH)
		buffer[i++] = stri;
	return (1);
}

/**
 * put_file - Write a character to a file or flush buffer.
 * @stri: Character to be written or BUF_FLUSH to flush.
 * @file: File descriptor to write to.
 *
 * Return: 1 after writing or flushing.
 */
int put_file(char stri, int file)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (stri == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(file, buffer, i);
		i = 0;
	}
	if (stri != BUF_FLUSH)
		buffer[i++] = stri;
	return (1);
}

/**
 * puts_file2 - Write a string to a file.
 * @stri: Source string to be written.
 * @file: File descriptor to write to.
 *
 * Return: Number of characters written.
 */
int puts_file2(char *stri, int file)
{
	int i = 0;

	if (!stri)
		return (0);
	while (*stri)
	{
		i += put_file(*stri++, file);
	}
	return (i);
}
