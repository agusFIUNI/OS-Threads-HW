#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *ej2_thread_func(void *arg) {
    int i;
    for (i = 0; i < 1000; i++) {
        pthread_mutex_lock(&counter_mutex);
        counter++;
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}

int main(void) {
    int i;

    printf("\n=== Ejercicio 2 ===\n");
    pthread_t threads_ej2[2];
    for (i = 0; i < 2; i++) {
        if (pthread_create(&threads_ej2[i], NULL, ej2_thread_func, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    for (i = 0; i < 2; i++) {
        pthread_join(threads_ej2[i], NULL);
    }
    printf("Ejercicio 2 - Contador global: %d\n", counter);

    return 0;
}