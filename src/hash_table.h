#ifndef HASHTABLE
#define HASHTABLE

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "hash_function.h"
#include "linked_list.h"

typedef struct HashTable {
	// Vector of keys (buckets)
	LinkedList **bucket;
	// Load factor out of 10
	int32_t load_factor;
	// Hashing function
	size_t (*hash_func)(void *);
	// Destructor function
	void (*destructor)(void *, void *);
	// Comparison function
	bool (*compare)(void *, void *);
	// Size
	size_t size;
	// Length
	size_t len;
} HashTable;

HashTable *hash_table_new(size_t hash_func(void *), bool compare(void *, void *), void destructor(void *, void *));

HashTable *hash_table_with_capacity(size_t hash_func(void *), bool compare(void *, void *), void destructor(void *, void *), size_t capacity);

void *hash_table_find(HashTable *hash_table, void *key);

bool hash_table_emplace(HashTable *hash_table, void *key, void *value);

bool hash_table_insert(HashTable *hash_table, void *key, void *value, size_t key_size, size_t value_size);

void *hash_table_remove(HashTable *hash_table, void *key);

bool hash_table_destroy(HashTable *hash_table, void *key);

bool hash_table_clear(HashTable *hash_table);

bool hash_table_contains(HashTable *hash_table, void *key);

bool hash_table_resize(HashTable *hash_table, size_t new_size);

bool hash_table_is_empty(HashTable *hash_table);

#endif // !HASHTABLE
