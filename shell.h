#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3


/**
 * struct liststr - for a singly-linked list
 * @num: number
 * @str: string
 * @next: points to next
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;
/**
 *struct passinfo - allows uniform prototype for function pointer struct
 *@arg: a string from getline function
 *@readfd: file descriptor
 *@histcount: history line counter
 *@argv: strings generated from arg
 *@path: path for the current command
 *@status: status of the exxecuted command
 *@cmd_buf: address of pointer to cmd buffer
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@argc: argument count
 *@line_count: error count
 *@err_num: error exit code
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias:node representing  alias
 *@env_changed: if the environment id chaged
 *@linecount_flag: if on count this line of input
 *@fname: filename
 *@env: local copy of environment
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char **environ;
	int env_changed;
	int status;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	list_t *env;
	list_t *history;
	list_t *alias;
	int linecount_flag;
	char *fname;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}


/**
 *struct builtin - a built in string and its function
 *@type: flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int loophsh(char **);

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char **strtow(char *, char *);
char **strtow2(char *, char);


char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);


int bfree(void **);


int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);


int _myhistory(info_t *);
int _myalias(info_t *);

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

extern char **environ;

#endif
