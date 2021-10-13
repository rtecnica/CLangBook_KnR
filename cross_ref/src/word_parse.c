/*
 *
 *
 *
 *
 *
 */

#include "../include/word_parse.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int compare_word_alph(void *item1, void *item2) {
    struct word_t *word1 = (struct word_t *) item1;
    struct word_t *word2 = (struct word_t *)item2;
    for(int i = 0; i < MAX_WORD_LEN; i++) {
        int expr = (word1->word[i] > word2->word[i]) - (word1->word[i] < word2->word[i]);
        if(word1->word[i] == '\0' || word2->word[i] == '\0') {
            return -expr; 
        }
        switch(expr) {
            case 1:
                return 1;
                break;
            case -1:
                return -1;
                break;
            default:
                break;
        }
    }
    return 0;
}

int compare_word_count(void *item1, void *item2) {
    struct word_t *word1 = (struct word_t *) item1;
    struct word_t *word2 = (struct word_t *)item2;
    return (int)((word1->count < word2->count) - (word1->count > word2->count));
}

struct word_t create_word(char *word) {
    struct word_t new;
    int i = 0;
    char c = word[i];
    while(c != '\0' || i > MAX_WORD_LEN) {
        new.word[i] = tolower(c);
        i++;
        c = word[i];
    }
    new.word[i] = '\0';
    new.count = 0;
    new.pages = llist_init();
    return new;
}

int compare_pages(void *page1, void *page2) {
    return (int)((*(int*)page1 < *(int*)page2) - (*(int*)page1 > *(int*)page2));
}

void word_add_page(struct word_t *word, int page) {
    int *p = malloc(sizeof(int));
    *p = page;
    if(llist_select(&(word->pages), p, &compare_pages) == NULL) { 
        llist_push(&(word->pages), p);
    } else {
        free(p);
    }
}

void deinit_word(struct word_t *word) {
    llist_deinit((word->pages));
}

void print_word(struct word_t *word) {
    printf("%s:\t\t", word->word);
    printf("%d\tp: ", word->count);
    struct lnode *ptr = word->pages.head;
    while(ptr != NULL) {
       printf("%d", *(int*)ptr->item);
       ptr = ptr->next;
       if(ptr != NULL) {
           printf(", ");
       } else {
           printf("\n");
           return;
       }
    }
    printf("none\n");
    return;
}

