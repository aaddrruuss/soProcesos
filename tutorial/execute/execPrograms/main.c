/*
execl(fichero_a_ejecutar, fichero_a_ejecutar, argumentos) -> ejecuta el fichero con los argumento(s) dado(s)
Debe terminara siempre en NULL

Si el fichero ejecutado termina correctamente nada de lo que haya despues se ejecutara
Si termina con un error si se ejecutara lo siguiente que haya en el programa

Para poder ejecutar el fichero y ejecutar algo mas despues tenemos que usar procesos

* execl -> "l" significa "lista de argumentos"
* execlp -> la "p" significa "path" y buscara el primer argumento que se le pase en el PATH

*execv -> "v" significa "vector" y nos indica que el argumento que queremos ejecutar debe ser pasado como vector
*execvp -> ejecuta el comando/programa pasado como vector buscandolo en el path
*execve -> la "e" viene de env o enviroment 

? EJEMPLOS
? execl("/home/adrian/soProcesos/programacionConProcesos/ejercicio2/mayusculas", "/home/adrian/soProcesos/programacionConProcesos/ejercicio2/mayusculas", NULL);
? execlp("mayusculas", "mayusculas", NULL); -> buscara en el PATH
? execl("/home/adrian/soProcesos/programacionConProcesos/ejercicio2/mayusculas", "/home/adrian/soProcesos/programacionConProcesos/ejercicio2/mayusculas", NULL);

? execvp(argv[1], &argv[1]); -> ejecutará el comando pasado buscandolo en el PATH
? execv(argv[1], &argv[1]); -> ejecutará el comando pasado buscandolo en el directorio completo enviado contenido en el vector (array)

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/wait.h>


int main(int argc, char const *argv[]) {
    execl("/home/user/your/directory/here/program", "/home/user/your/directory/here/program", NULL);

    printf("Solo imprime esto si execl falla\n");

    return 0;
}
