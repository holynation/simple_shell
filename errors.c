#include "shell.h"

/**
 * not_found_err - write error ("sh: 1: qwerty: not found")
 * @str: user's typed command
 * @c_n: nth user's typed command
 */
void not_found_err(char *str, int c_n)
{
	int count = 0;
	char *shell, *num;

	shell = _getenv("_",2); /* get shell name to write */
	while (shell[count] != '\0')
		count++;
	write(STDOUT_FILENO, shell, count);
	free(shell);
	write(STDOUT_FILENO, ": ", 2);
	num = int_to_string(c_n); /* convert cmd line num to string to write */
	count = 0;
	while (num[count] != '\0')
		count++;
	write(STDOUT_FILENO, num, count);
	free(num);
	write(STDOUT_FILENO, ": ", 2);
	count = 0;
	while (str[count] != '\0')
		count++;
	write(STDOUT_FILENO, str, count);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "not found\n", 10);
}
