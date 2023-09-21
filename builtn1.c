#include "shell.h"

/**
 * print_history - Print history list.
 * @info: Structure containing arguments.
 *
 * Return: Always 0
 */
int print_history(infocmd *info)
{
    print_list(info->history);
    return 0;
}

/**
 * unsetAlias - Unset alias.
 * @info: struct infocmd
 * @s: Alias string
 *
 * Return: 0 if OK, 1 if fails
 */
int unsetAlias(infocmd *info, char *s)
{
    char *p, c;
    int rt;

    p = str_find_char(s, '=');
    if (!p)
        return 1;
    c = *p;
    *p = 0;
    rt = del_node_index(&(info->alias),
        node_index(info->alias, node_start(info->alias, s, -1)));
    *p = c;
    return rt;
}

/**
 * setAlias - Set alias.
 * @info: struct info cmd
 * @s: Alias string
 *
 * Return: 0 if OK, 1 if fails
 */
int setAlias(infocmd *info, char *s)
{
    char *p;

    p = str_find_char(s, '=');
    if (!p)
        return 1;
    if (!*++p)
        return unsetAlias(info, s);

    unsetAlias(info, s);
    return (add_end_node(&(info->alias), s, 0) == NULL);
}

/**
 * printAlias - Prints an alias string.
 * @n: Alias node
 *
 * Return: 0 if OK, 1 if fails
 */
int printAlias(liststr *n)
{
    char *ptt = NULL, *a = NULL;

    if (n)
    {
        ptt = str_find_char(n->s, '=');
        for (a = n->s; a <= ptt; a++)
            putchar(*a);
        putchar('\'');
        fputs(ptt + 1, stdout);
        puts("'");
        return 0;
    }
    return 1;
}

/**
 * man_alias - Manage alias.
 * @info: Structure containing arguments.
 *
 * Return: Always 0
 */
int man_alias(infocmd *info)
{
    int i = 0;
    char *p = NULL;
    liststr *n = NULL;

    if (info->argc == 1)
    {
        n = info->alias;
        while (n)
        {
            printAlias(n);
            n = n->next;
        }
        return 0;
    }
    for (i = 1; info->argv[i]; i++)
    {
        p = str_find_char(info->argv[i], '=');
        if (p)
            setAlias(info, info->argv[i]);
        else
            printAlias(node_start(info->alias, info->argv[i], '='));
    }

    return 0;
}
