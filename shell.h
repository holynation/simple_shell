#ifndef MAIN_H
#define MAIN_H

#include<unistd.h>
#include<stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


int _strcmp(const char *str1, const char *str2)
{
	int i, rtn;

	i, rtn = 0;

	while(1)
	{
		for (i = 0; str1[i] != '\0' || str2[i] != '\0'; i++)
		{
			if (str1[i] != str2[i])
			{
			    rtn = 1;

				return (-1);
			}
		}

		if (rtn == 0)
			return (0);

	}
}


void trim(char *str)
{
	int len;

	len = strlen(str) - 1;

	while (len > 0)
	{
		if (str[len] == ' ')
			len--;

		else break;
	}

	str[len] = '\0';

}


#endif