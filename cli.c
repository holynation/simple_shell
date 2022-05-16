#include "shell.h"

/**
 * get_user_command - This is to get input from cli
 * Return: return the address to the buffer
 */
char *get_user_command(void)
{
	char *buffer_ptr;
	size_t size = 0;
	ssize_t i = 0;

	i = getline(&buffer_ptr, &size, stdin);

	if (i == -1)
		return (NULL);
	buffer_ptr[i - 1] = '\0';

	return (buffer_ptr);

}

/**
 * get_stdin - This is to read input from file
 * Return: return string separated by space so that
 * each string can be tokenized
 */
char *get_stdin(void)
{

}
