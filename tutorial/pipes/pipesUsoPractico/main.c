/*

? Ejemplo de caso de uso practico

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define TAMANO_FD 2

int main(void) {
    int i;
    
    int arr[] = {1 ,2 ,3 ,4 ,5 ,1 ,3, 4 };

    int tamanoArray = sizeof(arr)/sizeof(int);
    tamanoArray /= 2;

    int *fd = (int*)malloc(sizeof(int*) * TAMANO_FD);
    if (fd == NULL) {
        fprintf(stderr, "Error al resevar memoria para fd\n");
        return -1;
    }
    if (pipe(fd) == -1){
        fprintf(stderr, "Error al abrir un pipe\n");
        return -1;
    }

    int id = fork();
    if(id == -1) {
        fprintf(stderr, "Error al crear un proceso hijo");
        return -1;
    }

    if (id == 0) {
        close(fd[0]);
        int suma = 0;
        for(i = 0; i < tamanoArray ; i++){
            suma += arr[i];
        }
        if (write(fd[1], &suma, sizeof(int)) == -1) {
            fprintf(stderr, "Error al escribir en el pipe\n");
            return -1;
        }
        close(fd[1]);
    } else {
        close(fd[1]);
        int sumaProcesoHijo;
        if (read(fd[0], &sumaProcesoHijo, sizeof(int)) == -1) {
            fprintf(stderr, "Error al leer del pipe\n");
            return -1;
        }
        close(fd[0]);
        int suma = 0;
        for(i = tamanoArray; i < sizeof(arr)/sizeof(int) ; i++){
            suma += arr[i];
        }
        suma += sumaProcesoHijo;
        printf("La suma de todos los elementos del array usando dos procesos separados es: %d\n", suma);
    }

    return 0;
}
