#include "../src/hash_function.h"
#include "../src/hash_table.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZESTR(str) sizeof(char) * (strlen(str) + 1)

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
	clock_t start = clock();

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
	assert(hash_table_insert(hash_table, "key", "value", SIZESTR("key"), SIZESTR("value")));
	assert(hash_table_insert(hash_table, "text", "yerp", SIZESTR("text"), SIZESTR("yerp")));
	assert(hash_table_insert(hash_table, "sjweifo", "i", SIZESTR("sjweifo"), SIZESTR("i")));
	assert(hash_table_insert(hash_table, "efewejfi", "i", SIZESTR("efewejfi"), SIZESTR("i")));
	assert(hash_table_insert(hash_table, "test", "i", SIZESTR("test"), SIZESTR("i")));
	assert(hash_table_insert(hash_table, "test1", "i", SIZESTR("test1"), SIZESTR("i")));
	assert(hash_table_insert(hash_table, "test2", "i", SIZESTR("test2"), SIZESTR("i")));
	assert(hash_table_insert(hash_table, "test3", "i", SIZESTR("test3"), SIZESTR("i")));
	assert(hash_table_insert(hash_table, "test4", "i", SIZESTR("test4"), SIZESTR("i")));
	assert(hash_table_insert(hash_table, "test5", "i", SIZESTR("test5"), SIZESTR("i")));
	assert(hash_table_insert(hash_table, "test6", "i", SIZESTR("test6"), SIZESTR("i")));
	assert(hash_table_insert(hash_table, "test7", "i", SIZESTR("test7"), SIZESTR("i")));
	assert(hash_table_insert(hash_table, "test8", "i", SIZESTR("test8"), SIZESTR("i")));
	assert(hash_table_insert(hash_table, "test9", "i", SIZESTR("test9"), SIZESTR("i")));
	assert(hash_table_insert(hash_table, "test10", "coollllllll", SIZESTR("test10"),
				 SIZESTR("coollllllll")));

	assert(!hash_table_is_empty(hash_table));
	assert(hash_table->size == 40);
	assert(hash_table->len == 15);

	assert(hash_table_insert(hash_table, "insert", "value",
				 (sizeof(char) * (strlen("insert") + 1)),
				 (sizeof(char) * (strlen("value") + 1))));
	assert(hash_table->len == 16);

	assert(hash_table_destroy(hash_table, "insert"));
	assert(hash_table->len == 15);

	assert(hash_table_clear(hash_table));
	assert(hash_table_is_empty(hash_table));
	clock_t end = clock();
;
	printf("All tests passed!: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
	return EXIT_SUCCESS;
}
