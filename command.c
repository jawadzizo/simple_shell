#include "shell.h"


/**
 * map_sections - sets the sections of the command based on the separators
 * @cmd: a pointer to a structure that holds the required data
 * @line: holds the entire command line
 */
void map_sections(command_t *cmd, char *line)
{
	const char *separators[] = {"||", "&&", ";", " #", NULL};
	int i = 0;
	
	cmd->section[i] = _strtok(line, separators, &cmd->separator[i]);

	while (cmd->section[i] != NULL)
	{
		i++;
		cmd->section[i] = _strtok(NULL, separators, &cmd->separator[i]);
	}
}


/**
 * map_arguments - sets the command and its arguments
 * @cmd: a pointer to a structure that holds the required data
 * @section: holds the entire section
 */
void map_arguments(command_t *cmd, char *section)
{
	int i = 0;
	const char *separators[] = {" ", NULL};
	char *alias;

	cmd->argument[0] = _strtok(section, separators, NULL);

	alias = find_alias(cmd->alias, cmd->argument[0]);
	if (alias != NULL)
		cmd->argument[0] = alias;

	while (cmd->argument[i] != NULL)
	{
		i++;
		cmd->argument[i] = _strtok(NULL, separators, NULL);
		map_variable(cmd, &cmd->argument[i]);
	}
}


/**
 * map_variable - sets the variables of the arguments if found
 * @cmd: a pointer to a structure that holds the required data
 * @argument: the arguments to find its variables
 */
void map_variable(command_t *cmd, char **argument)
{
	char *env_var = NULL;

	if (*argument == NULL)
		return;
	
	if ((*argument)[0] == '$')
	{
		if ((*argument)[1] == '$')
		{
			_itoa(cmd->shell_id, cmd->shell_id_str);
			*argument = cmd->shell_id_str;
		}

		else if ((*argument)[1] == '?')
		{
			_itoa(cmd->status, cmd->status_str);
			*argument = cmd->status_str;
		}

		else
		{
			env_var = _getenv(&argument[0][1]);
			*argument = (env_var != NULL) ? env_var : *argument;
		}
	}
}


/**
 * find_command_path - searches for the command's absolute path (similat to "which")
 * @cmd: a pointer to a structure that holds the required data
 * Return: true if found, false otherwise
 */
bool find_command_path(command_t *cmd)
{
	char *environment_path_copy = NULL; /* holds a copy of PATH */
	char *path = NULL;
	const char *sep[] = {":", NULL};
	char exe_path[PATH_MAX];

	cmd->path[0] = '\0';

	if (environ == NULL || _getenv("PATH") == NULL)
		return (FALSE);

	environment_path_copy = checked_malloc(_strlen(_getenv("PATH")) + 1);
	environment_path_copy[0] = '\0';
	_strcat(environment_path_copy, _getenv("PATH"));

	path = _strtok(environment_path_copy, sep, NULL);

	while (path != NULL)
	{
		exe_path[0] = '\0';
		_strcat(exe_path, path);
		_strcat(exe_path, "/");
		_strcat(exe_path, cmd->argument[0]);

		if (access(exe_path, X_OK) == 0)
		{
			_strcat(cmd->path, exe_path);
			FREE(environment_path_copy);
			return (TRUE);
		}

		path = _strtok(NULL, sep, NULL);
	}

	FREE(environment_path_copy);
	return (FALSE);
}


/**
 * print_command_not_found - prints an error if the command is not found
 * @cmd: a pointer to a structure that holds the required data
 */
void print_command_not_found(command_t *cmd)
{
	char *missing = "not found\n";
	char *colon = ": ";
	char command_count[9];
	_itoa(cmd->count, command_count);

	print(STDERR_FILENO, cmd->shell_name);
	print(STDERR_FILENO, colon);
	print(STDERR_FILENO, command_count);
	print(STDERR_FILENO, colon);
	print(STDERR_FILENO, cmd->argument[0]);
	print(STDERR_FILENO, colon);
	print(STDERR_FILENO, missing);
}

