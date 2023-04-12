#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int argc, char *argv[]){
    int  num;
    pid_t pid;

    for(num = 0; num < 4; num++){
        pid = fork();
        printf("Soy %d y mi padre es %d.\n",getpid(),getppid());
    }
    
    if(pid == 0){
        sleep(random() % 5);
    }else{
        for(int num = 0; num < 4; num++){
            printf("Fin de %d\n", wait(NULL));
        }
    }

    return 0;
}
