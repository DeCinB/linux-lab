/*两线程*/
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

void* add(void* x)
{       
    for(sum=0;sum<APPLE_MAX_VALUE;sum++)
    {
        ((struct apple *)x)->a += sum;
        ((struct apple *)x)->b += sum;   
    }
         
    return NULL;
}
     
int main (int argc, const char * argv[]) {
        // insert code here...
    struct apple test;
    struct orange test1={{0},{0}};
    pthread_t ThreadA;
         
    pthread_create(&ThreadA,NULL,add,&test);
         
    for(index=0;index<ORANGE_MAX_VALUE;index++)
    {
        sum += test1.a[index]+test1.b[index];
    }       
     
     pthread_join(ThreadA,NULL);
 
    return 0;
}
