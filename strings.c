#include "main.h"












int _strlen(const char *string)
{
	int i = 0;

	while (string[i] != '\0')
		i++;

	return (i);
}




char * _strcon(char * string1, char *string2)
{
	int i, j;
	char *concatenated_string = malloc(PATH_MAX);

	for (i = 0; i < _strlen(string1); i++)
		concatenated_string[i] = string1[i];

	for (j = 0; j <= _strlen(string2); i++, j++)
		concatenated_string[i] = string2[j];

	return(concatenated_string);
}




int _strncmp(const char *string1, const char *string2, int length)
{
	int i;

	for (i = 0; i < length; i++)
	{
		if (string1[i] != string2[i])
			return (-1);
	}

	return (0);
}




int str_to_int(char *string)
{
	int i;
	int value = 0;
	int multiply = 1;

	for (i = _strlen(string) - 1; i >= 0; i--)
	{
		value = value + ((string[i] - 48) * multiply);
		multiply *= 10;
	}

	return (value);
}




char* int_to_str(int number)
{
	int i;
	int length = 0;
	int temp = number;
	char *str = malloc (sizeof(char) * 10);

	for (i = 0; temp > 0; i++)
	{
		length++;
		temp /= 10;
	}

	for (i = length - 1; i >= 0; i--)
	{
		str[i] = (number % 10) + 48;
		number /= 10;
	}

	str[length] = '\0';

	return(str);
}