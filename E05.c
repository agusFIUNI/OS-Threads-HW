#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int turn = 0;  /* 0: turno de Ping, 1: turno de Pong */
pthread_mutex_t pingpong_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t pingpong_cond = PTHREAD_COND_INITIALIZER;

void *ping_func(void *arg) {
    int i;
    for (i = 0; i < 10; i++) {
        pthread_mutex_lock(&pingpong_mutex);
        while (turn != 0) {
            pthread_cond_wait(&pingpong_cond, &pingpong_mutex);
        }
        printf("Ping ");
        turn = 1;
        pthread_cond_signal(&pingpong_cond);
        pthread_mutex_unlock(&pingpong_mutex);
    }
    return NULL;
}

void *pong_func(void *arg) {
    int i;
    for (i = 0; i < 10; i++) {
        pthread_mutex_lock(&pingpong_mutex);
        while (turn != 1) {
            pthread_cond_wait(&pingpong_cond, &pingpong_mutex);
        }
        printf("Pong\n");
        turn = 0;
        pthread_cond_signal(&pingpong_cond);
        pthread_mutex_unlock(&pingpong_mutex);
    }
    return NULL;
}

int main(void) {

    printf("\n=== Ejercicio 5 ===\n");
    pthread_t ping_thread, pong_thread;
    if (pthread_create(&ping_thread, NULL, ping_func, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&pong_thread, NULL, pong_func, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    pthread_join(ping_thread, NULL);
    pthread_join(pong_thread, NULL);

    return 0;
}