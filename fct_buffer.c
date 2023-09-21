#include "shell.h"

/**
 * inputBuffer - Read a line of input into a buffer.
 * @info: struct infocmd
 * @bfr: address of buffer
 * @l: pointer to length variable
 *
 * Return: bytes read
 */
ssize_t inputBuffer(infocmd *info, char **bfr, size_t *l)
{
    ssize_t r = 0;
    size_t len_p = 0;

    if (!*l)
    {
        free(*bfr);
        *bfr = NULL;
        signal(SIGINT, sigint_handler);

        /* Use getline or _get_line based on a condition (USE_get_line) */
        r = USE_get_line ? getline(bfr, &len_p, stdin) : _get_line(info, bfr, &len_p);

        if (r > 0)
        {
            if ((*bfr)[r - 1] == '\n')
            {
                (*bfr)[r - 1] = '\0';
                r--;
            }
            info->linecount_flag = 1;
            fct_remove(*bfr);
            build_history_list(info, *bfr, info->histcount++);
            *l = r;
            info->cmd_buf = bfr;
        }
    }
    return r;
}

/**
 * extract_input - Extract input line minus the newline.
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t extract_input(infocmd *info)
{
    static char *b;
    static size_t i, j, l;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    _put_char(BUF_FLUSH);
    r = inputBuffer(info, &b, &l);
    if (r == -1)
        return -1;
    if (l)
    {
        j = i;
        p = b + i;

        fct_check(info, b, &j, i, l);
        while (j < l)
        {
            if (fct_chain(info, b, &j))
                break;
            j++;
        }

        i = j + 1;
        if (i >= l)
        {
            i = l = 0;
            info->cmd_buf_type = CMD_NORM;
        }

        *buf_p = p;
        return str_length(p);
    }

    *buf_p = b;
    return r;
}

/**
 * readBuffer - Read a buffer.
 * @info: struct infocmd
 * @b: buffer
 * @i: size of the buffer
 *
 * Return: buffer
 */
ssize_t readBuffer(infocmd *info, char *b, size_t *i)
{
    ssize_t r = 0;

    if (*i)
        return 0;
    r = read(info->readfd, b, READ_BUF_SIZE);
    if (r >= 0)
        *i = r;
    return r;
}

/**
 * _get_line - Get the next line from STDIN.
 * @info: struct infocmd
 * @pt: address of pointer to buffer
 * @length: size of preallocated buffer
 *
 * Return: s
 */
int _get_line(infocmd *info, char **pt, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *pt;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = readBuffer(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return -1;

    c = str_find_char(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = realloc_mem(p, s, s ? s + k : k + 1);
    if (!new_p)
        return p ? free(p), -1 : -1;

    if (s)
        str_ncat(new_p, buf + i, k - i);
    else
        str_ncopy(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *pt = p;
    return s;
}

/**
 * sigint_handler - Signal handler for Ctrl-C (SIGINT).
 * @sn: the signal number
 *
 * This function is called when Ctrl-C is pressed. You can customize its behavior.
 */
void sigint_handler(__attribute__((unused)) int sn)
{
    str_puts("\n");
    str_puts("$ ");
    _put_char(BUF_FLUSH);
}
