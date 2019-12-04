#include <linux/unistd.h>
#include <stdio.h>
#include <stdlib.h>


#define EVENTSHOW 443

int main(int argc, char ** argv)
{
	syscall(EVENTSHOW);
	return 1;
}
