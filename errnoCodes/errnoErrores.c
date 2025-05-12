#include <stdio.h>
#include <string.h>
#include <errno.h>

extern int errno;

int main(int argc, char const *argv[])
{
    int i;
    char *err_str;
    for (i = 0; i < 133 ; i++){
        errno = i;
        err_str = strerror(errno);
        fprintf(stdout, "Errno: %d [%s]\n", errno, err_str);
    }

    return 0;
}
