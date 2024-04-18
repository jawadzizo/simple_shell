#include "shell.h"


/**
 * _alias - adds, modifies aliases
 * @cmd: pointer to the command 
 */
void _alias(command_t *cmd)
{
	int i;

	if (cmd->argument[1] == NULL)
		print_alias(cmd->alias, NULL);

	for (i = 1; cmd->argument[i] != NULL; i++)
	{
		if (is_name_value(cmd->argument[i]))
			add_alias(&cmd->alias, cmd->argument[i]);

		else
			print_alias(cmd->alias, cmd->argument[i]);
	}

	cmd->status = 0;
}


/**
 * add_alias - adds (or modifies an alias if found) to the alias nodes
 * @head: a pointer to head of alias nodes
 * @alias_content: name and value of the alias node
 */
void add_alias(alias_t **head, char *alias_content)
{
	alias_t *node = NULL;
	int i, j;
	char name[CHARS_MAX], value[CHARS_MAX];
	char *found = NULL;

	for (i = 0; alias_content[i] != '='; i++)
		name[i] = alias_content[i];

	name[i] = '\0';
	i++;

	for (j = 0; alias_content[i] != '\0'; i++, j++)
		value[j] = alias_content[i];

	value[j] = '\0';

	if ((found = find_alias(*head, name)) != NULL)
	{
		found[0] = '\0';
		_strcat(found, value);
		return;
	}

	node = checked_malloc(sizeof(alias_t));
	node->name[0] = '\0';
	_strcat(node->name, name);
	node->value[0] = '\0';
	_strcat(node->value, value);
	node->next = NULL;

	if (*head != NULL)
		node->next = *head;

	*head = node;
}


/**
 * print_alias - prints a specific alias if to_find != NULL, prints all alias otherwise
 * @head: the head to the alias nodes 
 * @to_find: the alias node to print, it can be NULL to prine all aliases
 */
void print_alias(alias_t *head, char *to_find)
{
	if (head == NULL)
		return;

	while (head != NULL)
	{
		if (to_find != NULL)
		{
			if ((_strlen(head->name) == _strlen(to_find)) &&
				(_strncmp(head->name, to_find, _strlen(to_find)) == 0))
			{
				print(STDOUT_FILENO, head->name);
				print(STDOUT_FILENO, "=");
				print(STDOUT_FILENO, "'");
				print(STDOUT_FILENO, head->value);
				print(STDOUT_FILENO, "'");
				print(STDOUT_FILENO, "\n");
			}
		}

		else
		{
			print(STDOUT_FILENO, head->name);
			print(STDOUT_FILENO, "=");
			print(STDOUT_FILENO, "'");
			print(STDOUT_FILENO, head->value);
			print(STDOUT_FILENO, "'");
			print(STDOUT_FILENO, "\n");
		}

		head = head->next;
	}
}


/**
 * find_alias - searches throught alias nodes to find the given name's value
 * @head: the head to the alias nodes
 * @name: the name of the alias node to find
 * Return: a pointer to the node's value, or NULL otherwise
 */
char *find_alias(alias_t *head, char *name)
{
	alias_t *base = head;
	char *value = NULL;

	if (head == NULL)
		return (NULL);

	while (head != NULL)
	{
		if ((_strlen(head->name) == _strlen(name)) &&
			(_strncmp(head->name, name, _strlen(name)) == 0))
			{
				value = head->value;

				if ((_strlen(head->name) == _strlen(value)) &&
					(_strncmp(head->name, value, _strlen(name)) == 0))
					{
						break;
					}

				name = value;
				head = base;
				continue;
			}

		head = head->next;
	}

	return (value);
}


/**
 * free_alias_nodes - frees the list of nodes
 * @head: the head to the alias nodes
 */
void free_alias_nodes(alias_t *head)
{
	alias_t *temp = NULL;

	if (head == NULL)
		return;

	while(head->next != NULL)
	{
		temp = head;
		head = head->next;
		FREE(temp);
	}

	FREE(head);
}

