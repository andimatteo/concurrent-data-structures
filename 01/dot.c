#include "lib.h"

#define NTHREADS 8
#define N 100000

pthread_mutex_t m;

void * thread_body(void * args) {

    thread_doubles_t * t = (thread_doubles_t*)args;

    // compute dot product
    for (int i = 0; i < t->n; i++) {
        t->acc += *(t->x++) * *(t->y++);
    }

    // take mutual exclusion on acc
    sys_check(pthread_mutex_lock(&m));
    *t->z += t->acc;
    sys_check(pthread_mutex_unlock(&m));

    // free mem
    free((void*)args);
    return NULL;
}

int main(int argc, char * argv[]) {

    pthread_mutex_init(&m,NULL);

    pthread_t threads[NTHREADS];

    double x[N];
    double y[N];
    double z;

    int hm = N / NTHREADS;
    int remainder = N % NTHREADS;
    int n = 0;

    struct timespec t0;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    for (int i = 0; i < NTHREADS; i++) {
        thread_doubles_t * t = (thread_doubles_t*)
            malloc(sizeof(thread_doubles_t));
        t->acc = 0;
        t->x = (x + i * hm);
        t->y = (y + i * hm);
        t->n = hm + (remainder > 0);
        t->z = &z;
        sys_check(pthread_create(&threads[n], NULL, thread_body, (void*)t));
        remainder--;
        n++;
    }

    // wait for completion
    for (int i = 0; i < NTHREADS; i++)
        pthread_join(threads[i],NULL);

    struct timespec t1;
    clock_gettime(CLOCK_MONOTONIC, &t1);

    printf("%.3fms\n", MS(t1) - MS(t0));

    sys_check(0);
    return 0;
}
