#include "lib.h"

#define N 10
#define NUM_THREADS 10

/*
 * coarse-grained circular buffer:
 *  pointers point to first to fill (head)
 *  or first to empty (tail)
 * */
int h = 0, t = 0;
int size = 0;
int A[N];

static inline int next(int i) {
    return (i + 1) % N;
}

pthread_mutex_t m;

int insert(int val) {

    pthread_mutex_lock(&m);

    if (size == N) {
        pthread_mutex_unlock(&m);
        return -1;
    }
    A[h] = val;
    h = next(h);
    size++;

    pthread_mutex_unlock(&m);

    return 0;
}

int extract() {

    pthread_mutex_lock(&m);

    if (size == 0) {
        pthread_mutex_unlock(&m);
        return -1;
    }

    int ret = A[t];

    t = next(t);
    size--;

    pthread_mutex_unlock(&m);

    return ret;
}

void * thread_producer(void * args) {
    for (int i = 0; i < 10; i++) {
        insert(10);
    }

    return NULL;
}

void * thread_consumer(void * args) {
    for (int i = 0; i < 5; i++) {
        extract();
    }
    return NULL;
}

int main() {

    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&m,NULL);


    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_producer, NULL);
    }

    for (int i = 0 ; i < NUM_THREADS; i++) {
        pthread_join(threads[i],NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, thread_consumer, NULL);
    }

    for (int i = 0 ; i < NUM_THREADS; i++) {
        pthread_join(threads[i],NULL);
    }

    // check for correct size of array
    printf("%d\n",size);

    return 0;
}
