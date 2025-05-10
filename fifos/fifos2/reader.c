#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

#include <sys/wait.h>

#define ARR_SIZE 5
#define FILE_NAME "sum"

int main(void) {
    int *arr = (int *)malloc(sizeof(int) * ARR_SIZE);
    if(arr == NULL) {
        fprintf(stderr, "Error al reservar memoria para el array");
        return -1;
    }
    int i, fd;
    fd = open(FILE_NAME, O_RDONLY);
    if (fd == -1) {
        if (errno == ENOENT) {
            fprintf(stderr, "No existe dicho fichero\n");
            return -1;
        } else{
            fprintf(stderr, "Error al leer el fichero FIFO\n");
            return -1;
        }
    }

    for (i = 0 ; i < ARR_SIZE ; i++) {
        if (read(fd, &arr[i], sizeof(int)) == -1) {
            fprintf(stderr, "Error al leer del arr en la posicion [%d]\n", i);
            return -1;
        }
        fprintf(stdout, "Leido valor: %d\n", arr[i]);
    }   
    close(fd);
    int sum = 0;
    for (i = 0 ; i < ARR_SIZE ; i++) {
        sum += arr[i];
    }
    fprintf(stdout, "Suma de los valores del array en reader.c: %d\n", sum);
    fd = open(FILE_NAME, O_WRONLY);
    if (fd == -1) {
        if(errno != EEXIST){
            fprintf(stderr, "Error al escribir en el fichero %s\n", FILE_NAME);
            return -1;
        }
    }

    if (write(fd, &sum, sizeof(int)) == -1) {
        fprintf(stderr, "Error al escribir el resultado de la suma\n");
        return -1;
    }
    free(arr);
    close(fd);
    return 0;
}
