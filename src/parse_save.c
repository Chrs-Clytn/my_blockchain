#include "parse_save.h"

chain_t *open_chain(char *filename)
{
    chain_t *chain = malloc(sizeof(chain_t));
    chain->head = NULL;
    //node_t *node_header = chain->head;

    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("%s\n", ERR_7);
        chain = NULL;
        return chain;
    }
    // char buffer[MAX_INPUT_SIZE];
    // int readbytes = read(fd, buffer, MAX_INPUT_SIZE);
    // //printf("readbytes = %d\n", readbytes);
    // buffer[strlen(buffer) - 1] = '\0';
    // printf("%s strlen buffer = %ld\n", buffer, strlen(buffer));
    // for(int i = 0; i <= readbytes; i++)
    // {
    //     if(i == 0 || (buffer[i - 2] == '\n'))
    //     {
    //         char s = buffer[i];
    //         //printf("s = %d\n", s);
    //         int node = s - 48;
    //         chain->head = append_node(chain->head, node);
    //     }
    //     else if((buffer[i - 1] == ':') || (buffer[i - 1] == ','))
    //     {
    //         char *block_id_convert = NULL;
    //         int k = 0, j = i + 1;
    //         while(buffer[j] != ',' || buffer[j] != '\n')
    //         {
    //             block_id_convert[k] = buffer[j];
    //             k++;
    //             j++;
    //         }
    //         append_block(chain->head->block_head, block_id_convert);
    //         //chain->head->block_head = chain->head->block_head->next;
    //     }
    // }
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
    readBytes = read(0, buff, MAX_INPUT_SIZE - 1);
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

    // USE SWITCH CASE?
    // We should also add some security in here incase wrong number of arguments

    // go through string arr, fill command struct according to input
    for (int i = 0; i < input_arr->size - 1; i++)                       
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

        if (input_arr->size > 3 && my_strcmp("node", input_arr->array[1]) == 0 && (my_strcmp("add", input_arr->array[0])) == 0)
            command->cmd_node_id = my_atoi(input_arr->array[2]);
        if (input_arr->size > 3 && my_strcmp("node", input_arr->array[1]) == 0 && (my_strcmp("rm", input_arr->array[0])) == 0)
            command->cmd_node_id = my_atoi(input_arr->array[2]);
        if (input_arr->size > 3 && my_strcmp("block", input_arr->array[1]) == 0 && (my_strcmp("add", input_arr->array[0])) == 0)
        {
            command->cmd_block_id = malloc(sizeof(char) * my_strlen(input_arr->array[2]) + 1);
            command->cmd_block_id = input_arr->array[2];
            command->cmd_node_id = my_atoi(input_arr->array[3]);
        }
        if (input_arr->size > 2 && my_strcmp("block", input_arr->array[1]) == 0 && (my_strcmp("rm", input_arr->array[0])) == 0)
        {
            command->cmd_block_id = malloc(sizeof(char) * my_strlen(input_arr->array[2]) + 1);
            command->cmd_block_id = input_arr->array[2];
        }
        if (input_arr->size > 4 && my_strcmp("*", input_arr->array[3]) == 0)
            command->all = true;
        if (input_arr->size > 3 && my_strcmp("*", input_arr->array[2]) == 0)
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

// create a save file

void save_blockchain(chain_t *chain)
{
    int fd = open("blockchain", O_WRONLY | O_CREAT, 0644);
    node_t *current_node = chain->head;
    while(current_node != NULL)
    {
        //printf("Current node id = %d\n", current_node->nId);
        block_t *current_block = current_node->block_head;
        char* node_id = my_itoa(current_node->nId);
        if(current_node->nId && (current_node->next != NULL))
        {
            //printf("first if, 172\n");
            write(fd, node_id, strlen(node_id));
            write(fd, ":", 1);
        }
        else if(current_node->next == NULL && (current_block->bId == NULL))
        {
            //printf("178, node id = %d, bid = NULL\n", current_node->nId);
            write(fd, node_id, strlen(node_id));
            write(fd, "\0", 1);
            break;
        }
        else if(current_node->next == NULL && (current_block->bId != NULL))
        {
            write(fd, node_id, strlen(node_id));
            write(fd, ":", 1);
        }
        while(current_block != NULL)
        {
            //printf("block id = %s\n", current_block->bId);
            if(current_block->bId && (current_block->next != NULL))
            {
                //printf("188 bid present, next != NULL");
                write(fd, current_block->bId, strlen(current_block->bId));
                write(fd, ",", 1);
            }
            else if(current_block->next == NULL)
            {
                //printf("next block = NULL\n");
                write(fd, current_block->bId, strlen(current_block->bId));
                write(fd, "\n", 1);
            }
            current_block = current_block->next;
        }
       current_node = current_node->next;
    }
    close(fd);
}