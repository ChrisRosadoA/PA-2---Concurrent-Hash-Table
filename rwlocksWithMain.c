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

void* reader_function(void* arg) {
    rwlock_t* lock = (rwlock_t*) arg;
    while (1) {
        rwlock_readLock(lock);
        printf("Reader reading...\n");
        rwlock_readUnlock(lock);
        sleep(1); // Sleep for 500 milliseconds
    }
    return NULL;
}

void* writer_function(void* arg) {
    rwlock_t* lock = (rwlock_t*) arg;
    while (1) {
        rwlock_writeLock(lock);
        printf("Writer writing...\n");
        rwlock_writeUnlock(lock);
        sleep(1); // Sleep for 1 second
    }
    return NULL;
}

int main() {
    rwlock_t lock;
    rwlock_init(&lock);

    pthread_t reader_thread, writer_thread;

    // Create reader thread
    if (pthread_create(&reader_thread, NULL, reader_function, &lock)) {
        fprintf(stderr, "Error creating reader thread\n");
        return 1;
    }

    // Create writer thread
    if (pthread_create(&writer_thread, NULL, writer_function, &lock)) {
        fprintf(stderr, "Error creating writer thread\n");
        return 1;
    }

    // Join reader thread
    if (pthread_join(reader_thread, NULL)) {
        fprintf(stderr, "Error joining reader thread\n");
        return 1;
    }

    // Join writer thread
    if (pthread_join(writer_thread, NULL)) {
        fprintf(stderr, "Error joining writer thread\n");
        return 1;
    }

    rwlock_destroy(&lock);

    return 0;
}

