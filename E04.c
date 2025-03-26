#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int ej4_done = 0;
pthread_mutex_t ej4_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t ej4_cond = PTHREAD_COND_INITIALIZER;

void *ej4_thread1_func(void *arg) {
    int i;
    for (i = 1; i <= 5; i++) {
        printf("Ejercicio 4 - Hilo 1: %d\n", i);
        sleep(1);
    }
    pthread_mutex_lock(&ej4_mutex);
    ej4_done = 1;
    pthread_cond_signal(&ej4_cond);
    pthread_mutex_unlock(&ej4_mutex);
    return NULL;
}

void *ej4_thread2_func(void *arg) {
    pthread_mutex_lock(&ej4_mutex);
    while (ej4_done == 0) {
        pthread_cond_wait(&ej4_cond, &ej4_mutex);
    }
    pthread_mutex_unlock(&ej4_mutex);
    printf("Ejercicio 4 - Hilo 2: ¡Ahora me toca a mí!\n");
    return NULL;
}

int main(void) {

    printf("\n=== Ejercicio 4 ===\n");
    pthread_t ej4_t1, ej4_t2;
    if (pthread_create(&ej4_t1, NULL, ej4_thread1_func, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&ej4_t2, NULL, ej4_thread2_func, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    pthread_join(ej4_t1, NULL);
    pthread_join(ej4_t2, NULL);

    return 0;
}