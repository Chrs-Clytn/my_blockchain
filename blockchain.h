#include <unistd.h>

#ifndef BLOCKCHAIN.H
#define BLOCKCHAIN.H

typedef struct block_s {
    char *bId;
    struct block_s *next;
} block_t;

typedef struct node_s {
    block_t *head;
    int nId;
    struct node_s *next;
} node_t;

#define ERR_1 "no more resources available on the computer"
#define ERR_2 "this node already exists"

node_t *append_node(node_t *head, int n_id);
block_t *append_block(block_t *block_head, char *b_id);

#endif