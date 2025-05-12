/*
Tenemos un array con 5 elementos cada uno de ellos enteros aleatorios del 0 al 9
Este array de 5 elementos se le envia al otro proceso el cual hara elementos * 4
Y esos 20 elementos se le envia de vuelta al primer proceso e imprimimos todo por pantalla
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include <sys/wait.h>

#define FD_SIZE 2

int main(void) {
    int *p1 = (int*)malloc(sizeof(int) * FD_SIZE);
    if (p1 == NULL) {
        fprintf(stderr, "Error al reservar memoria\n");
        return -1;
    }

    if (pipe(p1) == -1) {
        fprintf(stderr, "Error al abrir el pipe 1\n");
        return -1;
    }

    int pid = fork();

    if (pid == -1) {
        fprintf(stderr, "Error al crear un nuevo proceso\n");
        return -1;
    }
    //Proceso Hijo
    if (pid == 0) {
        int x;
        if (read(p1[0], &x, sizeof(int)) == -1) {
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
        close(p1[0]);
        close(p1[1]);
    //Proceso Padre
    } else {
        srand(time(NULL));
        int y = rand() % 10;
        if (write(p1[1], &y, sizeof(int)) == -1){
            fprintf(stderr, "[PADRE] Error al escribir en el pipe\n");
            return -1;
        }
        wait(NULL);

        if (read(p1[0], &y, sizeof(int)) == -1) {
            fprintf(stderr, "[PADRE] Error al leer del pipe\n");
            return -1;
        }
        fprintf(stdout, "[PADRE] Recibido %d del proceso hijo\n", y);
    }
    return 0;
}