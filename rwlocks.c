#include "rwlocks.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Initilize locks */
void rwlock_init(rwlock_t* lock)
{
    lock -> readers = 0;  
    sem_init(&lock -> mutex, 0, 1); // mutex = 1
    sem_init(&lock -> write, 0, 1); // write = 1
}
/* Destroy locks */
void rwlock_destroy(rwlock_t* lock)
{
    sem_destroy(&lock -> mutex);
    sem_destroy(&lock -> write);
}
/* Read LOCK */
void rwlock_readLock(rwlock_t* lock)
{
    sem_wait(&lock -> mutex); // Wait until we can acquire the lock
    lock -> readers++; // If we can then decrement to indicate the lock is in use
    if(lock -> readers == 1) // Check if reader == 1, If it is then there is no active readers
    {
        sem_post(&lock -> write); // Signals the writer that is waiting for the lock
    }
    sem_post(&lock->mutex); // Release mutex lock
}
/*Read UNLOCK*/
void rwlock_readUnlock(rwlock_t* lock)
{
    sem_wait(&lock -> mutex); // Wait until we can acquire the lock
    lock -> readers--;  // Decrement to indicate that the reader is releasing the lock
    if(lock -> readers == 0) // If reader == 0...
    {
        sem_post(&lock -> write); // Signal active writers to acquire the lock
    }
    sem_post(&lock -> mutex);   // Releaser the mutex lock
}
/*Write LOCK*/
void rwlock_writeLock(rwlock_t* lock)
{
    sem_wait(&lock -> write);
}
/*Wire UNLOCK*/
void rwlock_writeUnlock(rwlock_t* lock)
{
    sem_post(&lock -> write);
}
