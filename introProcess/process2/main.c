/*
! Como esperar a que termine un proceso
* Vamos a crear un programa que cuente numeros, la primera mitad la debera hacer el proceso hijo
* Mientras que la segunda mitad la debera hacer el proceso padre


? Usaremos la funcion wait()
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int id = fork();
    int n, i;

    // Proceso hijo
    if (id == 0) {
        n = 1;
    }
    else{
        n = 6;
    }

    //Si estamos en el proceso padre esperamos a que el proceso hijo termine
    if(id != 0) {
        wait(0); //Le pasamos 0 ya que los procesos hijos siempre tiene id = 0
    }   

    for(i = n ; i < n + 5 ; i++){
        printf("%d ", i);
        fflush(stdout);
    }

    // Solo imprime salto de linea en el proceso padre
    if(id != 0) {
        printf("\n");
    }
    return 0;
}