#ifndef

typedef struct block_s {
    char *bId;
    block_s *next;
} block_t;

typedef struct node_s {
    block_t *head;
    int nId;
    node_s *next;
} node_t;

<<<<<<< HEAD
#endif
=======
#define ERR_1 "no more resources available on the computer"
#define ERR_2 "this node already exists"
>>>>>>> 3c0de1ebe3f52c979141f0bb5f28ea88b2636189


