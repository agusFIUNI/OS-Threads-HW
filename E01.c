#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *ej1_thread_func(void *arg) {
    int id = *(int *)arg;
    printf("Ejercicio 1 - Hilo %d: Hola, soy el hilo con id %d\n", id, id);
    return NULL;
}

int main(void) {
    int i;

    printf("=== Ejercicio 1 ===\n");
    pthread_t threads_ej1[3];
    int ids[3];
    for (i = 0; i < 3; i++) {
        ids[i] = i + 1;
        if (pthread_create(&threads_ej1[i], NULL, ej1_thread_func, (void *)&ids[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    for (i = 0; i < 3; i++) {
        pthread_join(threads_ej1[i], NULL);
    }

    return 0;
}