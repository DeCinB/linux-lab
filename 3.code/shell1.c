#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFER_SIZE 256

int main()
{
	char buf[BUFFER_SIZE],*cmd,*argv[20];
	char c;
	int n,v,length;
	length=0;

	while(1){
		printf("shell1=>");

		c=getchar();
		while(c!='\n' && length<BUFFER_SIZE){
			buf[length++]=c;
			c=getchar();
		}

		if(length>=BUFFER_SIZE){
			printf("命令过长！请重新输入\n");
			length=0;
			continue;
		}
		else buf[length]='\0';

		cmd=strtok(buf," \t\n");//分隔出的首个为命令名
		if(cmd){
			if(strcmp(cmd,"exit")==0)
				exit(0);
			argv[0]=cmd;
			n=1;
			while(argv[n++]=strtok(NULL," \t\n"));//再次调用strtok，s指向NULL，分割出参数
			if(fork()==0){
				execvp(cmd,argv);
				fprintf(stderr, "%s command not found.\n",buf );//错误输出
				exit(1);
			}
			wait(&v);
		length=0;
		}
	}
}