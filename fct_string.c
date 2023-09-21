#include "shell.h"

/**
 * str_length - Get the length of a string.
 * @str: A string.
 *
 * Return: Length of the string or 0 if NULL.
 */
int str_length(const char *str)
{
    int length = 0;

    if (str != NULL)
    {
        while (*str != '\0')
        {
            length++;
            str++;
        }
    }

    return length;
}

/**
 * str_comparison - Lexicographic comparison of two strings.
 * @str1: String 1.
 * @str2: String 2.
 *
 * Return:
 *   < 0 if str1 < str2
 *   > 0 if str1 > str2
 *   0 if str1 == str2
 */
int str_comparison(const char *str1, const char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);
        str1++;
        str2++;
    }

    return (*str1 - *str2);
}

/**
 * starts_with - Check if a string starts with a substring.
 * @str: String.
 * @substr: Substring.
 *
 * Return: Pointer to the start of the substring in str or NULL if not found.
 */
const char *starts_with(const char *str, const char *substr)
{
    while (*substr)
    {
        if (*substr != *str)
            return NULL;
        substr++;
        str++;
    }

    return str;
}

/**
 * str_cat - Concatenate two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: Pointer to the destination buffer.
 */
char *str_cat(char *dest, const char *src)
{
    char *result = dest;

    while (*dest)
        dest++;

    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';

    return result;
}
