// Concurrent Hash Table implementation
// Author: Sophia Gnisci

#include "hashdb.h"

// Creates the Concurrent Hash Table
// In: size of hash table (tableSize)
// Out: pointer to concurrent hash table
hashRecord** createTable() {

    // allocate memory
    concurrentHashTable = (hashRecord**) malloc(tableSize*sizeof(hashRecord*));

    // allocation error
    if (!concurrentHashTable) {
        printf("\nError: couldn't allocate memory to hash table");
        return NULL;
    }

    // initialize
    for (int i=0; i<tableSize; i++)
        concurrentHashTable[i] = NULL;

    return concurrentHashTable;
}

// Search Based on Key
// In: name (key)
// Out: salary or 0
uint32_t search(uint8_t* key) {
    uint32_t retval = 0;

    // compute hash value and corresponding index
    size_t index = computeIndex(key);

    // aquire reader lock

    // linked list is found at this index
    if (concurrentHashTable[index] != NULL) {
        hashRecord* t = concurrentHashTable[index];

        // traverse linked list
        while (t->next && !strcmp(t->name, key))
            t = t->next;

        // found key
        if (strcmp(t->name, key))
            retval = t->salary;
    }
    
    // release reader lock

    return retval;
}

// Creates a Linked List Node (hashRecord)
// In: name (key) & salary (value)
// Out: node
hashRecord* createNode(uint8_t* key, uint32_t value, uint32_t hashValue) {
    
    // allocate memory
    hashRecord* node = (hashRecord*) malloc(sizeof(hashRecord));
    
    // allocation error
    if (!node) {
        printf("\nError: couldn't allocate memory to hash table");
        return NULL;
    }

    node->hash = hashValue;
    strcpy(node->name, key);
    node->salary = value;
    node->next = NULL;

    return node;
}

// Insert Into Hash table
// In: name (key) & salary (value)
void insert(uint8_t* key, uint32_t value) {

    // compute hash value and corresponding index
    size_t keyLen = strlen(key);
    uint32_t hashValue = jenkinsOneAtATime(key, keyLen);
    size_t index = hashValue % tableSize;

    // aquire writer lock

    // search linked list for hash
    int foundValue = search(key);

    // hash found (update value)
    if (foundValue > 0) {


    // hash not found
    } else {

        // create new node
        hashRecord* node = createNode(key, value, hashValue);

        if (node == NULL)
            return;
        


    }

    // release writer lock

    return;
}

// Delete Key-Data Pair from Hash Table
// In: name (key)
void deleteItem(uint8_t* key) {

    // compute hash value and corresponding index
    size_t index = computeIndex(key);

    // aquire writer lock

    // search linked list for hash

        // hash found 
        if ( search(key) != 0 && search(key) != 0 ) {

            // delete node and free memory

        }

    // release writer lock

    return;
}

// Helper Function: compute hash table index
// In: name (key) & size of hash table (tableSize)
// Out: index
size_t computeIndex(uint8_t* key) {
    size_t keyLen = strlen(key);
    uint32_t hashValue = jenkinsOneAtATime(key, keyLen);
    return hashValue % tableSize;
}

// Helper Function: compute Jenkin's-One-at-a-Time hash 
// In: name (key) & length of name (length)
// Out: hash value
uint32_t jenkinsOneAtATime(uint8_t* key, size_t length) {
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

// Computes the Size of the Concurrent Hash Table
// In: # of keys (expectedNumKeys) & load factor (loadFactor)
// Out: size of table
size_t computeTableSize(int expectedNumKeys, double loadFactor) {
    tableSize = expectedNumKeys/loadFactor;

    while (!isPowerOf2(tableSize))
        tableSize++;
    
    return tableSize;
}

// Helper Function: calculate if a number is a power of 2
// In: an integer (num)
// Out: 1 if true or 0 if false
int isPowerOf2(int num) {

    // log is undefined at 0
    if (num == 0)
        return 0;
    
    double numLog = log2(num);
    double res = fmod(numLog, 1.0);

    // whole number
    if (res == 0)
        return 1;
    
    // decimal
    return 0;
}




// // Testing & Examples ------------------------------------------
// int main () {

//     // creating and initializing the table
//     tableSize = computeTableSize(15, 0.7);
//     concurrentHashTable = createTable();

//     if (concurrentHashTable == NULL)
//         exit(1);

//     // insert

//     // delete

//     // search

//     // free memory!!!!
//     free(concurrentHashTable);
    
//     return 0;
// }