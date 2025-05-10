/*

! Parecido al caso practico 1 pero hecho de forma tal vez más eficiente

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define SIZE_FD 2

int main(void) {
    int arr[] = {1,2,300,3,4,1,2,5,2,12,2,4,5,1,2,3,6,7,8,34,5,2,3,45,6,12,32,5,65,2,3,1,3,3542,5,1,3,34,53,6,32,23,1,2,3,4,2,23,42,2,1,34,1};
    int start, end, i; 
    int sizeArr = sizeof(arr) / sizeof(int);


    int *fd = (int*)malloc(sizeof(int) * SIZE_FD);
    if (fd == NULL) {
        fprintf(stderr, "Error al reservar memoria\n");
        return -1;
    }
    if (pipe(fd) == -1){
        fprintf(stderr, "Error al abrir el pipe\n");
        return -1;
    }

    int id = fork();
    if (id == -1) {
        fprintf(stderr, "Error al crear un proceso nuevo\n");
        return -1;
    }
    if (id == 0){
        start = 0;
        end = sizeArr / 2;
    } else {
        start = sizeArr / 2;
        end = sizeArr;
    }
    int suma = 0;
    wait(NULL);
    for(i = start; i < end; i++){
        suma += arr[i];
    }
    if(id == 0) {
        printf("[HIJO] El resultado de la suma de los elementos [");
    } else {
        printf("[PADRE] El resultado de la suma de los elementos [");
    }
    for(i = 0; i < sizeArr ; i++){
        if(i != sizeArr - 1){
            printf("%d ", arr[i]);
        } else {
            printf("%d", arr[i]);
        }
    }
    printf("] es %d\n", suma);

    if (id == 0) {
        close(fd[0]);
        if (write(fd[1], &suma, sizeof(int)) == -1) {
            fprintf(stderr, "Error al escribir en el descriptor de fichero\n");
            return -1;
        }
        close(fd[1]);
    } else {
        close(fd[1]);
        int sumaHijo;
        if(read(fd[0], &sumaHijo, sizeof(int)) == -1){
            fprintf(stderr, "Error al leer del descriptor de fichero\n");
            return -1;
        }
        close(fd[0]);
        suma += sumaHijo;
        printf("El resultado de la suma total usando dos procesos es: %d\n", suma);
        wait(NULL);
    }
    return 0;
}
