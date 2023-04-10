#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#include "hash_function.h"

int main(int argc, char *argv[])
{
	//printf("%lu\n", hash_str("hell"));
	HashTable *hash_table = hash_table_new();

	//hash_int32(2020);
	char *nuts = "nut";
	printf("%lu\n", hash_table->hash_func("nutt"));
	//hash_table_insert(hash_table, nuts);

	return EXIT_SUCCESS;
}
