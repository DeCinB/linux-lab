/*两线程硬亲和力*/
#include "two_thread_hard.h"

int set_cpu(int i)
{
    int cpu_nums;
    cpu_set_t mask;
    
    cpu_nums = sysconf(_SC_NPROCESSORS_CONF);
    CPU_ZERO(&mask);
     
    if(2 <= cpu_nums)
    {
        CPU_SET(i,&mask);
         
        if(-1 == sched_setaffinity(gettid(),sizeof(&mask),&mask))
        {
            return -1;
        }
    }
    return 0;
}
 
     
void* add(void* x)
{
    int sum;
    if(-1 == set_cpu(1))
    {
        return NULL;
    } 
         
    for(sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)x)->a += sum;
        ((struct apple *)x)->b += sum;
    }   

    return NULL;
}
     
int two_thread_hard () {
    int sum;
    struct apple test;
    struct orange test1;
    int index;
    pthread_t ThreadA;
     
    if(-1 == set_cpu(0))
    {
        return -1;
    } 
         
    pthread_create(&ThreadA,NULL,add,&test);
                 
    for(index=0;index<ORANGE_MAX_VALUE;index++)
    {
        sum += test1.a[index]+test1.b[index];
    }       

    pthread_join(ThreadA,NULL);
         
    return 0;
}
