#include "main.h"
#include "blockchain.h"
#include "string_mgmt.h"
#include "dbg.h"

char *get_input();
char *change_prompt(char *input);

int main(void)
{
    char *prompt_string = "s0";
    char *input = NULL;

    while (1)
    {
        printf("[%s]>\n", prompt_string);

        input = get_input();
        
        // do other stuff with input info -> parsing

        // exit condition
        if (my_strcmp(input, "quit") == 0)
            break;
        
        // prepare string for next prompt
        // prompt_string = change_prompt(input);

        input = NULL;
        free(input);
    }

    // when the user quit, input still has to be freed
    if (input)
    {
        input = NULL;
        free(input);
    }
    return 0;
}

char *get_input()
{
    // set up strings
    char *input = NULL;
    char buff[MAX_INPUT_SIZE];
    my_memset(buff, '\0', MAX_INPUT_SIZE - 1);

    // read input and close buffer
    int readBytes = 0;
    readBytes = read(0, buff, MAX_INPUT_SIZE);
    buff[readBytes - 1] = '\0';

    // copy buffer for better handling & return
    input = my_strdup(buff);
    return input;
}

char *change_prompt(char *input)
{
    char *prompt = NULL;

    return prompt;
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
