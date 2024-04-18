#include "shell.h"


/**
 * __exit - exit the shell
 * @cmd: a pointer to a structure that holds the required data
 * @is_environ_allocated: a pointer that tells us if environ is malloc'd or not
 */
void __exit(command_t *cmd, bool is_environ_allocated)
{
	int exit_status;

	if (cmd->argument[1] == NULL)
	{
		if (is_environ_allocated)
			free_environ();

		free_alias_nodes(cmd->alias);
		exit(cmd->status);
	}
	
	else if (is_positive_digit(cmd->argument[1]))
	{
		if (is_environ_allocated)
			free_environ();

		free_alias_nodes(cmd->alias);
		exit_status = _atoi(cmd->argument[1]);
		exit(exit_status);
	}

	print_illegal_number_error(cmd);
	cmd->status = 2;

}


/**
 * is_positive_digit - checks if the string consists only of digits
 * @string: the string to check if it's a number
 * Return: true if the string is a number, false otherwise
 */
bool is_positive_digit(char *string)
{
	int i;

	if (string == NULL)
		return (FALSE);

	for (i = 0; string[i] != '\0'; i++)
	{
		if ((string[i] > '9') || (string[i] < '0'))
			return (FALSE);
	}

	return (TRUE);
}


/**
 * print_illegal_number_error - prints an error if a non-number passed to exit
 * @cmd: a pointer to a structure that holds the required data
 */
void print_illegal_number_error(command_t *cmd)
{
	char *illegal_number = "Illegal number";
	char *colon = ": ";
	char command_count[9];
	_itoa(cmd->count, command_count);

	print(STDERR_FILENO, cmd->shell_name);
	print(STDERR_FILENO, colon);
	print(STDERR_FILENO, command_count);
	print(STDERR_FILENO, colon);
	print(STDERR_FILENO, cmd->argument[0]);
	print(STDERR_FILENO, colon);
	print(STDERR_FILENO, illegal_number);
	print(STDERR_FILENO, colon);
	print(STDERR_FILENO, cmd->argument[1]);
	print(STDERR_FILENO, "\n");
}

