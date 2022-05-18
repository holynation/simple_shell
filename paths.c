#include "shell.h"

/**
 * locate_path - this is to find a path in the environ variable
 * @name: name of the exec to find in the environment variable
 * Return: return the absolute path of the exec func
 */
char *locate_cmd_in_path(const char *name)
{
	char *path = _getenv("PATH",0);
	char *dir_path = NULL;
	char *file_path = NULL;

	/* PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin */
	if (file_exist(name)) /* check if command is absolute path */
		return (_strdup(name));
	/* PATH\0/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin */
	strtok(path, "=");
	dir_path = strtok(NULL, ":");
	while (dir_path)
	{
		file_path = combine_path('/', dir_path, name);
		if (file_exist(file_path))
			break;

		free(file_path);
		file_path = NULL;

		dir_path = strtok(NULL, ":");
	}

	free(path);
	return (file_path);
}

/**
 * combine_path - This is to combine path together
 * @sep: the delimiter to combine the paths
 * @path1: the first path to be join
 * @path2: the other paht to follow
 * Return: the absolute combine_path of the two path
 */
char *combine_path(const char sep, const char *path1, const char *path2)
{
	size_t i = 0, k = 0, len = 0;
	char *path_join = NULL;

	while (path1[i++] != '\0')
		;
	len += i;

	i = 0;
	while (path2[i++] != '\0')
		;
	len += i;
	len += 1;

	path_join = malloc(sizeof(char *) * (len + 1));
	if (path_join == NULL)
		return (NULL);

	i = 0;
	while (path1[k])
	{
		path_join[i] = path1[k];
		i++;
		k++;
	}
	path_join[i++] = sep;
	k = 0;
	while (path2[k])
	{
		path_join[i] = path2[k];
		i++;
		k++;
	}
	path_join[i] = '\0'; /* added null byte */
	return (path_join);
}

/**
 * file_exist - This is to check if a path truly exists
 * @path: the pathname to look for
 * Return: return 1 for success, 0 for otherwise 
 */
int file_exist(const char *path)
{
	struct stat buffer;

	if (stat(path, &buffer) == 0)
	{
		return (1);
	}
	return (0);
}
