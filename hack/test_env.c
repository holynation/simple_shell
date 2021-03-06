#include "shell.h"

/**
 * _unsetenv - removes an environment variable
 * @name: name of the environment variable
 * Return: 0 on sucess otheewise -1
 */

int _unsetenv(char *name)
{
	char **new_env;
	unsigned int i = 0, count = 0;
	int cmp_val;

	while (environ[i])
	{
		cmp_val = _strcmp(name, environ[i]);
		if (cmp_val == 0)
			count++;
		i++;
	}
	i--;
	if (count == 0)
	{
		write(STDERR_FILENO, "No variable to unset\n", 21);
		return (0);
	}
	new_env = malloc(i * sizeof(char *));
	if (new_env == NULL)
	{
		perror("Unable to remove env variable");
		return (-1);
	}
	count = 0;
	for (i = 0; environ[i]; i++)
	{
		cmp_val =  _strcmp(name, environ[i]);
		if (cmp_val == 0)
			;
		else
			new_env[count++] = environ[i];
	}
	new_env[count++] = NULL;
	environ = new_env;
	return (0);
}

/**
 * _setenv -  set an environmental variable
 * @name: name of the variable
 * @value: value of the variable
 * Return: 0 on success and -1 on failure
 */

int _setenv(char *name, char *value)
{
	int i = 0, count = 0;
	char **new_env = NULL, *new_var = NULL;

	while (environ[i] != NULL)
	{
		if (_strcmp(name, environ[i]) == 0)
			count++;
		i++;
	}
	if (count != 0)
		new_env = malloc(sizeof(char *) * i);
	else
		new_env = malloc(sizeof(char *) * (i + 1));
	count = 0;
	new_var = setenv_cat(name, value);
	if (new_var == NULL)
	{
		free(new_env);
		perror("unable to set environmental variable");
		return (-1);
	}
	for (i = 0; environ[i]; i++)
	{
		if (_strcmp(name, environ[i]) == 0)
		{
			new_env[i] = new_var;
			count++;
		}
		else
			new_env[i] = environ[i];
	}
	if (count == 0)
		new_env[i++] = new_var;
	new_env[i] = NULL;
	environ = new_env;
	return (0);
}

/**
 * setenv_cat - concats name and value about to be set
 * @name: name of env variable
 * @value: value of env variable
 * Return: a pointer to the concatenated env variable
 */

char *setenv_cat(char *name, char *value)
{
	int len, i;
	char *new_var;

	len = _strlen(name) + _strlen(value) + 2;
	if (len <= 2)
		return (NULL);
	new_var = malloc(sizeof(char) * len);
	if (new_var == NULL)
		return (NULL);
	for (len = 0; name[len]; len++)
		new_var[len] = name[len];
	new_var[len] = '=';
	len++;
	for (i = 0; value[i]; i++, len++)
		new_var[len] = value[i];
	new_var[len] = '\0';
	return (new_var);
}

/**
 * locate_cmd_in_path_1 - filter out command by appending it to a 
 * matching PATH directory
 * @str: first command user typed into shell (e.g. "ls" if user typed "ls -l")
 * Return: a copy of fleshed out command (e.g. "/bin/ls" if originally "ls")
 */
char *locate_cmd_in_path_1(char *str)
{
	char *pth, *cat = NULL, **toks;
	int i = 0;

	if (file_exist(str)) /* check if command is absolute path */
		return (_strdup(str));
	/* get and tokenize PATH directories, then free original string */
	pth = _getenv("PATH", 0);
	toks = c_str_tok(pth, ":");
	free(pth);

	/* append "/str" to each token to see it's valid */
	i = 0;
	while (toks[i] != NULL)
	{
		if (toks[i][0] == '\0')
			cat = getcwd(cat, 0);
		else
			cat = _strdup(toks[i]);
		cat = combine_path('/', cat, str);
		if (access(cat, F_OK) == 0)
		{
			/* free tokens before returning legit fleshed path */
			free_double_ptr(toks);
			return (cat);
		}
		free(cat); /* free concatenated string if cmd is never found */
		i++;
	}
	free_double_ptr(toks);
	return (str); /* return string if not found; won't pass execve */
}