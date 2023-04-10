#include "hash_function.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>


typedef struct HashTable {
	// Vector of keys (buckets)
	void **bucket;
	// Load factor out of 10
	int32_t load_factor;
	// Hashing function
	size_t (*hash_func)(char *);
	// Size
	size_t size;
	// Length
	size_t len;
} HashTable;

HashTable *hash_table_new(void)
{
	HashTable *this = malloc(sizeof(HashTable));
	this->hash_func = hash_str;
	this->load_factor = 7;
	this->len = 0;
	this->bucket = 0;

	return this;
}

void hash_table_insert(HashTable *hash_table, void *value)
{
	hash_table->size;
}

void hash_table_remove(HashTable *hash_table)
{
}
