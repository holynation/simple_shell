#include "shell.h"

/**
 * not_found_err - write error ("sh: 1: qwerty: not found")
 * @str: user's typed command
 * @c_n: nth user's typed command
 * @av: this is the program args
 */
void not_found_err(char *str, int c_n, char **av)
{
	int count = 0;
	(void)c_n;
	(void)str;
	count = _strlen(*av);
	write(STDOUT_FILENO, *av, count);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "No such file or directory\n", 26);
}

/**
 * illegal_number - write error ("hsh: 3: exit: Illegal number abc (or -1)")
 * @av: this is the program args
 */
void unknown_number(char **av)
{
	int count = 0;

	count = _strlen(*av);
	write(STDOUT_FILENO, *av, count);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "exit: Illegal number: ", 22);
}
