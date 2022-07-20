#include "parse_save.h"

chain_t *open_chain(char *filename)
{
    chain_t *chain = malloc(sizeof(chain_t));

    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("%s\n", ERR_7);
        chain = NULL;
        return chain;
    }
    // read file and get info for synced, nodes and head
    // if it's no valid chain file
    // {
    //     printf("%s\n", ERR_8);
    //     chain = NULL;
    //     return chain;
    // }

    close(fd);
    return chain;
}


char *get_input(char *prompt_string)
{
    // set up strings
    char *input = NULL;
    char buff[MAX_INPUT_SIZE];
    char *s1 = &prompt_string[0];
    char *s2 = &prompt_string[1];
    my_memset(buff, '\0', MAX_INPUT_SIZE - 1);
    write(1, "[", 1);
    write(1, s1, 1);
    write(1, s2, 1);
    write(1, "]", 1);
    write(1, ">", 1);
    write(1, " ", 1);
    // read input and close buffer
    int readBytes = 0;
    readBytes = read(0, buff, MAX_INPUT_SIZE);
    buff[readBytes - 1] = '\0';

    // copy buffer for better handling & return
    input = my_strdup(buff);
    return input;
}

// char *get_input()
// {
//     // set up strings
//     char *input = NULL;
//     char buff[MAX_INPUT_SIZE];
//     my_memset(buff, '\0', MAX_INPUT_SIZE - 1);

//     // read input and close buffer
//     int readBytes = 0;
//     readBytes = read(0, buff, MAX_INPUT_SIZE - 1);
//     buff[readBytes - 1] = '\0';

//     // copy buffer for better handling & return
//     input = my_strdup(buff);
//     return input;
// }

command_t *parse_input(char *input)  // all the functionality (append, remove, list, sync) comes in here!!
{
    // create command struct and set all fields to 0
    command_t *command = malloc(sizeof(command_t));
    if (command == NULL)
        printf("%s", ERR_1);

    command->add = false;
    command->rm = false;
    command->ls = false;
    command->ls_blocks = false;
    command->sync = false;
    command->node = false;
    command->block = false;
    command->cmd_node_id = 0;
    command->cmd_block_id = NULL;
    command->all = false;

    // create string arr for all the input items by using my_split on the input
    string_array *input_arr = my_split(input, " ");

    // go through string arr, fill command struct according to input
    for (int i = 0; i < input_arr->size - 1; i++)                       // USE SWITCH CASE?
    {
        if (my_strcmp("add", input_arr->array[i]) == 0)
            command->add = true;
        if (my_strcmp("rm", input_arr->array[i]) == 0)
            command->rm = true;
        if (my_strcmp("ls", input_arr->array[i]) == 0)
            command->ls = true;
        if (my_strcmp("-l", input_arr->array[i]) == 0)
            command->ls_blocks = true;
        if (my_strcmp("sync", input_arr->array[i]) == 0)
            command->sync = true;
        if (my_strcmp("node", input_arr->array[i]) == 0)
            command->node = true;
        if (my_strcmp("block", input_arr->array[i]) == 0)
            command->block = true;

        if (input_arr->size > 3 && my_strcmp("node", input_arr->array[1]) == 0)
            command->cmd_node_id = my_atoi(input_arr->array[2]);
        if (input_arr->size > 3 && my_strcmp("block", input_arr->array[1]) == 0)
        {
            command->cmd_block_id = malloc(sizeof(char) * my_strlen(input_arr->array[2]) + 1);
            command->cmd_block_id = input_arr->array[2];
            command->cmd_node_id = my_atoi(input_arr->array[3]);
        }

        if (input_arr->size > 4 && my_strcmp("*", input_arr->array[3]) == 0)
            command->all = true;
    }

    input_arr = NULL;
    free(input_arr);
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