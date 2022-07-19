#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "parse_save.h"
#include "blockchain.h"
#include "string_mgmt.h"
#include "dbg.h"

#ifndef PROMPT_S
#define PROMPT_S
typedef struct prompt_s {
    char synced;
    int nodes;
} prompt_t;
#endif

#define ERR_1 "No more resources available on the computer.\n"
#define ERR_2 "This node already exists.\n"
#define ERR_3 "This block already exists.\n"
#define ERR_4 "Node doesn't exist.\n"
#define ERR_5 "Block doesn't exist.\n"
#define ERR_6 "Command not found.\n"

#endif
