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

typedef struct {
    double *x;
    double *y;
    double *z;
    double acc;
    size_t n;
} thread_doubles_t;

#define MS(ts)                                                              \
    ((ts).tv_sec * 1000.0 + (ts).tv_nsec / 1000000.0)

#endif
