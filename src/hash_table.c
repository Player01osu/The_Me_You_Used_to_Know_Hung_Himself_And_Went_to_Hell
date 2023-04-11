#include "linked_list.h"
#include "hash_function.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define GROW_TABLE(size) exp2(log2(size) + 1)

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

HashTable *hash_table_new(void)
{
	HashTable *this = malloc(sizeof(HashTable));
	this->hash_func = hash_str;
	this->load_factor = 7;
	this->len = 0;
	this->bucket = NULL;
	this->size = 0;

	return this;
}

// Grow in powers of 2
void hash_table_resize(HashTable *hash_table)
{
	// Hmm... Maybe it's possible to use realloc, and if it doesn't move the block,
	// just reinitialize it.
	size_t old_size = hash_table->size;
	LinkedList **old_bucket = hash_table->bucket;

	hash_table->size = GROW_TABLE(hash_table->size);
	hash_table->bucket = malloc(sizeof(LinkedList *) * hash_table->size);

	for (size_t i = 0; i < hash_table->size; ++i) {
		hash_table->bucket[i] = linked_list_new();

		if (i > 0)
			hash_table->bucket[i - 1]->next = hash_table->bucket[i];
	}

	// Recompute hashes and insert into new bucket.
	// Follow linked list
	LinkedList *p = *old_bucket;
	while (p) {
		if (p->key) {
			size_t idx = hash_table->hash_func(p->key) % hash_table->size;
			linked_list_push_front(hash_table->bucket[idx], p->key, p->value);
		}
		p = p->next;
	}
	for (size_t i = 0; i < old_size; ++i) {
		free(old_bucket[i]);
	}
}

bool hash_table_insert(HashTable *hash_table, char *key, void *value)
{
	// Have to allocate.
	if (hash_table->size == 0) {
		hash_table->size = 16;
		hash_table->bucket = malloc(sizeof(LinkedList *) * hash_table->size);
		for (size_t i = 0; i < hash_table->size; ++i) {
			hash_table->bucket[i] = linked_list_new();
			if (i > 0)
				hash_table->bucket[i - 1]->next = hash_table->bucket[i];
		}
	}

	// Resize if hash table length exceeds load factor.
	if (((float)++hash_table->len / (float)hash_table->size) >
	    ((float)hash_table->load_factor / 10.0)) {
		hash_table_resize(hash_table);
	}

	size_t idx = hash_table->hash_func(key) % hash_table->size;

	LinkedList *slot = hash_table->bucket[idx];

	// TODO: Replace collision with new value and
	// return old value.
	//
	// Push to front
	linked_list_push_front(slot, key, value);

	return true;
}

/*
 * Return ptr to element.
 *
 * Returns NULL if doesn't exist.
 */
char *hash_table_find(HashTable *hash_table, char *key)
{
	size_t idx = hash_table->hash_func(key) % hash_table->size;
	LinkedList *slot = hash_table->bucket[idx];
	LinkedList *end = hash_table->bucket[idx + 1];
	slot = slot->next;

	// Knowing the first node is a dummy node, the first slot is skipped.
	while (slot != end) {
		if (!strncmp(slot->key, key, 64)) {
			return slot->value;
		}
		slot = slot->next;
	}
	return NULL;
}

void hash_table_remove(HashTable *hash_table, char *key)
{
	todo("hash_table_remove: Not implemented yet");
}
