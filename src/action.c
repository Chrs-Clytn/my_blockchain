#include "blockchain.h"
#include "string_mgmt.h"
#include "parse_save.h"
#include "action.h"

node_t *action_node(command_t *command, chain_t *chain)
{
    node_t *current = chain->head;
    if (command->add == true) // add node
    {
        if (chain->head == NULL)
        {
            chain->head = append_node(chain->head, command->cmd_node_id);
            chain->nodes += 1;
            // printf("head node id = %d\n", chain->head->nId);
            return chain->head;
        }
        else
        {
            while (current != NULL) // loop through nodes
            {
                if (current->nId == command->cmd_node_id) // compare the node ids for a match
                {
                    printf("%s", ERR_2);
                    return chain->head;
                }
                else if (current->next == NULL) // else if next is NULL, no more nodes to check so append a new node.
                {
                    chain->head = append_node(chain->head, command->cmd_node_id); // give head (lol), rather than current as otherwise we lose our heads (lol)
                    chain->nodes += 1;
                    return chain->head;
                }
                current = current->next;
            }
        }
    }
    if (command->rm == true) // remove node
    {
        if (command->all == true)
        {
            while (current != NULL) // loop through nodes and remove based on id, setting id to current nid
            {
                node_t *next = current->next; // set temp to current->next to save
                int all_id = current->nId;    // set al_id to current node id
                remove_nodes(current, all_id);
                current = next;
            }
            chain->nodes = 0;
            chain->head = NULL;
        }
        else
        {
            chain->head = remove_nodes(current, command->cmd_node_id);
            chain->nodes -= 1;
            chain->synced = true;
        }
    }
    return chain->head;
}

node_t *action_block(command_t *command, chain_t *chain)
{
    node_t *currNode = chain->head;
    if (command->add == true) // add block
    {
        if (chain->head == NULL)
            printf("%s", ERR_4);

        while (currNode != NULL) // loop through nodes
        {
            if (command->all == true) // if * is called
            {
                while (currNode != NULL) // loop through nodes
                {
                    currNode->block_head = append_block(currNode->block_head, command->cmd_block_id); // append block to all nodes by loop
                    currNode = currNode->next;
                }
                return chain->head;
            }
            if (currNode->nId == command->cmd_node_id) // compare node ids
            {
                currNode->block_head = append_block(currNode->block_head, command->cmd_block_id); // append block to specific node
                chain->synced = false;
                return chain->head;
            }
            else if (currNode->next == NULL)
                printf("%s", ERR_4);
            // should also add something more specific to counter whether block also already exists.
            currNode = currNode->next;
        }
    }
    if (command->rm == true) // remove block
    {
        while (currNode != NULL) // loop through nodes
        {
            block_t *currBlock = currNode->block_head;
            remove_blocks(currBlock, command->cmd_block_id);
            currNode = currNode->next;
        }
    }
    return chain->head;
}

int block_check(block_t *blockHead, char *list_bid)
{
    block_t *block_head = blockHead;
    while (block_head != NULL)
    {
        if (my_strcmp(block_head->bId, list_bid) == 0)
            return 1;
        block_head = block_head->next;
    }
    return 0;
}

void block_adder(block_t *list, node_t *node) // function to add blocks from my list into the block lists in each node
{
    node_t *noder = node;
    block_t *lister = list;
    while (lister != NULL) // loop through the list of blocks to add first
    {
        node_t *c_node = noder;
        // printf("block lister is = %s\n", lister->bId);
        while (c_node != NULL)
        {
            if (c_node->block_head == NULL)
                c_node->block_head = append_block(c_node->block_head, lister->bId);
            else
            {
                block_t *blocker = c_node->block_head;
                int check_res = block_check(blocker, lister->bId);
                if (check_res == 0)
                    append_block(blocker, lister->bId); // append bid from list to block struct within each node
                c_node = c_node->next;
            }
        }
        lister = lister->next;
    }
}

chain_t *kitchen_sync(chain_t *chain) // sync function
{
    block_t *list = NULL; // create new list of blocks to fill with all
    node_t *n_head = chain->head;
    while (n_head != NULL) // loop through the nodes
    {
        block_t *b_head = n_head->block_head; // assign blockhead from each node within the loop
        while (b_head != NULL)                // loop through blockhead
        {
            if (b_head->bId != NULL)
                list = append_block(list, b_head->bId); // append each bid to my new list
            b_head = b_head->next;
        }
        n_head = n_head->next;
    }
    block_adder(list, chain->head); // add bid from block list to each node individually
    return chain;
}

chain_t *take_action(command_t *command, chain_t *chain)
{
    if (command->node == true && command->block == false) // we know the node is being affected
        chain->head = action_node(command, chain);

    if (command->block == true) // we know the block is being affected
        chain->head = action_block(command, chain);

    if (command->ls == true) // ls
    {
        if (chain->nodes <= 0 || chain->head == NULL)
        {
            printf("%s", ERR_4);
            return chain;
        }
        if (command->ls_blocks == true)
            listPrinter(chain->head, "-l");
        else
            listPrinter(chain->head, "no long");
    }
    if (command->sync == true)
    {
        chain = kitchen_sync(chain);
        chain->synced = true;
    }
    return chain;
}