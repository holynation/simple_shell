#include "shell.h"

/**
 * built_in - handles builtins (exit, env, cd)
 * @token: user's typed command
 * @num: take in nth user command typed to write error message
 * @command: bring in command to be freed
 * Return: 1 if acted on builtin, 0 if not
 */
int built_in(char **token, int num, char **command)
{
	int i = 0;

	/* if user types "exit", free cmd tokens, and exit */
	if (_strcmp(token[0], "exit") == 0)
	{
		i = __exit(token, num, command);
	}
	/* if user types "env", print, free cmd tokens, and reprompt */
	else if (_strcmp(token[0], "env") == 0)
	{
		/*_env(token);*/ /* print env var */
		i = 1;
	}
	return (i);
}

/**
 * c_atoi - custom atoi converts string to int
 * @s: string
 * Return: number if success, -1 if string contains non-numbers
 */
int c_atoi(char *s)
{
	int i = 0;
	unsigned int num = 0;

	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9') /* calculate num */
			num = num * 10 + (s[i] - '0');
		if (s[i] > '9' || s[i] < '0') /* account for non-numbers */
			return (-1);
		i++;
	}
	return (num);
}

/**
 * __exit - frees user input and then exits main program with a value
 * @str: user's command into shell (e.g. "exit 99")
 * @num: bring in nth user command line input to print in error message
 * @command: bring in command to be freed
 * Return: 0 if success 2 if fail
 */
int __exit(char **str, int num, char **command)
{
	int e_value = 0;

	if (str[1] != NULL) /* if no value given after exit, return 0 */
		e_value = c_atoi(str[1]);

	if (e_value == -1) /* if value given after exit is invalid, perror */
	{
		/*illegal_number(str[1], num, env);*/ /* print error msg */
		free_double_ptr(str);
		return (2);
	}
	free_double_ptr(str); /* free user input before exiting program */
	if (command != NULL)
		free_double_ptr(command);
	exit(e_value);
}
