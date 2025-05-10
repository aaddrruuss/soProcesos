#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define ARR_SIZE 5
#define FILE_NAME "sum"

int main(void) {
    int arr[ARR_SIZE];
    srand(time(NULL));
    int i;
    for(i = 0 ; i < ARR_SIZE ; i++) {
        arr[i] = rand() % 100;
    }
    // Creamos un descriptor de fichero
    int fd = open(FILE_NAME, O_WRONLY);
    if (fd == -1) {
        if (errno != EEXIST) {
            fprintf(stderr, "Error al abrir %s\n", FILE_NAME);
            return -1;
        } else {
            fprintf(stderr, "El fichero [%s] ya existe\n", FILE_NAME);
            return -1;
        }
    }

    for (i = 0 ; i < ARR_SIZE ; i++) {
        if (write(fd, &arr[i], sizeof(int)) == -1) {
            fprintf(stderr, "Error al escribir en el array\n");
            return -1;
        }
        fprintf(stdout, "Escrito %d\n", arr[i]);
    }
    // Cerramos el descriptor de fichero
    close(fd);

    return 0;
}
