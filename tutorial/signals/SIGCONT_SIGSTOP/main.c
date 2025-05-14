#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>

#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>

int main(int argc, char const *argv[]) {
    int pid = fork();

    if(pid == -1) {
        fprintf(stderr, "Error al crear un nuevo proceso\n");
        return -1;
    }

    //Proceso Hijo
    if (pid == 0) {
        int i = 0;
        while (1) {
            fprintf(stdout, "[HIJO - %d] Test test\n", i);
            usleep(50000);
            i++;
        }
    //Proceso Padre
    } else {
        int t;
        kill(pid, SIGSTOP);
        fprintf(stdout, "[PADRE] Acabo de detener el proceso hijo\n");
        do {
            fprintf(stdout, "Introduce segundos que quieres que dure la ejecucion del proceso hijo: \n");
            scanf("%d", &t);
            if (t > 0) {
                kill(pid, SIGCONT);
                sleep(t);
                kill(pid, SIGSTOP);
            }
        } while (t > 0);
        kill(pid, SIGKILL);
        wait(NULL);
    }


    return 0;
}
