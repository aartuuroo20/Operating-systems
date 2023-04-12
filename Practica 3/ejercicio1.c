#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <string.h>

#define SIZE 512

int main(int argc, char **argv){
    pid_t pid;
    int p[2], readbytes;
    int b[2];
    char buffer[SIZE];

    pipe(p);
    pipe(b);
    if ((pid = fork()) == 0){
        close(p[0]); 
	close(b[1]); 

        strcpy(buffer, "Soy el hijo.\n"); 

        write(p[1], buffer, strlen(buffer)); 

        close(p[1]);

        while ((readbytes = read(b[0], buffer, SIZE)) > 0){
            write(1, buffer, readbytes);
        }

        close(b[0]);
    }else{
        
        close(p[1]); 
	close(b[0]);

        while ((readbytes = read(p[0], buffer, SIZE)) > 0){
            write(1, buffer, readbytes); 
        }
        close(p[0]);

        strcpy(buffer, "Soy el padre.\n");

        write(b[1], buffer, strlen(buffer)); //escribe el mensaje del buffer en el pipe 

        close(b[1]); //cerramos la escritura en el pipe
    }
    waitpid(pid, NULL, 0);
    exit(0);
}
