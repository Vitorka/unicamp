#include <stdlib.h>

#include "list.h"

node* node_create(ball *b) {
    node *new = (node*) calloc(1, sizeof(node));
    new->b = b;
    
    return new;
}

list* list_create() {
    return calloc(1, sizeof(list));
}

void list_insertBack(list *l, ball *b) {
    if (l->head == NULL) {
        l->head = node_create(b);
        l->tail = l->head;
    } else {
        l->tail->next = node_create(b);
        l->tail->next->prev = l->tail;
        l->tail = l->tail->next;
    }

    l->size++;
}

node* list_find(list *l, ball *b) {
    node *cur = l->head;

    while (cur != NULL && cur->b != b) {
        cur = cur->next;
    }

    return cur;
}

void list_remove(list *l, ball *b) {
    node *rmv = list_find(l, b);

    if (rmv == NULL) {
        return;
    }

    if (l->head == rmv || l->tail == rmv) {
        if (l->head == rmv) {
            l->head = rmv->next;

            if (l->size > 1) {
                rmv->next->prev = NULL;
            }
        }

        if (l->tail == rmv) {
            l->tail = rmv->prev;

            if (l->size > 1) {
                rmv->prev->next = NULL;
            }
        }
    } else {
        rmv->next->prev = rmv->prev;
        rmv->prev->next = rmv->next;
    }
    l->size--;

    free(rmv);
}

void list_free(list *l) {
    node *cur = l->head, *next;

    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }

    free(l);
}

void list_concatenate(list *l1, list *l2) {
    node *l2Current = l2->head;

    while (l2Current != NULL) {
        list_insertBack(l1, l2Current->b);
        l2Current = l2Current->next;
    }
}
