#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef PROMPT_S
#define PROMPT_S
typedef struct prompt_s {
    char synced;
    int nodes;
} prompt_t;
#endif

#define MAX_INPUT_SIZE 128

#define ERR_1 "no more resources available on the computer"
#define ERR_2 "this node already exists"

#endif
