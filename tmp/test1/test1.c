// On souhaite créer un utilitaire nommé analyseur qui surveille l'activité d'un processus ouvrier.

// Le processus Père installe un handler pour le signal SIGALRM. Il configure une alarme pour recevoir ce signal après 5 secondes.

// Le Père effectue ensuite un fork().

// Le processus Fils effectue immédiatement un recouvrement complet (exec) pour lancer un autre binaire de ton choix (par exemple /bin/ls ou un autre de tes programmes) en lui passant des arguments valides.

// Le processus Père se bloque en attente de la mort de son fils.

// Gestion de la concurrence temporelle :

// Si le fils se termine avant les 5 secondes, le père annule l'alarme, affiche "Fils terminé à temps." et s'arrête proprement.

// Si le signal SIGALRM se déclenche avant que le fils n'ait fini, le handler du père s'exécute, affiche "Temps limite dépassé !" et envoie un signal SIGKILL au fils pour le détruire. Le père récupère ensuite le statut du fils et s'arrête.
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <signal.h>



int pidfils;
void handler(int sig){
    printf("\n ALARMEEEEE");

    kill(pidfils,SIGKILL);
    exit(1);
}

int main(){
    alarm(5);
    signal(SIGALRM,&handler);
    int pid=fork();
    switch(pid){
        case -1: perror("err fork");exit(-1);
        break;
        case 0:sleep(6);execl("/bin/ls","ls",NULL);
        break;
        default:pidfils =pid;wait(NULL);alarm(0);printf("fils terminer bien ");
        break;
    }
    return 0;
}