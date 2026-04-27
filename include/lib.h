#ifndef _LIB_H
#define _LIB_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdatomic.h>

#define sys_check(cond)                                                      \
do {                                                                         \
    if ((cond) != 0) {                                                       \
        perror(#cond);                                                       \
        exit(1);                                                             \
    }                                                                        \
} while (0)

#endif
