#include <stdio.h>
#include <stdlib.h>

typedef struct s {
	void *p;
} wat;

int main(int argc, char const *argv[])
{
	puts("doin a leak");
	wat thefuk;
	thefuk.p = malloc(1000);
	return 0;
}