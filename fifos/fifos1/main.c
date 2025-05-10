

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h> //para poder usar la funcion 'open()'

#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_FILE_NAME "firstFIFO"

int main(void) {
    if (mkfifo(FIFO_FILE_NAME, 0777) == -1) { // 0777 representa los permisos que se le dan al fichero (-rwxrwxrwx --> todos los permisos) 
        if(errno != EEXIST){
            fprintf(stderr, "Error al crear fifo\n"); 
            return -1;
        }else {
            fprintf(stderr, "Ya existe un fichero con el mismo nombre\n");
            return -1;
        }
    } 
    printf("Abriendo...\n");
    int fd = open(FIFO_FILE_NAME, O_WRONLY); // open() devuelve el descriptor de fichero
    if(fd == -1) {
        fprintf(stderr, "Error al abrir el fichero %s", FIFO_FILE_NAME);
        return -1;
    }
    printf("Abierto\n");
    
    int x = 100; //Que en realidad es la letra 'd' en la tabla ASCI
    if (write(fd, &x, sizeof(int)) == -1) {
        fprintf(stderr, "Error al escribir en el descriptor de fichero\n");
        return -1;
    }
    printf("Written\n");
    close(fd);
    printf("Descriptor de ficheros cerrado\n");



    return 0;
}
