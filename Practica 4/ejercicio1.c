#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int pipes[2];
    pipe(pipes);
    if (fork() == 0) {
        dup2(pipes[1], STDOUT_FILENO);
        close(pipes[0]);
        close(pipes[1]);
        execlp("grep", "grep", argv[1], argv[2]);
    }
    else {
        if (fork() == 0) {
             dup2(pipes[1], STDOUT_FILENO);
             close(pipes[0]);
             close(pipes[1]);
             execlp("grep", "grep", argv[1], argv[3]);
        }else{
            if (fork() == 0) {
            	int fd = creat(argv[4], 00644);
                dup2(pipes[0],STDIN_FILENO);
                dup2(fd,STDOUT_FILENO);
            	close(pipes[0]);
            	close(pipes[1]);     
         	execlp("wc", "wc","-l", NULL);
            }
        }
    }
    return 0;
}

