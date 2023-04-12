#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    pid_t pid1, pid2;

    pid1 = fork();
    switch (pid1) {
        case -1: perror ("No se ha podido crear el hijo");
                 exit(1);
        case 0:  //Soy el hijo
        	printf("Los impares son: \n");
        	for(int i=1; i<21; i++){
        	   if(i % 2 == 1){
        	     printf("%d\n", i*i);
        	   }
        	}
                   
        default: //Soy el padre
        	pid2 = fork();
        	
        	if((pid2 = wait(0)) == -1){
        	  perror ("No se ha podido crear el hijo");
        	}else{
         	  printf("Los pares son: \n");
        	  for(int i=1; i<21; i++){
        	     if(i % 2 == 0){
        	        printf("%d\n", i*i);  	        
        	     }
        	   }
        	}
        	wait(0);
        	wait(0);
    }
    exit(0);
}
