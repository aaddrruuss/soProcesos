/*
! Como ejecutar comandos de bash desde C
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <sys/wait.h>

int main (int argc, char **argv) {
    int pid = fork();

    if (pid == -1) {
        fprintf(stderr, "Error al crear un proceso nuevo\n");
        return -1;
    }
    //Proceso Hijo
    if (pid == 0) {
        int file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777); //O_WRONLY -> indica que solo queremos escribir | O_CREAT -> crear el fichero si no existe, 0777 -> todos los permisos para el fichero
        if (file == -1) {
            fprintf(stderr, "Error al abrir / crear fichero\n");
            return -1;
        }
        int file2 = dup2(file, STDOUT_FILENO);
        close(file);
        int err;
        err = execlp("pinasfsafg", "ping", "-c", "3", "google.com", NULL);
        perror("execvp");
        exit(-1);

    // Proceso Padre
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





