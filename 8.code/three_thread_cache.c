/*三线程未加锁加cache128*/
/*apple 的两个成员 a 和 b 位于不同的 cache 行中*/
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
    char c[128];  /*32,64,128*/
    unsigned long long b;
};

void* addx(void* x)
{
    for(sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)x)->a += sum;
    }
    return NULL;
}

void* addy(void* y)
{
    for(sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)y)->b += sum;
    }  
    return NULL;
}

int main (int argc, const char * argv[]) {
    // insert code here...
    struct apple test;
    struct orange test1={{0},{0}};
    pthread_t ThreadA,ThreadB;

    pthread_create(&ThreadA,NULL,addx,&test);
    pthread_create(&ThreadB,NULL,addy,&test);
  
    for(index=0;index<ORANGE_MAX_VALUE;index++)
    {
        sum+=test1.a[index]+test1.b[index];
    }
  
     pthread_join(ThreadA,NULL);
     pthread_join(ThreadB,NULL);
  
     return 0;
}
