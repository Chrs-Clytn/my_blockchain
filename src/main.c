#include "main.h"

int main(void)
{
    chain_t *chain = malloc(sizeof(chain_t));
    if (chain == NULL)
        printf("%s", ERR_1);
        
    // if saved blockchain exists, load it here
    // chain = open_chain(argv[1]);  // chain struct might need more info on actual nodes and blocks

    // else create empty blockchain
    chain->synced = true;
    chain->nodes = 0;
    chain->node_head = NULL;

    // set strings for first prompt
    char *prompt_string = change_prompt(chain);
    char *input = "";

    while (true)
    {
        // print prompt to terminal, then reset input before get_input()
        printf("[%s]> %s\n", prompt_string, input);
        // we are getting an extra newline from read for enter when starting program

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
        debug("node id? %d", command->node_id);
        debug("block id? %s", command->block_id);
        debug("all? %d", command->all);

        // the action takes places here, depending on command

        // need a function to take the command and depending on what is true append to node or block.
        take_action(command, chain);
        
        // prepare string for next prompt
        prompt_string = NULL;
        prompt_string = change_prompt(chain);
    }

    // when the user quit, input still has to be freed
    if (input)
    {
        input = NULL;
        free(input);
    }
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
