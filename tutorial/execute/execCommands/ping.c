/*
! Como ejecutar comandos de bash desde C
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/wait.h>

int main (int argc, char **argv) {
    int pid = fork();

    if (pid == -1) {
        fprintf(stderr, "Error al crear un proceso nuevo\n");
        return -1;
    }
    if (pid == 0) {
        int err;
        err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
        perror("execvp");
        exit(-1);
    } else {
        int wstatus;
        wait(&wstatus);
        if (WIFEXITED(wstatus)) {
            int statusCode = WEXITSTATUS(wstatus);
            if (statusCode == 0) {
                fprintf(stdout, "Programa ejecutado correctamente\n");
            } else {
                fprintf(stderr, "Error al ejecutar el programa. Error: %d\n", statusCode);
            }
        }     
    }


    return 0;
}





