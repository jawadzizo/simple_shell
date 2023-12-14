#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>

extern char **environ;

extern int arguments_length;
extern int arguments_length_each[64];
extern int arguments_position[64];
extern char **arguments_for_execve;

extern char *execve_path;

extern int path_length;
extern char **path;

extern int command_count;
extern char *command;


#define BUFFSIZE 1024



int _strlen(const char *string);
char * _strcon(char * string1, char *string2);
int _strncmp(const char *string1, const char *string2, int length);
int str_to_int(char *string);
char* int_to_str(int number);


void command_line_arguments_counter(char *text);
void arguments_reset();
void allocate_execve(char *text);
int find_execve_path();



int check_built_in();
void the_exit();
void print_environment();


void remove_command_new_line(int command_length);
void command_not_found(char *program_name);
void eof_reached();



char *_getenv(const char *name);
void allocate_path();



#endif