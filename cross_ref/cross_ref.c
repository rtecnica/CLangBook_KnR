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

#define IN_WORD 1
#define OUT_WORD 0

#define UC_LO 65
#define UC_HI 90
#define LC_LO 97
#define LC_HI 122
#define ALPH_L 25
#define NUM_LO 48
#define NUM_HI 57

void check_if_word_is_new_and_update(struct llist *list, char *word, int line) {
    struct word_t *new_word = malloc(sizeof(word_t));
    *new_word = create_word(word);
    struct word_t *old_word = (struct word_t *)llist_select(list, new_word, &compare_word_alph);
            
    struct word_t *new_or_old_wd;
    if(old_word != NULL) {
        new_or_old_wd = ((struct word_t *)(old_word));
        free(new_word);
    } else {
        new_or_old_wd = new_word;
        llist_push(list, new_or_old_wd);
    }     
    word_add_page(new_or_old_wd, line);
    (new_or_old_wd->count++);
    return;
}

int main(int argc, char **argv) {

    FILE *input;
    if(argc > 1) {
        input = fopen(argv[1], "r");
    } else {
        return 1;
    }
    struct llist list = llist_init();
    int line = 1;
    uint8_t word_state = OUT_WORD;
    char word_contents[MAX_WORD_LEN];
    int i = 0;
    char cursor = 'c';
    while(cursor != EOF) {
        cursor = getc(input);
        if((cursor >= UC_LO) && (cursor <= UC_HI)){
            if(!word_state) {
                word_state = IN_WORD;
            }
            word_contents[i] = cursor;
            i++;
        } 
        else if((cursor >= LC_LO) && (cursor <= LC_HI)) {
            if(!word_state) {
                word_state = IN_WORD;
            }
            word_contents[i] = cursor;
            i++; 
        } 
        else if((cursor >= NUM_LO) && (cursor <= NUM_HI)) {
            // add word to list
            if(word_state){
                word_state = OUT_WORD;
                word_contents[i] = '\0';
                i = 0;
                check_if_word_is_new_and_update(&list, word_contents, line); 
            }
        }
        else if(cursor == '\n'){
            line++;
            printf("\rln:%d", line);
            fflush(stdout);

            if(word_state){
                word_state = OUT_WORD;
                word_contents[i] = '\0';
                i = 0;
                check_if_word_is_new_and_update(&list, word_contents, line); 
            }
        }
        else {
            //add word to bucket
            if(word_state){
                word_state = OUT_WORD;
                word_contents[i] = '\0';
                i = 0;
                check_if_word_is_new_and_update(&list, word_contents, line); 
            }
        } 
    }
    printf("\r\n"); 
    llist_bubble_sort(&list, &compare_word_alph);

    struct lnode *ptr = list.head;
    while(ptr != NULL) {
        print_word((struct word_t *)ptr->item);
        ptr = ptr->next;
    }
   
    printf("word list length: %d\n", list.length);
    int page_cnt = 0;
    ptr = list.head;
    while(ptr != NULL) {
        page_cnt += ((struct word_t *)ptr->item)->pages.length;
        llist_deinit(((struct word_t *)ptr->item)->pages);
        ptr = ptr->next;
    }
    printf("\n");
    printf("page count: %d\n", page_cnt);
    llist_deinit(list);
    printf("\n");
    return 0;
    
}
