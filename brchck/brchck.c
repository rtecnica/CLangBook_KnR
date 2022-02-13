/* Page 34 
 * Exercise 1-24
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "br_stack.h"

typedef enum state {
    open,
    close,
    non,
    mism,
} state;


int check_bracket(shead_t *stack, bracket_t br) {
    if(stack->head == NULL) {
        return 1;
    } else if(stack->head->br != br){
        return 1;
    }
    return 0;
}


int main(int argc, char **argv) {
    
    struct shead bracket_stack = stack_init();
    
    int line = 1;
    int col = 0;

    FILE *input;
    if(argc > 1) {
        input = fopen(argv[1], "r");
    } else {
        return 1;
    }

    int escape_flag = 1;
    int out_squote = 0;
    int out_dquote = 0;
    int is_comment = 0;

    char c = 'F';
    char lc = c;    
    while(c != EOF) { 
        lc = c; 
        c = getc(input);
        col++; 
       
        // calculate state??
        // 
        out_dquote = check_bracket(&bracket_stack, dquote); 
        out_squote = check_bracket(&bracket_stack, squote);

        switch(c) {
            case '/':
                if(escape_flag && out_dquote && out_squote && lc == c) {
                    push(&bracket_stack, fslash, line, col);
                    is_comment = !check_bracket(&bracket_stack, fslash);
                }
                break;

            case '(':
                if(escape_flag && out_dquote && out_squote && !is_comment) {
                    push(&bracket_stack, paren, line, col);
                }
                break;

            case ')':
                if(escape_flag && out_dquote && out_squote && !is_comment) {
                    if(check_bracket(&bracket_stack, paren)) {
                        printf("Unbalanced parenthesis ln:%d col:%d\n", line, col);
                        return 1;
                    } else {
                        pop(&bracket_stack);
                    }
                }
                break;

            case '{':
                if(escape_flag && out_dquote && out_squote && !is_comment) {
                    push(&bracket_stack, curly, line, col);
                }
                break;
        
            case '}':
                if(escape_flag && out_dquote && out_squote && !is_comment) {
                    if(check_bracket(&bracket_stack, curly)) {
                        printf("Unbalanced curly braces ln:%d col:%d\n", line, col);
                        return 1;
                    } else {
                        pop(&bracket_stack);
                    }
                } 
                break;

            case '[':
                if(escape_flag && out_dquote && out_squote && !is_comment) {
                    push(&bracket_stack, brack, line, col);
                }
                break;

            case ']':
                if(escape_flag && out_dquote && out_squote && !is_comment) {
                    if(check_bracket(&bracket_stack, brack)) {
                        printf("Unbalanced square braces ln:%d col:%d\n", line, col);
                        return 1;
                    } else {
                        pop(&bracket_stack);
                    }
                }
                break;

            case '\"':
                if(escape_flag && out_squote && out_dquote && !is_comment) {
                    push(&bracket_stack, dquote, line, col);
                } else if(!out_dquote) {
                    pop(&bracket_stack);
                }
                break;

            case '\'':
                if(escape_flag && out_dquote && out_squote && !is_comment) {
                    push(&bracket_stack, squote, line, col);
                } else if(!out_squote) {
                    pop(&bracket_stack);
                }
                break;

            case '\\':
                if(escape_flag && !is_comment) {
                    push(&bracket_stack, bslash, line, col);
                    escape_flag = 0;
                    continue;
                }
                break;


            case '\n':
                if(!out_dquote || !out_squote) {
                    printf("Unbalanced quote ln:%d col:%d\n", bracket_stack.head->ln, bracket_stack.head->col);
                    return 1;
                } else if(is_comment) {
                    pop(&bracket_stack);
                    is_comment = !check_bracket(&bracket_stack, fslash);
                }
                col = 0;
                line++;
                break;

            default:
                break;
        };
       
        if(!escape_flag) { 
            escape_flag = 1;
            if(!check_bracket(&bracket_stack, bslash)){
                pop(&bracket_stack);
            } else {
                printf("Something's wrong\n");
            }
        }   
    }
    if(bracket_stack.height > 0) {
        printf("Unbalanced bracket ln:%d col:%d\n", bracket_stack.head->ln, bracket_stack.head->col);
        return 1;
    }
    printf("A OK!!"); 
    return 0;
}
