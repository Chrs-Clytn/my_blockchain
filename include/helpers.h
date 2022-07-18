#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "string_mgmt.h"

#ifndef STRUCT_STRING_ARRAY
#define STRUCT_STRING_ARRAY
typedef struct s_string_array {
    int size;
    char **array;
} string_array;
#endif

int my_atoi(char *str);
char* my_itoa(int num);
string_array *my_split(char *str, char *sep);

#endif