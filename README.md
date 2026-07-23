# Concurrent Data Structures

Code of Concurrent Data Structures course @ Scuola Superiore
Sant'Anna, held by professor [@tomcucinotta](https://github.com/tomcucinotta).


## Course syllabus

This course provides an overview of the concurrent data structures most 
commonly used across different application domains, with a specific focus 
on the performance scalability achievable on multi-core and many-core 
platforms, using the C programming language as a reference.

The course revisits concepts related to synchronization and locking 
mechanisms, ranging from mutexes and condition variables to futexes, 
spinlocks, atomic operations, and memory barriers. These primitives are 
then applied to the implementation of data structures supporting 
lock-free operations.

Basic concepts concerning optimistic locking mechanisms and transactional 
memory are introduced, together with the use of software transactional 
memory mechanisms commonly available in modern compilers.

The course also provides an overview of formal methods for verifying the 
correctness of synchronization protocols, such as the Temporal Logic 
of Actions (TLA+), as well as synchronization primitives available within 
an operating-system kernel such as Linux. These include read-write locks,
mutexes, real-time mutexes, spinlocks, Read-Copy-Update (RCU), 
and primitives for enabling and disabling preemption and interrupts.

Although many of the topics covered are generally applicable to a variety 
of programming languages and operating systems, the course examples are 
presented in the C programming language and on the Linux operating system.

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
