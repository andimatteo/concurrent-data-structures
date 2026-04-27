#include "lib.h"

#define NTHREADS 12
#define N 10000000

typedef struct {
    double *x;
    double *y;
    size_t n;
    double acc;
} thread_data_t;

int main() {
    sys_check(0);
    return 0;
}
