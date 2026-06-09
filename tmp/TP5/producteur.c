#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "test.h"


int main(){
    int * tab;

    int pid=fork();

    switch(pid){
        case -1:perror("err fork");exit(1);
        break;
        case 0:execl("./consomateur","consomateur",NULL);
        break;
        default: producteur(tab); wait(NULL);
        break;


    }
    reset();
    return 0;
}