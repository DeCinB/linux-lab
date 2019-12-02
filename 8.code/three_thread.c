/*三线程未加锁程序*/
/*三线程未加锁程序*/
/*计算 apple 的值（add）分解为两个线程（计算a，计算b）*/
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

void* addx(void* x)
{	int sum;
    for(sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)x)->a += sum;
    }
    return NULL;
}
 
void* addy(void* y)
{	int sum;
    for(sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)y)->b += sum;
    }  
    return NULL;
}
 
 
 
int three_thread() {
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