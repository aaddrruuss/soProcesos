#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>


#include <sys/wait.h>

#define ERROR_FILE_NAME "errores.txt"

int main(int argc, char const *argv[])
{
    int file = open(ERROR_FILE_NAME, O_WRONLY | O_CREAT, 0777); //0777 para establecer permisos = -rwxrwxrwx

    if (file == -1) {
        fprintf(stderr, "Error al crear / abrir fichero [%s]", ERROR_FILE_NAME);
        return -1;
    }
    dup2(file, STDERR_FILENO); // Con esto conseguimos que todos los errores se envien directamente al ficheor de errores con nombre "errores.txt"

    int pid = fork();
    if (pid == -1) {
        fprintf(stderr, "Error al crear un proceso nuevo\n");
        return -1;
    }

    //Proceso Hijo
    if (pid == 0) {
        int i = 0;
        while (1) {
            fprintf(stdout, "[HIJO - %d] TEST TEST\n", i);
            usleep(50000);
            i += 1;
        }
    //Proceso Padre
    } else {
        sleep(1);
        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;
}
