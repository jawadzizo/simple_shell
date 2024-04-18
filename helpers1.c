#include "shell.h"


/**
 * print_prompt - prints "$ " if the shell is attached to a terminal
 * @is_terminal: using the isatty() function
 */
void print_prompt(int is_terminal)
{
	if (is_terminal)
	{
		print(STDOUT_FILENO, "$ ");
		fflush(stdout);
	}
}


/**
 * remove_newline - removes the new line character of the given line
 * @line: the line to remove its new line character
 */
void remove_newline(char *line)
{
	if (line[_strlen(line) - 1] == '\n')
		line[_strlen(line) - 1] = '\0';
}


/**
 * is_line_empty - checks if a line is empty
 * @cmd: a pointer to a structure that holds the required data
 * Return: true if the line is empty, false otherwise
 */
bool is_line_empty(command_t *cmd)
{
	int i;

	if (_strlen(cmd->line) == 0)
		return (TRUE);

	if (cmd->line[0] == '#' || cmd->line[0] == '\n')
		return (TRUE);

	for (i = 0; cmd->line[i] != '\0' && cmd->line[i] == ' '; i++)
	{
		if (cmd->line[i + 1] == '\0' || cmd->line[i + 1] == '#')
			return (TRUE);
	}

	return (FALSE);
}


/**
 * initialise_command - initialises the commands structure
 * @cmd: a pointer to a structure that holds the required data
 * @shell_name: the name of the simple shell, obtained by using argv[0]
 */
void initialise_command(command_t *cmd, char *shell_name)
{
	cmd->count = 0;
	cmd->status = 0;

	cmd->line[0] = '\0';
	cmd->section[0] = NULL;
	cmd->separator[0] = _comment;
	cmd->argument[0] = NULL;

	cmd->shell_id = getpid();
	cmd->path[0] = '\0';

	cmd->alias = NULL;

	cmd->shell_name = shell_name;
}


/**
 * set_input_stream - sets the input stream, either a file or stdin
 * @argc: numer of passed arguments
 * @argv: the array of passed arguments
 * Return: the file descriptor of the input stream
 */
int set_input_stream(int argc, char **argv)
{
	int fd;

	if (argc == 1)
		return (STDIN_FILENO);

	fd = open(argv[1], O_RDONLY);

	if (fd == -1)
	{
		print(STDERR_FILENO, argv[0]);
		print(STDERR_FILENO, ": 0: Can't open ");
		print(STDERR_FILENO, argv[1]);
		print(STDERR_FILENO, "\n");
		exit(127);
	}

	return (fd);
}

