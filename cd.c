#include "shell.h"


/**
 * cd - changes the directory (similat to "cd")
 * @cmd: a pointer to a structure that holds the required data
 * @is_environ_allocated: a pointer that tells us if environ is malloc'd or not
 */
void cd(command_t *cmd, bool *is_environ_allocated)
{
	char current_dir[PATH_MAX];

	getcwd(current_dir, PATH_MAX);

	if (cmd->argument[1] == NULL)
	{
		cd_home(is_environ_allocated);
		cmd->status = 0;
		return;
	}
	
	else if ((_strlen(cmd->argument[1]) == 1) && (cmd->argument[1][0] == '-'))
	{
		cd_back(is_environ_allocated);
		cmd->status = 0;
		return;
	}

	else if (chdir(cmd->argument[1]) == -1)
	{
		cd_error(cmd);
		cmd->status = 0;
		return;
	}

	change_dir_env("PWD", cmd->argument[1], is_environ_allocated);
	change_dir_env("OLDPWD", current_dir, is_environ_allocated);

	cmd->status = 0;
}


/**
 * cd_home - changes the directory to user's home
 * @is_environ_allocated: a pointer that tells us if environ is malloc'd or not
 */
void cd_home(bool *is_environ_allocated)
{
	char *home = _getenv("HOME");
	char current_dir[PATH_MAX];

	if (home == NULL)
		return;

	getcwd(current_dir, PATH_MAX);

	chdir(home);

	change_dir_env("PWD", home, is_environ_allocated);
	change_dir_env("OLDPWD", current_dir, is_environ_allocated);
}


/**
 * cd_back - changes the directory to the previous one (using OLDPWD)
 * @is_environ_allocated: a pointer that tells us if environ is malloc'd or not
 */
void cd_back(bool *is_environ_allocated)
{
	char *oldpwd = _getenv("OLDPWD");
	char current_dir[PATH_MAX];

	getcwd(current_dir, PATH_MAX);

	if (oldpwd == NULL)
	{
		print(STDOUT_FILENO, current_dir);
		print(STDOUT_FILENO, "\n");
		return;
	}

	chdir(oldpwd);
	print(STDOUT_FILENO, oldpwd);
	print(STDOUT_FILENO, "\n");

	change_dir_env("PWD", oldpwd, is_environ_allocated);
	change_dir_env("OLDPWD", current_dir, is_environ_allocated);
}


/**
 * cd_error - prints an error if cd failed
 * @cmd: a pointer to a structure that holds the required data
 */
void cd_error(command_t *cmd)
{
	char *missing_dir = "can't cd to ";
	char *colon = ": ";
	char command_count[9];
	_itoa(cmd->count, command_count);

	print(STDERR_FILENO, cmd->shell_name);
	print(STDERR_FILENO, colon);
	print(STDERR_FILENO, command_count);
	print(STDERR_FILENO, colon);
	print(STDERR_FILENO, cmd->argument[0]);
	print(STDERR_FILENO, colon);
	print(STDERR_FILENO, missing_dir);
	print(STDERR_FILENO, cmd->argument[1]);
	print(STDERR_FILENO, "\n");
}


/**
 * change_dir_env - changes the environment variables PWD and OLDPWD
 * @name: the environment variable to change - either PWD or OLDPWD
 * @value: the new value of the selected environment variable
 * @is_environ_allocated: a pointer that tells us if environ is malloc'd or not
 */
void change_dir_env(char *name, char *value, bool *is_environ_allocated)
{
	char *arguments[3];
	arguments[0] = "setenv";
	arguments[1] = name;
	arguments[2] = value;

	_setenv(arguments, is_environ_allocated);
}

