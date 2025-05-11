#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Debes agregar argumentos (./ejecuta + comando)\n");
        return -1;
    }
    pid_t pid = fork();

    //Proceso Hijo
    if (pid == 0) {
        int err = execvp(argv[1], &argv[1]);
        if (err == -1) {
            fprintf(stderr, "Error al ejecutar el comando\n");
            perror("");
            return -1;
        }

    //Proceso Padre
    } else{
        int wstatus, exitCode;
        wait(&wstatus);
        if (WIFEXITED(wstatus)) {
            exitCode = WEXITSTATUS(wstatus);
            if (exitCode == 0){
                fprintf(stdout, "El programa se ejecuto exitosamente. Codigo de salida %d\n", exitCode);
            } else {
                fprintf(stderr, "El comando no se ejecuto correctamente. Codigo de salida %d\n", exitCode);
            }
        }
    }
    return 0;
}
