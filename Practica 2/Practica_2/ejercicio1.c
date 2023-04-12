#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_t thread1, thread2, thmain; /* Declaración de los threads */
pthread_attr_t attr;                /* Atributos de los threads */

void *func(void *arg)
{
    int numero = atoi((char *) arg);
    int factorial = 1;
    
    for(int i=1; i<=numero; i++){
    	factorial = factorial * i;
    }
    
    printf("Factorial de %d es: %d\n", numero, factorial);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    thmain = pthread_self();

    /* Inicialización de los parametros de los threads por defecto */
    pthread_attr_init(&attr);
    
    if(argv[1] == NULL || argv[2] == NULL){
    	printf("Error, introduce 2 numeros \n");
    	exit(1);
    }
    
    //Realizamos la creacion de threads 
    pthread_create(&thread1, &attr, func, (void *)argv[1]);
    pthread_create(&thread2, &attr, func, (void *)argv[2]);
    
    //Mediante la funcion thread_join hacemos que nuestro thread espere a que acabe el main
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_exit(NULL);
}
