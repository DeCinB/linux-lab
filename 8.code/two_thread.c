/*两线程*/
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

int sum,sum1;

void* add(void* x)
{       
    for(sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)x)->a += sum;
        ((struct apple *)x)->b += sum;   
    }
    printf("apple:sum is %d.\n",sum);
    return NULL;
}
     
int main (int argc, const char * argv[]) {
        // insert code here...
    struct apple test;
    struct orange test1={{0},{0}};
    int index;
    pthread_t ThreadA;                           //线程标识符
         
    pthread_create(&ThreadA,NULL,add,&test);     //标识符，线程属性，执行函数，函数参数
         
    for(index=0;index<ORANGE_MAX_VALUE;index++)
    {
        sum += test1.a[index]+test1.b[index];
    }       
    printf("orange:sum1 is %d.\n",sum1);
 
    pthread_join(ThreadA,NULL);                //等待线程结束（标识符，返回值），阻塞式
 
    return 0;
}
