#include "shell.h"


/**
 * main - the entry point of the simple shell
 * @argc: numer of passed arguments
 * @argv: the array of passed arguments
 * Return: returns last executed command's exit status
 */
int main(int argc, char *argv[])
{
	int fd = set_input_stream(argc, argv);
	bool is_environ_allocated = FALSE;
	bool is_terminal = isatty(fd);
	int i;

	command_t cmd;
	initialise_command(&cmd, argv[0]);
	print_prompt(is_terminal);

	while (_getline(cmd.line, BUFFER_SIZE, fd) > 0)
	{
		cmd.count++;
		remove_newline(cmd.line);
		map_sections(&cmd, cmd.line);
		if (is_line_empty(&cmd))
		{
			print_prompt(is_terminal);
			continue;
		}

		for (i = 0; cmd.section[i] != NULL; i++)
		{
			map_arguments(&cmd, cmd.section[i]);

			if (is_command_found(&cmd) == FALSE)
			{
				print_command_not_found(&cmd);
				if (find_next_command(&cmd, &i) == STOP)
					break;

				continue;
			}

			if (is_built_in(&cmd))
			{
				run_built_in_command(&cmd, &is_environ_allocated);
				continue;
			}

			run_command_in_new_process(&cmd);

			if (find_next_command(&cmd, &i) == STOP)
				break;
		}
		print_prompt(is_terminal);
	}

	if (isatty(fd))
		print(STDOUT_FILENO, "\n");

	if (is_environ_allocated)
		free_environ();

	free_alias_nodes(cmd.alias);

	if (fd > 2)
		close(fd);

	return (cmd.status);
}

