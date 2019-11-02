#ifndef LIST_H_INCLUDED_
#define LIST_H_INCLUDED_ 

#include "entities.h"

struct _node {
    ball *b;

    struct _node *next;
    struct _node *prev;
};
typedef struct _node node;

struct _list {
    node *head;
    node *tail;

    int size;
};
typedef struct _list list;

node* node_create(ball *b);

list* list_create();
void list_insertBack(list *l, ball *b);
void list_remove(list *l, ball *b);
node* list_find(list *l, ball *b);
void list_free(list *l);
void list_concatenate(list *l1, list *l2);

#endif /* LIST_H_INCLUDED_ */
