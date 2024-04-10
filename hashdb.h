// Concurrent Hash Table struct definitions
// Authors: Jazz Olario and Sophia Gnisci

#include <stdint.h>

typedef struct hash_struct
{
  uint32_t hash;
  char name[50];
  uint32_t salary;
  struct hash_struct *next;
} hashRecord;

// Function Declarations
uint32_t jenkinsOneAtATime(const uint8_t* key, size_t length);
void insert(uint8_t* key, uint32_t value);
void deleteItem(uint8_t* key);
uint32_t search(uint8_t* key);