#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

node_t *append_node(node_t *head, int n_id);
block_t *append_block(block_t *block_head, char *b_id);
void sorter(node_t *node_head, int n_id, char *b_id);
void remove_nodes(node_t *node_head, int n_id);
void remove_blocks(node_t *node_head, char* b_id, int n_id);
void listPrinter(node_t* node_head, char* argument);

#endif