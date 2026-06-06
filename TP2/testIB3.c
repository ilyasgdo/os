// Écrire un source C qui se dédouble et pour lequel :

// le fils se recouvre par un nouveau processus qui exécute le programme de l'exercice I-B.1 
// auquel on passe l'argument Je suis le fils
// le père affiche Je suis le père (via la bibliothèque de l'exercice I-A).

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gestionProcessus.h"
int main(){
    int pid = fork();
    int res;
    switch(pid){
        case -1:perror("err fork ");
        break;
        case 0:  execl("./testIB1", "testIB1" , "je suis le fils", NULL); perror("err exec");exit(1);
        break;
        default : printIDS("je suis ton pere");wait(NULL);
        break;
    }
    return 0;
}
