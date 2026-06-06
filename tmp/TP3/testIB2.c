#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
int code = 1234;



void handlerDOMMAGE(int i){
    printf("DOOOOMAGE");
    exit(1);
}

int timer(){
    sleep(10);
    kill(getppid(),  SIGUSR1);
    exit(1);
}
int testCode(int pidSon){
    int code = 1234;
    int input;
    int res;
    signal(SIGUSR1, handlerDOMMAGE);

    do {
        printf("Donnez le code : ");
        fflush(stdout); // Force l'affichage du prompt immédiatement
        
        res = scanf("%d", &input);
        
        // Si scanf échoue (lettre saisie ou interruption par signal)
        if (res != 1) {
            // On vide le tampon stdin pour éviter la boucle infinie
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            
            // Optionnel : on remet input à une valeur invalide pour continuer la boucle
            input = -1; 
        }
    } while(input != code);

    signal(SIGUSR1, SIG_IGN);
    
    kill(pidSon, SIGKILL);
    
    printf("SUCCES\n");
    return 0;
}

int main(){

    int pid =fork();
    switch(pid){
        case -1:perror("err fork");exit(1);
        break;
        case 0 : timer();
        break;
        default:testCode(pid);
        break;
    }
    return 0;



}