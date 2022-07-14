#include "blockchain.h"

node_t *append(node_t *head, int n_id) //this appends to the node struct, takes the head and node id. 
{
    if (head->nId == NULL) // if head is empty, fill and return head
    {
        head->nId = n_id;
        head->next = NULL;
        return head;
    } 
    while (head->next != NULL) // otherwise loop through list until we reach the last entry
        head = head->next;
    node_t *new = (node_t *)malloc(sizeof(node_t)); // allocate memory to a new node and fill with node id.
    new->nId = n_id;
    new->next = NULL;
    head->next = new;
    return head;
};