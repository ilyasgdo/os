//Utiliser read/write pour écrire une procédure de copie de fichiers.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 #include <fcntl.h>



 int copieFichier(){
    char buffer[99];
    int src =open("test3.c",O_RDWR);
    int des =open("des.txt",O_RDWR|O_TRUNC|O_CREAT,0644);
    int res;
    while(1){
        res= read(src,buffer,sizeof(buffer));
        if(res==-1){
            perror("err read");
            exit(1);
        }
        if(res==0){
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