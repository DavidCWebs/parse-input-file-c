#ifndef FILE_UTILITIES_H
#define FILE_UTILITIES_H

#include <ctype.h>

void replaceSpaces(char *str, char substitution)
{
	while (*str) {
		if (*str == ' ') {
			*str = substitution;
		}
		str++;
	}
}

void makeLowercase(char *str)
{
	while(*str) {
		*str = tolower(*str);
		str++;
	}
}

#endif
