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
    if (concurrentHashTable[index]) {
        hashRecord* t = concurrentHashTable[index];

        // traverse linked list
        while (t->next && strcmp(t->name, key) != 0)
            t = t->next;

        // found key
        if (strcmp(t->name, key) == 0)
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
    int insertNew = 1;

    // compute hash value and corresponding index
    size_t keyLen = strlen(key);
    uint32_t hashValue = jenkinsOneAtATime(key, keyLen);
    size_t index = hashValue % tableSize;

    // aquire writer lock

    // linked list is found at index
    if (concurrentHashTable[index] != NULL) {
        hashRecord* t = concurrentHashTable[index];

        // search linked list for hash
        while (t->next && t->hash != hashValue)
            t = t->next;

        // update existing node
        if (t->hash == hashValue) {
            insertNew = 0;
            t->salary = value;
        }
    }

    // insert new node
    if (insertNew == 1) {

        // create new node
        hashRecord* node = createNode(key, value, hashValue);
        
        // insert
        if (node != NULL) {
            node->next = concurrentHashTable[index];
            concurrentHashTable[index] = node;
        }
    } 

    // release writer lock

    return;
}

// Delete Key-Data Pair from Hash Table
// In: name (key)
void deleteItem(uint8_t* key) {

    // compute hash value and corresponding index
    size_t keyLen = strlen(key);
    uint32_t hashValue = jenkinsOneAtATime(key, keyLen);
    size_t index = hashValue % tableSize;

    // aquire writer lock

    // linked list is found at index
    if (concurrentHashTable[index] != NULL) {

        // delete beginning of list
        if (concurrentHashTable[index]->hash == hashValue) {
            hashRecord* temp = concurrentHashTable[index];
            concurrentHashTable[index] = concurrentHashTable[index]->next;
            free(temp);

        // delete in middle or end of list
        } else {
            hashRecord* t = concurrentHashTable[index];
            
            // search linked list for node previous to node to delete
            while (t->next && t->next->hash != hashValue)
                t = t->next;

            // delete node
            if (t->next && t->next->hash == hashValue) {
                hashRecord* temp = t->next;
                t->next = t->next->next;
                free(temp);
            }
        }
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
//     insert("key1", 876543);
//     insert("KEY1", 43322);
//     insert("key2", 81653);
//     insert("key3", 1234);
//     insert("key3", 123456);

//     // delete
//     deleteItem("key2");

//     // search
//     uint32_t found1 = search("key2");
//     if (found1 > 0) printf("\nSalary of %d has been found at key \"key2\"", found1);
//     else printf("\nData at key \"key2\" does not exist");

//     uint32_t found2 = search("KEY2");
//     if (found2 > 0) printf("\nSalary of %d has been found at key \"KEY2\"", found2);
//     else printf("\nData at key \"KEY2\" does not exist");

//     uint32_t found3 = search("key3");
//     if (found3 > 0) printf("\nSalary of %d has been found at key \"key3\"\n", found3);
//     else printf("\nData at key \"key3s\" does not exist\n");

//     // free memory!!!!
//     free(concurrentHashTable);
    
//     return 0;
// }