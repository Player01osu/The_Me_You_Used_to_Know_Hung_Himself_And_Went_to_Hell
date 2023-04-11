#include <stdio.h>
#include <stdlib.h>

void todo(char *msg)
{
	fprintf(stderr, "%s", msg);
	exit(69);
}

// TODO
void dbg(char *s)
{
#ifdef DEBUG
	printf("%s\n", s);
#endif /* ifdef DEBUG */
}

