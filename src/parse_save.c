#include "parse_save.h"

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

void parse_input(char *input, chain_t chain)  // all the functionality (append, remove, list, sync) comes in here!!
{
    debug("input: %s", input);
    // create string arr for all the input items
    // char **input_arr = NULL;

    // use my_split or one of those to take each input item separately
    // if (my_strcmp("add", input_arr[0]) == 0)
    //  append_node()
    // etc...
}

char *change_prompt(chain_t chain)
{
    /// build prompt str from basic chain info ///

    // create string from node size for malloc
    char *node_size = my_itoa(chain.nodes);
    int len = my_strlen(node_size) + 1;

    char *prompt = malloc(sizeof(char) * len + 1); // '+ 1' is the 'synced' char
    prompt[len] = '\0';

    // set synced char in the string
    if (chain.synced == true)
        prompt[0] = 's';
    else
        prompt[0] = '-';

    // copy node size
    for (int i = 0; node_size[i] != '\0'; i++)
        prompt[i + 1] = node_size[i];

    // debug("prompt: %s", prompt);

    return prompt;
}

void save_blockchain()
{

}