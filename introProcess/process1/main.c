#include <stdio.h>
#include <unistd.h>

int main(void){
    // fork() crea un proceso hijo que ejecuta el mismo codigo en paralelo por asi decirlo
    int id = fork();
    
    if(id != 0){
        fork();
    }
    printf("El id de este proceso es: %d\n", id);
    //printf("Hello World desde id = %d\n", id);

    /*
    * El id del proceso hijo es SIEMPRE 0 (cero)
    * Si el id != 0 estamos en el proceso principal
    */

    /*
    if (id == 0){
        printf("Estamos en el proceso hijo con id = %d\n", id);
    }else{
        printf("Estamos en el proceso padre con id = %d\n", id);
    }
    */
    return 0;
}