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

char *get_input();
void parse_input(char *input, chain_t chain);
char *change_prompt(chain_t chain);
void save_blockchain();

#endif