/*
 *
 *
 *
 *
 *
 */

#ifndef WORD_PARSE_H
#define WORD_PARSE_H

#include <string.h>
#include <inttypes.h>
#include "llist.h"

#define MAX_WORD_LEN 256

typedef struct word_t {
    char word[MAX_WORD_LEN];
    uint16_t count;
    struct llist pages;
} word_t;

int compare_word_alph(void *item1, void *item2);

int compare_word_count(void *item1, void *item2);

struct word_t create_word(char *word);

void word_add_page(struct word_t *word, int page);

void deinit_word(struct word_t *word);

void print_word(struct word_t *word);
#endif //WORD_PARSE_H
