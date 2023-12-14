#ifndef SHELL_H
#define SHELL_H

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
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* for convertNumber() */
#define CONVERT_LOWERCASE      1
#define CONVERT_UNSIGNED       2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK  0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;


/**
 * struct liststr - singly linked list
 *
 * @num: number field
 *
 * @str: string
 *
 * @next: pointer to next node
 *
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo arguments to pass
 * into a function, allowing uniform prototype for function
 * pointer struct
 * @arg: a string generated from getline
 * @argv: argument vector
 * @path: string path for the current command
 * @argc: argument count
 * @line_count: error count
 * @err_num: error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: program filename
 * @env: linked list.local
 * @environ: custom modified copy of environ from LL env
 * @history: history node
 * @alias: alias node
 * @env_changed: on if environ was changed
 * @status: return status of last executed command
 * @cmd_buf: address of pointer
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fd from which to read line input
 * @histcount: history line number count
 *
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	info cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 *
 * @type: builtin command flag
 *
 * @func: function
 *
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_loop.c */
int hsh(info_t *, char **);
int findBuiltin(info_t *);
void findCommand(info_t *);
void fork_cmd(info_t *);

/* toem_cmd.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *findPath(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *startString(const char *, const char *);
char *_strcat(char *, char *);

/* toem_strings.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_strtok.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_alloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_mem.c */
int bfree(void **);

/* toem_atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_err_ors.c */
int _erratoi(char *);
void printError(info_t *, char *);
int print_d(int, int);
char *convertNumber(long int, int, int);
void removeComments(char *);

/* toem_Builtin.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* toem_alias.c */
int myHistory(info_t *);
int unsetAlias(info_t *);
int setAlias(info *, char *);
int printAlias(list_t *);
int _myalias(info_t *);

/* toem_getline.c */
ssize_t get_input(info_t *);
ssize_t input_buf(info_t *, char **, size_t *);
ssize_t read_buf(info_t *, char *, size_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* toem_info.c */
void clearInfo(info_t *);
void setInfo(info_t *, char **);
void freeInfo(info_t *, int);

/* toem_environ.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* toem_envs.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* toem_histories.c */
char *getHfile(info_t *info);
int writeHistory(info_t *info);
int readHistory(info_t *info);
int buildHlist(info_t *info, char *buf, int linecount);
int renumberHistory(info_t *info);

/* toem_list.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* toem_lists.c */
size_t listLength(const list_t *);
char **listStrings(list_t *);
size_t printList(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t getIndexnode(list_t *, list_t *);

/* toem_vars.c */
int isChain(info_t *, char *, size_t *);
void checkChain(info_t *, char *, size_t *, size_t, size_t);
int replaceAlias(info_t *);
int replaceVars(info_t *);
int replaceString(char **, char *);

#endif
