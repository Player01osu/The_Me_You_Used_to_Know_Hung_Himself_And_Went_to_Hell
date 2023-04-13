#ifndef HASHFUNCTION
#define HASHFUNCTION

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

size_t hash_int32(int32_t d);

size_t hash_str(void *s);

#endif // !HASHFUNCTION
