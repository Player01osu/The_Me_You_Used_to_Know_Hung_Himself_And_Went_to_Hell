#ifndef HASHTABLE
#define HASHTABLE

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "hash_function.h"

typedef struct LinkedList {
	char *key;
	char *value;
	struct LinkedList *next;
} LinkedList;

typedef struct HashTable {
	// Vector of keys (buckets)
	LinkedList **bucket;
	// Load factor out of 10
	int32_t load_factor;
	// Hashing function
	size_t (*hash_func)(char *);
	// Size
	size_t size;
	// Length
	size_t len;
} HashTable;

HashTable *hash_table_new(void);

char *hash_table_find(HashTable *hash_table, char *key);

bool hash_table_insert(HashTable *hash_table, char *key, void *value);

char *hash_table_remove(HashTable *hash_table, char *key);

bool hash_table_contains(HashTable *hash_table, char *key);

bool hash_table_resize(HashTable *hash_table, size_t new_size);


#endif // !HASHTABLE
