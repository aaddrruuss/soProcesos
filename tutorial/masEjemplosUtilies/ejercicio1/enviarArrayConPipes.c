#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

#include <sys/wait.h>

#define SIZE_NUMBERS 10
#define SIZE_FD 2
#define RESULTS_FILE "resultados.txt"

/*
* 2 procesos
1. El proceso hijo debera generar numeros al azar y enviarselos al padre (5 - 20)
2. El padre los recibe y los suma todos y lo imprime
*/

int main(int argc, char const *argv[]) {
    
    int *fd = (int*)malloc(sizeof(int) * SIZE_FD);

    int file = open(RESULTS_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (file == -1 ) {
        fprintf(stderr, "Error al crear / abrir / escribir en el fichero %s", RESULTS_FILE);
        return -1;
    }
    dup2(file, STDOUT_FILENO);
    fflush(NULL);
    close(file);

    if(pipe(fd) == -1) {
        fprintf(stderr, "Error al abrir una pipe\n");
        return -1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        fprintf(stderr, "Erro al crear proceso\n");
        return -1;
    }

    //Proceso Hijo
    if (pid == 0) {
        close(fd[0]);
        int *numbers = NULL;
        int n, i;
        srand(time(NULL));
        n = (rand() % 10) + 1;

        if (write(fd[1], &n, sizeof(n)) == -1) {
            fprintf(stderr, "[HIJO] Error al escribir en el descritor de ficheros\n");
        }

        numbers = (int *)realloc(numbers, sizeof(int) * n);
        fprintf(stdout, "[HIJO] El array de numeros aleatorios es [");

        for (i = 0 ; i < n ; i++) {
            numbers[i] = rand() % 11;
            if (i != n - 1) {
                fprintf(stdout, "%d ", numbers[i]);
            }
            else {
                fprintf(stdout, "%d", numbers[i]);
            }
        }

        fprintf(stdout, "]\n");

        if (write(fd[1], numbers, n * sizeof(int)) < 0) {
            fprintf(stderr, "[HIJO] Error al escribir en el descriptor de ficheros\n");
            return -1;
        }
        fflush(stdout);
        free(numbers);
        close(fd[1]);
    //Proceso padre
    }
    else {
        close(fd[1]);
        
        int i, result = 0, n2;
        if(read(fd[0], &n2, sizeof(int)) == -1) {
            fprintf(stderr, "[PADRE] Error al leer del descriptor de ficheros\n");
        }
        int *numbers2 = (int *)malloc(sizeof(int) * SIZE_NUMBERS);
        if (read(fd[0], numbers2, n2 * sizeof(int)) < 0) {
            fprintf(stderr, "[PADRE] Error al leer del descriptor de ficheros\n");
        }
        for (i = 0 ; i < n2 ; i++) {
            result += numbers2[i];
        }
        fprintf(stdout, "[PADRE] El resultado de la suma de los valores del array es: %d\n", result);
        
        fflush(stdout);
        free(numbers2);
        close(fd[0]);
        wait(NULL);
    }
    
    free(fd);
    return 0;
}