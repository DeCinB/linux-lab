/*两线程硬亲和力*/
#include "two_thread_hard_cache.h"

int set_cpu(int i)
{
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
    if(-1 == set_cpu(1))
    {
        return NULL;
    } 
         
    for(sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)x)->a += sum;
        ((struct apple *)x)->b += sum;
    }   
    //printf("apple:sum is %d.\n",sum);
    return NULL;
}
     
int two_thread_hard_cache() {
        // insert code here...
    struct apple test;
    struct orange test1;
    int index;
    pthread_t ThreadA;
     
    cpu_nums = sysconf(_SC_NPROCESSORS_CONF);
     
    if(-1 == set_cpu(0))
    {
        return -1;
    } 
         
    pthread_create(&ThreadA,NULL,add,&test);
                 
    for(index=0;index<ORANGE_MAX_VALUE;index++)
    {
        sum1 += test1.a[index]+test1.b[index];
    }       
    //printf("orange:sum1 is %d.\n",sum1);     
    pthread_join(ThreadA,NULL);
         
    return 0;
}