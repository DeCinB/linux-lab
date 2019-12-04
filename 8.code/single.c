#include "single.h"

int single()
{     
	struct apple test;  
	struct orange test1;    
	for(int sum=0;sum<APPLE_MAX_VALUE;sum++)  
	{

	   test.a += sum;   
	   test.b += sum;  
	}
	
	int sum=0;  

	for(int index=0;index<ORANGE_MAX_VALUE;index++)
	{
	   sum += test1.a[index]+test1.b[index]; 
 	} 

    return 0; 
 } 
