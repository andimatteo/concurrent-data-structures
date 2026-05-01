#include "lib.h"

struct coarse_elem {
    int val;
    struct coarse_elem * next;
};

struct fine_elem {
    pthread_mutex_t m;
    int val;
    struct fine_elem * next;
};

pthread_mutex_t coarse_m;
struct coarse_elem coarse_list;

struct fine_elem fine_list;

int add_coarse_elem(struct coarse_elem * l, int val) {
    struct coarse_elem *p = l, *q;
    
    struct coarse_elem * coarse_new = (struct coarse_elem*)
        malloc(sizeof(struct coarse_elem));
    coarse_new->val = val;
    coarse_new->next = NULL;

    pthread_mutex_lock(&coarse_m);
    while (p && p->val <= val) {
        q = p;
        p = p->next;
    }
    coarse_new->next = p;
    q->next = coarse_new;

    pthread_mutex_unlock(&coarse_m);
    return 0;
}

int add_fine_elem(struct fine_elem * l, int val) {
    struct fine_elem *p = l->next, *q = l;

    struct fine_elem * fine_new = (struct fine_elem*)
        malloc(sizeof(struct fine_elem));
    fine_new->val = val;
    pthread_mutex_init(&fine_new->m,NULL);
    fine_new->next = NULL;

    pthread_mutex_lock(&q->m);

    while (p && p->val <= val) {
        pthread_mutex_lock(&p->m);
        pthread_mutex_unlock(&q->m);
        q = p;
        p = p->next;
    }
    fine_new->next = p;
    q->next = fine_new;
    pthread_mutex_unlock(&q->m);

    return 0;
}


/*
 * to make tests comparable with a variable
 * number of threads, each thread takes
 * as input the number of inserts it should do.
 * */
void * coarse_thread(void * arg) {
    int * n = (int*)arg;

    for (int i = 0; i < *n; i++)
        sys_check(add_coarse_elem(&coarse_list,i));

    return NULL;
}

void * fine_thread(void * arg) {
    int * n = (int*)arg;

    for (int i = 0; i < *n; i++)
        sys_check(add_fine_elem(&fine_list,i));

    return NULL;
}

int init_fine_elem(struct fine_elem * p) {
    return pthread_mutex_init(&p->m,NULL);
}

int init_coarse_list() {
    return pthread_mutex_init(&coarse_m,NULL);
}

/*
 * main thread checks for total list
 * size at the end of all inserts
 *
 * this check is done after all threads apart
 * from main threads have terminated 
 * */
int check_fine_list(int size) {
    struct fine_elem * p = &fine_list;
    while (p->next) {
        p = p->next;
        size--;
    }
    return size;
}


int check_coarse_list(int size) {
    struct coarse_elem * p = &coarse_list;
    while (p->next) {
        p = p->next;
        size--;
    }
    return size;
}

int main(int argc, char * argv[]) {

    struct timespec t0, t1, t2, t3;
    clock_gettime(CLOCK_MONOTONIC,&t0);
    clock_gettime(CLOCK_MONOTONIC,&t1);
    
    int nthreads = 8;
    int totinserts = 10000;
    int n = totinserts/nthreads;

    pthread_t threads[nthreads];

    init_fine_elem(&fine_list);
    init_coarse_list();

    clock_gettime(CLOCK_MONOTONIC,&t0);
    for (int i = 0; i < nthreads; i++) {
        pthread_create(&threads[i],NULL,fine_thread,(void*)&n);
    }

    for (int i = 0; i < nthreads; i++) {
        pthread_join(threads[i],NULL);
    }
    clock_gettime(CLOCK_MONOTONIC,&t1);

    clock_gettime(CLOCK_MONOTONIC,&t2);
    for (int i = 0; i < nthreads; i++) {
        pthread_create(&threads[i],NULL,coarse_thread,(void*)&n);
    }

    for (int i = 0; i < nthreads; i++) {
        pthread_join(threads[i],NULL);
    }
    clock_gettime(CLOCK_MONOTONIC,&t3);

    sys_check(check_fine_list(totinserts));
    sys_check(check_coarse_list(totinserts));

    printf("fine: %.3f, coarse: %.3f\n",MS(t3) - MS(t2), MS(t1) - MS(t0));

    return 0;
}
