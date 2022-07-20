#include "blockchain.h"
#include "string_mgmt.h"
#include "parse_save.h"

// replace lib functions with self-made functions; these are either in helpers.c (include helpers.h if necessary) or string_mgmt.c

node_t *append_node(node_t *node_head, int n_id) // this appends to the node struct, takes the node_head and node id.
{
    printf("9 blockchain\n");
    if (node_head == NULL) // if node_head is empty, fill and return node_head
    {
        node_t *node_head = malloc(sizeof(node_t));
        block_t *block_head = malloc(sizeof(block_t));
        block_head->bId = NULL;
        block_head->next = NULL;
        node_head->nId = n_id;
        node_head->next = NULL;
        return node_head;
    }
    node_t *current = node_head;
    while (current->next != NULL) // otherwise loop through list until we reach the last entry
        current = current->next;
    node_t *new = (node_t *)malloc(sizeof(node_t)); // allocate memory to a new node and fill with node id.
    block_t *block_head = NULL;
    block_head->bId = NULL;
    block_head->next = NULL;
    new->nId = n_id;
    new->next = NULL;
    current->next = new;

    return node_head;
}

block_t *append_block(block_t *block_head, char *b_id) // this appends to the block struct, takes the block_head and block id.
{
    block_t *current = block_head;
    if (current->bId == NULL) // if current is empty, fill and return current
    {
        current->bId = b_id;
        current->next = NULL;
        return current;
    }
    while (current->next != NULL) // otherwise loop through list until we reach the last entry
        current = current->next;
    block_t *new = (block_t *)malloc(sizeof(block_t)); // allocate memory to a new node and fill with node id.
    new->bId = b_id;
    new->next = NULL;
    current->next = new;
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

void remove_blocks(block_t *block_head, char *b_id) // function to remove blocks, will require some testing
{
    block_t *temp, *current, *prev;
    if (my_strcmp(b_id, "*") == 0) // if node id == * delete all nodes
    {
        current = block_head;
        while (current != NULL) // this should loop through all nodes in list, setting the current->next to NULL and freeing the current. not convinced this will work. Need to test once stuff is up and running
        {
            temp = current->next;
            current->next = NULL;
            free(block_head);
            current = temp;
        }
    }
    while (block_head != NULL) // while the blockhead exists and isnt null
    {
        if (my_strcmp(block_head->next->bId, b_id)) // use my_strcmp to see whter the bid matches, if it does switch some nodes around and free the node with matching bid
        {
            prev = block_head;
            temp = block_head->next;
            current = block_head->next->next;
            prev->next = current;
            temp->next = NULL;
            free(temp);
        }
    }
}

int listPrinter(node_t *node_head, char *argument) // generic list printer
{
    node_t *current = node_head;
    if(node_head == NULL)
    {
        printf("%s\n", ERR_4);
        return 1;
    }
    if (my_strcmp(argument, "-l")) // if argument -l provided print out node id, followed by block ids followed by \n
    {
        while (current != NULL)
        {
            printf("%d : ", current->nId);
            while (current->block_head != NULL)
            {
                printf("%s, ", current->block_head->bId);
                current->block_head = current->block_head->next;
            }
            printf("\n");
            current = current->next;
        }
    }
    else
        while (current != NULL) // if no -l argument, print out node id and \n
        {
            printf("%d\n", current->nId);
            current = node_head->next;
        }
    return 0;
}

node_t *action_node(command_t *command, chain_t *chain)
{
    node_t *current = chain->head;
    if((command->add == true)) // add node
    {
        //printf("160 blockchain");
        if(chain->head == NULL)
        {
            // printf("164 bc\n");
            chain->head = append_node(chain->head, command->cmd_node_id);
            printf("head node id = %d\n", chain->head->nId);
            return chain->head;
        }
        else
        {
            while(current != NULL) // loop through nodes
            {
                // printf("Here\n");
                if(current->nId == command->cmd_node_id) // compare the node ids for a match
                    printf("%s", ERR_2);
                else if(current->next == NULL) // else if next is NULL, no more nodes to check so append a new node.
                    append_node(current, command->cmd_node_id);
                current = current->next;
            }
        }
    }
    // if((command->rm == true)) // remove node
    // {
    //     while(chain->head != NULL) // loop through nodes
    //     {
    //         // need to add coverage for *
    //         if(chain->head->nId == command->cmd_node_id)
    //             remove_nodes(chain->head, command->cmd_node_id);
    //         else if (chain->head->next == NULL)
    //             printf("%s\n", ERR_4);
    //     }    
    // }
    return chain->head;
}

node_t *action_block(command_t *command, chain_t *chain)
{
    //block_t *current = chain->head->block_head;
    node_t *currNode = chain->head;
    if ((command->add == true)) // add block
    {
        // need to add coverage for if * is used to edit all nodes
        if (chain->head == NULL)
            printf("this %s\n", ERR_4);
        else
        {
            while (currNode!= NULL) // loop through nodes
            {
                if (currNode->nId == command->cmd_node_id)                                               // compare node ids
                    currNode->block_head = append_block(currNode->block_head, command->cmd_block_id); // append block to specific node
                else if (currNode->next == NULL)
                    printf("222 - %s\n", ERR_4);
                // should also add something more specific to counter whether block also already exists.
                currNode = currNode->next;
            }
        }
    }
    // if((command->rm == true)) // remove block
    // {
    //     while(chain->head != NULL) // loop through nodes
    //     {
    //         // need to add coverage for *
    //         if(chain->head->block_head->bId == command->cmd_block_id)
    //             remove_blocks(chain->head->block_head, command->cmd_block_id);
    //         else if (chain->head->next == NULL)
    //             printf("%s\n", ERR_5);
    //     }
    // }
    return chain->head;
}

chain_t *take_action(command_t *command, chain_t *chain)
{
    if(command->node == true) // we know the node is being affected
        chain->head = action_node(command, chain);
    printf("node id in take action = %d\n", chain->head->nId);
    if(command->block == true) // we know the block is being affected
        action_block(command, chain);
    if(command->ls == true)  // ls 
    {
        if(command->ls_blocks == true)
            listPrinter(chain->head, "-l");
        else
            listPrinter(chain->head, "no long");
    }
    return chain;
}

// Need to add a sync function
// loop through nodes and find node with most blocks,
//ccopy blocks from that node to all other nodes