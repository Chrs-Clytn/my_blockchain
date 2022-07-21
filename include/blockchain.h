#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef BLOCK_S
#define BLOCK_S
typedef struct block_s {
    char *bId;
    struct block_s *next;
} block_t;
#endif

#ifndef NODE_S
#define NODE_S
typedef struct node_s {
    block_t *block_head;
    int nId;
    struct node_s *next;
} node_t;
#endif

#ifndef CHAIN_S
#define CHAIN_S
typedef struct chain_s {
    bool synced;
    int nodes;
    node_t *head;
} chain_t;
#endif

node_t *append_node(node_t *head, int n_id);
block_t *append_block(block_t *block_head, char *b_id);
void sorter(node_t *node_head, int n_id, char *b_id);
node_t *remove_nodes(node_t *node_head, int n_id);
block_t *remove_blocks(block_t *block_head, char *b_id);
node_t *listPrinter(node_t* node_head, char* argument); 

#endif