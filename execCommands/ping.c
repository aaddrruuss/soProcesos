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
        execlp("ping", "ping", "-c", "3", "google.com", NULL);
    } else {
        wait(NULL);
        fprintf(stdout, "Success!\n");        
    }


    return 0;
}
