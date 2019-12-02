/*三线程未加锁程序*/
/*计算 apple 的值（add）可以分解为两个线程（计算a，计算b）需要给apple加锁*/
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
    pthread_rwlock_t rwLock;        //读写锁（读写者模式），相比互斥量允许更高的并行性
};

void* addx(void* x)
{
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
    for(sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)y)->b += sum;
    }
    pthread_rwlock_unlock(&((struct apple *)y)->rwLock);
     
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
