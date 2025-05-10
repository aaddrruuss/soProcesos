/*
* Resumidamente lo que hemos hecho aqui ha sido crear 4 procesos y con ello
* Imprimir en cada caso el proceso teniendo en cuenta los valores que devuelve 
* La funcion fork() en cada uno de los casos

* Tambien importante el uso que hemos dado al final del while, para esperar
* A que terminen de ejecutarse todos los hijos de cada uno de los procesos
* Antes de ejecutarse el propio proceso

*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main(void) {
    int id1 = fork();
    int id2 = fork();

    if (id1 == 0) {
        if (id2 == 0) {
            printf("Somos [Y]\n");
        }else {
            printf("Somos [X]\n");
        }
    }else {
        if (id2 == 0){
            printf("Somos [Z]\n");
        }else {
            printf("Somos el proceso padre\n");
        }
    }

    while (wait(NULL) != -1 || errno != ECHILD){
        printf("Hemos esparado a que termine la ejecucion de un hijo\n");
        fflush(stdout);
    }
    return 0;
}
