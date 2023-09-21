#include "shell.h"

/**
 * fct_active - Check if the shell is running in an active mode.
 * @pis: Pointer to infocmd struct.
 *
 * Return: 1 if active, else 0.
 */
int fct_active(infocmd *pis)
{
    return (isatty(STDIN_FILENO) && pis->readfd <= 2);
}

/**
 * fct_delim - Check if a character is a delimiter.
 * @strin: Character to be checked.
 * @del: String of delimiters to compare against.
 *
 * Return: 1 if 'strin' is a delimiter, else 0.
 */
int fct_delim(char strin, char *del)
{
    while (*del)
        if (*del++ == strin)
            return (1);
    return (0);
}

/**
 * fct_alphabetic - Check if a value represents an alphabetic character.
 * @vc: Value to be checked.
 *
 * Return: 1 if 'vc' is alphabetic, else 0.
 */
int fct_alphabetic(int vc)
{
    if ((vc >= 'a' && vc <= 'z') || (vc >= 'A' && vc <= 'Z'))
        return (1);
    else
        return (0);
}

/**
 * fct_conv - Convert a string to an integer.
 * @strin: Pointer to the input string.
 *
 * Return: The converted integer value.
 */
int fct_conv(char *strin)
{
    int i, sg = 1, fl = 0, put;
    unsigned int res = 0;

    for (i = 0; strin[i] != '\0' && fl != 2; i++)
    {
        if (strin[i] == '-')
            sg *= -1;

        if (strin[i] >= '0' && strin[i] <= '9')
        {
            fl = 1;
            res *= 10;
            res += (strin[i] - '0');
        }
        else if (fl == 1)
            fl = 2;
    }

    if (sg == -1)
        put = -res;
    else
        put = res;

    return (put);
}
