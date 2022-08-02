#include "parse_save.h"

static chain_t *fill_chain(chain_t *chain, char *line);

chain_t *open_chain(char *filename)
{
    chain_t *chain = malloc(sizeof(chain_t));
    chain->head = NULL;
    // node_t *node_header = chain->head;

    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("%s\n", ERR_7);
        chain = NULL;
        return chain;
    }

    char *line = NULL;
    while ((line = my_readline(fd)) != NULL)
    {
        printf("%s\n", line);
        // convert line to chain info
        // chain = fill_chain(chain, line);
        free(line);
    }

    /* char buffer[MAX_INPUT_SIZE];
    int readbytes = read(fd, buffer, MAX_INPUT_SIZE);
    debug("readbytes = %d", readbytes);

    buffer[readbytes] = '\0';
    debug("buff: %s", buffer); */

    close(fd);
    return chain;
}

static chain_t *fill_chain(chain_t *chain, char *line)
{
    for (int i = 0; line[i] != '\0'; i++)
    {
        if (i == 0 || (line[i - 2] == '\n'))
        {
            char s = line[i];
            printf("s = %d\n", s);
            int node = s - 48;
            debug("%d", node);
            chain->head = append_node(chain->head, node);
        }
        else if ((line[i - 1] == ':') || (line[i - 1] == ','))
        {
            char *block_id_convert = NULL;
            int k = 0, j = i + 1;
            while (line[j] != ',' || line[j] != '\n')
            {
                block_id_convert[k] = line[j];
                k++;
                j++;
            }
            append_block(chain->head->block_head, block_id_convert);
            // chain->head->block_head = chain->head->block_head->next;
        }
    }
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

command_t *parse_input(char *input) // all the functionality (append, remove, list, sync) comes in here!!
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
        if (input_arr->size > 2 && my_strcmp("block", input_arr->array[1]) == 0 && (my_strcmp("add", input_arr->array[0])) == 0)
        {
            command->cmd_block_id = malloc(sizeof(char) * my_strlen(input_arr->array[2]) + 1);
            command->cmd_block_id = input_arr->array[2];
            if (input_arr->size > 4)
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

    return prompt;
}

// create a save file
void save_blockchain(chain_t *chain)
{
    // open file
    int fd = open("blockchain", O_WRONLY | O_CREAT, 0644);

    // synced or not?
        if (chain->synced == true)
            write(fd, "s", 1);
        else
            write(fd, "-", 1);
        write(fd, "\n", 1);

    // move through chain and write info to file
    node_t *current_node = chain->head;
    while (current_node != NULL)
    {
        // write node id of current node
        block_t *current_block = current_node->block_head;
        char *node_id = my_itoa(current_node->nId);
        if (current_node->nId && (current_node->next != NULL))
        {
            write(fd, node_id, my_strlen(node_id));
            write(fd, ":", 1);
        }
        else if (current_node->next == NULL) // removed the bid check as was causing segfault
        {
            write(fd, node_id, my_strlen(node_id));
            write(fd, "\0", 1);
            break;
        }
        else if (current_node->next == NULL && (current_block->bId != NULL))
        {
            write(fd, node_id, my_strlen(node_id));
            write(fd, ":", 1);
        }
        // write blocks for each node
        while (current_block != NULL)
        {
            if (current_block->bId && (current_block->next != NULL))
            {
                write(fd, current_block->bId, my_strlen(current_block->bId));
                write(fd, ",", 1);
            }
            else if (current_block->next == NULL)
            {
                write(fd, current_block->bId, my_strlen(current_block->bId));
                write(fd, "\n", 1);
            }
            current_block = current_block->next;
        }
        current_node = current_node->next;
    }
    close(fd);
}