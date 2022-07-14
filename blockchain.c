#include "blockchain.h"

node_t *append_node(node_t *node_head, int n_id) //this appends to the node struct, takes the node_head and node id. 
{
    if (node_head->nId == NULL) // if node_head is empty, fill and return node_head
    {
        node_head->nId = n_id;
        node_head->next = NULL;
        return node_head;
    } 
    while (node_head->next != NULL) // otherwise loop through list until we reach the last entry
        node_head = node_head->next;
    node_t *new = (node_t *)malloc(sizeof(node_t)); // allocate memory to a new node and fill with node id.
    new->nId = n_id;
    new->next = NULL;
    node_head->next = new;
    return node_head;
}

block_t *append_block(block_t *block_head, char *b_id) // this appends to the block struct, takes the block_head and block id.
{

    if (block_head->bId == NULL) // if block_head is empty, fill and return block_head
    {
        block_head->bId = b_id;
        block_head->next = NULL;
        return block_head;
    }
    while (block_head->next != NULL) // otherwise loop through list until we reach the last entry
        block_head = block_head->next;
    block_t *new = (block_t *)malloc(sizeof(block_t)); // allocate memory to a new node and fill with node id.
    new->bId = b_id;
    new->next = NULL;
    block_head->next = new;
    return block_head;
}

void sorter(block_t *block_head, node_t *node_head, int n_id, char *b_id) // sorts through the nodes to know where to append the blocks
{
    node_t *current = node_head;
    char *comp = atoi(n_id);
    if (strcmp(comp, "*")) // if node id == * append block to all nodes
    {
        while (current != NULL) // loop through nodes
        {
            append_block(block_head, b_id);
            current = node_head->next;
        }
    }
    else
    {
        while (current->next != NULL)
        {
            current = node_head->next;
            if (current->nId == n_id) // if node id matches the input to the function then we continue
                append_block(block_head, b_id);
        }
    }
}
