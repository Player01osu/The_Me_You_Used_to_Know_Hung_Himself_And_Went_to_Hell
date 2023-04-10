#ifndef HASHTABLE
#define HASHTABLE

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "hash_function.h"

typedef struct HashTable {
	// Vector of keys (buckets)
	void **bucket;
	// Load factor
	int32_t load_factor;
	// Hashing function
	size_t (*hash_func)(char *);
	// Size
	size_t size;
	// Length
	size_t len;
} HashTable;

HashTable *hash_table_new(void);

void hash_table_insert(HashTable *hash_table);

void hash_table_remove(HashTable *hash_table);

bool hash_table_contains(HashTable *hash_table);

#endif // !HASHTABLE
