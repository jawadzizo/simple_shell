#include "main.h"






/**
 * command_line_arguments_counter - a function to find the length of command.
 * @entire_command: the command to check.
 */
void command_line_arguments_counter(char *entire_command)
{
	int i;
	int j = 0;

	for (i = 0; i < _strlen(entire_command); i++)
	{
		if ((entire_command[i] != ' ') && (entire_command[i] != '\0') && (entire_command[i] != '\n') && (entire_command[i] != '#') && (entire_command[i] != ';'))
		{
			arguments_length_each[j]++;
			arguments_length++;
			arguments_position[j] = i;
			i++;

			while ((entire_command[i] != ' ') &&
			(entire_command[i] != '\0') &&
			(entire_command[i] != '\n') &&
			(entire_command[i] != '#') &&
			(entire_command[i] != ';'))
			{
				i++;
				arguments_length_each[j]++;
			}

			j++;
		}
	}
}



/**
 * allocate_execve - a function to separate command arguments for execve.
 * @text: the command to separate into separate strings.
 */
void allocate_execve(char *text)
{
	int i, j, position;

	arguments_for_execve = malloc(sizeof(char *) * (arguments_length + 1));

	for (i = 0; i < arguments_length; i++)
	{
		arguments_for_execve[i] = malloc(arguments_length_each[i] + 1);

		position = arguments_position[i];

		for (j = 0; j < arguments_length_each[i]; j++, position++)
			arguments_for_execve[i][j] = text[position];

		arguments_for_execve[i][j] = '\0';
	}

	arguments_for_execve[i] = NULL;
}



/**
 * arguments_reset - a function to free the allocated memory for all needed
 * variables.
 */
void arguments_reset(void)
{
	int i;

	if ((execve_path != arguments_for_execve[0]) && (execve_path != NULL))
	{
		free(execve_path);
		execve_path = NULL;
	}

	for (i = 0; i < arguments_length; i++)
	{
		arguments_length_each[i] = 0;
		arguments_position[i] = 0;

		free(arguments_for_execve[i]);
		arguments_for_execve[i] = NULL;
	}

	free(arguments_for_execve);
	arguments_for_execve = NULL;

	arguments_length = 0;

	free(command);
	command = NULL;

}



/**
 * find_execve_path - a function to find the command's executable path.
 * Return: returns 0 for success, or -1 otherwise.
 */
int find_execve_path(void)
{
	int i;

	if ((access(arguments_for_execve[0], X_OK)) == 0)
	{
		execve_path = arguments_for_execve[0];
		return (0);
	}

	for (i = 0; path[i] != NULL; i++)
	{
		if (chdir(path[i]) == 0)
		{
			if (access(arguments_for_execve[0], X_OK) == 0)
			{
				execve_path = _strcon(path[i], arguments_for_execve[0]);
				chdir(_getenv("PWD"));
				return (0);
			}
		}
	}

	return (-1);
}
