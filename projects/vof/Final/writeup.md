# Proving Threaded Programs

## Introduction
I am very interested in multi-threaded programs. 
It will be more important in the future. 
In assignment 1, I was very disappointed in CBMC's threading checking. 
CBMC has many limitations, like thread synchronization, and deadlocks.
I wanted to do more research on if there is more model checking on threading.
I want to look for other tools, and run it on my threaded code to see its capabilities.

## CBMC Multi-threading Analysis
CBMC can analysis different non-deterministic paths the code can take, and therefore can analysis if there is a race condition.
Also CBMC can also verify code with mutexes, but unfortunately CBMC doesn't track mutex locks and unlocks and therefore can't account for deadlocks.
CBMC doesn't understand barriers and therefore can't not account for thread synchronization. 


## Other Tools for C/c++ static model checking
First I wanted to look at other static model checking tools to see if anything else can analysis threaded code.
I recreated the code using openmp instead of pthreads.
I looked up other C/C++ Bounded Model checkers, and found CSeq, DBRover, LLBMC, SATABS, and Ompca.


### CSeq
I downloaded the program from http://users.ecs.soton.ac.uk/gp4/cseq/cseq.html.
There were multiple versions, Lazy, MU, UL, LAl-Reps.
The Lazy version is carefully designed to introduce very small memory overheads and very few sources of nondeterminism.
The MU version looks into memory unwinding.
The UL version allows for unbounded numbers of context switches and unbounded loops.
The LAl-Reps version support dynamic thread creation.
I started with the Lazy version because it was the simplest version.
I was disappointed with the results, so I tried LAl-Reps version as well
CSeq allows CBMC, ESBMC, and LLBMC as the backend BMC.

pthread_race.c should Fail because result can range from 1 to 4
cbmc fails which is correct
lazy cseq using cbmc returns True which is wrong. 
lal-reps cseq using cbmc returns unsafe which is correct.

pthread_mutex.c should pass
cbmc is successful.
lazy cseq returns unknown and no reason why.
lal-reps cseq safe which is correct

pthread_deadlock.c should fail or be unsafe
cbmc was successful because it doesn't understand deadlocks
lazy cseq returns unknown which doesn't mean it is correct
lal-reps cseq said it was safe which was interesting because I thought it would catch this.

pthread_simplified.c should fail but should be safe
cbmc went into an infinite loop
lazy cseq returned False maybe because it hit the bounds.
lal-reps cseq returned unsafe and also returned that it doesn't understand barriers.


http://users.ecs.soton.ac.uk/gp4/papers/cseq-ase.pdf
Our CSeq tool implements a novel sequentialization for C
programs using pthreads, which extends the Lal/Reps sequentialization
to support dynamic thread creation. CSeq now works with
three different backend tools, CBMC, ESBMC, and LLBMC,
and is competitive with state-of-the-art verification tools for
concurrent programs.


### LLBMC
I look in LLBMC from http://llbmc.org/ to test a low-level system code. 
I had to compile using clang into bitcode that LLBMC understands.
I thought it be able understand pthread code by looking at memory accesses, but it doesn't understand pthreads.
Unfortunately, it return an error: 
No function body for the function "pthread_create" available. The program analysis is thus not complete.

### Ompca, OpenMP C Analysis
This was the most promising threading checker. 
I download it from http://sourceforge.net/projects/redlib/.
It is part of RedLib applications.
I had to recode the pthread program to use OpenMP directives instead.
It seems that ompca can only run on a 32bit computer.
I'm on a 64bit computer, so when I ran ompca, it was missing modules that were already installed on my computer.
I installed the 32bit version, it fixed the error.
Once I reinstalled all the missing modules, it gives me a Segmentation fault.
I can't take this texting any farther.
If I had more time, I would get a 32bit computer to test ompca.

### SATABS
http://www.cprover.org/satabs/
SATABS understands pthread_create, because it runs the threaded code.
The same goes for mutexes, but it doesn't understand barriers, joins, cancel, and attributes.
I really don't see the point of testing pthread_create without functions to allow interaction between threads.
SATABS always gives a verifcation failed, and result is always 0 for the race, mutex, and deadlock tests.
This makes me believe that SATABS is unable to convert threaded code into a non-deterministic code.

