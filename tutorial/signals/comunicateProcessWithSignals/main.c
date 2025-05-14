/*
! SIGUSR1
! SIGUSR2 
* Estas señales son usadas por el usuario / programador, nunca por el kernel o SO
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <sys/wait.h>
#include <sys/types.h>

int x = 0;

//Imprimimos una pista para el usuario
void handler_sigusr1(int sig){
    fprintf(stdout, "\n(Pista)\n3 * 1 = 3\n3 * 2 = 6\n3 * 3 = 9\n3 * 4 = 12\nEntonces... 3 * 5 = ");
    fflush(stdout);
}

int main(int argc, char const *argv[]) {
    pid_t pid = fork();

    if (pid == -1) {
        fprintf(stderr, "Error al crear un proceso nuevo\n");
        return -1;
    }


    //PROCESO HIJO
    if (pid == 0) {
        sleep(5);
        kill(getppid(), SIGUSR1); //Si no definimos el comportamiento de esta señal simplemente se finaliza el proceso al que estamos mandando al señal, en este caso el Proceso Padre
    //PROCESO PADRE
    } else {
        struct sigaction sa = { 0 }; // Para asegurarnos de que todos los elementos del struct se han inicializado con el valor de 0
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handler_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);

        fprintf(stdout, "Cual es el resultado de 3*5? ");
        scanf("%d", &x);
        if (x == 15) {
            fprintf(stdout, "Correcto!\n");
        } else {
            fprintf(stdout, "Incorrecto!\n");
        }
        kill(pid, SIGKILL);
        wait(NULL);
    }   

    return 0;
}
