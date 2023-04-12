#include "linked_list.h"
#include "hash_function.h"
#include "utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

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

/*
 * Resize hash_table. Reallocates and recomputes hashes
 * for keys.
 *
 * Returns if resize was successful.
 */
// TODO What to do if size causes 'sufficient collisions'?
bool hash_table_resize(HashTable *hash_table, size_t new_size)
{
	// Hmm... Maybe it's possible to use realloc, and if it doesn't move the block,
	// just reinitialize it.
	size_t old_size = hash_table->size;
	LinkedList **old_bucket = hash_table->bucket;

	hash_table->size = new_size;
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
	return true;
}

/*
 * Insert into hash_table creating copies for both key and value.
 */
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
	// TODO: This could be better
	if (((float)++hash_table->len / (float)hash_table->size) >
	    ((float)hash_table->load_factor / 10.0)) {
		hash_table_resize(hash_table, hash_table->size * 2);
	}

	size_t idx = hash_table->hash_func(key) % hash_table->size;

	LinkedList *slot = hash_table->bucket[idx];

	// TODO: Replace collision with new value and
	// return old value.
	//
	// Push to front
	// TODO Need to deal with a destructor function.
	char *key_copy = malloc(sizeof(char) * strnlen(key, 64) + 1);
	char *value_copy = malloc(sizeof(char) * strnlen(value, 64) + 1);

	memcpy(key_copy, key, sizeof(char) * strnlen(key, 64) + 1);
	memcpy(value_copy, value, sizeof(char) * strnlen(value, 64) + 1);

	#ifdef DEBUG
	assert(strcmp(key, key_copy) == 0);
	assert(strcmp(value, value_copy) == 0);
	assert(key != key_copy);
	assert(value != value_copy);
	#endif /* ifdef DEBUG */

	linked_list_push_front(slot, key_copy, value_copy);

	return true;
}

/*
 * Insert into hash_table with references to both key and value.
 */
bool hash_table_emplace(HashTable *hash_table, char *key, void *value)
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
	// TODO: This could be better
	if (((float)++hash_table->len / (float)hash_table->size) >
	    ((float)hash_table->load_factor / 10.0)) {
		hash_table_resize(hash_table, hash_table->size * 2);
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
	LinkedList *slot = hash_table->bucket[idx]->next; /* First node is dummy node */
	LinkedList *end = hash_table->bucket[idx + 1];

	while (slot != end) {
		if (!strncmp(slot->key, key, 64)) {
			return slot->value;
		}
		slot = slot->next;
	}
	return NULL;
}

/*
 * Remove element and return ptr to it.
 *
 * Return NULL if element does not exist.
 */
char *hash_table_remove(HashTable *hash_table, char *key)
{
	size_t idx = hash_table->hash_func(key) % hash_table->size;
	LinkedList *slot = hash_table->bucket[idx];
	LinkedList *ptr = hash_table->bucket[idx + 1]; /* Initially points to 'end' */
	char *value = NULL;

	while (slot->next != ptr) {
		if (!strncmp(slot->next->key, key, 64)) {
			ptr = slot->next;
			slot->next = ptr->next;
			value = ptr->value;

			--hash_table->len;
			free(ptr);
			return value;
		}
		slot = slot->next;
	}

	return NULL;
}

bool hash_table_contains(HashTable *hash_table, char *key) {
	size_t idx = hash_table->hash_func(key) % hash_table->size;
	LinkedList *slot = hash_table->bucket[idx]->next;
	LinkedList *end = hash_table->bucket[idx + 1];

	while (slot != end) {
		if (!strncmp(slot->key, key, 64)) {
			return true;
		}
		slot = slot->next;
	}

	return false;
}

bool hash_table_is_empty(HashTable *hash_table)
{
	return hash_table->len == 0;
}
