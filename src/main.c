#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#include "hash_function.h"
#include <string.h>

int main(int argc, char *argv[])
{
	HashTable *hash_table = hash_table_new();

	char *nuts = "nut";
	char *value = "value";

	printf("%lu\n", hash_table->hash_func("nutt"));
	printf("%d\n", hash_table_insert(hash_table, nuts, value));
	printf("%d\n", hash_table_insert(hash_table, "fand", "you dont even know what I have gone through"));
	printf("%d\n", hash_table_insert(hash_table, "sjweifo", "i"));
	printf("%d\n", hash_table_insert(hash_table, "efewejfi", "i"));
	printf("%d\n", hash_table_insert(hash_table, "test", "i"));
	printf("%d\n", hash_table_insert(hash_table, "test1", "i"));
	printf("%d\n", hash_table_insert(hash_table, "test2", "i"));
	printf("%d\n", hash_table_insert(hash_table, "test3", "i"));
	printf("%d\n", hash_table_insert(hash_table, "test4", "i"));
	printf("%d\n", hash_table_insert(hash_table, "test5", "i"));
	printf("%d\n", hash_table_insert(hash_table, "test6", "i"));
	printf("%d\n", hash_table_insert(hash_table, "test7", "i"));
	printf("%d\n", hash_table_insert(hash_table, "test8", "i"));
	printf("%d\n", hash_table_insert(hash_table, "test9", "i"));
	printf("%d\n", hash_table_insert(hash_table, "test10", "coollllllll"));

	printf("hash_table size: %lu\n", hash_table->size);
	{
		char *find_me = "nut";
		char *found_ya = hash_table_find(hash_table, find_me);
		if (found_ya != NULL) {
			printf("%s => %s\n", find_me, found_ya);
		} else {
			printf("Nope :<\n");
		}
	}{
		char *find_me = "fand";
		char *found_ya = hash_table_find(hash_table, find_me);
		if (found_ya != NULL) {
			printf("%s => %s\n", find_me, found_ya);
		} else {
			printf("Nope :<\n");
		}
	}{
		char *find_me = "fwejfiojweiofwej";
		char *found_ya = hash_table_find(hash_table, find_me);
		if (found_ya != NULL) {
			printf("%s => %s\n", find_me, found_ya);
		} else {
			printf("Nope: %s :<\n", find_me);
		}
	}{
		char *find_me = "test10";
		char *found_ya = hash_table_find(hash_table, find_me);
		if (found_ya != NULL) {
			printf("%s => %s\n", find_me, found_ya);
		} else {
			printf("Nope: %s :<\n", find_me);
		}
	}

	hash_table_remove(hash_table, "HI");

	return EXIT_SUCCESS;
}
