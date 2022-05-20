#include "shell.h"

/**
 * ctrl_D - exits program if Ctrl-D was pressed
 * @command: user's typed in command
 */
void ctrl_D(char *command)
{
	if (isatty(STDIN_FILENO))/* ctrl+d prints newline */
		write(STDOUT_FILENO, "\n", 1);
	free(command);
	exit(0);
}

/**
 * ignore_space - return string without spaces in front
 * @str: string
 * Return: new string
 */
char *ignore_space(char *str)
{
	while (*str && *str == ' ')
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
	ssize_t i = 0;
	int j = 0;

	i = _getline(&buffer_ptr);
	printf("cli: got here\n");
	if (i == -1 || i == 0)
	{
		if (i == -1)
			ctrl_D(buffer_ptr); /* exits shell if ctrl-D */
		exit(0);
	}
	buffer_ptr = ignore_space(buffer_ptr);
	j = 0;
	while (buffer_ptr && buffer_ptr[j] != '\n') /* replace getline's \n with \0 */
		j++;
	buffer_ptr[j] = '\0';

	return (buffer_ptr);
}
