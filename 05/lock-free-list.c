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

int main() {
    return 0;
}
