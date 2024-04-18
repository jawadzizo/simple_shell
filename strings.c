#include "shell.h"


/**
 * _strlen - calculates the length of the given string
 * @string: the string to find its length.
 * Return: returns the length of the string.
 */
size_t _strlen(const char *string)
{
	size_t i = 0;

	while (string[i] != '\0')
		i++;

	return (i);
}


/**
 * _strcat - concatenates a source string to a destination string
 * @dest: the destination string.
 * @src: the source string.
 * Return: returns a pointer to the concatenated string.
 */
char *_strcat(char *dest, const char *src)
{
	size_t i = _strlen(dest);
	size_t j = 0;

	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';

	return (dest);
}


/**
 * _strncmp - compares 2 strings for equality.
 * @s1: the first function to compare.
 * @s2: the second function to compare.
 * @n: count of bytes to compare
 * Return: returns 0 if the strings are equal, -1 otherwise.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return (-1);
	}

	return (0);
}


/**
 * _atoi - converts a string to number.
 * @string: the string to convert to number.
 * Return: returns the converted number.
 */
int _atoi(char *string)
{
	int i;
	int value = 0;
	int multiply = 1;

	for (i = _strlen(string) - 1; i >= 0; i--)
	{
		value += ((string[i] - 48) * multiply);
		multiply *= 10;
	}

	return (value);
}


/**
 * _itoa - converts a number to string
 * @number: the number to convert to string
 * @str: pointer to character array where the number should be stored
 * Return: returns a pointer to the converted string
 */
char *_itoa(int number, char *str)
{
	int i;
	int length = 0;
	int temp = number;

	if (number == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}

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

	return (str);
}

