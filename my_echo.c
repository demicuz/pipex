#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	// int fd[2];
	// pipe(fd);
	for (int i = 0; i < argc; ++i)
	{
		printf("argv[%d] : %s\n", i, argv[i]);
	}
	// printf("%zd\n", sizeof(int[2]));
	return 0;
}
