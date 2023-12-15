#include "main.h"






/**
 * print_environment - a function similar to env.
 */
void print_environment(void)
{
	int i, j;
	char new_line = '\n';

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '\0'; j++)
			write(STDOUT_FILENO, &environ[i][j], 1);

		write(STDOUT_FILENO, &new_line, 1);
	}
}


/**
 * the_exit - a function to exit the program.
 */
void the_exit(void)
{
	int status;

	if (arguments_length == 1)
	{
		arguments_reset();
		free_path();
		exit(0);
	}

	status = str_to_int(arguments_for_execve[1]);

	arguments_reset();
	free_path();

	exit(status);
}


/**
 * check_built_in - a functions that checks if the command is a built-in one.
 * Return: returns 0 if found, or -1 otherwise.
 */
int check_built_in(void)
{
	char *first_argument = arguments_for_execve[0];

	if (_strncmp(first_argument, "exit", _strlen(first_argument)) == 0)
	{
		the_exit();
		return (0);
	}

	else if (_strncmp(first_argument, "env", _strlen(first_argument)) == 0)
	{
		print_environment();
		arguments_reset();
		return (0);
	}

	return (-1);
}
