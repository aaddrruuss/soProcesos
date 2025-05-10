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
    free(arr);
    close(fd);
    
    return 0;
}
