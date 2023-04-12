
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd1, fd2;
    char *buffer = (char *)malloc(100);

    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_WRONLY | O_CREAT, 0644);

    if(fd1 == -1 || fd2 == -1)
    {
        perror("Error al abrir el archivo");
        exit(-1);
    }

    while(read(fd1, buffer, 100) > 0)
    {
        write(fd2, buffer, strlen(buffer));
    }

    close(fd1);
    close(fd2);

    return 0;
}
