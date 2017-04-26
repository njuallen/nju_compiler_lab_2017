#include <set>
#include <vector>
#include "csapp.h"
#include "adt.h"

using std::set;
using std::vector;
using std::swap;

int hash(void *elem) {
    return *(int *)elem;
}

int compare(void * elem_1, void *elem_2) {
    return *(int *)elem_1 - *(int *)elem_2;
}

void test_hash_table() {
    // test hash_table
    int n = 100000;
    int size = 10993;
    vector<hash_node *> v;

    std::multiset<int> s;

    struct hash_table *t = create_hash_table(size, hash, compare);
    for(int i = 0; i < n; i++) {
        int *elem = new int(rand());
        struct hash_node *node = hash_table_insert(t, elem);
        s.insert(*elem);
        v.push_back(node);
    }
    for(int i = 0; i < n; i++) {
        int size = v.size();
        /* randomly choose one element
         * search for it in the hash table
         * and delete it
         */
        int target = rand() % size;
        /* move the target element to the end of the vector
         * so that it can be easily removed with vector pop_back
         */
        swap(v[target], v[size - 1]);
        void *elem = v[size - 1]->elem;
        int value = *(int *)elem;
        auto it = s.find(value);
        int *a = (int *)hash_table_search(t, elem);
        if(*a != *it)
            printf("test_hash_table: failed\n");
        s.erase(it);
        hash_table_delete(t, v[size - 1]);
        v.pop_back();
    }
    destroy_hash_table(t);
    printf("test_hash_table: passed!\n");
}

void test_push_pop(struct cstack *s, vector<int *> &v, int n, int push, int pop) {
    // push:pop = 4 : 1
    for(int j = 0; j < n; j++) {
        int *elem = new int(rand());
        // randomly push or pop
        int action = rand() % push + pop;
        if(action < push) {
            // push
            if(!cstack_is_full(s)) {
                cstack_push(s, elem);
                v.push_back(elem);
            }
        }
        else {
            // pop
            if(!cstack_is_empty(s)) {
                void *a = cstack_pop(s);
                void *b = v[v.size() - 1];
                v.pop_back();
                if(a != b)
                    printf("test_cstack: failed\n");
            }
        }
    }
}

void test_cstack() {
    int round = 100;
    int size = 109;
    vector<int *> v;

    struct cstack *s = create_cstack(size);
    for(int i = 0; i < round; i++) {
        test_push_pop(s, v, size * 10, 5, 1);
        test_push_pop(s, v, size * 10, 1, 5);
    }
    destory_cstack(s);
    printf("test_cstack: passed\n");
}

int main(void) {
    srand(time(NULL));
    test_hash_table();
    test_cstack();
    return 0;
}
