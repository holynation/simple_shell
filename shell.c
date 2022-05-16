#include "main.h"

int main()
{
	char *buffer, *token;

	size_t buf;

	buf = 12;

	buffer = malloc(buf * sizeof(char));

	while (1)
	{
		printf("~$ ");

		getline(&buffer, &buf, stdin);

		token = strtok(buffer, " ");

		trim(token);

		if (_strcmp(token, "exit") == 0)
			exit(0);

		printf("%s\n", token);

	}

	return (0);
}



