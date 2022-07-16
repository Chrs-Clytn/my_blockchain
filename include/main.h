#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

#define ERR_1 "no more resources available on the computer"
#define ERR_2 "this node already exists"
#define ERR_3 "this block already exists"
#define ERR_4 "node doesn't exist"
#define ERR_5 "block doesn't exist"
#define ERR_6 "command not found"

#endif
