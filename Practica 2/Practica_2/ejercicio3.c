#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_t thread1, thread2, thmain; /* Declaración de los threads */
pthread_attr_t attr;                /* Atributos de los threads */
pthread_mutex_t my_lock;
int final[50];

void *func1(void *arg)
{
    pthread_mutex_lock(&my_lock);
    int impar = atoi((char *)arg);
    int arrImpares[impar];
    printf("Hilo 1, que calcula impares: \n");
    for(int i=0; i<impar; i++){
      if(i % 2 == 1){
	arrImpares[i] = i * i;
        final[i] = i * i;
	printf("El cuadrado del numero %d es: %.d\n", i, arrImpares[i]);
      }
    }
    pthread_mutex_unlock(&my_lock);
    pthread_exit(NULL);  
}

void *func2(void *arg)
{
     pthread_mutex_lock(&my_lock);
     int par = atoi((char *)arg);
     int arrPares[par];
     printf("Hilo 2, que calcula pares: \n");
     for(int i=0; i<par; i++){
         if(i % 2 == 0){
	     arrPares[i] = i * i;
	     final[i] = i * i;
	     printf("El cuadrado del numero %d es: %.d\n", i, arrPares[i]);
         }
      }
      pthread_mutex_unlock(&my_lock);
      pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    thmain = pthread_self();

    /* Inicialización de los parametros de los threads por defecto */
    pthread_attr_init(&attr);
    
    //Inicializamos el una variable de tipo mutex
    pthread_mutex_init(&my_lock, NULL);
    
    //Realizamos la creacion de threads 
    pthread_create(&thread1, &attr, func1, (void *)argv[1]);
    pthread_create(&thread2, &attr, func2, (void *)argv[1]);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    size_t n = sizeof(final);
    for(int i=0; i<n; i++){
    	if(final[i] != 0){
    	   printf("%d \n", final[i]);
    	}
    }
   
    pthread_exit(NULL);
}
