#ifndef STRING_MGMT_H
#define STRING_MGMT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int my_strlen(char *string);
void my_strcpy(char *dst, char *src);
char* my_strdup(char *str);
int my_strcmp(char *s1, char *s2);
int my_putchar(char c);
void my_putstr(char *string);
void my_memset(char *str, char c, int n);

#endif