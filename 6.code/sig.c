#include <linux/unistd.h>
#include <stdio.h>
#include <stdlib.h>


#define EVENTSIG 442

int main(int argc, char ** argv)
{
	int i = 3;
	if (argc != 2)
	{
		return -1;
	}

	syscall(EVENTSIG, atoi(argv[1]));
	printf("%d\n", i);
	return 1;
}
