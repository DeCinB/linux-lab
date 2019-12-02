/*三线程未加锁硬亲和力*/
#include<pthread.h>
#include<sched.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/sysinfo.h>
#include<unistd.h>
#include<ctype.h>

#define __USE_GNU 
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


inline int set_cpu(int i)
{
    cpu_set_t  mask;
  
    CPU_ZERO(&mask);  //宏函数，对CPU集mask进行初始化将其设置为空集
    if(2 <= cpu_nums)
    {
        CPU_SET(i,&mask); //宏函数，将指定的CPU i加入CPU集mask中
         
        if(-1 == sched_setaffinity(gettid(),sizeof(&mask),&mask))   //绑定进程和CPU
        {
            fprintf(stderr, "pthread_setaffinity_np erro\n");
            return -1;
        }
    }
    return 0;
}


void* addx(void* x)
{
    if(-1 == set_cpu(1))
    {
        return NULL;
    } 
       
    for(sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)x)->a += sum;
    }
    return NULL;
}
void* addy(void* y)
{
    if(-1 == set_cpu(2))
    {
        return NULL;
    } 
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
  
    int cpu_nums = sysconf(_SC_NPROCESSORS_CONF);//获取cpu个数
    if(-1 == set_cpu(0))
    {
        return -1;
    } 
  
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
