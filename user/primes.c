#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

void prime(int *fd){
    int p,d;
    close(fd[1]);//关闭写
    if((read(fd[0],&p,sizeof(p)))==0){
        fprintf(2,"Read fail\n");
        exit(1);
    }
    printf("prime %d\n",p);
    if(read(fd[0],(void*)&d,sizeof(d))){
        int fd1[2];
        pipe(fd1);
        if(fork()==0){
            prime(fd1);
        }else{
            close(fd1[0]);
            do{
                if(d % p != 0){
                    write(fd1[1],(void*)&d,sizeof(d));
            
                }
            }while(read(fd[0],(void*)&d,sizeof(d)));
            close(fd[0]);
            close(fd1[1]);
            wait(0);
        }
        
    }
    exit(0);
    
}


int main(int argc,char *argv[])
{
    int fd[2];
    pipe(fd);
    int start = 2;
    int end = 35;
    if(fork()==0){
        prime(fd);
    }else{
        close(fd[0]);
        for(int i = start;i<end;i++){
            if(write(fd[1],(void*)&i,sizeof(i)) != 4){
                fprintf(2,"Write fail\n");
                exit(1);
            }
        }
        close(fd[1]);
        wait(0);
    }
    exit(0);

}
