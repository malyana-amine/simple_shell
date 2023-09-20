#include "shell.h"

/**
 * addTopNode - add a node at the top of the list
 * @h: the head of the list
 * @str: string to add to the list
 * @n: index history
 *
 * Return: the head of the list
 */
liststr *addTopNode(liststr **h, const char *str, int n)
{
	liststr *new;

	if (!h)
		return (NULL);
	new = malloc(sizeof(liststr));
	if (!new)
		return (NULL);
	set_mem((void *)new, 0, sizeof(liststr));
	new->n = n;
	if (str)
	{
		new->str = str_duplicate(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *h;
	*h = new;
	return (new);
}

/**
 * add_end_node - Adds a new node at the end of a linked list.
 * @h: Pointer to the pointer of the linked list'str head.
 * @str: String value for the new node.
 * @n: Numeric value for the new node.
 *
 * Return: Pointer to the newly added node, or NULL on error.
 */
liststr *add_end_node(liststr **h, const char *str, int n)
{
	liststr *new, *node;

	if (!h)
		return (NULL);

	node = *h;
	new = malloc(sizeof(liststr));
	if (!new)
		return (NULL);
	set_mem((void *)new, 0, sizeof(liststr));
	new->n = n;
	if (str)
	{
		new->str = str_duplicate(str);
		if (!new->str)
		{
			free(new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*h = new;
	return (new);
}

/**
 * print_list - prints the strings of the list
 * @h: head of the list
 *
 * Return: size of list
 */
size_t print_list(const liststr *h)
{
	size_t i = 0;

	while (h)
	{
		str_puts(h->s ? h->s : "(nil)");
		str_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * del_node_index - deletes node at given index
 * @h: address of pointer to first node
 * @indx: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int del_node_index(liststr **h, unsigned int indx)
{
	liststr *node, *pnode;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!indx)
	{
		node = *h;
		*h = (*h)->next;
		free(node->s);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (i == indx)
		{
			pnode->next = node->next;
			free(node->s);
			free(node);
			return (1);
		}
		i++;
		pnode = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees the list
 * @h: head of the list
 *
 * Return: nothing
 */
void free_list(liststr **h)
{
	liststr *node, *nxnode, *head;

	if (!h || !*h)
		return;
	head = *h;
	node = head;
	while (node)
	{
		nxnode = node->next;
		free(node->s);
		free(node);
		node = nxnode;
	}
	*h = NULL;
}
