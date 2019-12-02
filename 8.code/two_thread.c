#include "test.h"
void* add(void* x)
{       
	int sum;
    for( sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)x)->a += sum;
        ((struct apple *)x)->b += sum;   
    }
    //printf("apple:sum is %d.\n",sum);
    return NULL;
}
     
int two_thread () {
        // insert code here...
    struct apple test;
    struct orange test1={{0},{0}};
    int index;

    pthread_t ThreadA;                           //线程标识符
         
    pthread_create(&ThreadA,NULL,add,&test);     //标识符，线程属性，执行函数，函数参数
    int sum;
    for(index=0;index<ORANGE_MAX_VALUE;index++)
    {
        sum += test1.a[index]+test1.b[index];
    }       
   	//	printf("orange:sum is %d.\n",sum);
 
    pthread_join(ThreadA,NULL);                //等待线程结束（标识符，返回值），阻塞式
 
    return 0;
}