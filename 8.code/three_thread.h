#include <pthread.h>

#define ORANGE_MAX_VALUE      1000000
#define APPLE_MAX_VALUE       100000000
#define MSECOND               1000000

struct orange
{
    int a[ORANGE_MAX_VALUE];
    int b[ORANGE_MAX_VALUE];
     
};
struct apple
{
    unsigned long long a;
    unsigned long long b;
};

void* addx(void* x);
void* addy(void* y);
int three_thread();