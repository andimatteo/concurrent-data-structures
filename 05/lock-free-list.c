#include "lib.h"


/*
 * we want to see how to implement lock-free list operations with
 * insert and extract operations
 *
 * each primitive passes the node to insert or extract
 *
 * insert and extract on the same side (back or front)
 * or different sides:
 *  - insert in front and extract in the back will
 *  make a queue
 *  - insert in front and extract in frotn wil
 *  make a stack
 *
 * atomic built-ins get compiled to
 * lock load store lock in x86-64
 *
 * the ABA problem on extraction:
 *  - the typical solution is adding a
 *  versioning or marking on the pointers
 *
 * remove the use of malloc, the problem
 * is that another thread could free on head
 *
 * always exchange solution making the whole list private for the moment,
 * then when I put back the list.
 * This means I always exchange without testing.
 * */


struct node {
    int val;
    _Atomic struct node * next;
} node;

_Atomic struct node * list = NULL;

bool atomic_insert(int val) {

    // create new node
    _Atomic struct node * p = (_Atomic struct node*)malloc(sizeof node);
    
    bool insert = false;

    while (!insert) {
        // take val of list
        p->next = list;

        // try to assign
        insert = atomic_compare_exchange_weak(&list,&p->next,p);
    }

    return insert;
}

bool atomic_extract(int * ret) {
    bool extract = false;

    _Atomic struct node * p;

    while (!extract) {
        p = list;
        atomic_compare_exchange_weak(&list,&p, p->next);
    }

    *ret = p->val;
    free(p);
}

void * pthread_body(void * args) {
    for (int i = 0; i < 5; i++) {
        atomic_insert(0);
    }

    // for (int i = 0; i < 2; i++) {
    //     int ret = 1;
    //     atomic_extract(&ret);
    // }
}

int main() {

    pthread_t t[10];
    for (int i = 0; i < 10; i++) {
        pthread_create(&t[i], NULL, pthread_body, NULL);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(t[i],NULL);
    }

    // check correct number of elements in list
    int n = 0;
    int expected = 10 * 5 - 10 * 2;
    _Atomic struct node * p = list;

    while (p) {
        n++;
        p = p->next;
    }

    printf("%d\n",n);

    // sys_check(expected == n ? 0 : 1);

    return 0;
}









