#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <dirent.h>

#define READ_BUF 1024
#define TOK_BUFSIZE 64

#define DELIM " \t\r\n\a"
#define AND_DELIM "&&"
#define OR_DELIM "||"

/* logical command type*/
#define LOGIC_AND 1
#define LOGIC_OR 2
#define NOT_FOUND 0

/* command type */
#define EXTERNAL_CMD 1
#define PATH_CMD 2
#define INTERNAL_CMD 3
#define INVALID_CMD -1

/* declaring global environ variable*/
extern char **environ;
/**
 * struct shell_data - Global data structure
 * @shell_name: the shell name at compile name
 * @old_pwd: old path
 * @aliases: aliases
 * @cmd_counter: counts the number of cmds executed
 * @error_status: error status
 */

typedef struct shell_data
{
	char *shell_name;
	char *old_pwd;
	char **aliases;
	int cmd_counter;
	int error_status;
} shell_i;

/**
 * struct internal_func - maps a command to a function
 * @cmd_name: command name
 * @func: the function that executes the command
 */

typedef struct internal_func
{
	char *cmd_name;
	void (*func)(char **comand, shell_i *);
} map_func;

/* bultin command*/
void env(char **, shell_i *);
void ch_dir(char **, shell_i *);
void quit(char **, shell_i *);
void display_help(char **, shell_i *);
void handle_setenv(char **, shell_i *);
void handle_unsetenv(char **, shell_i *);
void aliasFunc(char **, shell_i *);
void set_alias(char *, shell_i *);
char *alias_error(char **, shell_i *);

/* shell main*/
int main(int, char **);
shell_i *init_shell(shell_i *);

/* shell utilty function*/
void ctrl_C(int);
char *_getline(void);
char **tokenize(char *, const char *);
void shell_execute(char **, int, shell_i *);
int check_command(char *);
void execute(char **, int, shell_i *);
void shell_loop(shell_i *);
/* shell helper function*/
int print(char *, int);
void (*get_func(char *))(char **, shell_i *);
void non_interractive(shell_i *);
void free_tokenized(char **);
void comment_remover(char *);

/* shell string function*/
int _strlen(char *);
int _strcmp(char *, char *);
char *_strcpy(char *, char *);
char *_strcat(char *, char *);
char *_strdup(char *);
int _atoi(char *);
int is_delimeter(const char *, char);

/* shell string function 2*/
char *_strndup(char *, int);

/* shell memory management*/
void *_realloc(void *, unsigned int, unsigned int);
void clear_memory(shell_i *);

/*environment path*/
char *_getenv(char *);
char *check_path(char *);
int _setenv(char *, char *);
int _unsetenv(char *);
void replace_vars(char **, shell_i *);

/* logic function,*/
void execute_logic(char *, shell_i *);
char **logic_token(char *);
void logic_token_help(char *, shell_i *);

int endsWith(char *, char *);
int startsWith(char *, char *);
char *_itoa(int);

/* error function*/
void print_error(char **, shell_i *);
char *env_error(char **, shell_i *);
char *exit_error(char **, shell_i *);
char *invalid_cmd_error(char **, shell_i *);
char *chdir_error(char **, shell_i *);

#endif /* SHELL_H*/
