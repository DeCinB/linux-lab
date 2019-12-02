#include<stdlib.h>
#include<stdio.h>

#define __USE_GNU
#include<sched.h>
#include<pthread.h>

#include<unistd.h>
#include<sys/syscall.h>
#define gettid() syscall(__NR_gettid)

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
    char c[128];                //32,64,128或__attribute__((__aligned__(L1_CACHE_BYTES)))
    unsigned long long b;
};

int sum,sum1;
int cpu_nums;
cpu_set_t mask;
int set_cpu(int i);
void* addx(void* x);
void* addy(void* y);
int three_thread_hard_cache ();