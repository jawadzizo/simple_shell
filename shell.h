#ifndef SHELL_H
#define SHELL_H

#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


extern char **environ;


#define FREE(x) free(x);x=NULL   /* be careful of "macro expands to multiple statements" error */
#define print(fd,x) write(fd,x,_strlen(x))


#define BUFFER_SIZE 4096         /* the buffer to hold the whole command line*/
#define SEP_LIMIT 3              /* limit of characters in the separators*/
#define ARGS_MAX 128             /* limit of arguments passed to execve */
#define SEP_MAX ARGS_MAX         /* limit of separators */
#define CHARS_MAX ARGS_MAX       /* limit of characters for each alias */


#define TRUE 1
#define FALSE 0


#define CONTINUE TRUE
#define STOP FALSE


typedef int bool;


/**
 * separator_t - Typedef for the separators as enum
 * @_or: enum for the "||" operator
 * @_and: enum for the "&&" operator
 * @_semi_colon: enum for the ";" operator
 * @_comment: enum for the "#" operator
 */
typedef enum separator_e
{
	_or, 			/* "||" */
	_and, 			/* "&&" */
	_semi_colon, 	/* ";" */
	_comment 		/* " #" */
}separator_t;


/**
 * alias_t - Typedef for the alias linked list
 * @name: name of the alias node
 * @value: value of the alias node
 * @next: pointer to the next alias node
 */
typedef struct alias_s
{
	char name[CHARS_MAX];
	char value[CHARS_MAX];
	struct alias_s *next;
}alias_t;


/**
 * command_t - Typedef for the command structure
 * @count: counts the executed commands, increments whenever a command is executed
 * @status: the return value of the last executed command
 * @status_str: the exit status as a string, 3 is the maximim number of digits
 * @line: holds the line from _getline
 * @section: separated by separators
 * @separator: separators enum array
 * @argument: the tokens of the section
 * @shell_id: the pid of the simple shell
 * @shell_id_str: the pid of the simple shell as a string, pid limit is 4194304 on 64-bit machines, so 7 characters
 * @path: absolute path to the command's executable if it's not a built-in command
 * @alias: the head pointer to the first alias node
 * @shell_name: the name of the simple shell
 */
typedef struct command_s
{
	int count;
	int status;
	char status_str[4];

	char line[BUFFER_SIZE];
	char *section[ARGS_MAX];
	separator_t separator[ARGS_MAX];
	char *argument[ARGS_MAX];

	pid_t shell_id;
	char shell_id_str[8];
	char path[PATH_MAX];

	alias_t *alias;

	char *shell_name;
}command_t;


/* command setting functions */
void map_sections(command_t *cmd, char *line);
void map_arguments(command_t *cmd, char *section);
void map_variable(command_t *cmd, char **argument);
bool find_command_path(command_t *cmd);
void print_command_not_found(command_t *cmd);

/*helpers 1*/
int set_input_stream(int argc, char **argv);
void initialise_command(command_t *command, char *shell_name);
void remove_newline(char *line);
bool is_line_empty(command_t *cmd);
void print_prompt(int is_terminal);

/* helpers 2*/
void *checked_malloc(size_t size);
bool is_path(char *command);
bool is_name_value(char *alias);
bool is_command_found(command_t *cmd);
bool is_built_in(command_t *cmd);


/*string related functions*/
size_t _strlen(const char *string);
char *_strcat(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
int _atoi(char *string);
char *_itoa(int number, char *str);


/*token functions*/
int _getline(char *line, int size, int fd);
char *_strtok(char *string, const char **delimiter, separator_t *separator);
void set_anchor(char **anchor, const char **delimiter, separator_t *separator);
bool is_token_empty(char **anchor, char **token, const char **delimiter);
bool is_delimiter(char **anchor, const char **delimiter, separator_t *separator);


/*environment functions*/
char *_getenv(const char *env_var);
void _setenv(char **arguments, bool *is_environ_allocated);
void _unsetenv(char *name, bool is_environ_allocated);
void free_environ();
void _env();


/*alias related functions*/
void _alias(command_t *cmd);
void add_alias(alias_t **head, char *alias_content);
char *find_alias(alias_t *head, char *name);
void print_alias(alias_t *head, char *to_find);
void free_alias_nodes(alias_t *head);


/*exit*/
void __exit(command_t *cmd, bool *is_environ_allocated);
bool is_positive_digit(char *string);
void print_illegal_number_error(command_t *cmd);


/*execution*/
void run_built_in_command(command_t *cmd, bool *is_environ_allocated);
void run_command_in_new_process(command_t *cmd);
bool find_next_command(command_t *cmd, int *index);


/*change directory*/
void cd(command_t *cmd, bool *is_environ_allocated);
void cd_home(bool *is_environ_allocated);
void cd_back(bool *is_environ_allocated);
void cd_error(command_t *cmd);
void change_dir_env(char *name, char *value, bool *is_environ_allocated);


#endif

