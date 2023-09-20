#include "shell.h"

/**
 **set_mem - fills memory with bytes
 *@p: pointer
 *@byte: source of the byte
 *@n_b: nbr of bytes
 *Return: pointer
 */
char *set_mem(char *p, char byte, unsigned int n_b)
{
	unsigned int i;

	for (i = 0; i < n_b; i++)
		p[i] = byte;
	return (p);
}

/**
 * str_free - array of string is freed
 * @str: string
 */
void str_free(char **string)
{
	char **p = string;

	if (!string)
		return;
	while (*string)
		free(*string++);
	free(p);
}

/**
 * realloc_mem - realloc
 * @ptr: pointer
 * @size_old: size of previous block
 * @size_new: size of new block
 *
 * Return: pointer
 */
void *realloc_mem(void *ptr, unsigned int size_old, unsigned int size_new)
{
	char *p;

	if (!ptr)
		return (malloc(size_new));
	if (!size_new)
		return (free(ptr), NULL);
	if (size_new == size_old)
		return (ptr);

	p = malloc(size_new);
	if (!p)
		return (NULL);

	size_old = size_old < size_new ? size_old : size_new;
	while (size_old--)
		p[size_old] = ((char *)ptr)[size_old];
	free(ptr);
	return (p);
}
