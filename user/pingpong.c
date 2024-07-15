#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

int main(int argc,char const* argv[])
{
    int p[2];
    char buf[1];
    char parmsg = 'i';
    char chilmsg = 'o';
    pipe(p);
    if(fork() == 0){
        if(read(p[0],buf,1) != 1){
            fprintf(2,"child read error\n");
            exit(1);
        }
        
        fprintf(1,"child receive:%c\n",buf[0]);
        close(p[0]);

        fprintf(1,"%d: received ping\n",getpid());

        if(write(p[1],&chilmsg,1) != 1){
            fprintf(2,"child write error\n");
            exit(1);
        }
        close(p[1]);
        exit(0);
    }else{
        if(write(p[1],&parmsg,1) != 1){
            fprintf(2,"parent write error\n");
            exit(1);
        }
        close(p[1]);
        wait(0);

        if(read(p[0],buf,1) != 1){
            fprintf(2,"parent read error\n");
            exit(1);
        }

        fprintf(1,"parent receive:%c\n",buf[0]);
        close(p[0]);
        fprintf(1,"%d: received pong\n",getpid());
        exit(0);

    }
}










// int main(int argc,char const* argv[])
// {
//     int fd_f2c[2];
//     int fd_c2f[2];
//     pipe(fd_f2c);
//     pipe(fd_c2f);
//     int pid = fork();
//     int exit_status = 0;

//     char buf = 'P';

//     if(pid == 0)
//     {//子进程
//         close(fd_f2c[1]);
//         close(fd_c2f[0]);

//         if(read(fd_f2c[0],&buf,sizeof(char)) != sizeof(char))
//         {
//             fprintf(2,"child read error!\n");
//             exit_status = 1;
//         }
//         else
//         {
//             fprintf(1,"%d,child received ping\n",getpid());
//         }

//         if(write(fd_c2f[1],&buf,sizeof(char)) != sizeof(char))
//         {
//             fprintf(2,"child write error!\n");
//             exit_status = 1;
//         }
        
//         close(fd_f2c[0]);
//         close(fd_c2f[1]);
        
//         exit(exit_status);
//     }else{
//         close(fd_f2c[0]);
//         close(fd_c2f[1]);

//         if(write(fd_f2c[1],&buf,sizeof(char)) != sizeof(char))
//         {
//             fprintf(2,"parent write error!\n");
//             exit_status = 1;
//         }
        
//         if(read(fd_c2f[0],&buf,sizeof(char)) != sizeof(char))
//         {
//             fprintf(2,"parent read() error!\n");
//             exit_status = 1;
//         }
//         else{
//             fprintf(1,"%d,parent received pong\n",getpid());
//         }

//         close(fd_f2c[1]);
//         close(fd_c2f[0]);
        
      
//         exit(exit_status);

//     }

    
//     // close(p[0]);
// }