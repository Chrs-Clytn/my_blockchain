#include "main.h"
#include "blockchain.h"
#include "string_mgmt.h"

int main(void)
{
    char *buff = malloc(sizeof(char) * PROMPT_SIZE); // protect read & malloc
    buff[my_strlen(buff)] = '\0';

    printf("[char nbr]> ");

    // prompting loop here
    while ((my_strcmp(buff, "quit") != 0))
    {
        printf("[char nbr]> "); // user enters command here

        int readBytes = 0;
        readBytes = read(0, buff, PROMPT_SIZE);
        buff[readBytes - 1] = '\0';

        printf("buff: %s\n", buff);
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

// add quit to the intial loop inside the main
