#include "shell.h"


/**
 * run_built_in_command - searches for and runs the built-in command
 * @cmd: a pointer to a structure that holds the required data
 * @is_environ_allocated: a pointer that tells us if environ is malloc'd or not
 */
void run_built_in_command(command_t *cmd, bool *is_environ_allocated)
{
	char *built_in_commands[] = {"exit", "env", "setenv", "unsetenv", "cd", "alias", NULL};
	int i;

	for (i = 0; built_in_commands[i] != NULL; i++)
	{
		if ((_strlen(cmd->argument[0]) == _strlen(built_in_commands[i])) &&
			(_strncmp(cmd->argument[0], built_in_commands[i], _strlen(cmd->argument[0])) == 0))
			{
				break;
			}
	}

	switch (i)
	{
		case 0:
			__exit(cmd, is_environ_allocated);
			break;
		case 1:
			_env(cmd);
			cmd->status = 0;
			break;
		case 2:
			_setenv(cmd->argument, is_environ_allocated);
			cmd->status = 0;
			break;
		case 3:
			_unsetenv(cmd->argument[1], *is_environ_allocated);
			cmd->status = 0;
			break;
		case 4:
			cd(cmd, is_environ_allocated);
			cmd->status = 0;
			break;
		case 5:
			_alias(cmd);
			break;
	}
}


/**
 * run_command_in_new_process - runs an external command in a new process using execve
 * @cmd: a pointer to a structure that holds the required data
 */
void run_command_in_new_process(command_t *cmd)
{
	int status;

	if (fork() == 0)
	{
		if (execve(cmd->path, cmd->argument, environ) == -1)
		{
			perror("external command execution error");
			exit(EXIT_FAILURE);
		}
	}

	else
	{
		wait(&status);

		if (WIFEXITED(status))
			cmd->status = WEXITSTATUS(status);
	}
}


/**
 * find_next_command - searches for the next command to execute if there are separators
 * @cmd: a pointer to a structure that holds the required data
 * @index: the index of the section we are on
 * Return: STOP if we reached the end or a comment, CONTINUE otherwise
 */
bool find_next_command(command_t *cmd, int *index)
{
	if (cmd->separator[*index] == _comment)
		return (STOP);
	
	else if (cmd->separator[*index] == _semi_colon)
		return (CONTINUE);

	else if (cmd->separator[*index] == _and)
	{
		if (cmd->status == 0)
			return (CONTINUE);
		
		while (cmd->separator[*index] == _and)
			(*index)++;

		if (cmd->separator[*index] == _comment)
			return (STOP);
	}

	else if (cmd->separator[*index] == _or)
	{
		if (cmd->status != 0)
			return (CONTINUE);
		
		while (cmd->separator[*index] == _or)
			(*index)++;

		if (cmd->separator[*index] == _comment)
			return (STOP);
	}

	return (STOP);
}

