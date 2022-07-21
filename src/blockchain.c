#include "blockchain.h"
#include "string_mgmt.h"
#include "parse_save.h"

// replace lib functions with self-made functions; these are either in helpers.c (include helpers.h if necessary) or string_mgmt.c

node_t *append_node(node_t *node_head, int n_id) // this appends to the node struct, takes the node_head and node id.
{
    if (node_head == NULL) // if node_head is empty, fill and return node_head
    {
        (printf("11, node head was NULL\n"));
        node_t *node_head = malloc(sizeof(node_t));
        node_head->block_head = NULL;
        node_head->nId = n_id;
        node_head->next = NULL;
        return node_head;
    }
    printf("18, appending new node. node_head->nid = %d\n", node_head->nId);
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
        printf("line 36 add new block\n");
        block_t *block_head = malloc(sizeof(block_t));
        block_head->bId = b_id;
        block_head->next = NULL;
        return block_head;
    }
    while (current->next != NULL) // otherwise loop through list until we reach the last entry
        current = current->next;
    printf("line 44 append block\n");
    block_t *new = (block_t *)malloc(sizeof(block_t)); // allocate memory to a new block and fill with block id.
    new->bId = b_id;
    new->next = NULL;
    current->next = new;

    return block_head;
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

node_t *action_node(command_t *command, chain_t *chain)
{
    node_t *current = chain->head;
    if ((command->add == true)) // add node
    {
        if (chain->head == NULL)
        {
            chain->head = append_node(chain->head, command->cmd_node_id);
            chain->nodes += 1;
            //printf("head node id = %d\n", chain->head->nId);
            return chain->head;
        }
        else
        {
            while (current != NULL) // loop through nodes
            {
                if (current->nId == command->cmd_node_id) // compare the node ids for a match
                    printf("%s", ERR_2);
                else if (current->next == NULL) // else if next is NULL, no more nodes to check so append a new node.
                {
                    chain->head = append_node(chain->head, command->cmd_node_id); // give head (lol), rather than current as otherwise we lose our heads (lol)
                    chain->nodes += 1;
                    //chain->synced = false;
                    return chain->head;
                }
                current = current->next;
            }
        }
    }
    // if((command->rm == true)) // remove node
    // {
    //     while(current != NULL) // loop through nodes
    //     {
    //         // need to add coverage for *
    //         if(current->nId == command->cmd_node_id)
    //             remove_nodes(current, command->cmd_node_id);
    //         else if (current->next == NULL)
    //             printf("%s\n", ERR_4);
    //     }
    // }
    return chain->head;
}

// Blocks dont seem to persist after 1 cycle, need to figure out why.
// Seems that block_head is equal to NULL after my list printer.
// is list printer resetting blockhead to null? or cycling through the list maybe....

node_t *action_block(command_t *command, chain_t *chain)
{
    node_t *currNode = chain->head;
    if ((command->add == true)) // add block
    {
        // need to add coverage for if * is used to edit all nodes
        if (chain->head == NULL)
            printf("this %s\n", ERR_4);
        else
        {
            while (currNode != NULL) // loop through nodes
            {
                if (currNode->nId == command->cmd_node_id) // compare node ids
                {
                    currNode->block_head = append_block(currNode->block_head, command->cmd_block_id); // append block to specific node
                    //printf("207 current node id %d\n", currNode->nId);
                    //printf("current bid = %s\n", currNode->block_head->bId);
                    return chain->head;
                }
                else if (currNode->next == NULL)
                    printf("207 - %s\n", ERR_4);
                // should also add something more specific to counter whether block also already exists.
                currNode = currNode->next;
            }
        }
    }
    // if((command->rm == true)) // remove block
    // {
    //     while(currNode != NULL) // loop through nodes
    //     {
    //         // need to add coverage for *
    //         if(currNode->block_head->bId == command->cmd_block_id)
    //             remove_blocks(currNode->block_head, command->cmd_block_id);
    //         else if (currNode->next == NULL)
    //             printf("%s\n", ERR_5);
    //     }
    // }
    return chain->head;
}

chain_t *take_action(command_t *command, chain_t *chain)
{
    if (command->node == true && command->block == false) // we know the node is being affected
        chain->head = action_node(command, chain);
    // printf("node id in take action = %d\n", chain->head->nId);
    if (command->block == true) // we know the block is being affected
    {
        chain->head = action_block(command, chain);
        //printf("240, block take action = %s\n", chain->head->block_head->bId);
    }
    if (command->ls == true) // ls
    {
        if (chain->nodes <= 0)
        {
            printf("%s", ERR_4);
            return chain;
        }
        if (command->ls_blocks == true)
            listPrinter(chain->head, "-l");
        else
            listPrinter(chain->head, "no long");
    }
    return chain;
}

// Need to add a sync function
// loop through nodes and find node with most blocks,
// ccopy blocks from that node to all other nodes

// void sorter(node_t *node_head, int n_id, char *b_id) // sorts through the nodes to know where to append the blocks
// {
//     node_t *current = node_head;
//     char *comp = my_itoa(n_id);
//     if (my_strcmp(comp, "*")) // if node id == * append block to all nodes
//     {
//         while (current != NULL) // loop through nodes
//         {
//             append_block(current->block_head, b_id);
//             current = node_head->next;
//         }
//     }
//     else
//     {
//         while (current->next != NULL)
//         {
//             if (current->nId == n_id) // if node id matches the input to the function then we continue
//                 append_block(current->block_head, b_id);
//             current = node_head->next;
//         }
//     }
// }