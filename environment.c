#include "shell.h"


/**
 * _getenv - searches for the environment variable's value
 * @env_var: the environment variable to search for
 * Return: returns a pointer to the variable's value, or NULL if not found
 */
char *_getenv(const char *env_var)
{
	int i;

	if (environ == NULL)
		return (NULL);

	if (_strlen(env_var) == 0)
		return (NULL);

	for (i = 0; environ[i] != NULL; i++)
	{
		if ((_strncmp(environ[i], env_var, _strlen(env_var)) == 0) &&
			(environ[i][_strlen(env_var)] == '='))
		{
			return (environ[i] + _strlen(env_var) + 1);
		}
	}

	return (NULL);
}


/**
 * _env - prints the environment variables, one in line
 */
void _env()
{
	int i;

	if (environ == NULL)
		return;

	for (i = 0; environ[i] != NULL; i++)
	{
		print(STDOUT_FILENO, environ[i]);
		print(STDOUT_FILENO, "\n");
	}
}


/**
 * _setenv - adds (and changes) environment variables 
 * @arguments: name and value of the variable to set
 * @is_environ_allocated: a pointer that tells us if environ is malloc'd or not
 */
void _setenv(char **arguments, bool *is_environ_allocated)
{
	char **new_environ = NULL;
	bool is_env_var_found;
	size_t new_environ_len, i;

	if ((arguments[1] == NULL) || (arguments[2] == NULL))
		return;

	is_env_var_found = (_getenv(arguments[1]) != NULL);

	for (i = 0; environ != NULL && environ[i] != NULL; i++);
	new_environ_len = i;
	new_environ_len += is_env_var_found ? 1 : 2; /* one for last NULL pointer, other one if the variable don't exist */

	new_environ = checked_malloc(sizeof(char *) * new_environ_len);

	for (i = 0; i < new_environ_len; i++)
		new_environ[i] = NULL;

	for (i = 0; environ != NULL && environ[i] != NULL; i++)
	{
		if (is_env_var_found && (environ[i] == (_getenv(arguments[1]) - _strlen(arguments[1]) - 1)))
		{
			new_environ[i] = checked_malloc(_strlen(arguments[1]) + _strlen(arguments[2]) + 2); /* for '=' and '\0' */
			new_environ[i][0] = '\0';
			_strcat(new_environ[i], arguments[1]);
			_strcat(new_environ[i], "=");
			_strcat(new_environ[i], arguments[2]);
		}

		else
		{
			new_environ[i] = checked_malloc(_strlen(environ[i]) + 1);
			new_environ[i][0] = '\0';
			_strcat(new_environ[i], environ[i]);
		}
	}

	if (is_env_var_found == FALSE)
	{
		new_environ[i] = checked_malloc(_strlen(arguments[1]) + _strlen(arguments[2]) + 2); /* for '=' and '\0' */
		new_environ[i][0] = '\0';
		_strcat(new_environ[i], arguments[1]);
		_strcat(new_environ[i], "=");
		_strcat(new_environ[i], arguments[2]);
	}

	if (*is_environ_allocated)
		free_environ();

	environ = new_environ;
	*is_environ_allocated = TRUE;
}


/**
 * _unsetenv - unsets environment variables 
 * @name: name of the variable to unset
 * @is_environ_allocated: a pointer that tells us if environ is malloc'd or not
 */
void _unsetenv(char *name, bool is_environ_allocated)
{
	size_t environ_len, i, to_unset_index;
	char *temp;

	if (name == NULL)
		return;

	if (_getenv(name) == NULL)
		return;

	for (i = 0; environ != NULL && environ[i] != NULL; i++)
	{
		if (environ[i] == (_getenv(name) - _strlen(name) - 1))
			to_unset_index = i;
	}

	environ_len = i;
	environ_len--; /* points to last environ variable */

	temp = environ[to_unset_index];
	environ[to_unset_index] = environ[environ_len];
	environ[environ_len] = NULL;

	if (is_environ_allocated)
	{
		FREE(temp);
	}
}



/**
 * free_environ - frees the new malloc'd environ 
 */
void free_environ()
{
	int i;

	if (environ == NULL)
		return;

	for (i = 0; environ[i] != NULL; i++)
	{
		FREE(environ[i]);
	}

	FREE(environ);
}

