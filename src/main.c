#include "hash_function.h"
#include "hash_table.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void string_string_destructor(void *key, void *value)
{
	free(key);
	free(value);
}

bool string_compare(void *s1, void *s2)
{
	return !strncmp((char *)s1, (char *)s2, 64);
}

int main(int argc, char *argv[])
{
	HashTable *hash_table = hash_table_new(hash_str, string_compare, string_string_destructor);

	/* Insert 15 elements into table */
	assert(hash_table_emplace(hash_table, "key", "value"));
	assert(hash_table_emplace(hash_table, "text", "yerp"));
	assert(hash_table_emplace(hash_table, "sjweifo", "i"));
	assert(hash_table_emplace(hash_table, "efewejfi", "i"));
	assert(hash_table_emplace(hash_table, "test", "i"));
	assert(hash_table_emplace(hash_table, "test1", "i"));
	assert(hash_table_emplace(hash_table, "test2", "i"));
	assert(hash_table_emplace(hash_table, "test3", "i"));
	assert(hash_table_emplace(hash_table, "test4", "i"));
	assert(hash_table_emplace(hash_table, "test5", "i"));
	assert(hash_table_emplace(hash_table, "test6", "i"));
	assert(hash_table_emplace(hash_table, "test7", "i"));
	assert(hash_table_emplace(hash_table, "test8", "i"));
	assert(hash_table_emplace(hash_table, "test9", "i"));
	assert(hash_table_emplace(hash_table, "test10", "coollllllll"));

	assert(hash_table->size == 32);
	assert(hash_table->len == 15);

	/* Find elements in table */
	assert(hash_table_find(hash_table, "not_in_table") == NULL);
	assert(strcmp(hash_table_find(hash_table, "key"), "value") == 0);
	assert(strcmp(hash_table_find(hash_table, "text"), "yerp") == 0);
	assert(strcmp(hash_table_find(hash_table, "sjweifo"), "i") == 0);
	assert(strcmp(hash_table_find(hash_table, "efewejfi"), "i") == 0);
	assert(strcmp(hash_table_find(hash_table, "test"), "i") == 0);
	assert(strcmp(hash_table_find(hash_table, "test1"), "i") == 0);
	assert(strcmp(hash_table_find(hash_table, "test2"), "i") == 0);
	assert(strcmp(hash_table_find(hash_table, "test3"), "i") == 0);
	assert(strcmp(hash_table_find(hash_table, "test4"), "i") == 0);
	assert(strcmp(hash_table_find(hash_table, "test5"), "i") == 0);
	assert(strcmp(hash_table_find(hash_table, "test6"), "i") == 0);
	assert(strcmp(hash_table_find(hash_table, "test7"), "i") == 0);
	assert(strcmp(hash_table_find(hash_table, "test8"), "i") == 0);
	assert(strcmp(hash_table_find(hash_table, "test9"), "i") == 0);
	assert(strcmp(hash_table_find(hash_table, "test10"), "coollllllll") == 0);

	/* Remove and reinsert element into table */
	assert(strcmp(hash_table_remove(hash_table, "key"), "value") == 0);
	assert(hash_table->len == 14);
	assert(hash_table_find(hash_table, "key") == NULL);
	assert(hash_table_emplace(hash_table, "key", "value"));
	assert(strcmp(hash_table_find(hash_table, "key"), "value") == 0);

	/* Remove every element from table */
	assert(strcmp(hash_table_remove(hash_table, "key"), "value") == 0);
	assert(strcmp(hash_table_remove(hash_table, "text"), "yerp") == 0);
	assert(strcmp(hash_table_remove(hash_table, "sjweifo"), "i") == 0);
	assert(strcmp(hash_table_remove(hash_table, "efewejfi"), "i") == 0);
	assert(strcmp(hash_table_remove(hash_table, "test"), "i") == 0);
	assert(strcmp(hash_table_remove(hash_table, "test1"), "i") == 0);
	assert(strcmp(hash_table_remove(hash_table, "test2"), "i") == 0);
	assert(strcmp(hash_table_remove(hash_table, "test3"), "i") == 0);
	assert(strcmp(hash_table_remove(hash_table, "test4"), "i") == 0);
	assert(strcmp(hash_table_remove(hash_table, "test5"), "i") == 0);
	assert(strcmp(hash_table_remove(hash_table, "test6"), "i") == 0);
	assert(strcmp(hash_table_remove(hash_table, "test7"), "i") == 0);
	assert(strcmp(hash_table_remove(hash_table, "test8"), "i") == 0);
	assert(strcmp(hash_table_remove(hash_table, "test9"), "i") == 0);
	assert(strcmp(hash_table_remove(hash_table, "test10"), "coollllllll") == 0);

	assert(hash_table->len == 0);
	assert(hash_table->size == 32);
	assert(hash_table_is_empty(hash_table));

	/* Resize table */
	assert(hash_table_resize(hash_table, 40));
	assert(hash_table->size == 40);
	assert(!(hash_table->size == 32));
	assert(hash_table->len == 0);
	assert(hash_table_is_empty(hash_table));

	/* Insert 15 elements into table */
	assert(hash_table_emplace(hash_table, "key", "value"));
	assert(hash_table_emplace(hash_table, "text", "yerp"));
	assert(hash_table_emplace(hash_table, "sjweifo", "i"));
	assert(hash_table_emplace(hash_table, "efewejfi", "i"));
	assert(hash_table_emplace(hash_table, "test", "i"));
	assert(hash_table_emplace(hash_table, "test1", "i"));
	assert(hash_table_emplace(hash_table, "test2", "i"));
	assert(hash_table_emplace(hash_table, "test3", "i"));
	assert(hash_table_emplace(hash_table, "test4", "i"));
	assert(hash_table_emplace(hash_table, "test5", "i"));
	assert(hash_table_emplace(hash_table, "test6", "i"));
	assert(hash_table_emplace(hash_table, "test7", "i"));
	assert(hash_table_emplace(hash_table, "test8", "i"));
	assert(hash_table_emplace(hash_table, "test9", "i"));
	assert(hash_table_emplace(hash_table, "test10", "coollllllll"));

	assert(!hash_table_is_empty(hash_table));
	assert(hash_table->size == 40);
	assert(hash_table->len == 15);

	assert(hash_table_insert(hash_table, "insert", "value",
				 (sizeof(char) * (strlen("insert") + 1)),
				 (sizeof(char) * (strlen("value") + 1))));
	assert(hash_table->len == 16);

	return EXIT_SUCCESS;
}
