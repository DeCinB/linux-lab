/*三线程加锁*/
/*计算 apple 的值（add）可以分解为两个线程（计算a，计算b）需要给apple加锁*/

#include <pthread.h>
#include "three_thread_lock.h"

void* addx(void* x)
{	int sum;
    pthread_rwlock_wrlock(&((struct apple *)x)->rwLock);    //获取写入锁  
    for(sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)x)->a += sum;
    }
    pthread_rwlock_unlock(&((struct apple *)x)->rwLock);    //释放锁
    return NULL;
}

void* addy(void* y)
{
    pthread_rwlock_wrlock(&((struct apple *)y)->rwLock);
    for(int sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)y)->b += sum;
    }
    pthread_rwlock_unlock(&((struct apple *)y)->rwLock);
    return NULL;
}

int three_thread_lock () {
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