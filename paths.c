#include "shell.h"

/**
 * c_tsize - returns number of delim
 * @str: user's command typed into shell
 * @delm: delimeter (e.g. " ");
 * Return: number of tokens
 */
int c_tsize(char *str, char delm)
{
	int i = 0, num_delm = 0;

	while (str[i] != '\0')
	{
		if (str[i] == delm)
			num_delm++;
		i++;
	}
	return (num_delm);
}

/**
 * c_str_tok - tokenizes a string even the continuous delim with empty string
 * (e.g. path --> ":/bin::/bin/usr" )
 * @str: user's command typed into shell
 * @delm: delimeter (e.g. " ");
 * Return: an array of tokens (e.g. {"\0", "/bin", "\0", "/bin/usr"}
 * (purpose is to have which command look through current directory if ":")
 */
char **c_str_tok(char *str, char *delm)
{
	int buffsize = 0, p = 0, si = 0, i = 0, len = 0, se = 0;
	char **toks = NULL, d_ch;

	/* set variable to be delimeter character (" ") */
	d_ch = delm[0];
	/* malloc number of ptrs to store array of tokens, and NULL ptr */
	buffsize = c_tsize(str, d_ch);
	toks = malloc(sizeof(char *) * (buffsize + 2));
	if (toks == NULL)
		return (NULL);

	/* iterate from string index 0 to string ending index */
	while (str[se] != '\0')
		se++;
	while (si < se)
	{
		/* malloc lengths for each token ptr in array */
		len = t_strlen(str, si, d_ch);
		toks[p] = malloc(sizeof(char) * (len + 1));
		if (toks[p] == NULL)
			return (NULL);
		i = 0;
		while ((str[si] != d_ch) &&
		       (str[si] != '\0'))
		{
			toks[p][i] = str[si];
			i++;
			si++;
		}
		toks[p][i] = '\0'; /* null terminate at end*/
		p++;
		si++;
	}
	toks[p] = NULL; /* set last array ptr to NULL */
	return (toks);
}

/**
 * locate_cmd_in_path - filter out command by appending it to a
 * matching PATH directory
 * @str: first command user typed into shell (e.g. "ls" if user typed "ls -l")
 * Return: a copy of fleshed out command (e.g. "/bin/ls" if originally "ls")
 */
char *locate_cmd_in_path(char *str)
{
	char *path = _getenv("PATH", 0);
	char *dir_path = NULL;
	char *file_path = NULL;

	/* PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin */
	if (file_exist(str)) /* check if command is absolute path */
		return (_strdup(str));
	/* PATH\0/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin */
	strtok(path, "=");
	dir_path = strtok(NULL, ":");
	while (dir_path)
	{
		file_path = combine_path('/', dir_path, str);
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
