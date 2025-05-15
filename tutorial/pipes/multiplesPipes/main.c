#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

#define FD_SIZE 2
#define FD_TOTAL 3

int main(int argc, char const *argv[])
{
    int i;

    int fd[3][2];

    for (i = 0 ; i < 3 ; i++) {
        if (pipe(fd[i]) == -1) {
            fprintf(stderr, "Error al abrir la pipe numero %d\n", i);
            return -1;
        }
    }

    int pid1 = fork();
    if (pid1 == -1) {
        fprintf(stderr, "Error al crear proceso hijo 1\n");
        return -1;
    }

    if (pid1 == 0) {
        close(fd[1][0]);
        close(fd[0][1]);
        close(fd[2][0]);
        close(fd[2][1]);
        int x;
        if (read(fd[0][0], &x, sizeof(int)) == -1) {
            fprintf(stderr, "[HIJO] Error al leer del pipe (0,0)\n");
            return -1;
        }
        x += 5;
        if (write(fd[1][1], &x, sizeof(int)) == -1) {
            fprintf(stderr, "[HIJO] Error al escribir en el pipe (1,1)\n");
            return -1;
        }
        close(fd[0][0]);
        close(fd[1][1]);
        return 0;
    }
    
    int pid2 = fork();
    if (pid2 == -1) {
        fprintf(stderr, "Error al crear el segundo proceso\n");
        return -1;
    }

    if (pid2 == 0) {
        close(fd[0][0]);
        close(fd[0][1]);
        close(fd[1][1]);
        close(fd[2][0]);
        int x;
        if (read(fd[1][0], &x, sizeof(int)) == -1) {
            fprintf(stderr, "[NIETO] Error al leer del pipe 1,0\n");
            return -1;
        }
    
        x += 5;

        if (write(fd[2][1], &x, sizeof(int)) == -1) {
            fprintf(stderr, "[NIETO] Error al escribir en el descriptor de ficheros\n");
            return -1;
        }

        close(fd[1][0]);
        close(fd[2][1]);
        return 0;
    }
    
    close(fd[1][0]);
    close(fd[1][1]);
    close(fd[0][0]);
    close(fd[2][1]);

    int x;
    fprintf(stdout, "Introduce un numero: ");
    scanf("%d", &x);
    if (write (fd[0][1], &x, sizeof(int)) == -1) {
        fprintf(stderr, "[PADRE] Error al escribir en el pipe 0,1\n");
        return -1;
    }

    if (read (fd[2][0], &x, sizeof(int)) == -1) {
        fprintf(stderr, "[PADRE] Error al leer del pipe 2,0");
        return -1;
    }
    fprintf(stdout, "[PADRE] El valor de x despues de pasar por todos los procesos es de: %d\n", x);
    close(fd[0][1]);
    close(fd[2][0]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}
