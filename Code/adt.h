#ifndef ADT_H
#define ADT_H

struct hash_node {
    // pointer to the element
    void *elem;
    /* if there is a hash collision
     * collided hash nodes are chained into a doubly linked list
     */
    struct hash_node *prev, *next;
};

struct hash_table {
    // size of the hash table(number of slots)
    int size;
    struct hash_node **nodes;
    // user must specify how to hash their elements
    int (*hash_func)(void *elem);
    int (*compare)(void * elem_1, void *elem_2);
};

/* 
 * hash_func:
 *   hash an element to a non-negative integer
 * compare function:
 *   returns 0 if elem_1 == elem_2
 *   returns nonzero if elem_1 != elem_2
 */
struct hash_table *create_hash_table(int size, int (*hash_func)(void *elem), 
    int (*compare)(void * elem_1, void *elem_2));
struct hash_node *hash_table_insert(struct hash_table *t, void *elem);
void hash_table_delete(struct hash_table *t, struct hash_node *node);
void *hash_table_search(struct hash_table *t, void *elem);
void destroy_hash_table(struct hash_table *t);

/*
 * do not name it stack
 * it will collide with STL stack
 */
struct cstack {
    int size;
    int top;
    void **buffer;
};
struct cstack *create_cstack(int size);
void destory_cstack(struct cstack *s);
int cstack_is_empty(struct cstack *s);
int cstack_is_full(struct cstack *s);
void cstack_push(struct cstack *s, void *elem);
void *cstack_pop(struct cstack *s);
void cstack_clear(struct cstack *s);
#endif
