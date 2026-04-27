#include "lib.h"

#define NTHREADS 2
#define N 100000000


void * thread_body(void * args) {

    thread_doubles_t * t = (thread_doubles_t*)args;

    for (int i = 0; i < t->n; i++) {
        t->z[i] = t->x[i] + t->y[i];
    }

    // free mem
    free((void*)args);
    return NULL;
}


void * alternating_thread_body(void * args) {

    thread_doubles_t * t = (thread_doubles_t*)args;

    // compute sum
    for (int i = 0; i < t->n; i += 2) {
        t->z[i] = t->x[i] + t->y[i];
    }


    // free mem
    free((void*)args);
    return NULL;
}

int main(int argc, char * argv[]) {

    pthread_t threads[NTHREADS];

    double *x = malloc(N * sizeof(double));
    double *y = malloc(N * sizeof(double));
    double *z = malloc(N * sizeof(double));
    for (int i = 0; i < N; i++) {
        x[i] = i;
        y[i] = i * 2;
    }

    int hm = N / NTHREADS;
    int remainder = N % NTHREADS;
    int n = 0;

    struct timespec t0;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    // array split in two
    for (int i = 0; i < NTHREADS; i++) {
        thread_doubles_t * t = (thread_doubles_t*)
            malloc(sizeof(thread_doubles_t));
        t->x = (x + i * hm);
        t->y = (y + i * hm);
        t->n = hm + (remainder > 0);
        t->z = (z + i * hm);
        sys_check(pthread_create(&threads[n], NULL, thread_body, (void*)t));
        remainder--;
        n++;
    }

    // wait for completion
    for (int i = 0; i < NTHREADS; i++)
        pthread_join(threads[i],NULL);

    struct timespec t1;
    clock_gettime(CLOCK_MONOTONIC, &t1);

    // print first time
    printf("split in two halves: %.3fms\n", MS(t1) - MS(t0));

    // even and odd
    thread_doubles_t * thread_data_1 = (thread_doubles_t*)
        malloc(sizeof(thread_doubles_t));
    thread_doubles_t * thread_data_2 = (thread_doubles_t*)
        malloc(sizeof(thread_doubles_t));
    thread_data_1->n = N;
    thread_data_2->n = N - 1;
    thread_data_1->x = x;
    thread_data_1->y = y;
    thread_data_1->z = z;
    thread_data_1->n = N;

    thread_data_2->x = x + 1;
    thread_data_2->y = y + 1;
    thread_data_2->z = z + 1;
    thread_data_2->n = N - 1;
    clock_gettime(CLOCK_MONOTONIC, &t0);

    sys_check(pthread_create(&threads[0], NULL, alternating_thread_body, (void*)thread_data_1));
    sys_check(pthread_create(&threads[1], NULL, alternating_thread_body, (void*)thread_data_2));

    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);

    clock_gettime(CLOCK_MONOTONIC, &t1);

    // print second time
    printf("even-odd: %.3fms\n", MS(t1) - MS(t0));

    free(x);
    free(z);
    free(y);
    return 0;
}
