#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h> // Ajout indispensable pour wait()
#include "gestionFichier.h"

int serverA(int * canal){
    close(canal[0]);
    char * buffer;
    int des = open("testIB1.c", O_RDONLY);
    int res;
    if(des == -1){
        perror("err open ");
        close(canal[1]);
        exit(1);
    }
    
    while(1){
        buffer = litLigne(des);
        if(buffer == NULL){
            break; // Fin du fichier
        }
        
        res = write(canal[1], buffer, strlen(buffer));
        if(res == -1){
            perror("err write A  ");
            free(buffer);
            exit(1);
        }
        
        free(buffer); // CORRECTION : Libère la ligne actuelle avant de lire la suivante !
    }

    close(des);
    close(canal[1]); // On ferme pour signaler la fin à serverB
    return 0;
}

int serverB(int * canal){
    int des = open("dest.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if(des == -1){
        perror("err open dest.txt");
        close(canal[0]);
        exit(1);
    }
    
    close(canal[1]);
    char buffer[1024];
    int resR;
    
    while(1){
        resR = read(canal[0], buffer, sizeof(buffer));
        if(resR == -1){
            perror("err write B ");
            close(des);
            exit(1);
        }
        if(resR == 0){ 
            break; // CORRECTION : Plus de 'x' parasite ici
        }
        if (write(des, buffer, resR) == -1) {
            perror("err write dest.txt");
            close(des);
            exit(1);
        }
    }
    
    close(des);
    close(canal[0]);
    return 0;
}

int main(){
    int canal[2];
    int pid;
    
    if (pipe(canal) == -1) {
        perror("err pipe");
        return 1;
    }
    
    pid = fork();
    switch(pid){
        case -1:
            perror("err fork");
            exit(1);
            break;
        case 0: 
            serverB(canal);
            break;
        default:
            serverA(canal);
            wait(NULL); // Attente propre du fils
            break;
    }
    return 0;
}