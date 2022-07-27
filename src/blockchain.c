#include "blockchain.h"
#include "string_mgmt.h"
#include "parse_save.h"

node_t *append_node(node_t *node_head, int n_id) // this appends to the node struct, takes the node_head and node id.
{
    if (node_head == NULL) // if node_head is empty, fill and return node_head
    {
        node_t *node_head = malloc(sizeof(node_t));
        node_head->block_head = NULL;
        node_head->nId = n_id;
        node_head->next = NULL;
        return node_head;
    }
    node_t *current = node_head;
    while (current->next != NULL) // otherwise loop through list until we reach the last entry
        current = current->next;
    node_t *new = (node_t *)malloc(sizeof(node_t)); // allocate memory to a new node and fill with node id.
    new->block_head = NULL;
    new->nId = n_id;
    new->next = NULL;
    current->next = new;

    return node_head;
}

block_t *append_block(block_t *block_head, char *b_id) // this appends to the block struct, takes the block_head and block id.
{
    block_t *current = block_head;
    if (block_head == NULL) // if blockhead is empty, fill and return blockhead
    {
        block_t *block_head = malloc(sizeof(block_t));
        block_head->bId = b_id;
        block_head->next = NULL;
        return block_head;
    }
    while (current->next != NULL) // otherwise loop through list until we reach the last entry
        current = current->next;
    block_t *new = (block_t *)malloc(sizeof(block_t)); // allocate memory to a new block and fill with block id.
    new->bId = b_id;
    new->next = NULL;
    current->next = new;

    return block_head;
}

block_t *remove_blocks(block_t *block_head, char *b_id) // function to remove blocks, will require some testing
{
        block_t *temp;
        block_t *current = block_head;
        while (current != NULL)
        {
            if (my_strcmp(block_head->bId, b_id) == 0) // removes the first block
            {
                temp = block_head;
                block_head = block_head->next;
                temp->bId = NULL;
                temp->next = NULL;
                free(temp);
                return block_head;
            }
            else if (((my_strcmp(current->next->bId, b_id)) == 0) && current->next->next != NULL) // checks if the next block id is what we need, if it is set next to temp, current to next-next and then set temp nxt to NULL and free temp.
            {
                temp = current->next;
                current->next = current->next->next;
                temp->bId = NULL;
                temp->next = NULL;
                free(temp);
                return block_head;
            }
            else if (my_strcmp(current->bId, b_id) == 0 && current->next->next == NULL)
            {
                temp = current->next;
                temp->bId = NULL;
                current->next = NULL;
                free(temp);
                return block_head;
            }
            else
                break;
            current = current->next;
        }
    return block_head;
}

node_t *remove_nodes(node_t *node_head, int n_id) // function to remove nodes based on node id.
{
    node_t *current = node_head, *temp;
    while (current != NULL)
    {
        if(node_head->nId == n_id) // removes the first node bu pointing at the next and free
        {
            temp = node_head;
            node_head = node_head->next;
            temp->next = NULL;
            if(temp->block_head != NULL) // if blockhead is present
            {
                while(temp->block_head != NULL) // loop through the blockhead list
                {
                    block_t *prev;// create some temp block lists
                    prev = temp->block_head; // assign them to my blockhead
                    prev = NULL;
                    free(prev);
                    temp->block_head = temp->block_head->next;
                }
            }
            free(temp);
            return node_head;
        }
        else if (current->next->nId == n_id) // checks if the next node id is what we need, if it is set head to prev, next to temp, current to next-next and then set temp nxt to NULL and free temp. Also will need testing
        {
            temp = current->next;
            if (current->next->next != NULL)
                current->next = current->next->next;
            else
                current->next = NULL;
            temp->next = NULL;
            if(temp->block_head != NULL) // if blockhead is present
            {
                while(temp->block_head != NULL) // loop through the blockhead list
                {
                    block_t *prev;// create some temp block lists
                    prev = temp->block_head; // assign them to my blockhead
                    prev = NULL;
                    free(prev);
                    temp->block_head = temp->block_head->next;
                }
            }
            free(temp);
            return node_head;
        }
        current = current->next;
    }
    return node_head;
}

node_t *listPrinter(node_t *node_head, char *argument) // generic list printer
{
    node_t *current = node_head;
    //printf("node head list printer 118 %d\n", node_head->nId);
    if (node_head == NULL)
    {
        printf("%s\n", ERR_4);
        return node_head;
    }
    if (my_strcmp(argument, "-l") == 0) // if argument -l provided print out node id, followed by block ids followed by \n
    {
        //printf("block head printer, 123 %s\n", node_head->block_head->bId);
        while (current != NULL)
        {
            printf("%d : ", current->nId);
            block_t *currBlock = current->block_head;
            while (currBlock != NULL)
            {
                printf("%s, ", currBlock->bId);
                currBlock = currBlock->next;
            }
            printf("\n");
            current = current->next;
        }
        return node_head;
    }
    else
        while (current != NULL) // if no -l argument, print out node id and \n
        {
            printf("%d\n", current->nId);
            current = current->next;
        }
    return node_head;
}