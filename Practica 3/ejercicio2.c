#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 12

pthread_attr_t attr;
pthread_t hilo1, hilo2, mainthread;

sem_t Productor, Consumidor;
int buffer[10];
int contador = 0;

void *productor(void *arg){
    for (int i = 0; i < 10; i++){
        sem_wait(&Productor);
        if (buffer[i] == 0){
            buffer[i] = i + 1;
            printf("Dato producido: %d\n", buffer[i]);
            for (int i = 0; i < 10; i++){
                printf("%d ", buffer[i]);
            }
            printf("\n");
        }

        sem_post(&Consumidor);
        sleep(random() % 3);
    }

    pthread_exit(NULL);
}

void *consumidor(void *arg){
    for(int i =10; i>0; i--){
        sem_wait(&Consumidor);
        if(buffer[i] != 0){
            int data = buffer[i];
            buffer[i] = 0; 
            printf("Dato consumido: %d \n" , data); 
            for(int i = 0; i < 10; i++){
                printf("%d " , buffer[i]);
            }
            printf("\n");

        }
        sem_post(&Consumidor);
        sleep(random() % 3);
    }    
}

int main(int argc, char **argv){
    mainthread = pthread_self();
    pthread_attr_init(&attr);

    sem_init(&Productor, 0, 10);
    sem_init(&Consumidor, 0, 0);

    pthread_create(&hilo1, &attr, productor, NULL);
    pthread_create(&hilo2, &attr, consumidor, NULL);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    sem_destroy(&Productor);
    sem_destroy(&Consumidor);

    pthread_exit(NULL);
}
