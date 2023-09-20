#include "shell.h"

/**
 * free_mem - Frees memory allocated for a pointer and sets it to NULL.
 * @p: Pointer to the pointer to be freed.
 *
 * Return: 1 if memory was freed, 0 if not.
 */
int free_mem(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
