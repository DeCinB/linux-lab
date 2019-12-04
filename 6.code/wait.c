#include <linux/unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define EVENTWAIT 441


int main(int argc, char ** argv)
{
	int i;
	if (argc != 2)
	{
		return -1;
	}

	i = syscall(EVENTWAIT, atoi(argv[1]));
	printf("wait : %d\n", i);
	return 1;
}
