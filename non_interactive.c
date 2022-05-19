#include "shell.h"

/**
 * c_ignore - custom ignores spaces and newlines
 * (e.g. echo "ls\n ls" | ./a.out)
 * @str: envrionmental variables
 * Return: new string
 */
char *c_ignore(char *str)
{
	while (*str == ' ' || *str == '\n')
		str++;
	return (str);
}

/**
 * non_interactive - handles when user pipes commands into shell via "|"
 * (e.g. echo "ls/nls -al/n" | ./a.out)
 */
void non_interactive(void)
{
	size_t i = 0, n = 0;
	int command_line_num = 0, exit_stat = 0;
	char *command = NULL, *n_command = NULL, *dem = " ";
	char **n_line, **token;

	i = _getline(&command);
	if (i == 0)
	{
		free(command);
		exit(0);
	}
	n_command = command;
	command = c_ignore(command);
	n_line = _str_tok(command, "\n"); /* tokenize each command string */
	if (n_command != NULL)
		free(n_command);
	n = 0;
	while (n_line[n] != NULL)
	{
		command_line_num++;
		token = NULL; /* tokenize each command in array of commands */
		token = _str_tok(n_line[n], dem);
		exit_stat = built_in(token, command_line_num, n_line);
		if (exit_stat)
		{
			n++;
			continue;
		}
		exit_stat = _execve(token, command_line_num);
		n++;
	}
	free_double_ptr(n_line);
	exit(exit_stat);
}

/**
 * free_double_ptr - free malloced arrays
 * @str: array of strings
 */
void free_double_ptr(char **str)
{
	int i = 0;

	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
