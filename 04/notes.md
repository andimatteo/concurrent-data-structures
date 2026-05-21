todo: transactional memory read something about it

ring buffer + transactional memory

some other pointers on these topics:

1. 
```C
#include <pthread.h>

int pthread_condattr_getpshared(const pthread_condattr_t *attr,
    int *pshared);
int pthread_condattr_setpshared(pthread_condattr_t *attr,
    int pshared);
```

2. fast mutex (futex), Inter Processor Interrupt (IPI)

3. un processo riparte piu' velocemente quando il processo era idle o
c'era altro in esecuzione? dipende dal deep-idle state, il kernel potrebbe
aver ridotto il clock della CPU quindi in realta' prende ms dal deep-idle specifico.

4. l'alternativa migliore e' quella di evitare di commutare del tutto, quindi
fare spinlock. Spinlock prende il tempo di una cache miss in L1, ordini e ordini 
di grandezza inferiore rispetto a risvegliare un processo in deep-idle state
