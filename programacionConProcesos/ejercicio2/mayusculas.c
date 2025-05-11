#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define FD_SIZE 2
#define SIZE_BUFFER 1024
#define DIFF_MAYUS_MINUS 32

int main(int argc, char const *argv[]) {
    int *p1 = (int*)malloc(sizeof(int) * FD_SIZE); // HIJO -> PADRE (PADRE LEE, HIJO ESCRIBE)
    int *p2 = (int*)malloc(sizeof(int) * FD_SIZE); // PADRE -> HIJO (HIJO LEE, PADRE ESCRIBE)
    int numberBytes;
    int i;
    char *buffer = (char*)malloc(sizeof(char) * SIZE_BUFFER);
    
    
   

    if (pipe(p1) == -1) {
        fprintf(stderr, "Error al crear el pipe 1\n");
        return -1;
    }
    if (pipe(p2) == -1) {
        fprintf(stderr, "Error al crear el pipe 2\n");
        return -1;
    }
    
    // ! MUY IMPORTANTE CREAR LOS PIPES ANTES QUE LOS PROCESOS
    int id = fork();

    if (id == -1) {
        fprintf(stderr, "Error al crear proceso hijo");
        return -1;
    }
    //Proceso hijo
    if (id == 0) {
        close(p1[0]);
        close(p2[1]);
        while ((numberBytes = read(p2[0], buffer, SIZE_BUFFER)) > 0) {
            if (numberBytes == -1) {
                fprintf(stderr, "[Hijo] Error al leer del pipe\n");
                return -1;
            }
            for (i = 0 ; i < numberBytes ; i++) {
                if (buffer[i] >= 'a' && buffer[i] <= 'z') {
                    buffer[i] -= DIFF_MAYUS_MINUS;
                }
            }
            if (write(p1[1], buffer, SIZE_BUFFER) == -1) {
                fprintf(stderr, "[Hijo] Error al escribir en el pipe\n");
                return -1;
            }
        }
        close(p1[1]);
        close(p2[0]);   

    //Proceso padre
    }else {
        close(p1[1]);
        close(p2[0]);
        while ((numberBytes = read(0, buffer, SIZE_BUFFER)) > 0) {
            if (numberBytes == -1) {
                fprintf(stderr, "[PADRE] Error al leer de stdin\n");
                return -1;
            }
            buffer[numberBytes] = '\0';
            if (write(p2[1], buffer, SIZE_BUFFER) == -1) {
                fprintf(stderr, "[PADRE] Error al escribir del pipe\n");
            }
            if (read(p1[0], buffer, SIZE_BUFFER) == -1) {
                fprintf(stderr, "[PADRE] Error al leer del pipe\n");
            }
            fprintf(stdout, "%s", buffer);
        }
        close(p1[0]);
        close(p2[1]);
        wait(NULL);
    }
    free(p1);
    free(p2);
    free(buffer);
    return 0;
}
