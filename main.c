#include "main.h"

extern char **environ;


int arguments_length = 0;
int arguments_length_each[64] = {0};
int arguments_position[64] = {0};
char **arguments_for_execve;

char *execve_path;


int path_length = 1;
char **path;


int command_count = 0;
char *command;




/**
 * main - the main function.
 * @argc: arguments count.
 * @argv: arguments values.
 * Return: returns 0 if succeeded.
 */
int main(__attribute__((unused)) int argc, char *argv[])
{
	int reading;

	allocate_path();

	while (1)
	{
		command_count++;

		command = malloc(sizeof(char) * BUFFSIZE);

		write(STDOUT_FILENO, "$ ", 2);

		reading = read(STDIN_FILENO, command, BUFFSIZE);

		fflush(stdout);

		if (reading == 0)
			eof_reached();

		if (command[0] == '\n')
		{
			continue;
		}

		remove_command_new_line(reading);

		command_line_arguments_counter(command);
		allocate_execve(command);

		if (check_built_in() == 0)
			continue;

		if (find_execve_path() == -1)
		{
			command_not_found(argv[0]);
			arguments_reset();
			continue;
		}

		if (fork() == 0)
			execve(execve_path, arguments_for_execve, NULL);

		else
			wait(NULL);

		arguments_reset();
	}

    return (0);
}







/**
 * _getenv - a function to get the environment variables.
 * @name: the environment variable to get.
 * Return: returns a pointer to the variable, or NULL if not found.
 */
char *_getenv(const char *name)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if ((_strncmp(environ[i], name, _strlen(name))) == 0)
			return (environ[i] + _strlen(name) + 1);
	}

	return (NULL);
}




/**
 * allocate_path - a function to allocate memory for PATH.
 */
void allocate_path(void)
{
	int i, j, k;

	k = 0;

	for (i = 0; _getenv("PATH")[i] != '\0'; i++)
	{
		if (_getenv("PATH")[i] == ':')
			path_length++;
	}

	path = malloc(sizeof(char *) * (path_length + 1));

	for (i = 0; i < path_length; i++)
	{
		path[i] = malloc(PATH_MAX);

		for (j = 0; (_getenv("PATH")[k] != ':') &&
		(_getenv("PATH")[k] != '\0'); j++, k++)
			path[i][j] = _getenv("PATH")[k];

		k++;

		path[i][j] = '/';
		path[i][++j] = '\0';
	}

	path[i] = NULL;
}
