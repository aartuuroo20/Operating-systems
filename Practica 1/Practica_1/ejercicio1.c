#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main (void){

    int fd, bytes;
    char buffer[100];

    mode_t mode = S_IRWXU;

    if((fd = open("ejemplo", O_RDWR | O_CREAT, mode)) == -1){
        perror("Error abriendo o creando");
    }else{
        bytes = read(fd, buffer, 100);
        printf("%s\n",buffer);
    }
}
