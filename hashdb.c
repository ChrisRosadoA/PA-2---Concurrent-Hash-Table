// Concurrent Hash Table implementation
// Author: Sophia Gnisci

#include "hashdb.h"

// Hash Function (Jenkin's One at a Time)
// In: name (key) & length of name (length)
// Out: hash value
uint32_t jenkinsOneAtATime(const uint8_t* key, size_t length) {
  size_t i = 0;
  uint32_t hash = 0;
  while (i != length) {
    hash += key[i++];
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;
}

// Insert Into Hash table
// In: name (key) & salary (value)
void insert(uint8_t* key, uint32_t value) {

    // compute hash value
    size_t keyLen = strlen(key);
    uint32_t hash = jenkinsOneAtATime(key, keyLen);

    // aquire writer lock

    // search linked list for hash

        // hash found (update value)
        if ( search(key) != NULL && search(key) != 0 ) {


        // hash not found (create new node and insert)
        } else {
            
        }

    // release writer lock

    return;
}

// Delete Key-Data Pair from Hash Table
// In: name (key)
void deleteItem(uint8_t* key) {

    // compute hash value
    size_t keyLen = strlen(key);
    uint32_t hash = jenkinsOneAtATime(key, keyLen);

    // aquire writer lock

    // search linked list for hash

        // hash found 
        if ( search(key) != NULL && search(key) != 0 ) {

            // delete node and free memory

        }

    // release writer lock

    return;
}

// Search Based on Key
// In: name (key)
// Out: salary or NULL
uint32_t search(uint8_t* key) {

    // compute hash value
    size_t keyLen = strlen(key);
    uint32_t hash = jenkinsOneAtATime(key, keyLen);

    // aquire reader lock

    // search linked list for hash
    uint32_t retval = 0;
    int found = 0;

        // hash found
        if (found == 1)
            retval = 1; // change to salary
        
        // hash not found
        else
            retval = NULL;
    
    // release reader lock

    return retval;
}

// // Initializes the Hash Table
// void init(pthread_t hashTable) {

// }

// Testing
// void main () {

// }