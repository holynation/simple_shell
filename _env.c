#include "shell.h"

/**
 * c_strdup - custom string duplication; excludes beginning bytes
 * @str: string to duplicate (e.g. environmental variable PATH=/bin:/bin/ls)
 * @cs: number of bytes to exclude (e.g. excludes "PATH=")
 * Return: string (e.g. /bin:/bin/ls)
 */
char *ex_strdup(char *str, int cs)
{
	char *duplicate_str;
	int i, len = 0;

	if (str == NULL) /* validate str input */
		return (NULL);
	/* calculate len + null terminator to malloc */
	while (*(str + len))
		len++;
	len++;
	/* allocate memory but exclude environmental variable title (PATH) */
	duplicate_str = malloc(sizeof(char) * (len - cs));
	if (duplicate_str == NULL)
		return (NULL);

	i = 0;
	while (i < (len - cs))
	{
		*(duplicate_str + i) = *(str + cs + i);
		i++;
	}
	return (duplicate_str);
}

/**
 * _getenv - This is to get the environment variable
 * @name: the env name to look for in the environ
 * @num_ex: the num of bytes to exclude
 * Return: return the env path or null 
 */
char *_getenv(const char *name, const int num_ex)
{
	size_t i = 0, j = 0;
	char *env_val = NULL;

	while (environ[i] != NULL)
	{
		env_val = environ[i];
		j = 0;
		while (env_val[j] == name[j]) /* find desired env variable */
			j++;

		if (name[j] == '\0' && env_val[j] == '=')
			return ((num_ex == 0) ? _strdup(env_val) : ex_strdup(env_val, num_ex));

		i++;
	}
	return (NULL);
}
