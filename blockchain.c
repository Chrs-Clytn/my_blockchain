#include "blockchain.h"

node_t *append_node(node_t *node_head, int n_id) // this appends to the node struct, takes the node_head and node id.
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
            if (current->nId == n_id) // if node id matches the input to the function then we continue
                append_block(block_head, b_id);
            current = node_head->next;
        }
    }
}

void remove_nodes(node_t *node_head, int n_id) // function to remove nodes based on node id.
{
    node_t *temp, *current, *prev;
    char *comp = atoi(n_id);
    if (strcmp(comp, "*")) // if node id == * delete all nodes
    {
        current = node_head;
        while (current != NULL) // this should loop through all nodes in list, setting the current->next to NULL and freeing the current. not convinced this will work. Need to test once stuff is up and running
        {
            temp = current->next;
            current->next = NULL;
            free(node_head);
            current = temp;
        }
    }
    else // if node id isnt * then need to loop through node list until find correct node id
    {
        while (node_head != NULL)
        {
            if (node_head->next->nId == n_id) // checks if the next node id is what we need, if it is set head to prev, next to temp, current to next-next and then set temp nxt to NULL and free temp. Also will need testing
            {
                prev = node_head;
                temp = node_head->next;
                current = node_head->next->next;
                prev->next = current;
                temp->next = NULL;
                free(temp);
            }
        }
    }
}