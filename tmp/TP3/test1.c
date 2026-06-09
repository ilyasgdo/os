#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
int serverA(int * T){
    close(T[0]);
    char buffer[100];
    int src = open("test1.c",O_RDONLY);
    if(src == -1){
        perror("err open");
        exit(1);
    }
    int res;
    while(1){
        res = read(src,buffer,sizeof(buffer));
        if(res==-1){
            perror("err read A");
            close(T[1]);
            exit(1);
        }
        if(res==0){
            break;
        }
        write(T[1],buffer,res);
    }
    close(T[1]);
    close(src);
    return 0;

}
int serverB(int * T){
    int des = open("des.txt",O_RDWR|O_CREAT,0644);
    char buffer[100];
    close(T[1]);
    int res;
    if(des == -1){
        perror("err open des");
        exit(1);
    }
    while(1){
        res = read(T[0],buffer,sizeof(buffer));
        if(res==-1){
            perror("err read B");
            close(T[0]);
            exit(1);
        }
        if(res==0){
            close(T[0]);
            break;
        }
        write(des,buffer,res);

    }
    close(des);
    return 0;

}
int main(){
    int letube[2];
    int res = pipe(letube);
    if(res==-1){
        perror("err pipe");
        exit(1);
    }
    int pid = fork();

    switch(pid){
        case -1 : perror("err fork");exit(1);
        break;
        case 0 : serverB(letube);
        break;
        default : serverA(letube); wait(NULL);
        break;
    }
    return 0;

}