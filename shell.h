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
char **_str_tok(char *str, char *delm);
char *get_stdin(void);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
size_t _getline(char **str);
void free_double_ptr(char **str);
char *_getenv(const char *name, const int num_ex);
char *_strdup(const char *str);
char *locate_cmd_in_path(const char *name);
char *combine_path(const char sep, const char *path1, const char *path2);
int file_exist(const char *path);
char *int_to_string(int number);
void not_found_err(char *str, int c_n);
int built_in(char **token, int num, char **command);
int __exit(char **str, int num, char **command);
int _strcmp(char *s1, char *s2);
int _execve(char **s, int num);

void non_interactive(void);

#endif
