/* Page 34 
 * Exercise 1-24
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "br_stack.h"

int check_bracket(shead_t *stack, bracket_t br) {
    struct snode popped;
    if(stack->head == NULL) {
        return 1;
    } else if(stack->head->br != br){
        return 1;
    }
    popped = pop(stack);
    push(stack, popped.br, popped.ln, popped.col); 
    return 0;
}


int main(int argc, char **argv) {
    
    struct shead bracket_stack = stack_init();
    
    int line = 1;
    int col = 1;
    int mismatch = 0;


    FILE *input;
    if(argc > 1) {
        input = fopen(argv[1], "r");
    } else {
        return 1;
    } 
    
    char c = getc(input);
    while(c != EOF) { 
        switch(c) {
            case '(':
                mismatch = -1;
                push(&bracket_stack, paren, line, col);
                break;

            case ')':
                mismatch = check_bracket(&bracket_stack, paren); 
                break;

            case '{':
                mismatch = -1;
                push(&bracket_stack, curly, line, col);
                break;

            case '}':
                mismatch = check_bracket(&bracket_stack, curly); 
                break;

            case '[':
                mismatch = -1;
                push(&bracket_stack, brack, line, col);
                break;

            case ']':
                mismatch = check_bracket(&bracket_stack, brack); 
                break;

            case '\"':
                break;

            case '\'':
                break;

            case '\\':
                break;

            case '\n':
                col = 0;
                line++;
                break;
        };
        switch(mismatch) {
            case -1:
                break;
            case 0:
                pop(&bracket_stack);
                break;
            case 1:
                printf("Unbalanced bracket!\nline:%d col:%d\n", line, col);
                return 1;
                break;
        };

        c = getc(input);
        col++; 
    }
    printf("A OK!!");
    return 0;
}
