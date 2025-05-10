/*
Inicio al uso de pipes para comunicarnos de un proceso a otro

El uso principal es no copiar la memoria de un proceso a otro sino
que por asi decirlo cada proceso sea "independiente"


pipe(int array[2])
    -> Devuelve 0 si se ejecuta de forma correcta
    -> Devuelve -1 si hay algun tipo de error
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int *fd = (int*)malloc(sizeof(int) * 2); //Esto nos sirve para comunicar los procesos entre ellos
    if (fd == NULL) {
        fprintf(stderr, "Error al reservar memoria");
        return -1;
    }
    // * fd[0] ==> de donde tienes que leer (read)
    // * fd[1] ==> donde tienes que escribir (write)
    if (pipe(fd) != 0) {
        fprintf(stderr, "Error al abrir el pipe\n");
        return -1;
    }
    int id = fork();

    if (id == -1) {
        fprintf(stderr, "Error al crear un proceso hijo");
        return -1;
    }

    if (id == 0) {
        // Como no leemos del descriptor de ficheros entonces al entrar al proceso hijo
        // Simplemente lo cerramos
        close(fd[0]);
        int x;
        printf("[HIJO]Mi PID es: %d\n", getpid());
        printf("Introduce un numero: ");
        scanf("%d", &x);
        fflush(stdin);
        if (write(fd[1], &x, sizeof(int)) == -1){
            perror("write");
            return -1;
        }
        close(fd[1]);
    } else {
        close(fd[1]);
        int y;
        if (read(fd[0], &y, sizeof(int)) == -1) {
            perror("read");
            return -1;
        }
        close(fd[0]);
        printf("Obtenido del proceso hijo[%d] el valor de X que ejecutado desde el proceso padre hemos obtenido que es %d\n", id, y);   
    }
    return 0;
}