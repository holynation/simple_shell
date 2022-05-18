#include "shell.h"

/**
 * ctrl_D - exits program if Ctrl-D was pressed
 * @i: characters read via getline
 * @command: user's typed in command
 * @env: environmental variable linked list
 */
void ctrl_D(int i, char *command)
{
	if (i == 0) /* handles Ctrl+D */
	{
		free(command); /* exit with newline if in shell */
		if (isatty(STDIN_FILENO))/* ctrl+d prints newline */
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
}

/**
 * ignore_space - return string without spaces in front
 * @str: string
 * Return: new string
 */
char *ignore_space(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

/**
 * get_user_command - This is to get input from cli
 * Return: return the address to the buffer
 */
char *get_user_command(void)
{
	char *buffer_ptr;
	size_t size = 0;
	ssize_t i = 0;
	int j = 0;

	i = _getline(&buffer_ptr);
	if (i == -1)
		return (NULL);
	ctrl_D(i, buffer_ptr); /* exits shell if ctrl-D */
	buffer_ptr = ignore_space(buffer_ptr);
	j = 0;
	while (buffer_ptr[j] != '\n') /* replace getline's \n with \0 */
		j++;
	buffer_ptr[j] = '\0';

	return (buffer_ptr);

}

/**
 * get_stdin - This is to read input from file
 * Return: return string separated by space so that
 * each string can be tokenized
 */
char *get_stdin(void)
{
	char *buffer = NULL;
	size_t size = 0;
	ssize_t i = 0;
	char *buff;
	int j = 0, k = 0, l = 0, loop_count = 0;

	buff = malloc(sizeof( char *) * 1024);
	if(buff == NULL)
	{
		free(buff);
		return (NULL);
	}

	while ((i = getline(&buffer, &size, stdin)) != -1)
	{
		if (i == -1)
		{
			return (NULL);
		}
		loop_count++;
		if (buff){
			j = _strlen(buffer);
			buffer[j - 1] = ' ';
			if (!k)
			{
				/* this would be the first line */
				_strcpy(buff,buffer);
			}
			else
			{
				/* this would the other line */
				_strcat(buff, buffer);
			}
			k = 1;
		}
	}
	j = _strlen(buff);
	buff[j - 1] = '\0';
	free(buffer);
	return (buff);
}
