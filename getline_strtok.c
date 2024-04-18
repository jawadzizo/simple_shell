#include "shell.h"


/**
 * _getline - reads a line from fd, and stores it in "line" variable
 * @line: where to store the line
 * @size: the maximum size to store in "line"
 * @fd: the file descriptor to read from
 * Return: the number of read bytes, 0 if reached EOF, -1 if error occured
 */
int _getline(char *line, int size, int fd)
{
	char c = 0;
	ssize_t bytes = read(fd, &c, 1);
	int count = 0;

	if (bytes == -1)
		return (-1);

	while ((bytes > 0) &&
			(c != '\n' && c != '\0') &&
			(count < size - 1))
	{
		line[count] = c;
		count++;
		bytes = read(fd, &c, 1);
	}

	if (c == '\n')
	{
		line[count] = '\n';
		count++;
	}

	line[count] = '\0';

	return (count);
}


/**
 * _strtok - tokenize the given string based on the delimiters
 * @string: the string to tokenize
 * @delimiter: a null terminated array of strings of delimiters
 * Return: a pointer to the token, or NULL if no token is found
 */
char *_strtok(char *string, const char **delimiter, separator_t *separator)
{
	static char *anchor = NULL;
	char *token = NULL;

	if (string != NULL)
	{
		anchor = string;
	}

	if ((string == NULL && anchor == NULL) || anchor == NULL)
		return (NULL);

	if (delimiter == NULL || _strlen(*delimiter) == 0)
		return (NULL);

	if (is_token_empty(&anchor, &token, delimiter))
		return (NULL);

	set_anchor(&anchor, delimiter, separator);

	return (token);
}


/**
 * set_anchor - sets a static pointer to the next token
 * @anchor: a static pointer to the next token
 * @delimiter: a null terminated array of strings of delimiters
 */
void set_anchor(char **anchor, const char **delimiter, separator_t *separator)
{
	int size = 0;

	while (**anchor != '\0')
	{
		if ((size = is_delimiter(anchor, delimiter, separator)) != 0)
		{
			**anchor = '\0';
			*anchor += size;
			break;
		}

		(*anchor)++;
	}

	if (**anchor == '\0')
		*anchor = NULL;
}


/**
 * is_token_empty - checks if a string contains only delimiters
 * @anchor: a static pointer to the next token
 * @token: the token to be returned in _strtok
 * @delimiter: a null terminated array of strings of delimiters
 * Return: true if the string contains only delimiters, false otherwise
 */
bool is_token_empty(char **anchor, char **token, const char **delimiter)
{
	while (**anchor != '\0')
	{
		if (is_delimiter(anchor, delimiter, NULL) == FALSE)
		{
			*token = *anchor;
			break;
		}

		(*anchor)++;
	}

	if (**anchor == '\0')
	{
		*anchor = NULL;
		return TRUE;
	}

	return FALSE;
}


/**
 * is_delimiter - checks if the current pointer is a delimiter
 * @anchor: a static pointer to the next token
 * @delimiter: a null terminated array of strings of delimiters
 * Return: false if not a delimiter, otherwise the length of the delimiter
 */
bool is_delimiter(char **anchor, const char **delimiter, separator_t *separator)
{
	int i = 0;

	while (delimiter[i] != NULL)
	{
		if (_strlen(*anchor) < _strlen(delimiter[i]))
			return 0;

		if (_strncmp(*anchor, delimiter[i], _strlen(delimiter[i])) == 0)
		{
			if (separator != NULL)
			{
				*separator = i;
				*(separator + 1) = _comment;
			}
			return ((int)_strlen(delimiter[i]));
		}

		i++;
	}

	return FALSE;
}

