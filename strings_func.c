#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: string
 * Return: length
 */
int _strlen(char *s)
{
	int a = 0;

	while (*(s + a))
		a++;

	return (a);
}

/**
 * _strcpy - copies the string pointed to by src,
 * including the terminating null byte (\0),
 * to the buffer pointed to by dest
 * @dest: copy source to this buffer
 * @src: this is the source to copy
 * Return: copy of *src pointer value
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; i <= _strlen(src); i++)
		dest[i] = src[i];

	return (dest);
}

/**
 * _strcat - concatenate two strings
 * @dest: string to be appended to
 * @src: string to append
 * Return: concatenated string
 */
char *_strcat(char *dest, char *src)
{
	int i = 0;
	int j = 0;
	/* to count the str len without the null byte*/
	while (dest[i] != '\0')
	{
		i++;
	}

	while (src[j] != '\0')
	{
		/* appending src to the last index of dest */
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * _strdup - this is to duplicate the string
 * @str: the string to be duplicated
 * Return: the new duplicated string
 */
char *_strdup(const char *str)
{
	size_t i = 0;
	size_t len = 0;
	char *new_str = NULL;

	if (str == NULL) /* validate str input */
		return (NULL);

	while (str[i++])
		;
	len += i;
	len++; /* add null terminator to length */

	new_str = malloc(sizeof(char *) * (len + 1));
	if (new_str == NULL)
		return (NULL);

	i = 0;
	while (i <= len)
	{
		new_str[i] = str[i];
		i++;
	}

	return (new_str);
}
