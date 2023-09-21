#include "shell.h"

/**
 * fct_exit - Handle shell exit command.
 * @in: Pointer to the shell information struct.
 *
 * Return: Signal to terminate shell or error code.
 */
int fct_exit(infocmd *in)
{
    int ex;

    if (in->argv[1])
    {
        ex = er_conv(in->argv[1]);
        if (ex == -1)
        {
            in->status = 2;
            er_print(in, "Illegal number: ");
            er_puts(in->argv[1]);
            e_put_char('\n');
            return 1;
        }
        in->err_num = ex; // Set err_num with the valid value
        return -2;
    }
    in->err_num = -1;
    return -2;
}

/**
 * fct_current - Handle shell 'cd' command.
 * @in: Pointer to the shell information struct.
 *
 * Return: 0 on success, 1 on informational output, -1 on failure.
 */
int fct_current(infocmd *in)
{
    char buffer[1024];
    int rt;

    if (!getcwd(buffer, 1024))
    {
        str_puts("TODO: >>getcwd failure emsg here<<\n");
        return -1; // Handle getcwd failure
    }

    if (!in->argv[1])
    {
        const char *home = get_var_env(in, "HOME=");
        const char *pwd = get_var_env(in, "PWD=");
        const char *target = home ? home : pwd ? pwd : "/";
        rt = chdir(target);
    }
    else if (str_comparison(in->argv[1], "-") == 0)
    {
        const char *oldpwd = get_var_env(in, "OLDPWD=");
        if (!oldpwd)
        {
            str_puts(buffer);
            _put_char('\n');
            return 1;
        }
        str_puts(oldpwd);
        _put_char('\n');
        rt = chdir(oldpwd ? oldpwd : "/");
    }
    else
    {
        rt = chdir(in->argv[1]);
    }

    if (rt == -1)
    {
        er_print(in, "can't cd to ");
        er_puts(in->argv[1]);
        e_put_char('\n');
        return -1;
    }
    else
    {
        set_env(in, "OLDPWD", get_var_env(in, "PWD="));
        set_env(in, "PWD", getcwd(buffer, 1024));
    }
    return 0;
}

/**
 * fct_help - Handle shell 'help' command.
 * @in: Pointer to the shell information struct.
 *
 * Return: Always returns 0.
 */
int fct_help(infocmd *in)
{
    str_puts("help call works. Function not yet implemented \n");
    return 0;
}
