# Assignment 1

## Files
- **threading_race.c**: Simple threading program with a race condition.
- **threading_mutex.c**: Simple Threading program with mutex to fix race condition.
- **threading_deadlock.c**: Simple Threading program with a deadlock.
- **threading_complex.c**: Complex threaded simulator using task synchronization.
- **threading_simplified.c**:  Simplified program using task synchronization.
- **cbmc_complex.out**: output from running CBMC on threading_complex.c


## threading_complex.c
CBMC has problems with this program. The program creates 4 threads; deerThread, grainThread, invasiveThread, and watchThread. The deerThread, grainThread, and invasiveThread are on infinite loops, and using barriers to coordinate. The watchThread watches the simulation and exits when it hits the end. The main thread is waiting on the watchThread to exit, and when it does, it cancels the other 3 threads. I modified the program to run 1 loop with unwinding set at 2. It took 6 minutes to run and returned with an unwinding assertion from the grainThread. The grainThread is one of the threads that is in an infinite loop, and therefore never really exited the loop.

## threading_simplified.c
CBMC has the same problem as with threading_complex.c. the program threading_simplified works the same way using the thread synchronization. Because the code does less math, CBMC has an easier time solving this program. This allowed me to increase the number of unwinding, showing that we can't fix this problem. Removing the unwinding limit, made CBMC unwind updateA loop infinitely. With a closer look at the output from CBMC, it doesn't know how to handle barriers. 

## threading_race.c
CBMC fails to verify the program, which is correct.  Each thread increments the global variable g.  g is affected by the threaded race condition, and therefore could be in a range from 0 to the number of threads. The harness only checks if the result is equal to the number of threads, and therefore CBMC shows an example where the result is less than number of threads. 

## threading_mutex.c
CBMC correctly verifies the program.  Each thread increments the global variable g, but this time uses a mutex to limit access to g.  g is not affected by the threaded race condition, and therefore g is equal to the number of threads. Changing the assert finds a solution for other values.

## threading_deadlock.c
CBMC fails to find the deadlock. We know CBMC can handle mutex because of threading_mutex.c. I was told this doesn't work, but I had to verify.

