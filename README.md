# Multithreading Exercises in C (C90) [OS-Threads-HW]

This repository contains 5 separate C programs that demonstrate various multithreading concepts using POSIX threads (pthreads) in the C90 standard.

## Contents

- **E01.c**: Creates 3 threads that print a message including their identification number. The main thread waits for all threads to complete using `pthread_join`.
- **E02.c**: Implements a shared counter incremented 1000 times by each of two threads. Access to the counter is protected using a mutex (`pthread_mutex_t`).
- **E03.c**: Simulates a simple Producer-Consumer problem using a mutex and condition variable (`pthread_cond_t`). The producer creates work and signals the consumer.
- **E04.c**: Demonstrates coordination between two threads. The first thread prints numbers 1 to 5 (with a 1-second sleep between prints) and signals the second thread to print its message after finishing.
- **E05.c**: Two threads alternate printing "Ping" and "Pong" 10 times using condition variables to coordinate the turn.

## How to Compile

To compile any of these programs, use a compiler that supports POSIX threads (such as GCC) with the `-pthread` flag. For example:

```bash
gcc -std=c90 -pthread E01.c -o E01
gcc -std=c90 -pthread E02.c -o E02
gcc -std=c90 -pthread E03.c -o E03
gcc -std=c90 -pthread E04.c -o E04
gcc -std=c90 -pthread E05.c -o E05
```


## Requirements
- A C compiler that supports the C90 standard.
- POSIX threads library (pthreads). Most Unix-like systems have this by default.

## Notes
- Each file is self-contained and demonstrates a specific multithreading concept.
- Make sure to compile each file with the -pthread flag to link against the pthreads library.
- The programs include error checking for thread creation.
