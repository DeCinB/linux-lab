
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

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

void* add(void* x);
int two_thread ();