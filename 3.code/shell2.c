#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#define BUFFER_SIZE 256


int main()
{
	
	char buf1[BUFFER_SIZE];
	char *buf2,*buf3,*buf4;
	char *cmd1,*cmd2,*outfile,*infile;
	char *argv1[20],*argv2[20];
	int n,v,fd[2];
	int fdin=-1,fdout=-1;

	while(1){
		cmd1=NULL;
		cmd2=NULL;
		outfile=NULL;
		infile=NULL;
		buf2=NULL;
		buf3=NULL;
		buf4=NULL;
		printf("shell2=>");

		if(fgets(buf1,sizeof(buf1),stdin)==NULL) exit(0);
		//printf("%s\n",buf1);

		buf2=strstr(buf1,"|");
		buf3=strstr(buf1,">");
		buf4=strstr(buf1,"<");


		if(buf2) *buf2++='\0';
		if(buf3) *buf3++='\0';
		if(buf4) *buf4++='\0';

		//printf("%s,%s,%s\n",buf2,buf3,buf4);

		cmd1=strtok(buf1," \t\n");//分隔出的首个为命令名
		if(cmd1){
			//printf("首个指令%s\n",cmd1);
			if(strcmp(cmd1,"exit")==0)
				exit(0);
			argv1[0]=cmd1;
			n=1;
			while(argv1[n++]=strtok(NULL," \t\n"));//再次调用strtok，s指向NULL，分割出参数
		}
		else exit(1);

		if(buf2)//管道
		{	//printf("管道已发现");
			cmd2=strtok(buf2," \t\n");
            argv2[0]=cmd2;
            n=1;
			while(argv2[n++]=strtok(NULL," \t\n"));
		}
		if(buf3)//输出定向
		{	//printf("输出定向已发现");
			outfile=strtok(buf3," \t\n");
			//printf("%s\n",outfile);
			fdout=open(outfile,O_WRONLY | O_CREAT);
		}
		
		if(buf4)//输入定向
		{	//printf("输入定向已发现");
			infile=strtok(buf4," \t\n");
			//printf("%s\n",infile );
			fdin=open(infile,O_RDONLY);
		}
		
		

		if(!cmd2){//无需管道
			//printf("无管道\n" );
			if(fork()==0){
				
				if(outfile) {
					//printf("定向输出\n");
					dup2(fdout,1);}
				if(infile) {
					//printf("定向输入\n");
					dup2(fdin,0);}
				close(fdout);
				close(fdin);
				//printf("执行首个命令\n");
				execvp(cmd1,argv1);
				fprintf(stderr, "%s command not found.\n",buf1);//错误输出
				exit(1);
			}
			wait(&v);
		}
		else{//管道
			//printf("%s\n",cmd2);
			pipe(fd);
			if (fork()==0){
				dup2(fd[0],0);//fd[0]复制到描述符0
				if(outfile) dup2(fdout,1); 
				close(fd[0]);
				close(fd[1]);
				close(fdout);
				execvp(cmd2,argv2);
				fprintf(stderr, "%s command not found.\n",buf2);
			}
			else if(fork()==0){
				dup2(fd[1],1);
				if(infile) dup2(fdin,0);
				close(fd[0]);
				close(fd[1]);
				close(fdin);
				execvp(cmd1,argv1);
				fprintf(stderr, "%s command not found.\n",buf1);
			}
			close(fd[0]);close(fd[1]);
			wait(&v);wait(&v);
		}
	}
}