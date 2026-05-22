# Concurrent Data Structures

Code of Concurrent Data Structures course @ Scuola Superiore
Sant'Anna, held by professor [@tomcucinotta](https://github.com/tomcucinotta).


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
