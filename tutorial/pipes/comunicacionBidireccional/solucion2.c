/*
! En esta solucion se usaran dos pipes en lugar de esparar a que termine el proceso hijo
! antes de leer nada en el proceso padre
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#include <sys/wait.h>

#define PIPE_SIZE 2

int main(int argc, char const *argv[]) {
    int p1[PIPE_SIZE]; //Pipe Hijo -> Padre (leer del hijo y escribir en el padre)
    int p2[PIPE_SIZE]; //Pipe Padre -> Hijo (leer del padre y escribir en el hijo)

    if (pipe(p1) == -1) {
        fprintf(stderr, "Error al abrir el pipe 1\n");
        return -1;
    }
    if (pipe(p2) == -1) {
        fprintf(stderr, "Error al abrir el pipe 2\n");
        return -1;
    }

    int pid = fork();

    if (pid == -1) {
        fprintf(stderr, "Error al crear un nuevo proceso\n");
        return -1;
    }

    //Proceso Hijo
    if (pid == 0) {
        close(p1[0]);
        close(p2[1]);
        int x;
        if (read(p2[0], &x, sizeof(int)) == -1) {
            fprintf(stderr, "[HIJO] Error al leer el descriptor de ficheros\n");
            return -1;
        }
        
        fprintf(stdout, "[HIJO] Recibido: %d\n", x);
        x *= 4;
        if (write(p1[1], &x, sizeof(int)) == -1) {
            fprintf(stderr, "[HIJO] Error al escribir en el pipe\n");
            return -1;
        }
        fprintf(stdout, "[HIJO] Escrito: %d\n", x);
        close(p1[1]);
        close(p2[0]);
        
    //Proceso Padre
    } else {
        close(p2[0]);
        close(p1[1]);
        srand(time(NULL));

        int y = rand() % 10;

        if (write(p2[1], &y, sizeof(int)) == -1){
            fprintf(stderr, "[PADRE] Error al escribir en el pipe\n");
            return -1;
        }
        fprintf(stdout, "[PADRE] Escrito: %d\n", y);

        if (read(p1[0], &y, sizeof(int)) == -1) {
            fprintf(stderr, "[PADRE] Error al leer del pipe\n");
            return -1;
        }
    
        fprintf(stdout, "[PADRE] Recibido %d del proceso hijo\n", y);
        
        close(p2[1]);
        close(p1[0]);
        wait(NULL);
    }
    return 0;
}