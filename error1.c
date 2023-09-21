#include "shell.h"

/**
 * er_puts - Print a string to stderr.
 * @sp: Source string to be printed.
 *
 * This function prints a string to the standard error (stderr) stream.
 *
 * Return: None.
 */
void er_puts(char *sp)
{
    if (!sp)
        return;

    while (*sp != '\0')
    {
        e_put_char(*sp);
        sp++;
    }
}

/**
 * e_put_char - Write a character to stderr or flush buffer.
 * @stri: Character to be written or BUF_FLUSH to flush.
 *
 * This function writes a character to the standard error (stderr) stream
 * or flushes the buffer if it's full or if `stri` is BUF_FLUSH.
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
    return 1;
}

/**
 * put_file - Write a character to a file or flush buffer.
 * @stri: Character to be written or BUF_FLUSH to flush.
 * @file: File descriptor to write to.
 *
 * This function writes a character to the specified file descriptor
 * or flushes the buffer if it's full or if `stri` is BUF_FLUSH.
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
    return 1;
}

/**
 * puts_file2 - Write a string to a file.
 * @stri: Source string to be written.
 * @file: File descriptor to write to.
 *
 * This function writes a string to the specified file descriptor.
 *
 * Return: Number of characters written.
 */
int puts_file2(char *stri, int file)
{
    int count = 0;

    if (!stri)
        return 0;

    while (*stri)
    {
        count += put_file(*stri, file);
        stri++;
    }

    return count;
}
