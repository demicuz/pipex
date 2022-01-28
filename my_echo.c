#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	for (int i = 0; i < argc; ++i)
	{
		printf("argv[%d] : %s\n", i, argv[i]);
	}
	char *buffer = malloc(sizeof(char) * 1000);
	int ret = read(0, buffer, 999);
	if (ret > 0)
	{
		puts("Whoa, I've read something from stdin!");
		buffer[ret] = '\0';
		puts(buffer);
	}
	free(buffer);
	return 0;
}
