#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/wait.h>

#define FD_SIZE 2

int main(int argc, char const *argv[]) {
    int *fd = (int *)malloc(sizeof(int) * FD_SIZE);
    if (fd == NULL) {
        fprintf(stderr, "Error al reservar memoria para el derscriptor de ficheros\n");
        return -1;
    }

    if (pipe(fd) == -1) {
        fprintf(stderr, "Error al abrir el pipe\n");
        return -1;
    }

    int pid = fork();

        
    if (pid == -1) {
        fprintf(stderr, "Error al crear un nuevo proceso\n");
        return -1;
    }
    
    //PROCESO HIJO  
    if (pid == 0) {
        close(fd[0]);
        char buffer[256];
        int numberBytes;
        fprintf(stdout, "[HIJO] Introduce una palabra o una frase: ");
        fgets(buffer, 256, stdin);
        buffer[strlen(buffer) - 1] = '\0'; //Eliminar el salto de linea que se genera
        int size_buffer = strlen(buffer) + 1;
        if (write(fd[1], &size_buffer, sizeof(int)) < 0){
            fprintf(stderr, "[HIJO] Error al escribir en el descriptor de ficheros 1\n");
            return -1;
        }
        if(write(fd[1], buffer, sizeof(char) * size_buffer) < 0) {
            fprintf(stderr, "[HIJO] Error al escribir en el descriptor de ficheros 2\n");
            return -1;
        }
        close(fd[1]);
    }
    //PROCESO PADRE
    else {
        close(fd[1]);
        int size_buffer;
        if(read(fd[0], &size_buffer, sizeof(int)) < 0) {
            fprintf(stderr, "[PADRE] Error al leer del descriptor de ficheros\n");
            return -1;
        }
        char buffer[size_buffer];
        if(read(fd[0], buffer, sizeof(char) * size_buffer) < 0) {
            fprintf(stderr, "[PADRE] Error al leer del descriptor de ficheros\n");
            return -1;
        }


        fprintf(stdout, "[PADRE] La palabra introducida es %s\n", buffer);
        close(fd[0]);
        wait(NULL);
    }


    return 0;
}
