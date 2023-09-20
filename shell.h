#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_get_line 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - A structure to hold numeric and string
 * data in a linked list.
 * @n: Numeric value associated with the node.
 * @s: String value associated with the node.
 * @next: Pointer to the next node in the linked list.
 */
typedef struct liststr
{
	int n;
	char *s;
	struct liststr *next;
} liststr;

/**
 *struct info - contains pseudo-argargarguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@argargarg: a string generated from getline containing argargarguements
 *@argargargv: an array of strings generated from argargarg
 *@path: a string path for the current command
 *@argargargc: the argargargument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct info
{
	char *argargarg;
	char **argargargv;
	char *path;
	int argargargc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	liststr *env;
	liststr *history;
	liststr *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} infocmd;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(infocmd *);
} builtin_table;


/* shell_loop.c */
int shell_loop(infocmd *, char **);
int find_buil(infocmd *);
void path_cmd(infocmd *);
void fork_cmd(infocmd *);

/* fctString2.c */
int fct_cmd(infocmd *, char *);
char *fct_duplicate(char *, int, int);
char *fct_path(infocmd *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* err1.c */
void er_puts(char *);
int e_put_char(char);
int put_file(char c, int fd);
int puts_file2(char *str, int fd);

/* fctString.c */
int str_length(char *);
int str_comparison(char *, char *);
char *starts_with(const char *, const char *);
char *str_cat(char *, char *);

/* fctString1.c */
char *str_copy(char *, char *);
char *str_duplicate(const char *);
void str_puts(char *);
int _put_char(char);

/* exits.c */
char *str_ncopy(char *, char *, int);
char *str_ncat(char *, char *, int);
char *str_find_char(char *, char);

/* fctString3.c */
char **str_to_words(char *, char *);
char **str_to_words2(char *, char);

/* allocation.c */
char *set_mem(char *, char, unsigned int);
void str_free(char **);
void *realloc_mem(void *, unsigned int, unsigned int);

/* mem.c */
int free_mem(void **);

/* fctString4.c */
int fct_active(infocmd *);
int fct_delim(char, char *);
int fct_alphabetic(int);
int fct_conv(char *);

/* err2.c */
int er_conv(char *);
void er_print(infocmd *, char *);
int fct_decimal(int, int);
char *conv_number(long int, int, int);
void fct_remove(char *);

/* builtin.c */
int fct_exit(infocmd *);
int fct_current(infocmd *);
int fct_help(infocmd *);

/* builtin1.c */
int print_history(infocmd *);
int man_alias(infocmd *);

/* fctBuffer.c */
ssize_t extract_input(infocmd *);
int _get_line(infocmd *, char **, size_t *);
void sigint_handler(int);

/* getinfo.c */
void unset_info(infocmd *);
void set_info(infocmd *, char **);
void lib_info(infocmd *, int);

/* env.c */
char *get_var_env(infocmd *, const char *);
int cur_env(infocmd *);
int set_env_val(infocmd *);
int unset_env_val(infocmd *);
int init_env_list(infocmd *);

/* get_env.c */
char **get_env(infocmd *);
int unset_env(infocmd *, char *);
int set_env(infocmd *, char *, char *);

/* fctHistory.c */
char *history_file(infocmd *info);
int create_history(infocmd *info);
int read_history(infocmd *info);
int build_history_list(infocmd *info, char *buf, int linecount);
int renum_history(infocmd *info);

/* lists.c */
liststr *add_to_node(liststr **, const char *, int);
liststr *add_end_node(liststr **, const char *, int);
size_t print_list(const liststr *);
int del_node_index(liststr **, unsigned int);
void free_list(liststr **);

/* lists1.c */
size_t list_length(const liststr *);
char **list_string(liststr *);
size_t fct_list(const liststr *);
liststr *node_start(liststr *, char *, char);
ssize_t node_index(liststr *, liststr *);

/* vars.c */
int fct_chain(infocmd *, char *, size_t *);
void fct_check(infocmd *, char *, size_t *, size_t, size_t);
int rep_alias(infocmd *);
int rep_vars(infocmd *);
int rep_string(char **, char *);

#endif
