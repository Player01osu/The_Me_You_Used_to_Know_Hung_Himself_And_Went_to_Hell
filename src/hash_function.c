#include "utils.h"
#include "hash_function.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

size_t hash_int32(int32_t d)
{
	todo("hash_int32: Not implemented");
	return 1;
}

size_t hash_str(void *p)
{
	char *s = (char *)p;
	char c;
	size_t t = 5381;
	while ((c = *s++))
		t = ((t << 5) + t) + c;

	return t;
}
