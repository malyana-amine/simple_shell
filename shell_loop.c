#include "shell.h"

/**
 * shell_loop - Execute the main shell loop.
 * @pin: Pointer to the infocmd struct containing shell information.
 * @astr: Array of strings containing command line arguments.
 *
 * Return: the status code to indicate the exit condition of the shell.
 */
int shell_loop(infocmd *pin, char **astr)
{
	ssize_t i = 0;
	int ret = 0;

	while (i != -1 && ret != -2)
	{
		unset_info(pin);
		if (fct_active(pin))
			str_puts("$ ");
		e_put_char(BUF_FLUSH);
		i = extract_input(pin);
		if (i != -1)
		{
			set_info(pin, astr);
			ret = find_buil(pin);
			if (ret == -1)
				path_cmd(pin);
		}
		else if (fct_active(pin))
			_put_char('\n');
		lib_info(pin, 0);
	}
	create_history(pin);
	lib_info(pin, 1);
	if (!fct_active(pin) && pin->status)
		exit(pin->status);
	if (ret == -2)
	{
		if (pin->err_num == -1)
			exit(pin->status);
		exit(pin->err_num);
	}
	return (ret);
}

/**
 * find_buil - Find and execute a built-in command.
 * @pin: Pointer to the infocmd struct containing shell information.
 *
 * Return: the result of executing the built-in command or -1 if the command
 * is not found.
 */
int find_buil(infocmd *pin)
{
	int i, ret = -1;
	builtin_table table[] = {
		{"exit", fct_exit},
		{"env", cur_env},
		{"help", fct_help},
		{"history", print_history},
		{"set_env", set_env_val},
		{"unset_env", unset_env_val},
		{"cd", fct_current},
		{"alias", man_alias},
		{NULL, NULL}
	};

	for (i = 0; table[i].type; i++)
		if (str_comparison(pin->argv[0], table[i].type) == 0)
		{
			pin->line_count++;
			ret = table[i].func(pin);
			break;
		}
	return (ret);
}

/**
 * path_cmd - Handle non-built-in commands by searching in the PATH.
 * @pin: Pointer to the infocmd struct containing shell information.
 *
 * Return: none
 */
void path_cmd(infocmd *pin)
{
	char *th = NULL;
	int i, j;

	pin->path = pin->argv[0];
	if (pin->linecount_flag == 1)
	{
		pin->line_count++;
		pin->linecount_flag = 0;
	}
	for (i = 0, j = 0; pin->arg[i]; i++)
		if (!fct_delim(pin->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	th = fct_path(pin, get_var_env(pin, "PATH="), pin->argv[0]);
	if (th)
	{
		pin->path = th;
		fork_cmd(pin);
	}
	else
	{
		if ((fct_active(pin) || get_var_env(pin, "PATH=")
			|| pin->argv[0][0] == '/') && fct_cmd(pin, pin->argv[0]))
			fork_cmd(pin);
		else if (*(pin->arg) != '\n')
		{
			pin->status = 127;
			er_print(pin, "not found\n");
		}
	}
}

/**
 * fork_cmd - Fork and execute a command in a child process.
 * @pin: Pointer to the infocmd struct containing shell information.
 *
 * Return: none
 */
void fork_cmd(infocmd *pin)
{
	pid_t id;

	id = fork();
	if (id == -1)
	{
		perror("Error:");
		return;
	}
	if (id == 0)
	{
		if (execve(pin->path, pin->argv, get_env(pin)) == -1)
		{
			lib_info(pin, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(pin->status));
		if (WIFEXITED(pin->status))
		{
			pin->status = WEXITSTATUS(pin->status);
			if (pin->status == 126)
				er_print(pin, "Permission denied\n");
		}
	}
}
