#include "lib.h"

#define NUM_THREADS 10
#define N 20

pthread_cond_t empty;
pthread_cond_t full;
pthread_mutex_t m;

int h = 0;
int t = 0;
int size = 0;
int A[N];

static inline int next(int val) {
    return (val + 1) % N;
}

int insert(int val) {
    
    pthread_mutex_lock(&m);

    // wait for the buffer not to be full
    while (size == N)
        pthread_cond_wait(&full,&m);

    // do the insert
    A[h] = val;
    h = next(h);
    size++;

    pthread_mutex_unlock(&m);

    /*
     * I am doing signal after releasing lock
     * otherwise I think that process can get
     * preempted and he would try to acquire
     * lock on m but it's blocked on this actual
     * process
     *
     * the same also goes on the extract.
     * */
    pthread_cond_signal(&empty);

    return 0;
}

int extract() {
    
    pthread_mutex_lock(&m);
    
    while (size == 0)
        pthread_cond_wait(&empty, &m);

    // extract
    int ret = A[t];
    t = next(t);
    size--;

    pthread_mutex_unlock(&m);

    pthread_cond_signal(&full);

    return ret;
}

void * thread_body(void * args) {
    
    for (int i = 0; i < 10; i++)
        insert(i + 1);

    for (int i = 0; i < 10; i++)
        extract();

    return NULL;
}

int init() {
    pthread_cond_init(&empty,NULL);
    pthread_cond_init(&full,NULL);
    pthread_mutex_init(&m,NULL);
    return 0;
}

int main() {
    init();

    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i],NULL,thread_body,NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i],NULL);
    }

    // check on correct size
    printf("%d\n",size);

    return 0;
}
