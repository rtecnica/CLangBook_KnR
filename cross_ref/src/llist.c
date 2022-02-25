/*
 *
 *
 *
 *
 *
 */

#include "../include/llist.h"
#include <stdio.h>
#include <stdlib.h>

struct llist llist_init() {
  struct llist list;
  list.length = 0;
  list.head = NULL;
  list.tail = NULL;
  return list;
}

void llist_deinit(struct llist list) {
  void *ptr = llist_pop(&list, head);
  while (ptr != NULL) {
    free(ptr);
    ptr = llist_pop(&list, head);
  }

  if (list.head == NULL && list.tail == NULL) {
    return;
  } else {
    printf("Something went wrong!");
  }
}

void llist_push(struct llist *list, void *item) {
  struct lnode *new = malloc(sizeof(lnode));
  new->item = item;
  new->next = NULL;

  if (list->length > 0) {
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

  if (list->length < 1) {
    return NULL;
  } else {
    switch (side) {
    case head:
      old = list->head;
      list->head = old->next;
      break;

    case tail:
      old = list->tail;
      struct lnode *new_tail = list->head;
      while (new_tail->next != old && new_tail->next != NULL) {
        new_tail = new_tail->next;
      }
      list->tail = new_tail;
      break;
    }
  }

  list->length--;
  item = old->item;

  if (list->head == NULL || list->tail == NULL) {
    list->head = NULL;
    list->tail = NULL;
  }

  if (old != NULL) {
    free(old);
  }

  return item;
}

void *llist_select(struct llist *list, void *item,
                   int (*compare_fn)(void *item1, void *item2)) {
  struct lnode *ptr = list->head;

  while (ptr != NULL) {
    if (compare_fn(ptr->item, item) == 0) {
      break;
    }
    ptr = ptr->next;
  }

  if (ptr == NULL) {
    return NULL;
  } else {
    return ptr->item;
  }
}

// PROTIP: Sort linked lists by turning them into arrays first
void llist_bubble_sort(struct llist *list,
                       int (*compare_fn)(void *item1, void *item2)) {
  struct lnode **array = malloc(sizeof(void *) * list->length);
  struct lnode *ptr = list->head;
  int i = 0;
  while (ptr != NULL) {
    array[i] = ptr;
    ptr = ptr->next;
    i++;
  }

  int swapped_this_pass = 1;
  while (swapped_this_pass) {
    swapped_this_pass = 0;
    for (int j = 0; j < list->length - 1; j++) {
      if (compare_fn(array[j]->item, array[j + 1]->item) == 1) {
        struct lnode *temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
        swapped_this_pass = 1;
      }
    }
  }

  list->head = array[0];
  ptr = list->head;
  for (int j = 1; j < list->length; j++) {
    ptr->next = array[j];
    ptr = ptr->next;
  }
  ptr->next = NULL;

  free(array);
}
