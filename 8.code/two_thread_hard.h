#include<stdlib.h>
#include<stdio.h>
#define __USE_GNU
#include<sched.h>
#include<pthread.h>        //<pthread.h>要在<sched.h>的后面
#include<unistd.h>
#include<sys/syscall.h>
#define gettid() syscall(__NR_gettid)
#define ORANGE_MAX_VALUE      1000000
#define APPLE_MAX_VALUE       100000000
#define MSECOND               1000000
struct apple
{
    unsigned long long a;
    unsigned long long b;
};
     
struct orange
{
    int a[ORANGE_MAX_VALUE];
    int b[ORANGE_MAX_VALUE];        
};
        

int set_cpu(int i);
void* add(void* x);
int two_thread_hard () ;
