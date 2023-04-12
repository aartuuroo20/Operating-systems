#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXLON 1000

pthread_t thread;
pthread_attr_t attr;                /* Atributos de los threads */

void *cuenta(void *arg)
{
    int pos, cont = 0, leidos;
    char cadena[MAXLON];
    int fd;
    char *nombre = (char *)arg;

    fd = open(nombre, O_RDONLY);
    while ((leidos = read(fd, cadena, MAXLON)) != 0)
        for (pos = 0; pos < leidos; pos++)
            if ((cadena[pos] == 'a') || (cadena[pos] == 'A'))
                cont++;
    printf("Fichero %s: %d caracteres 'a' o 'A' encontrados\n", nombre, cont);
    close(fd);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Indica el nombre de un fichero.\n");
        exit(0);
    }
    
    pthread_create(&thread, &attr, cuenta, (void *)argv[1]);
    pthread_join(thread, NULL);
    return 0;
}
