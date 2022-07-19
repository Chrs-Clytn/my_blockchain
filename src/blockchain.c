#include "blockchain.h"

node_t *append_node(node_t *node_head, int n_id) // this appends to the node struct, takes the node_head and node id.
{
    if (node_head->nId == NULL) // if node_head is empty, fill and return node_head
    {
        block_t *block_head = NULL;
        node_head->nId = n_id;
        node_head->next = NULL;
        return node_head;
    }
    while (node_head->next != NULL) // otherwise loop through list until we reach the last entry
        node_head = node_head->next;
    node_t *new = (node_t *)malloc(sizeof(node_t)); // allocate memory to a new node and fill with node id.
    block_t *block_head = NULL;
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

void sorter(node_t *node_head, int n_id, char *b_id) // sorts through the nodes to know where to append the blocks
{
    node_t *current = node_head;
    char *comp = my_itoa(n_id);
    if (my_strcmp(comp, "*")) // if node id == * append block to all nodes
    {
        while (current != NULL) // loop through nodes
        {
            append_block(current->block_head, b_id);
            current = node_head->next;
        }
    }
    else
    {
        while (current->next != NULL)
        {
            if (current->nId == n_id) // if node id matches the input to the function then we continue
                append_block(current->block_head, b_id);
            current = node_head->next;
        }
    }
}

void remove_nodes(node_t *node_head, int n_id) // function to remove nodes based on node id.
{
    node_t *temp, *current, *prev;
    char *comp = my_itoa(n_id);
    if (my_strcmp(comp, "*")) // if node id == * delete all nodes
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

void remove_blocks(node_t *node_head, char *b_id, int n_id) // function to remove blocks, will require some testing
{
    block_t *temp, *current, *prev;
    while (node_head != NULL) // loop through all nodes
    {
        while (node_head->block_head != NULL) // while the blockhead exists and isnt null
        {
            if (my_strcmp(node_head->block_head->next->bId, b_id)) // use my_strcmp to see whter the bid matches, if it does switch some nodes around and free the node with matching bid
            {
                prev = node_head->block_head;
                temp = node_head->block_head->next;
                current = node_head->block_head->next->next;
                prev->next = current;
                temp->next = NULL;
                free(temp);
            }
        }
        node_head = node_head->next;
    }
}

void listPrinter(node_t *node_head, char *argument) // generic list printer
{
    while (node_head != NULL) // if no -l argument, print out node id and \n
    {
        printf("%s\n", node_head->nId);
        node_head = node_head->next;
    }
    if (my_strcmp(argument, "-l")) // if argument -l provided print out node id, followed by block ids followed by \n
    {
        while (node_head != NULL)
        {
            printf("%s : ", node_head->nId);
            while (node_head->block_head != NULL)
            {
                printf("%d, ", node_head->block_head->bId);
                node_head->block_head = node_head->block_head->next;
            }
            printf("\n");
            node_head = node_head->next;
        }
    }
}

void take_action(command_t *command, chain_t *chain)
{
    node_t *node_head = chain->head;    
    
}