#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

int main(void) {
    int id = fork();
    if (id == 0) {
        sleep(1);
    }
    
    if (id == 0) {
        printf("Proceso hijo:\nCurrent ID: %d\n Parent ID: %d\n", getpid(), getppid());
    }else {
        printf("Proceso padre:\nCurrent ID: %d\n Parent ID: %d\n", getpid(), getppid());
    }

    int waitResult = wait(NULL);
    if (waitResult == -1){
        printf("No hay ningun hijo al que esperar que termine su ejecucion\nSaliendo...\n");
    }else{
        printf("%d ha terminado de ejecutarse\n", waitResult);
    }
    return 0;
}
