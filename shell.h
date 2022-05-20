#ifndef __SHELL__
#define __SHELL__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>
#include <errno.h>
#include <stddef.h>

extern char **environ;

char *get_user_command(void);
char **_strtok(char *str, char *delm);
char *get_stdin(void);
int _strlen(char *s);
int t_strlen(char *str, int pos, char delm);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
size_t _getline(char **str);
void free_double_ptr(char **str);
char *_getenv(const char *name, const int num_ex);
char *_strdup(const char *str);
char *locate_cmd_in_path(char *str);
char *combine_path(const char sep, const char *path1, const char *path2);
int file_exist(const char *path);
char *int_to_string(int number);
void not_found_err(int c_n, char **av);
int built_in(char **token, int num, char **command, char **av);
int __exit(char **str, int num, char **command, char **av);
int _strcmp(char *s1, char *s2);
int _execve(char **s, int num, char **av);
void _printenv(void);
void unknown_number(char **av);


void non_interactive(void);

#endif
