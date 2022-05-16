#include "shell.h"

/**
 * main - This is the entry point to the program
 * Return: return 0
 */

int main(int ac, char **av)
{

	char *cmd_str = NULL;
	char **args = NULL;
	char *dem = " ";
	int exit_loop = 0;

	while(1)
	{
		/* check the standard input first from the pipe */
		cmd_str = get_stdin(); /* /bin/ls /bin/ls */
		if(cmd_str)
		{
			args = _str_tok(cmd_str, dem);
		}
		else if (ac > 1)
		{	/* non-interative mode */
			args = av + 1;
			exit_loop = 1;
		}
		else
		{
			/* interactive mode for the shell */
			/* get command from the user */
			cmd_str = get_user_command();

			/* tokenize the cmd_str to array of string */
			args = _str_tok(cmd_str, dem);
		}

		if (execve(args[0], args, NULL) < 0)
		{
			dprintf(STDERR_FILENO, "%s: No such file or directory\n",args[0]);
		}

		if (exit_loop)
			break;
	}

	return (0);
}
