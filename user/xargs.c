#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include  "kernel/param.h"

void copy(char**p1,char* p2){
    *p1 = malloc(strlen(p2)+1);
    strcpy(*p1,p2);
}
/*
int readLine(char** pars,int i){//把标准输入或者管道传参 接到argv后面
    int d = 1024;
    char buf[d];
    int j =0;
    while(read(0,buf+j,1)){//从标准输入读取一个字符到buf中
        if(buf[j] == '\n'){//根据\n进行划分
            buf[j] =0;
            break;
        }
        j++;
        if(j >= d){
            fprintf(2,"parameters are too long!\n");
            exit(1);
        }
    }

    if(j == 0){
        return -1;
    }

    // 按照空格划分
    int k=0;
    while(k < j){
        if(i > MAXARG){
            fprintf(2,"too much parameters!\n");
            exit(1);
        }

        //跳过多余的空格
        while((k < j) && buf[k] == ' '){
            k++;
        }

        int l =  k;

        //读取一个参数，读到空格就结束ex:  para</end> parb 
        while((k < j) && (buf[k] != ' ')){
            k++;
        }
        buf[k++] = 0;
        copy(&pars[i],buf+l);//加入到参数列表中
        i++;//参数个数+1；
    }

    return i;//参数个数
}
*/

int readLine(char** pars,int i){
    int maxSize = 1024;
    char buf[maxSize];
    int j = 0;
    while(read(0,buf+j,1)){
        if(buf[j] == '\n'){//按行读取
            buf[j] = 0;
            break;
        }
        j++;
        if(j >= maxSize){
            fprintf(2,"Parameters are too long!\n");
            exit(1);
        }
    }

    if(j == 0){
        return -1;//结束了
    }

    int k=0;
    while(k<j){//每一行根据空格划分命令
        if(i > MAXARG){
            fprintf(2,"Too much parateters!\n");
            exit(1);
        }

        while((k<j) && (buf[k] == ' ')){
            k++;
        }

        int s = k;//start

        while((k<j) && buf[k] !=' '){
            k++;
        }
        buf[k++] = 0;
        copy(&pars[i],buf+s);// copy buf[s,j] to pars; 
        i++;
    }
    return i;


}


// xargs grep hello b 
// 0:xargs 1:grep 2:hello 3:b
int main(int argc,char* argv[])
{
    if(argc < 2){
        printf("Please enter more parameters!\n");
        exit(1);
    }
    else{
        int i;
        char *pars[MAXARG];
        for(i=1; i<argc; i++){
            copy(&pars[i-1],argv[i]);
        }
        int end;
        while((end = readLine(pars,i-1)) != -1){
            pars[end] = 0;
            if(fork() == 0){
                exec(pars[0],pars);
                exit(1);
            }else{
                wait(0);
            }
        }

   
        exit(0);


    }

   


}