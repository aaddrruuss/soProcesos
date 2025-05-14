#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define _XOPEN_SOURCE 700

void const handle_sigtstp(int sig) {
    fprintf(stdout, "Stop no permitido\n");
}

void const handle_sigcont(int sig) {
    fprintf(stdout, "Introduce un numero: \n");
    fflush(stdout);
}

int main(int argc, char const *argv[])
{
    struct sigaction sa;
    sa.sa_handler = &handle_sigcont;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCONT, &sa, NULL);

    //signal(SIGTSTP, &handle_sigtstp); // Por temas de portabilidad es mejor usar la opcion anterior comentada para que funcione en la mayoria de versiones UNIX

    int x;
    fprintf(stdout, "Introduce un numero: ");
    scanf("%d", &x);
    fprintf(stdout, "%d * 5 = %d\n", x, x*5);
}
