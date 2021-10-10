/* Page 143
 * Exercise 6-3
 *
 *
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "include/llist.h"
#include "include/word_parse.h"

int main(int argc, char **argv) {

    FILE *input;
    if(argc > 1) {
        input = fopen(argv[1], "r");
    } else {
        return 1;
    }
    
    struct llist *list = llist_init();

    for(int i = 0; i < 10; i++) {
        int *p = malloc(sizeof(int));
        *p = i;
        llist_push(list, p);
    }

    llist_deinit(list);
    return 0;
    
}
