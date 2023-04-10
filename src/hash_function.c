#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

void todo(char *msg)
{
	fprintf(stderr, "%s", msg);
	exit(69);
}

size_t hash_int32(int32_t d)
{
	todo("This fucking is not implemented right.\nFuck off and maybe I'll implement it later. :D\n");
	return 1;
}

size_t hash_str(char *s)
{
	char c;
	size_t t = 37897;
	while ((c = *s++))
		t = ((t + c) << 33);

	return t;
}
