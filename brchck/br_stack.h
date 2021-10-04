typedef enum bracket {
    paren,
    curly,
    brack,
    squote,
    dqoute
} bracket_t;

typedef struct snode {
    bracket_t br;
    int ln;
    int col;
    struct snode *next;
} snode_t;

typedef struct shead {
    struct snode *head;
    int height;
} shead_t;

struct shead stack_init(void);
    
void push(struct shead *stack, bracket_t br, int line, int col);

struct snode pop(struct shead *stack);

