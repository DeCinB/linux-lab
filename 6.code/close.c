#include <linux/unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define EVENTCLOSE 440

int main(int argc, char ** argv)
{
	int i;
	if (argc != 2)
	{
		return -1;
	}

	syscall(EVENTCLOSE, atoi(argv[1]));
	printf("close : %d\n", i);
	return 1;
}