file pthread_simplified.c line 89 function main: no body for function `c::pthread_barrier_init'
file pthread_simplified.c line 28 function updateA: no body for function `c::pthread_barrier_wait'
file pthread_simplified.c line 99 function main: no body for function `c::pthread_join'
file pthread_simplified.c line 101 function main: no body for function `c::pthread_cancel'
file pthread_mutex.c line 29 function threadCount: no body for function `c::pthread_attr_init'
file pthread_mutex.c line 30 function threadCount: no body for function `c::pthread_attr_setdetachstate'
file pthread_mutex.c line 36 function threadCount: no body for function `c::pthread_attr_destroy'


## Other Thread checking tools
I wanted to look at other tools that were out there to get insight into static thread checking.
There are many tools out there, so I just wanted to briefly look at their features to see if I should look into it farther.
I found that many of the tools I looked at, run the code and analysis that run.
They aren't static analysis tools, instead are real-time performance tools.
They can't verify if code has a data race condition, but rather give you a trace of when and how a variable is changed.
This is the same with deadlocks.
A trace of a run will allow show any bottlenecks and areas where the system spends a lot of time. 
But a trace doesn't mean it will find a error with the parallalized code.

### Intel® Thread Checker built into ICC
I have worked with ICC and Intel threading building blocks before. 
I know it can analysis race conditions, deadlocks, and bottlenecks.
I know that OSU has ICC on their servers, but when I tried running it.
It seems that Thread Checker needs to be installed onto the system, thus allowing ICC to use it.
I tried to request a ICC trial for my system, but I never got a reply.
Intel Thread Checker 
This is a dynamic analysis tool for finding deadlocks (including potential deadlocks), stalls, data races, and incorrect uses of the native Windows synchronization APIs

### Open|SpeedShop
Open|SpeedShop is another runtime analysis tool that allows you to compare preformance between runs, processes and threads.
It can be found at http://www.openspeedshop.org/wp/


### TAU
http://www.cs.uoregon.edu/research/tau/about.php
TAU form an integrated analysis environment for parallel Fortran, C++, C, Java, and Python applications. 
It wasn't very clear on with features it had.


### HPCToolkit 
http://hpctoolkit.org/index.html 
HPCToolkit supports measurement and analysis of serial codes, threaded codes (e.g. pthreads, OpenMP), MPI, and
hybrid (MPI+threads) parallel codes.


### PAPI
http://icl.cs.utk.edu/papi/
PAPI enables software engineers to see, in near real time, the relation between software performance and processor events.

### Intel VTune Amplifier
https://software.intel.com/en-us/intel-vtune-amplifier-xe
Intel® VTune Amplifier provides a rich set of performance insight into hotspots, threading, locks & waits, OpenCL, bandwidth and more.
Low-overhead CPU, GPU, and thread profiling
Analyze OpenMP* 4.0 threaded performance and
scalability 
Thread profiling with lock and waits analysis
OpenMP scalability analysis,
Tune threading with locks and waits analysis.
Quickly find a common cause of slow performance in parallel
programs waiting too long on a lock, while the cores are
underutilized during the wait. New OpenMP* 4.0 support


### ThreadSpotter
http://www.paratools.com/threadspotter
ThreadSpotter automatically analyzes an application as it's running, lists the performance problems in order of importance, suggests fixes and gives the developer valuable insights and statistics needed to quickly assess and fix the problems.

### CHESS 
Created by Microsoft Research, CHESS is a novel combination of model checking and dynamic analysis. It detects concurrency errors by systematically exploring thread schedules and interleaving. It is capable of finding race conditions, deadlocks, hangs, livelocks, and data corruption issues.

### RacerX 
This flow-sensitive static analysis tool is used for detecting races and deadlocks.

### KISS 
Developed by Microsoft Research, this model checker tool is for concurrent C programs.

### Zing 
This tool is a pure model checker meant for design verification of concurrent programs. Zing has its own custom language that is used to describe complex states and transition, and it is fully capable of modeling concurrent state machines.


## Other research
I skimmed though papers on analyzing threaded code, and found a good one at https://msdn.microsoft.com/en-us/magazine/cc546569.aspx
It talks about 2 algorithms for finding race conditions, lockset and happens-before algorithms.
Both algorithm look simple, but would be very hard to implement for production code. 
The lockset algorithm only accounts for locks namely mutexes, and not for barrier and other thread synchronizing techniques.
The happens-before algorithms is hard to implement because it needs to account for all thread synchronizing techniques to create valid paths though the code.

### Lockset algorithm
The lockset algorithm reports a potential race when a shared variable is accessed by two or more threads without the threads holding a common lock.
For each shared memory variable v, maintain a set C(v) of locks. Initially C(v) is the list of all locks.
Each thread also maintains two sets of locks: locks(t) indicating all the locks held and writeLocks(t) indicating all the write locks held.

On each read of v by thread t:

Set C(v) = C(v) intersection locks(t).
If C(v) is empty, then raise an error.

On each write of v by thread t:
Set C(v) = C(v) intersection writeLocks(t).
If C(v) is empty, then raise an error.

Essentially, as the application progresses, the C(v) of each variable starts shrinking. An error is raised if the C(v) ever becomes null.
The lockset algorithm seems very easy to implement if only accounting for mutexes and could work made to work with SAT solvers. The article also states that not all race conditions reported by a lockset algorithm are real race conditions, but using this information, it would a easy to create a test to see if it is a real race condition.

### Happens-before algorithm
Another algorithm for detecting races is the "happens-before" algorithm, which is based on partial ordering of events in distributed systems. Here is an overview of the algorithm that computes the partial order to determine what events happened before another event (events, in this context, are all instructions, including read/write and locks):

Among threads, events are ordered according to the synchronization primitives' properties. For example, if lock(a) is being acquired by two threads, then the unlock by one thread is said to have happened-before the lock of another thread.

If two or more threads access a shared variable, and the accesses are not deterministically ordered by the "happens-before" relationship, then a race is said to have occurred.

The happens-before algorithm seems to be harder to implement, and wouldn't work well with a SAT solver because it has to analysis multiple paths though the code. Unlike the lockset algorithm, the bugs found by the happens-before algorithm are real, but it messes many bugs.



http://www.kroening.com/papers/cav2011-symmpa.pdf




pthread_race
Should Fail because result can range from 1 to 4
CBMC fails
cseq cbmc True
llbmc fails because No function body for the function "pthread_create" available. The program analysis is thus not complete.
cseq llbmc missing file?