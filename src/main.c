#include "main.h"

int main(int ac, char **av)
{     
    chain_t *chain = NULL;
    // if chain exists, open it & save info to chain struct
    if (ac == 2)
    {
        chain = open_chain(av[1]);
        if (chain == NULL)
            return -1;
    }
    // else create empty blockchain
    else
    {
        chain = malloc(sizeof(chain_t));
        if (chain == NULL)
            printf("%s", ERR_1);
            
        chain->synced = true;
        chain->nodes = 0;
        chain->head = NULL;
    }

    // set strings for first prompt
    char *prompt_string = change_prompt(chain);
    char *input = "";

    while (true)
    {
        // print prompt to terminal, then reset input before get_input()
        printf("[%s]> %s\n", prompt_string, input);
        
        input = NULL;
        free(input);
        input = get_input();

        // exit condition
        if (my_strcmp(input, "quit") == 0)
        {
            save_blockchain();
            break;
        }

        // input parsing
        command_t *command = parse_input(input);
        debug("add now? %d", command->add);
        debug("node? %d", command->node);
        debug("node_id? %d", command->cmd_node_id);
        debug("block_id? %s", command->cmd_block_id);
        debug("all? %d", command->all);
        debug("ls? %d", command->ls);
        debug("ls blocks? %d", command->ls_blocks);

        // the action takes places here, depending on command
        // take_action(command, chain);
        
        // prepare string for next prompt
        prompt_string = NULL;
        prompt_string = change_prompt(chain);

        // empty & free command for next round
        command = NULL;
        free(command);
    }

    // when the user quit, input still has to be freed
    if (input)
        free(input);
    
    free(chain);

    return 0;
}

// create main function to read the prompt to buffer
// this should consist of a loop to read the prompt
// should print out the prompt each loop
// print out either "s" or "-" whether synchronised or not. and the number of nodes surrounded by brackets with > e.g. [s1]>

// create function to append to the node struct
// take node id from prompt and create a node with that id

// create function to append to the block struct and to a specific node
// take node id add block struct to that node id
// take block id from prompt and create a block with that id
// if nid = "*" block is added to all nodes

// create function to remove nodes
// remove node based on nid
// if nid = "*" all nodes are removed

// create function to remove blocks
// remove block based on bid

// create function to list the node identifiers
// print out nid and "\n"
// if option -l print out nid followed by ":" space and then bid followed by "," until bid = NULL then "\n"

// create a sync function to copy all blocks to each node
// iterate through nodes and find one with the most blocks
// copy those blocks to each other node

// add quit to the initial loop inside the main
