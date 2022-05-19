#include "shell.h"

/**
 * ctrl_C - ignore Ctrl-C input and prints prompt again
 * @n: takes in int from signal
 */
void ctrl_C(int n)
{
	(void)n;
	write(STDOUT_FILENO, "\n#cisfun$", 3);
}

/**
 * main - This is the entry point to the program
 * @ac: This is the number of args
 * @av: This is the args supplied to the program
 * Return: return 0
 */
int main(int ac, char **av)
{
	char *cmd_str = NULL, *n_command = NULL, *dem = " ";
	char **token = NULL;
	int exit_stat = 0, command_line_num = 0;
	(void)ac;
	(void)av;
	/* on repeat till user exits the shell */
	do {
		command_line_num++;
		if (isatty(STDIN_FILENO)) /* reprompt if in interactive shell */
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		else
			non_interactive();
		signal(SIGINT, ctrl_C); /* handle signal */
		cmd_str = NULL; /* reset vars every time loop runs */
		cmd_str = get_user_command(); /* get command from the user */
		n_command = cmd_str;
		if (cmd_str[0] == '\0') /* reprompt if user hit enter only */
		{
			free(n_command);
			continue;
		}
		/* tokenize the cmd_str to array of string */
		token = NULL;
		token = _str_tok(cmd_str, dem);
		if (n_command != NULL)
			free(n_command);
		/*exit_stat = built_in(token, command_line_num, NULL);*/
		if (exit_stat)
			continue;
		exit_stat = _execve(token, command_line_num);
	} while (1);
	free(cmd_str);
	return (exit_stat);
}
