#include <stdio.h>
#include <stdlib.h>

void todo(char *msg)
{
	fprintf(stderr, "%s", msg);
	exit(69);
}

