/*
 *
 *
 *
 *
 *
 */
#ifndef LLIST_H
#define LLIST_H

#include <inttypes.h>

typedef struct lnode {
    void *item;
    struct lnode *next;
} lnode;

typedef struct llist {
    struct lnode *head;
    struct lnode *tail;
    uint16_t length;
} llist;

typedef enum llside {
    head,
    tail
} llside;

struct llist *llist_init();

void llist_deinit(struct llist *list); 

void llist_push(struct llist *list, void *item);

void *llist_pop(struct llist *list, llside side);

void *llist_select(struct llist *list, void* item, int (*compare_fn)(void *item1, void *item2));

void llist_bubble_sort(struct llist *list, int (*compare_fn)(void *item1, void *item2));

void llist_quick_sort(struct llist *list, int (*compare_fn)(void *item1, void *item2));


void llist_free(struct llist *list);

#endif //LLIST_H
