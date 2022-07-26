#include "blockchain.h"
#include "string_mgmt.h"
#include "parse_save.h"
#include "action.h"

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
    if ((command->rm == true)) // remove node
    {
        if (command->all == true)
        {
            while (current != NULL) // loop through nodes and remove based on id, setting id to current nid
            {
                node_t *next = current->next; // set temp to current->next to save
                int all_id = current->nId; // set al_id to current node id
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
        }
    }
    return chain->head;
}

node_t *action_block(command_t *command, chain_t *chain)
{
    node_t *currNode = chain->head;
    if ((command->add == true)) // add block
    {
        if (chain->head == NULL)
            printf("%s\n", ERR_4);
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
                printf("%s\n", ERR_4);
            // should also add something more specific to counter whether block also already exists.
            currNode = currNode->next;
        }
    }
    if((command->rm == true)) // remove block
    {
        while(currNode != NULL) // loop through nodes
        {
            block_t *currBlock = currNode->block_head;
            remove_blocks(currBlock, command->cmd_block_id);
            currNode = currNode->next;
        }
     }
    return chain->head;
}

void delete_duplicates(block_t *my_list) // deletes duplicates from block list
{
    block_t *a_list, *b_list, *last, *temp; // create some extras to assist with loops
    a_list = b_list = last = my_list; // assign to my list
    // printf("b_list id = %s\n", b_list->bId);
    b_list = b_list->next; // b_list equals next
    while (a_list != NULL)
    {
       // printf("110 alist bid = %s\n", a_list->bId);
        while (b_list != NULL && b_list->bId != a_list->bId)
        {
            //printf("113 blist bid = %s\n", b_list->bId);
            last = b_list; // loops through to assign last block to last
            b_list = b_list->next;
        }
        if (b_list == NULL) // if b list is null a_list is next
        {
            //printf("line 119\n");
            a_list = a_list->next;
            if (a_list != NULL && a_list->next != NULL)
            {
                //printf("alist != NULL\n");
                //printf(" 124 alist bid = %s\n", a_list->bId);
                //printf("alist next = %s\n", a_list->next->bId);
                b_list = a_list->next; // if a list isnt Null b_list is the next a list
                //printf("another thing\n");
            }
            else
                return;
        }
        else if (b_list->bId == a_list->bId) // otheriwse if bids from a and b list match
        {
            //printf("last bid = %s\n", last->bId);
            //printf("127 blist b id = %s\n", b_list->bId);
            last->next = b_list->next; // last next pointer is blist next which we then free
            temp = b_list;
            //printf("temp bid = %s\n", temp->bId);
           // printf("address to delete %p\n ", &(temp->bId));
            b_list = b_list->next;
            //printf("139\n");
            free(temp);
            temp = NULL;
            //printf("142\n");
        }
    }
    //printf("exit\n");
    // free(a_list);
    // free(b_list);
    // free(last);
}

void dup_block(node_t *node) // function to delete duplicate blocks from each of the nodes
{
    //printf("135\n");
    node_t *noder = node;
    while(noder != NULL) // loops through the each of the nodes
    {
        block_t *b_head = noder->block_head; // deletes duplicate blocks from the blockhead
        listPrinter(noder, "-l");
        if(b_head != NULL)
            delete_duplicates(b_head);
        //printf("144 bid = %s\n", b_head->bId);
        noder = noder->next;
    }
    //printf("143\n");
}

void block_adder(block_t *list, node_t *node) // function to add blocks from my list into the block lists in each node
{
    node_t *noder = node;
    block_t *lister = list;
    while(lister != NULL) // loop through the list of blocks to add first
    {
        node_t *c_node = noder;
        //printf("block lister is = %s\n", lister->bId);
        while(c_node != NULL)
        {
            if(c_node->block_head == NULL)
                c_node->block_head = append_block(c_node->block_head, lister->bId);
            block_t *blocker = c_node->block_head;
            append_block(blocker, lister->bId); // append bid from list to block struct within each node
            c_node = c_node->next;
        }
        lister = lister->next;
    }
    //printf("162\n");
    dup_block(node); // delete duplicate blocks from each node
    //printf("something\n");
}

chain_t *kitchen_sync(chain_t *chain) // sync function
{
    block_t *list = NULL; // create new list of blocks to fill with all
    node_t *n_head = chain->head;
    while (n_head != NULL) // loop through the nodes
    {
        block_t *b_head = n_head->block_head; // assign blockhead from each node within the loop
        while (b_head != NULL) // loop through blockhead
        {
            if(b_head->bId != NULL)
                list = append_block(list, b_head->bId); // append each bid to my new list
            b_head = b_head->next;
        }
        n_head = n_head->next;
    }
    //printf("180\n");
    //delete_duplicates(list); // deletes duplicates from my new list of all block ids
    //printf("182\n");
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
        // printf("current bid = %s\n", chain->head->block_head->bId);
        chain->synced = true;
    }
    return chain;
}