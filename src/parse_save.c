#include "parse_save.h"

static chain_t *fill_chain(chain_t *chain, char *line);

chain_t *open_chain(char *filename)
{
    chain_t *chain = malloc(sizeof(chain_t));
    chain->head = NULL;
    chain->nodes = 0;
    chain->synced = true;

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
        debug("%s", line);
        // convert line to chain info
        chain = fill_chain(chain, line);
        free(line);
    }

    close(fd);
    return chain;
}

static chain_t *fill_chain(chain_t *chain, char *line)
{
    // check if there are blocks in current node/line & count chars of node_str
    bool node_written = false;
    bool block_present = false;
    int node_str_size = 0; // for malloc
    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == ':')
            block_present = true;
        else
            node_str_size++;
    }

    int j = 0;
    char *node_str = malloc(sizeof(char) * node_str_size + 1);
    for (int i = 0; line[i] != '\0'; i++)
    {
        debug("line i: %c", line[i]);
        // set synced field
        if (i == 0 && line[i] == 's')
        {
            chain->synced = true;
            return chain;
        }
        if (i == 0 && line[i] == '-')
        {
            chain->synced = false;
            return chain;
        }
        // write node if not yet done
        if (node_written == false)
        {
            // find & convert node value to int, append node to chain
            while (line[i] != ':' && line[i] != '\n' && line[i] != '\0')
            {
                node_str[j] = line[i];
                i++;
                j++;
            }
            node_str[j] = '\0';
            // debug("node: %s", node_str);

            int node = my_atoi(node_str); // convert char to int
            debug("%d", node);
            chain->head = append_node(chain->head, node);
            chain->nodes += 1;
            node_written = true;

            if (line[i] == '\0' || line[i] == '\n')
                return chain;
            
            i++; // because i was still on the ':' if we get here
        }
        debug("line i: %c", line[i]);
        // write blocks
        if (block_present == true)
        {
            // count chars of block id for malloc
            int block_id_len = 0;
            for (int j = i; line[j] != ',' && line[j] != '\n' && line[j] != '\0'; j++)
                block_id_len++;
            debug("len: %d", block_id_len);
            char *block_id = malloc(sizeof(char) * block_id_len + 1);
            
            // copy block id & append block
            int k = 0;
            while (line[i] != ',' && line[i] != '\n' && line[i] != '\0')
            {
                block_id[k] = line[i];
                i++;
                k++;
            }
            block_id[k] = '\0';
            
            chain->head->block_head = append_block(chain->head->block_head, block_id);
        }
    }
    free(node_str);
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

// // create a save file
// void save_blockchain(chain_t *chain)
// {
//     // open file
//     int fd = open("blockchain", O_WRONLY | O_CREAT, 0644);

//     // synced or not?
//     if (chain->synced == true)
//         write(fd, "s", 1);
//     else
//         write(fd, "-", 1);
//     write(fd, "\n", 1);

//     // move through chain and write info to file
//     node_t *current_node = chain->head;
//     while (current_node != NULL)
//     {
//         // write node id of current node
//         block_t *current_block = current_node->block_head;
//         char *node_id = my_itoa(current_node->nId);
//         // 
//         if (current_node->nId && (current_node->next != NULL) && current_node->block_head != NULL)
//         {
//             write(fd, node_id, my_strlen(node_id));
//             write(fd, ":", 1);
//         }
//         else if (current_node->next == NULL && current_block != NULL)
//         {
//             write(fd, node_id, my_strlen(node_id));
//             write(fd, ":", 1);
//         }
//         else if (current_node->next == NULL && current_node->block_head == NULL) // removed the bid check as was causing segfault
//         {
//             write(fd, node_id, my_strlen(node_id));
//             write(fd, "\0", 1);
//             break;
//         }
//         else if (current_node)
//         // write blocks for each node
//         while (current_block != NULL)
//         {
//             if (current_block->bId && (current_block->next != NULL))
//             {
//                 write(fd, current_block->bId, my_strlen(current_block->bId));
//                 write(fd, ",", 1);
//             }
//             else if (current_block->next == NULL)
//             {
//                 write(fd, current_block->bId, my_strlen(current_block->bId));
//                 write(fd, "\n", 1);
//             }
//             current_block = current_block->next;
//         }
//         current_node = current_node->next;
//     }
//     close(fd);
// }

void save_blockchain(chain_t *chain)
{
    int fd = open("blockchain", O_WRONLY | O_CREAT, 0644);     // open file

    if (chain->synced == true)  // synced or not?
        write(fd, "s", 1);
    else
        write(fd, "-", 1);
    write(fd, "\n", 1);

    node_t *current_node = chain->head;
    while (current_node != NULL)  // move through chain and write info to file
    {
        block_t *current_block = current_node->block_head;
        char *node_id = my_itoa(current_node->nId);
        if (current_node->nId) 
        {
            write(fd, node_id, my_strlen(node_id)); // write node id of current node
            if (current_node->block_head != NULL) // if blockhead is present write : in order to write blocklist after, otherwise write \n
                write(fd, ":", 1);
            else
                write(fd, "\n", 1);
        }    
        while (current_block != NULL)
        {
            if (current_block->bId)
            {
                write(fd, current_block->bId, my_strlen(current_block->bId)); // write blocks for each node
                if(current_block->next != NULL) // if there is a next block write , to seperate the blocklist id, otherwise write \n
                    write(fd, ",", 1);
                else
                    write(fd, "\n", 1);
            }
            current_block = current_block->next;
        }
        current_node = current_node->next;
    }
    close(fd);
}