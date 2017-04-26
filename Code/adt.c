#include "csapp.h"
#include "adt.h"

/* 
 * hash_func:
 *   hash an element to a non-negative integer
 * compare function:
 *   returns 0 if elem_1 == elem_2
 *   returns nonzero if elem_1 != elem_2
 */
struct hash_table *create_hash_table(int size, int (*hash_func)(void *elem), 
        int (*compare)(void * elem_1, void *elem_2)) {
    struct hash_table *t = (struct hash_table *)Malloc(sizeof(struct hash_table));
    t->size = size;
    t->nodes = (struct hash_node **)Calloc(size, sizeof(struct hash_node *));
    t->hash_func = hash_func;
    t->compare = compare;
    return t;
}

struct hash_node *hash_table_insert(struct hash_table *t, void *elem) {
    int hash_val = t->hash_func(elem);
    int slot = hash_val % t->size;
    // insert the node at the beginning of the list
    struct hash_node *curr = (struct hash_node *)Calloc(1, sizeof(struct hash_node));
    curr->elem = elem;
    curr->next = t->nodes[slot];
    t->nodes[slot] = curr;
    if(curr->next)
        curr->next->prev = curr;
    return curr;
}

void hash_table_delete(struct hash_table *t, struct hash_node *node) {
    if(node->prev)
        node->prev->next = node->next;
    if(node->next)
        node->next->prev = node->prev;
}

void *hash_table_search(struct hash_table *t, void *elem) {
    int hash_val = t->hash_func(elem);
    int slot = hash_val % t->size;
    struct hash_node *curr = t->nodes[slot];
    while(curr)
        if(!t->compare(curr->elem, elem))
            return curr->elem;
        else
            curr = curr->next;
    return NULL;
}

void destroy_hash_table(struct hash_table *t) {
    for(int i = 0; i < t->size; i++) {
        struct hash_node *curr = t->nodes[i];
        while(curr) {
            curr = curr->next;
            Free(curr);
        }
    }
    Free(t->nodes);
    Free(t);
}

struct cstack *create_cstack(int size) {
    struct cstack *s = (struct cstack *)Malloc(sizeof(struct cstack));
    s->size = size;
    s->top = -1;
    s->buffer = (void **)Calloc(size, sizeof(void *));
    return s;
}

void destory_cstack(struct cstack *s) {
    Free(s->buffer);
    Free(s);
}

int cstack_is_empty(struct cstack *s) {
    return (s->top == -1);
}

int cstack_is_full(struct cstack *s) {
    return (s->top == s->size - 1);
}

void cstack_push(struct cstack *s, void *elem) {
    if(s->top < s->size - 1)
        s->buffer[++(s->top)] = elem;
    else
        app_error("cstack overflowed");
}

void *cstack_pop(struct cstack *s) {
    if(s->top == -1) {
        app_error("cstack underflowed");
        return NULL;
    }
    return s->buffer[s->top--];
}

void cstack_clear(struct cstack *s) {
    s->top = -1;
}
