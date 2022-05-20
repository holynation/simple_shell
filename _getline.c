#include "shell.h"
#define BUFF_SIZE 1024 /* random size */

/**
 * _getline - stores into malloced buffer the user's command into shell
 * @str: buffer
 * Return: number of characters read
 */
size_t _getline(char **str)
{
	ssize_t i = 0, size = 0, t = 0, t2 = 0, n = 0;
	char buff[BUFF_SIZE];
	/* read while there's stdin greater than buffsize; -1 to add a '\0' */
	while (t2 == 0 && (i = read(STDIN_FILENO, buff, BUFF_SIZE - 1)))
	{
		if (i == -1) /* check if read error occured */
			return (-1);
		buff[i] = '\0'; /* terminate buff with \0 to use with strcat */
		n = 0; /* last loop if \n is found in the stdin read */
		while (buff[n] != '\0')
		{
			if (buff[n] == '\n')
				t2 = 1;
			n++;
		}
		/* copy what's read to buff into getline's buffer */
		if (t == 0) /* malloc the first time */
		{
			if (buff == NULL)
				return (-1);
			i++;
			*str = malloc(sizeof(char) * i);
			if (*str == NULL)
				return (-1);
			*str = _strcpy(*str, buff);
			size = i;
			t = 1;
		}
		else /* realloc via strcat with each loop */
		{
			size += i;
			free(str);
			*str = _strcat(*str, buff);
		}
	}
	return (size);
}
