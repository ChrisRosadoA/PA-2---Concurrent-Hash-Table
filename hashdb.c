// Concurrent Hash Table implementation
// Author: Sophia Gnisci

#include "hashdb.h";

// Hash Function (Jenkin's One at a Time)
// In: name (key) & length of name (length)
// Out: hash value
uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, size_t length) {
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

}

// Delete Key-Data Pair from Hash Table
// In: name (key)
void deleteItem(uint8_t* key) {

}

// Search Based on Key
// In: name (key)
// Out: salary or NULL
uint32_t search(uint8_t* key) {

}