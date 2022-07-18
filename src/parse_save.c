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

command_t *parse_input(char *input)  // all the functionality (append, remove, list, sync) comes in here!!
{
    // create command struct and set all fields to 0
    command_t *command = malloc(sizeof(command_t));
    if (command == NULL)
        printf("%s", ERR_1);

    command->add = false;
    command->rm = false;
    command->ls = false;
    command->sync = false;
    command->node = false;
    command->block = false;
    command->nid = false;
    command->bid = false;

    debug("input: %s", input);
    // create string arr for all the input items by using my_split on the input
    string_array *input_arr = my_split(input, " ");

    // go through string arr, fill command struct according to input
    for (int i = 0; i < input_arr->size - 1; i++)
    {
        if (my_strcmp("add", input_arr->array[i]) == 0)
        {
            debug("ADD");
            command->add = true;
        }
        // etc.
    }

    return command;
}

char *change_prompt(chain_t *chain)
{
    /// build prompt str from basic chain info ///
    // create string from node size for malloc
    char *node_size = my_itoa(chain->nodes);
    int len = my_strlen(node_size) + 1;

    char *prompt = malloc(sizeof(char) * len + 1); // '+ 1' is the 'synced' char
    prompt[len] = '\0';

    // set synced char in the string
    if (chain->synced == true)
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