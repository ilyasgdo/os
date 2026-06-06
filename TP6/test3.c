// Utiliser read/write pour écrire une procédure de copie de fichiers.
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
int copieFichier(){
    char buffer[9999];
    int src = open("./test3.c",O_RDONLY);
    if(src == -1){
        perror("err open src");
        exit(1);
    }
    int des = open("./des.txt",O_CREAT|O_RDWR,0644);
    if(des == -1){
        perror("err open des");
        exit(1);
    }
    int res;
    while(1){
        res = read(src,buffer,sizeof(buffer));
        if(res==-1){
            perror("err read");
            exit(1);
        }
        if(res == 0){
            break;
        }
        write(des,buffer,res);
    }
    return 0;
}

int main(){
    copieFichier();
    return 0;
}