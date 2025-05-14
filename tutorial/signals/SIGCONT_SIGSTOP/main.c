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
        while (1) {
            fprintf(stdout, "[HIJO] Test test\n");
            usleep(50000);
        }
    //Proceso Padre
    } else {
        kill(pid, SIGSTOP);
        fprintf(stdout, "[PADRE] Acabo de detener el proceso hijo\n");
        sleep(1);
        kill(pid, SIGCONT);
        sleep(1);
        kill(pid, SIGKILL);
        wait(NULL);
    }


    return 0;
}
