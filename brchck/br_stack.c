
#include <stdio.h>
#include <stdlib.h>
#include "br_stack.h"

struct shead stack_init(void) {
    struct shead new;
    new.head = NULL;
    new.height = 0;
    return new;
}

void push(struct shead *stack, bracket_t br, int line, int col) {
    struct snode *new = malloc(sizeof(snode_t));
    if(new == NULL) {
        fprintf(stderr, "No memory available! Can't push to stack!\n");
    } else {
        new->br = br;
        new->ln = line;
        new->col = col;
        new->next = stack->head;
        stack->head = new;
        ++stack->height;
    }
}

struct snode pop(struct shead *stack) {
    struct snode new;
    
    struct snode *popped = stack->head;
    if(popped == NULL) {
        new.next = NULL;
        new.br = '\0';
        new.col = -1;
        new.ln = -1;
        return new;
    }
    
    new.next = NULL;
    new.br = popped->br;
    
    stack->head = popped->next;
    --stack->height;
 
    free(popped);
    
    return new; 
}
