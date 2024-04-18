#include "shell.h"


/**
 * checked_malloc - allocates memory and checks if an error occured while allocating
 * @size: the size of the memory to allocate
 * Return: a pointer to the allocated memory
 */
void *checked_malloc(size_t size)
{
	void *segment = malloc(size);

	if (segment == NULL)
	{
		perror("error allocating memory");
		exit(EXIT_FAILURE);
	}

	return (segment);
}


/**
 * is_path - checks if the passed command is an absolute path
 * @command: the command to check if it's an absolute path
 * Return: true if it's an absolute path, false otherwise
 */
bool is_path(char *command)
{
	int i;

	for (i = 0; command[i] != '\0'; i++)
	{
		if (command[i] == '/')
			return (TRUE);
	}

	return (FALSE);
}


/**
 * is_command_found - checks if the command is found
 * @cmd: a pointer to a structure that holds the required data
 * Return: true if the command is found, false otherwise
 */
bool is_command_found(command_t *cmd)
{
	if (is_path(cmd->argument[0]))
	{
		if (access(cmd->argument[0], X_OK) == 0)
		{
			cmd->path[0] = '\0';
			_strcat(cmd->path, cmd->argument[0]);
			return (TRUE);
		}
		return (FALSE);
	}

	if (is_built_in(cmd))
		return (TRUE);

	if (find_command_path(cmd))
		return (TRUE);

	cmd->status = 127;

	return (FALSE);
}


/**
 * is_built_in - checks if the command is a built_in command
 * @cmd: a pointer to a structure that holds the required data
 * Return: true if the command is a built_in, false otherwise
 */
bool is_built_in(command_t *cmd)
{
	char *built_in_commands[] = {"exit", "env", "setenv", "unsetenv", "cd", "alias", NULL};
	int i;

	for (i = 0; built_in_commands[i] != NULL; i++)
	{
		if ((_strlen(cmd->argument[0]) == _strlen(built_in_commands[i])) &&
			(_strncmp(cmd->argument[0], built_in_commands[i], _strlen(cmd->argument[0])) == 0))
			{
				return (TRUE);
			}
	}

	return (FALSE);
}


/**
 * is_name_value - checks if the argument is in format "name=value"
 * @alias: the argument to check if in format "name=value"
 * Return: TRUE if the argument is in format "name=value", or FALSE otherwise
 */
bool is_name_value(char *alias)
{
	while(*alias != '\0')
	{
		if (*alias == '=')
			return (TRUE);

		alias++;
	}

	return (FALSE);
}

