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

void llist_insert(struct llist *list, void* item, llside side);

void llist_sort(struct llist *list, int (*compare_fn)(void *item1, void *item2));

void llist_free(struct llist *list);

#endif //LLIST_H
