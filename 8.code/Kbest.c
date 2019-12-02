/*Kbest测量程序*/
#include<stdio.h>
#include <sys/time.h>
#include <unistd.h> 
#include "three_thread_cache.h"

#define K 10
#define EP 0.02
#define M 200
#define MSECOND 1000000

double ktime[K+1];


int main(int argc, char const *argv[])
{
	/* code */

	struct timeval begin,end;
	int n=0;
	double used=0.0;
	for(int i=0;i<=K;i++)
		ktime[i]=1000000000.0;

	while(n<M){

		gettimeofday(&begin,NULL);
		three_thread_cache();
		gettimeofday(&end,NULL);
	
		used=MSECOND * (end.tv_sec - begin.tv_sec) + end.tv_usec - begin.tv_usec;
		n++;
		//printf("第%d次用时%lf微秒\n",n,used);

		if(used<ktime[K-1])//如果最新测量的时间小于第K快
		{	
			printf("第%d次用时%lf微秒小于第K快%lf微妙\n",n,used,ktime[K-1]);
			int j=K-1;
			for (j;j>=0;j--)//插入到相应位置
			{
				if(used<ktime[j])
				{
					ktime[j+1]=ktime[j];

				}
				else
					break;
			}
			ktime[j+1]=used;


			int flag=0;//是否收敛
			if(n>=K)
			{	
				flag=1;
				for(int i=0;i<K-1;i++)
				{	
					printf("第%d快乘后为%lf微秒,第K快为%lf微秒\n", i,ktime[i]*(1+EP),ktime[K-1]);
					if(ktime[i]*(1+EP)<ktime[K-1])
					{
						flag=0;
						break;
					}
				}
			}

			if(flag){
				double avg=0.0;
				for(int i=0;i<K;i++)
				{
					avg+=ktime[i];
				}
				avg/=K;
				printf("n=%d,最快%lf微秒\n",n,avg);
				return 0;
			}
		}
	}
	double avg=0.0;
	for(int i=0;i<K;i++)
		{
			avg+=ktime[i];
		}
	avg/=K;
	printf("n=%d,最快%lf微秒\n",n,avg);
	return 0;
}
