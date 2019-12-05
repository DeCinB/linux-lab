#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
main()
{
    int hd;
    char buf[256];
    char *buf2,*buf3,*cmd,*cmd2,*cmd3,*argv[64],*argv2[64],*argv3[64];
    int n,sv,fd[2];
    for(;;) {
        printf("=> ");
        if(fgets(buf,sizeof(buf),stdin)==NULL) exit(0);
        buf2=strstr(buf,"|");
        buf3=strstr(buf, ">");
        if (buf2)
            *buf2++='\0';
        if(buf3)
            *buf3++='\0';
        cmd=strtok(buf," \t\n");     
        if (cmd) {
            if (strcmp(cmd,"exit") == 0 ) exit(0);
            n=0;
            argv[n++]=cmd;
            while(argv[n++]=strtok(NULL," \t\n"));}
        else exit(1);
        if (buf2){ 
            cmd2=strtok(buf2," \t\n");   
            n=0;
            argv2[n++]=cmd2;
            while(argv2[n++]=strtok(NULL," \t\n"));}
        if (buf3){
            cmd3=strtok(buf3," \t\n");
            n=0;
            argv3[n++]=cmd3;
            while(argv3[n++]=strtok(NULL," \t\n"));}
        if (!cmd2){
            if (fork() == 0) {
                execvp(cmd,argv);
                fprintf(stderr," ******ERROR******:  %s\n",strerror(errno));
                exit(1);
                }
            wait(&sv);
           }
        else {
            pipe(fd);    
            if(fork()==0) {
                hd=-1; 
                dup2(fd[0],0);
                if (cmd3) hd=open(cmd3, O_CREAT|O_WRONLY,0666);
                if (hd != -1 ) dup2(hd,1);
                close(fd[0]);  
                close(fd[1]);
                close(hd);
                execvp(cmd2,argv2);
                fprintf(stderr,"  ******ERROR******:   %s\n",strerror(errno)); exit(1);
               } 
            else if(fork()==0) { 
                dup2(fd[1],1);
                close(fd[0]);  
                close(fd[1]);
                execvp(cmd,argv);
                fprintf(stderr,"  ******ERROR******:   %s\n",strerror(errno)); exit(1);
               } 
            close(fd[0]); close(fd[1]);
            wait(&sv);  wait(&sv);
         
         }   
     }
 }

