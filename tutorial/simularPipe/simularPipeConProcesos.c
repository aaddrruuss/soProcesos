/*
Simulacion de ejecucion de la siguiente linea de script bash 
* ping -c 1 google.com | grep rtt
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/wait.h>

#define FD_SIZE 2

int main(int argc, char const *argv[])
{
    int *fd = (int *)malloc(sizeof(int) * FD_SIZE);
    if (fd == NULL) {
        fprintf(stderr, "Error al reservar memoria para el decriptor de ficheros\n");
        return -1;
    }

    if (pipe(fd) == -1) {
        fprintf(stderr, "Error al abrir una pipe\n");
        return -1;
    }

    int pid1 = fork();

    
    if (pid1 == -1) {
        fprintf(stderr, "Error al crear un proceso nuevo\n");
        return -1;
    }

    //PROCESO HIJO - ping
    if (pid1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ping", "ping", "-c", "4", "google.com", NULL); //Este proceso es sustituido por ./ping
        perror("execlp: ");
    }

    int pid2 = fork();
    if (pid2 == -1) {
        fprintf(stderr, "Error al crear el segundo proceso\n");
        return -1;
    }

    if (pid2 == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("grep", "grep", "rtt", NULL);
        perror("execlp: ");
    }

    close(fd[1]);
    close(fd[0]);
    
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    

    free(fd);
    return 0;
}
