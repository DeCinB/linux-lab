/*三线程未加锁硬亲和力*/
#include "three_thread_hard_cache.h"

int set_cpu(int i)
{
    int cpu_nums = sysconf(_SC_NPROCESSORS_CONF);//获取cpu个数
    cpu_set_t  mask;
  
    CPU_ZERO(&mask);  //宏函数，对CPU集mask进行初始化将其设置为空集
    if(2 <= cpu_nums)
    {
        CPU_SET(i,&mask); //宏函数，将指定的CPU i加入CPU集mask中
         
        if(-1 == sched_setaffinity(gettid(),sizeof(&mask),&mask))   //绑定进程和CPU
        {
            //fprintf(stderr, "pthread_setaffinity_np erro\n");
            return -1;
        }
    }
    return 0;
}


void* addx(void* x)
{
    int sum;
    if(-1 == set_cpu(0))
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
    int sum;
    if(-1 == set_cpu(1))
    {
        return NULL;
    } 
    for(sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)y)->b += sum;
    }  
    return NULL;
}

int three_thread_hard_cache () {
    int sum;
    struct apple test;
    struct orange test1={{0},{0}};
    pthread_t ThreadA,ThreadB;
  
    if(-1 == set_cpu(2)){
   	return -1;
  
    } 

    pthread_create(&ThreadA,NULL,addx,&test);
    pthread_create(&ThreadB,NULL,addy,&test);

    for(int index=0;index<ORANGE_MAX_VALUE;index++)
    {
        sum += test1.a[index]+test1.b[index];
    }

     pthread_join(ThreadA,NULL);
     pthread_join(ThreadB,NULL);
  
     return 0;
}
