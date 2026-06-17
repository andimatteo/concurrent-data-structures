# Concurrent Data Structures

Code of Concurrent Data Structures course @ Scuola Superiore
Sant'Anna, held by professor [@tomcucinotta](https://github.com/tomcucinotta).


## Course syllabus

This course provides an overview of the most used **concurrent data structures**
in different application areas, with a specific focus on the **scalability**
of performance achievable on **multi/many-core platforms**, with reference to
the `C` programming language. 

We will review some concepts related to **synchronization and locking mechanisms**,
from `mutexes` and `condition variables` to `futexes` to `spinlocks`, 
`atomics` and `memory barriers`, applying these primitives to the realization 
of **data structures with lock-free operations**. We will see some basic
concepts on the realization of **optimistic locking mechanisms** and those of
**transactional memory**, and how to use **software transactional memory**
mechanisms commonly available in modern compilers.

Although many of the covered topics are generally applicable to a variety of 
different programming languages and operating systems, 
during the course we will see examples in the C language 
and on the Linux operating system.

## lectures content

```
root/
    1/  # parallel execution of code & scalability with #threads
        # amdahl's and gustafson's laws
        - dot.c         # scalar product (critical sections)
        - sum.c         # vectorial sum (false sharing) (better run with nice)
    2/  # intro to concurrent data structures
        # fine grained and coarse grained locking
        # combining tree for common counter problem
        # see a bit of `perf`, for monitoring indices (context switches)
        - list.c        # coarse-grained and fine-grained locking
                        # on a simple linked list
    3/
        - ring-buffer.c # coarse-grained locking on ring buffer
        - blocking-ring-buffer.c # blocking ring buffer (coarse-grained lock)
    4/
    5/
    6/
    7/
```

## resources

Most of the code written during lectures has been written using
`man` reference
