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

HashTable *hash_table = NULL;
char buf[32];

void init_test(void)
{
	hash_table = hash_table_new(hash_str, string_compare, string_string_destructor);
}

void print_elapsed(clock_t start, clock_t end, char *benchmark_name)
{
	printf("%s Finished: %f\n", benchmark_name, (double)(end - start) / CLOCKS_PER_SEC);
}

void insert_n(int32_t n)
{
	for (int32_t j = 0; j < 50; ++j) {
		for (int32_t i = 0; i < n; ++i) {
			sprintf(buf, "%d", i);
			hash_table_insert(hash_table, buf, buf, SIZESTR(buf), SIZESTR(buf));
		}
		hash_table_clear(hash_table);
	}
}

void insert_1000(void)
{
	init_test();
	clock_t start = clock();
	/* Insert 1_000 elements into table and clear 50 times */
	insert_n(1000);
	clock_t end = clock();

	print_elapsed(start, end, "insert_1000");
}

void insert_10000(void)
{
	init_test();
	clock_t start = clock();
	/* Insert 1_000 elements into table and clear 50 times */
	insert_n(10000);
	clock_t end = clock();

	print_elapsed(start, end, "insert_10000");
}

void insert_100000(void)
{
	init_test();
	clock_t start = clock();
	/* Insert 100_000 elements into table and clear 50 times */
	insert_n(100000);
	clock_t end = clock();

	print_elapsed(start, end, "insert_100000");
}

int main(int argc, char *argv[])
{
	insert_1000();
	insert_10000();
	insert_100000();

	return EXIT_SUCCESS;
}
