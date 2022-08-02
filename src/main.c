#include "main.h"

int main(int ac, char **av)
{     
    chain_t *chain = NULL;
    // if chain exists, open it & save info to chain struct
    if (ac == 2)
    {
        chain = open_chain(av[1]);
        if (chain == NULL)
        {
            printf("%s", ERR_8);
            return -1;
        }
    }
    // else create empty blockchain
    else
    {
        chain = malloc(sizeof(chain_t));
        if (chain == NULL)
            printf("%s", ERR_1);
        
        node_t *node_head = NULL;
        //node_t *node_head = malloc(sizeof(node_t));
        //block_t *block_head = malloc(sizeof(block_t));
            
        chain->synced = true;
        chain->nodes = 0;
        //chain->head = NULL;
        chain->head = node_head;
        // chain->head->block_head = block_head;
        // chain->head->block_head->bId = "ADBCJada";
    }
    //printf("%s\n", chain->head->block_head->bId);

    // set strings for first prompt
    char *prompt_string = change_prompt(chain);
    char *input = "";

    while (true)
    {
        input = get_input(prompt_string);

        // input = NULL;
        // free(input);
        // input = get_input();

        // exit condition
        if (my_strcmp(input, "quit") == 0)
        {
            save_blockchain(chain);
            break;
        }

        // input parsing
        command_t *command = parse_input(input);

        // the action takes places here, depending on command
        chain = take_action(command, chain);
        
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
// mostly done, might want to refine s when adding nodes

// create function to append to the node struct
// take node id from prompt and create a node with that id
// DONE

// create function to append to the block struct and to a specific node
// take node id add block struct to that node id
// take block id from prompt and create a block with that id
// if nid = "*" block is added to all nodes
// DONE

// create function to remove nodes
// remove node based on nid
// if nid = "*" all nodes are removed
// DONE

// create function to remove blocks
// remove block based on bid
// DONE

// create function to list the node identifiers
// print out nid and "\n"
// if option -l print out nid followed by ":" space and then bid followed by "," until bid = NULL then "\n"
// DONE

// create a sync function to copy all blocks to each node
// iterate through nodes and blocks, store all block ids in a list
// copy those blocks to each other node
// remove duplicates from all block lists
// mostly done, still some edge cases to work out

// add quit to the initial loop inside the main

// create save function,
// make a file and store Node id : block id, block id etc. on each line
// mostly done, getting some memory warnings when quitting, but file is created

// create open function
// if file is added as argument, 
// open file and store info into current lists
