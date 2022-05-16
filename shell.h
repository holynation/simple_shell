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

char *get_user_command(void);
char **_str_tok(char *str, char *delm);
char *get_stdin(void);

#endif
