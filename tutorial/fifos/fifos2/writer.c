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
    int *arr = (int*)malloc(sizeof(int) * ARR_SIZE);
    srand(time(NULL));
    int i;
    for(i = 0 ; i < ARR_SIZE ; i++) {
        arr[i] = (rand() % 5) + 1;
        fprintf(stdout, "Generated: %d\n", arr[i]);
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

    
    if (write(fd, arr, sizeof(int) * ARR_SIZE) == -1) {
        fprintf(stderr, "Error al escribir en el array\n");
        return -1;
    }
        
    
    // Cerramos el descriptor de fichero
    close(fd);

    fd = open(FILE_NAME, O_RDONLY);
    if (fd == -1) {
        if (errno != EEXIST) {
            fprintf(stderr, "Error al leer el fichero %s\n", FILE_NAME);
            return -1;
        }
    }
    int sumaReader;
    if (read(fd, &sumaReader, sizeof(int)) == -1) {
        fprintf(stderr, "Error al obtener el valor de la suma del array del fichero reader.c\n");
        return -1;
    }

    fprintf(stdout, "Suma de los valores del array obtenida de reader.c: %d\n", sumaReader);
    
    free(arr);
    close(fd);

    return 0;
}
