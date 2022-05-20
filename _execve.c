#include "shell.h"

/**
 * c_exit - free user's typed command before exiting
 * @str: user's stdin command
 */
void c_exit(char **str)
{
	free_double_ptr(str);
	_exit(0);
}

/**
 * _execve - execute command user typed into shell
 * @s: command user typed
 * @num: nth user command; to be used in error message
 * @av: this is the program args
 * Return: 0 on success
 */
int _execve(char **s, int num, char **av)
{
	char *holder;
	int status = 0;
	pid_t pid;

	holder = locate_cmd_in_path(s[0]);
	/* if not an executable, free */
	if (holder == NULL)
	{
		not_found_err(num, av);
		free_double_ptr(s);
		free(holder);
		return (127);
	}
	else /* else fork and execute executable command */
	{
		pid = fork();
		if (pid == 0) /* if child process, execute */
		{
			if (execve(holder, s, NULL) == -1)
			{
				not_found_err(num, av); /* special err msg */
				c_exit(s);
			}
		}
		else /* if parent, wait for child then free all */
		{
			wait(&status);
			free_double_ptr(s);
			free(holder);
		}
	}
	return (0);
}
