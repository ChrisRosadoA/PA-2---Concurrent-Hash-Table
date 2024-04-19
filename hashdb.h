// Concurrent Hash Table definitions
// Authors: Jazz Olario and Sophia Gnisci

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Linked List Node
typedef struct hash_struct
{
  uint32_t hash;
  char name[50];
  uint32_t salary;
  struct hash_struct *next;
} hashRecord;

// Function Declarations
hashRecord** createTable();
uint32_t search(uint8_t* key);
hashRecord* createNode(uint8_t* key, uint32_t value, uint32_t hashValue);
void insert(uint8_t* key, uint32_t value);
void deleteItem(uint8_t* key);
size_t computeIndex(uint8_t* key);
uint32_t jenkinsOneAtATime(uint8_t* key, size_t length);
size_t computeTableSize(int expectedNumKeys, double loadFactor);
int isPowerOf2(int num);

// Global Variables
hashRecord** concurrentHashTable;
size_t tableSize;