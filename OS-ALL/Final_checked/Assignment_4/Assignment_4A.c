#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10

sem_t full, empty;
int buffer[BUFFER_SIZE];
pthread_mutex_t mutex;

void *producer_thread(void *p);
void *consumer_thread(void *p);

int item_count;

void initialize_resources() {
    pthread_mutex_init(&mutex, NULL);
    sem_init(&full, 1, 0);
    sem_init(&empty, 1, BUFFER_SIZE);
    item_count = 0;
}

int main() {
    int num_producers, num_consumers, i;
    printf("Enter the number of producers you want to create: ");
    scanf("%d", &num_producers);
    printf("Enter the number of consumers you want to create: ");
    scanf("%d", &num_consumers);
    initialize_resources();

    pthread_t producer_threads[num_producers];
    pthread_t consumer_threads[num_consumers];

    for (i = 0; i < num_producers; i++)
        pthread_create(&producer_threads[i], NULL, producer_thread, NULL);
    for (i = 0; i < num_consumers; i++)
        pthread_create(&consumer_threads[i], NULL, consumer_thread, NULL);

    sleep(50);
    exit(0);
}

void *producer_thread(void *p) {
    int item, wait_time;
    wait_time = rand() % 5;
    sleep(wait_time);
    item = rand() % 10;
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    printf("\nProducer produced %d item", item);
    buffer[item_count++] = item;
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

void *consumer_thread(void *p) {
    int item, wait_time;
    wait_time = rand() % 10;
    sleep(wait_time);
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    item = buffer[--item_count];
    printf("\nConsumer consumed %d item", item);
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
}
