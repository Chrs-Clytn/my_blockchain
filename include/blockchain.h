#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

typedef struct block_s {
    char *bId;
    struct block_s *next;
} block_t;

typedef struct node_s {
    block_t *block_head;
    int nId;
    struct node_s *next;
} node_t;

node_t *append_node(node_t *head, int n_id);
block_t *append_block(block_t *block_head, char *b_id);

#endif