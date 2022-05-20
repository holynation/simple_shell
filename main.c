#include "shell.h"

/**
 * ctrl_C - ignore Ctrl-C input and prints prompt again
 * @n: takes in int from signal
 */
void ctrl_C(int n)
{
	(void)n;
	if (n == SIGINT)
		write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * main - This is the entry point to the program
 * @ac: This is the number of args
 * @av: This is the args supplied to the program
 * Return: return 0
 */
int main(int ac, char **av)
{
	char *cmd_str = NULL, *dem = " ";
	char **token = NULL;
	int exit_stat = 0, command_line_num = 0;
	char *shell_name = "$ ";
	(void)ac;
	/* on repeat till user exits the shell */
	do {
		command_line_num++;
		if (isatty(STDIN_FILENO)) /* reprompt if in interactive shell */
			write(STDOUT_FILENO, shell_name, 2);
		else
			non_interactive();
		signal(SIGINT, ctrl_C); /* handle signal */
		cmd_str = NULL; /* reset vars every time loop runs */
		cmd_str = get_user_command();
		if (cmd_str == NULL)
		{
			free(cmd_str);
			continue;
		}
		else
		{
			if (cmd_str[0] == '\0') /* reprompt if user hit enter only */
			{
				free(cmd_str);
				continue;
			}
			/* tokenize the cmd_str to array of string */
			token = NULL;
			token = _strtok(cmd_str, dem);
			if (token == NULL)
				free(token);
			exit_stat = built_in(token, command_line_num, NULL, av);
			if (exit_stat)
				continue;
			exit_stat = _execve(token, command_line_num, av);
		}
	} while (1);
	free(cmd_str);
	return (exit_stat);
}
