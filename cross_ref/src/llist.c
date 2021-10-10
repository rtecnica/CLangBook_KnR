/*
 *
 *
 *
 *
 *
 */

#include "../include/llist.h"
#include <stdlib.h>
#include <stdio.h>

struct llist *llist_init() {
    struct llist *list = malloc(sizeof(llist));
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}    

void llist_deinit(struct llist *list) {
    void *ptr = llist_pop(list, head);
    while(ptr != NULL) {
        ptr = llist_pop(list, head);
    }
    
    if(list->head == NULL && list->tail == NULL) {
        printf("Freeing empty list!\n");
    }
    free(list);
}

void llist_push(struct llist *list, void *item) {
    struct lnode *new = malloc(sizeof(lnode));
    new->item = item;
    new->next = NULL;
    
    if(list->length > 0) {
        list->tail->next = new;
        list->tail = new;
    } else {
        list->tail = new;
        list->head = new;
    }
    list->length++;
}

void *llist_pop(struct llist *list, llside side) {
    void *item;
    struct lnode *old = NULL;
    
    if(list->length < 1) {
        return NULL;
    } else {
        switch(side) {
            case head:
                old = list->head;
                list->head = old->next;
                break;
         
            case tail:
                old = list->tail;
                struct lnode *new_tail = list->head;
                while(new_tail->next != old && new_tail->next != NULL) {
                    new_tail = new_tail->next;
                }
                list->tail = new_tail;
                break;
        }
    }

    list->length--;
    item = old->item;
   
    if(list->head == NULL || list->tail == NULL) {
        list->head = NULL;
        list->tail = NULL;
    }

    if(old != NULL) {
        printf("Freed: %d\n", *(int*)old->item);
        free(old);
    }
    
    return item;
}
             

void llist_insert(struct llist *list, void* item, llside side);

void llist_sort(struct llist *list, int (*compare_fn)(void *item1, void *item2));

struct lnode *llist_search(struct llist *list, int (*compare_fn)(void *item1, void *item2), void *item);
