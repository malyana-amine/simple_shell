#include "shell.h"

/**
 * fct_exit - Handle shell exit command.
 * @in: Pointer to the shell information struct.
 *
 * return: Signal to terminate shell or error code.
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
			return (1);
		}
		in->err_num = er_conv(in->argv[1]);
		return (-2);
	}
	in->err_num = -1;
	return (-2);
}

/**
 * fct_current - Handle shell 'cd' command.
 * @in: Pointer to the shell information struct.
 *
 * return: 0 on success, 1 on informational output, -1 on failure.
 */
int fct_current(infocmd *in)
{
	char *str, *d, buffer[1024];
	int rt;

	str = getcwd(buffer, 1024);
	if (!str)
		str_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!in->argv[1])
	{
		d = get_var_env(in, "HOME=");
		if (!d)
			rt = chdir((d = get_var_env(in, "PWD=")) ? d : "/");
		else
			rt = chdir(d);
	}
	else if (str_comparison(in->argv[1], "-") == 0)
	{
		if (!get_var_env(in, "OLDPWD="))
		{
			str_puts(str);
			_put_char('\n');
			return (1);
		}
		str_puts(get_var_env(in, "OLDPWD=")), _put_char('\n');
		rt = chdir((d = get_var_env(in, "OLDPWD=")) ? d : "/");
	}
	else
		rt = chdir(in->argv[1]);
	if (rt == -1)
	{
		er_print(in, "can't cd to ");
		er_puts(in->argv[1]), e_put_char('\n');
	}
	else
	{
		set_env(in, "OLDPWD", get_var_env(in, "PWD="));
		set_env(in, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * fct_help - Handle shell 'help' command.
 * @in: Pointer to the shell information struct.
 *
 * return: Always rturns 0.
 */
int fct_help(infocmd *in)
{
	char **arr;

	arr = in->argv;
	str_puts("help call works. Function not yet implemented \n");
	if (0)
		str_puts(*arr);
	return (0);
}
