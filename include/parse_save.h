#ifndef PARSE_SAVE_H
#define PARSE_SAVE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
//#include <sys/uio.h>
#include "main.h"
#include "blockchain.h"
#include "helpers.h"
#include "string_mgmt.h"
#include "dbg.h"

#define MAX_INPUT_SIZE 256
#define ERR_7 "File cannot be opened."
#define ERR_8 "Not a valid chain file."

#ifndef COMMAND_S
#define COMMAND_S
typedef struct command_s {
    bool add;
    bool rm;
    bool ls;
    bool ls_blocks;
    bool sync;
    bool node;
    bool block;
    int cmd_node_id;
    char *cmd_block_id;
    bool all;
} command_t;
#endif

chain_t *open_chain(char *filename);
char *get_input();
command_t *parse_input(char *input);
char *change_prompt(chain_t *chain);
void save_blockchain();
chain_t *take_action(command_t *command, chain_t *chain);

#endif