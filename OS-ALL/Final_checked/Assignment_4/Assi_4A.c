#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MaxItems 5 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 5 // Size of the buffer

sem_t empty_slots; // Semaphore to track empty slots in the buffer
sem_t full_slots;  // Semaphore to track filled slots in the buffer
int in = 0;        // Index for inserting into the buffer
int out = 0;       // Index for removing from the buffer
int buffer[BufferSize];
pthread_mutex_t mutex; // Mutex to protect the critical section

void *producer_thread(void *pno)
{
    int item;
    for (int i = 0; i < MaxItems; i++) {
        item = rand(); // Produce a random item
        sem_wait(&empty_slots);  // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Lock the critical section
        buffer[in] = item;
        printf("Producer %d: Inserted Item %d at %d\n", *((int *)pno), buffer[in], in);
        in = (in + 1) % BufferSize; // Update the insert index
        pthread_mutex_unlock(&mutex); // Unlock the critical section
        sem_post(&full_slots); // Signal that a slot is filled
        sleep(2); // Introduce a delay of 2 seconds
    }
}

void *consumer_thread(void *cno)
{
    for (int i = 0; i < MaxItems; i++) {
        sem_wait(&full_slots);  // Wait for a filled slot
        pthread_mutex_lock(&mutex); // Lock the critical section
        int item = buffer[out];
        printf("Consumer %d: Removed Item %d from %d\n", *((int *)cno), item, out);
        out = (out + 1) % BufferSize; // Update the removal index
        pthread_mutex_unlock(&mutex); // Unlock the critical section
        sem_post(&empty_slots); // Signal that a slot is empty
        sleep(3); // Introduce a delay of 3 seconds
    }
}

int main()
{
    int num_producers, num_consumers;
    printf("Enter the number of producers: ");
    scanf("%d", &num_producers);
    printf("Enter the number of consumers: ");
    scanf("%d", &num_consumers);

    pthread_t producers[num_producers], consumers[num_consumers];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty_slots, 0, BufferSize);
    sem_init(&full_slots, 0, 0);

    int producer_nums[num_producers];
    int consumer_nums[num_consumers];

    for (int i = 0; i < num_producers; i++) {
        producer_nums[i] = i + 1;
        pthread_create(&producers[i], NULL, (void *)producer_thread, (void *)&producer_nums[i]);
    }
    for (int i = 0; i < num_consumers; i++) {
        consumer_nums[i] = i + 1;
        pthread_create(&consumers[i], NULL, (void *)consumer_thread, (void *)&consumer_nums[i]);
    }

    for (int i = 0; i < num_producers; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < num_consumers; i++) {
        pthread_join(consumers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);

    return 0;
}


