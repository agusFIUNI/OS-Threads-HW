#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int work_available = 0;
pthread_mutex_t prodcons_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t prodcons_cond = PTHREAD_COND_INITIALIZER;

void *producer_func(void *arg) {
    pthread_mutex_lock(&prodcons_mutex);
    printf("Ejercicio 3 - Productor: Produciendo trabajo...\n");
    work_available = 1;  /* Se produce el recurso */
    pthread_cond_signal(&prodcons_cond);
    pthread_mutex_unlock(&prodcons_mutex);
    return NULL;
}

void *consumer_func(void *arg) {
    pthread_mutex_lock(&prodcons_mutex);
    while (work_available == 0) {
        pthread_cond_wait(&prodcons_cond, &prodcons_mutex);
    }
    printf("Ejercicio 3 - Consumidor: Trabajo consumido.\n");
    work_available = 0;
    pthread_mutex_unlock(&prodcons_mutex);
    return NULL;
}

int main(void) {
    int i;

    printf("\n=== Ejercicio 3 ===\n");
    pthread_t producer, consumer;
    if (pthread_create(&producer, NULL, producer_func, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&consumer, NULL, consumer_func, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    return 0;
}