#ifndef RWLOCKS_SEMAPHORE_H
#define RWLOCKS_SEMAPHORE_H

#include <semaphore.h>

typedef struct {
    sem_t mutex;
    sem_t write;
    int readers;
} rwlock_t;

void rwlock_init(rwlock_t* lock);
void rwlock_destroy(rwlock_t* lock);
void rwlock_readLock(rwlock_t* lock);
void rwlock_readUnlock(rwlock_t* lock);
void rwlock_writeLock(rwlock_t* lock);
void rwlock_writeUnlock(rwlock_t* lock);

#endif /* RWLOCKS_SEMAPHORE_H */
