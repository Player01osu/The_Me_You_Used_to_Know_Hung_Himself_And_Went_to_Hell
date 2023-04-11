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

void linked_list_push(LinkedList *linked_list, char *key, char *value);
LinkedList *linked_list_new(void);

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

// TODO
void dbg(char *s)
{
#ifdef DEBUG
	printf("%s\n", s);
#endif /* ifdef DEBUG */
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

	// Initialize rest bucket
	for (size_t i = 0; i < hash_table->size; ++i) {
		hash_table->bucket[i] = linked_list_new();
	}

	// Recompute hashes and insert into new bucket.
	for (size_t i = 0; i < old_size; ++i) {
		// Follow linked list
		LinkedList *p = old_bucket[i];
		// TODO This could be better.
		if (p->next) {
			p = p->next;

			do {
				size_t idx = hash_table->hash_func(p->key) % hash_table->size;
				linked_list_push(hash_table->bucket[idx], p->key, p->value);
				p = p->next;
			} while (p);
		}
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
		}
	}

	if (((float)++hash_table->len / (float)hash_table->size) >
	    ((float)hash_table->load_factor / 10.0)) {
		hash_table_resize(hash_table);
	}

	size_t idx = hash_table->hash_func(key) % hash_table->size;

	LinkedList *slot = hash_table->bucket[idx];

	// TODO: Replace collision with new value and
	// return old value.
	linked_list_push(slot, key, value);
	return true;
}

/**
 * Returns NULL if doesn't exist.
 */
char *hash_table_find(HashTable *hash_table, char *key)
{
	size_t idx = hash_table->hash_func(key) % hash_table->size;
	LinkedList *slot = hash_table->bucket[idx];

	// TODO This could be better.
	//
	// Knowing the first node is a dummy node, the first slot is skipped.
	if (slot->next) {
		slot = slot->next;
		do {
			if (!strncmp(slot->key, key, 64)) {
				return slot->value;
			}
			slot = slot->next;
		} while (slot);
	}
	return NULL;
}

void hash_table_remove(HashTable *hash_table, char *key)
{
	todo("hash_table_remove: Not implemented yet");
}

LinkedList *linked_list_new(void)
{
	LinkedList *this = malloc(sizeof(LinkedList));
	this->value = NULL;
	this->key = NULL;
	this->next = NULL;

	return this;
}

void linked_list_push(LinkedList *linked_list, char *key, char *value)
{
	LinkedList *p = linked_list;

	while (p->next) {
		p = p->next;
	}
	p->next = malloc(sizeof(LinkedList));
	p = p->next;

	p->next = NULL;
	p->key = key;
	p->value = value;
}

