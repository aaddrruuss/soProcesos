#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define FILE_NAME "errnoCodes.txt"

extern int errno;

int main(int argc, char const *argv[])
{
    int file = open(FILE_NAME, O_WRONLY | O_CREAT, 0777);
    if (file == -1) {
        fprintf(stderr, "Error al crear / abrir el fichero %s", FILE_NAME);
    }
    dup2(file, STDOUT_FILENO);
    close(file);

    int i;
    char *err_str;

    for (i = 0; i < 133 ; i++){
        if (i != 132) {
            errno = i;
            err_str = strerror(errno);
            fprintf(stdout, "Errno: %d [%s]\n", errno, err_str);
        } else {
            errno = i;
            err_str = strerror(errno);
            fprintf(stdout, "Errno: %d [%s]", errno, err_str);
        }
    }

    return 0;
}
