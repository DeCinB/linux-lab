/*三线程未加锁加cache128*/
/*apple 的两个成员 a 和 b 位于不同的 cache 行中*/
#include "three_thread_cache.h"
void* addx(void* x)
{
    for(int sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)x)->a += sum;
    }
    return NULL;
}

void* addy(void* y)
{
    for(int sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)y)->b += sum;
    }  
    return NULL;
}

int three_thread_cache () {
    // insert code here...
    struct apple test;
    struct orange test1={{0},{0}};
    pthread_t ThreadA,ThreadB;

    pthread_create(&ThreadA,NULL,addx,&test);
    pthread_create(&ThreadB,NULL,addy,&test);
  
  	int sum;
    for(int index=0;index<ORANGE_MAX_VALUE;index++)
    {
        sum+=test1.a[index]+test1.b[index];
    }
  
     pthread_join(ThreadA,NULL);
     pthread_join(ThreadB,NULL);
  
     return 0;
}