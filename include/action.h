#ifndef ACTION_H
#define ACTION_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef BLOCK_S
#define BLOCK_S
typedef struct block_s {
    char *bId;
    struct block_s *next;
} block_list_t;
#endif
#endif