#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#define CODE 1234

void  handlerDomage(int p ){
    printf("\nDOMMAGE\n");
    exit(1);

}
int timer(int pid){
    sleep(10);
    kill(pid, SIGUSR1);
    exit(1);
}
int getCode(){
    signal(SIGUSR1,&handlerDomage);
    int s;
    do{
        printf("\ndonnez le code\n");
        scanf("%d",&s);

    }while(s!=CODE);
    signal(SIGUSR1,SIG_IGN);
    printf("\n\nbravo le code est bon ");
    return 0;
    
}

int main(){
    int pidPERE=getpid();
    int pid=fork();
    
    switch(pid){
        case -1: perror("err fork");exit(1);
        break;
        case 0 : timer(pidPERE);
        break;
        default : getCode();
        break;
    }
    return 0;
}