/*
* Ahora haremos lo mismo que los casos practicos 1 y 2 pero esta vez con 3 procesos en lugar de unicamente con 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define SIZE_FD1 2
#define SIZE_FD2 2


int main(void) {
    int arr[] = {1,2,2,3,3,4,4,5,1};
    int sizeArr = sizeof(arr)/sizeof(int);

    int start, end, i;
    int id2;
    int *fd1 = (int*)malloc(sizeof(int) * SIZE_FD1);
    if (fd1 == NULL){
        fprintf(stderr, "Error al reservar memoria para el descriptor de ficheros 1\n");
        return -1;
    }
    int *fd2 = (int*)malloc(sizeof(int) * SIZE_FD2);
    if (fd2 == NULL){
        fprintf(stderr, "Error al reservar memoria para el descriptor de ficheros 2\n");
        return -1;
    }

    if (pipe(fd1) == -1){
        fprintf(stderr, "Error al abrir un pipe\n");
        return -1;
    }

    int id1 = fork();
    if (id1 == -1 ){
        fprintf(stderr, "[PADRE] Error al crear un nuevo proceso\n");
        return -1;
    }
    // Proceso hijo1
    if (id1 == 0){

        if (pipe(fd2) == -1) {
            fprintf(stderr, "Error al abrir pipe2\n");
            return -1;
        }

        id2 = fork();
        if (id2 == -1) {
            fprintf(stderr, "[HIJO1] Error al crear un nuevo proceso ");
            return -1;
        }
        // Proceso hijo2
        if (id2 == 0) {
            start = 0;
            end = sizeArr / 3;
        } else {
            start = sizeArr / 3;
            end = (sizeArr * 2) / 3; // --> para que el proceso hijo1 del padre coja el segundo tercio del array
        }
    // Proceso padre
    } else {
        start = (sizeArr * 2) / 3;
        end = sizeArr;
    }
    int suma = 0;
    for(i = start ; i < end ; i++) {
        suma += arr[i];
    }
    if (id1 == 0) {
        if (id2 == 0) {
            printf("[NIETO] La suma de los elementos [");
        } else {
            printf("[HIJO] La suma de los elementos [");
        }
    } else {
        printf("[PADRE] La suma de los elementos [");
    }
    for(i = 0; i < sizeArr ; i++) {
        if(i != sizeArr - 1) {
            printf("%d ", arr[i]);
        }else {
            printf("%d", arr[i]);
        }
    }
    printf("] es: %d\n", suma);
    if(id1 == 0){
        if(id2 == 0){
            close(fd1[0]);
            close(fd1[1]);
            close(fd2[0]);
            if (write(fd2[1], &suma, sizeof(int)) == -1) {
                fprintf(stderr, "[NIETO] Error al escribir en el descriptor de fichero\n");
                return -1;
            }
            close(fd2[1]);
        }else {
            close(fd1[0]);
            close(fd2[1]);
            int sumaNieto;
            if (read(fd2[0], &sumaNieto, sizeof(int)) == -1) {
                fprintf(stderr, "[HIJO] Error al leer del descriptor de ficheros\n");
                return -1;
            }
            close(fd2[0]);
            suma += sumaNieto;
            if (write(fd1[1], &suma, sizeof(int)) == -1){
                fprintf(stderr, "[HIJO] Error al escribir en el descriptor de ficheros\n");
                return -1;
            }
            close(fd1[1]);
        }
        wait(NULL);
    } else {
        close(fd2[0]);
        close(fd2[1]);
        close(fd1[1]);
        int sumaHijo;
        if (read(fd1[0], &sumaHijo, sizeof(int)) == -1) {
            fprintf(stderr, "[PADRE] Error al leer del descriptor de ficheros\n");
            return -1;
        }
        close(fd1[0]);
        suma += sumaHijo;
        wait(NULL);
        printf("[PADRE] El resultado total de la suma de los elementos del array es: %d\n", suma);
    }
    free(fd1);
    free(fd2);
    return 0;
}
