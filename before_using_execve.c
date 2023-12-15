#include "main.h"




/**
 * eof_reached - a function to check if we reached end of file.
 */
void eof_reached(void)
{
	free_path();
	free(command);

	if (terminal == 1)
		write(STDOUT_FILENO, "\n", 1);

	exit(0);
}


/**
 * remove_command_new_line - a function to remove the last new line character.
 * @command_length: the length of the string to remove the character from.
 */
void remove_command_new_line(int command_length)
{
	int i;

	for (i = 0; i < command_length; i++)
	{
		if (command[i] == '\n')
		{
			command[i] = '\0';
			break;
		}
	}
}


/**
 * command_not_found - a function to check if the command is found.
 * @program_name: the program name (argv[0]).
 */
void command_not_found(char *program_name)
{
	char *missing = "not found\n";
	char *separator = ": ";
	char *command_count_string = int_to_str(command_count);

	char *first_argument = arguments_for_execve[0];

	write(STDOUT_FILENO, program_name, _strlen(program_name));
	write(STDOUT_FILENO, separator, _strlen(separator));
	write(STDOUT_FILENO, command_count_string, _strlen(command_count_string));
	write(STDOUT_FILENO, separator, _strlen(separator));
	write(STDOUT_FILENO, first_argument, _strlen(first_argument));
	write(STDOUT_FILENO, separator, _strlen(separator));
	write(STDOUT_FILENO, missing, _strlen(missing));

	free(command_count_string);

	if (terminal == 0)
		exit(127);
}
