#ifndef PARSE_SAVE_H
#define PARSE_SAVE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"
#include "blockchain.h"
#include "helpers.h"
#include "string_mgmt.h"
#include "dbg.h"

#define MAX_INPUT_SIZE 128

#ifndef COMMAND_S
#define COMMAND_S
typedef struct command_s {
    bool add;
    bool rm;
    bool ls;
    bool sync;
    bool node;
    bool block;
    int nid;
    int bid;
} command_t;
#endif

char *get_input();
command_t *parse_input(char *input);
char *change_prompt(chain_t *chain);
void save_blockchain();

#endif