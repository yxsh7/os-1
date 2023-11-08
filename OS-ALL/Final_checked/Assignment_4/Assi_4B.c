#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


void *writer_thread(int temp);
void *reader_thread(int temp);

// Semaphores for mutual exclusion and writer priority
sem_t mutex; // Controls access to readcount
sem_t writer_priority; // Ensures writer priority

int read_count = 0; // Number of readers
int num_writers, num_readers; // Number of writers and readers

int main() {
  long int i;

  sem_init(&mutex, 0, 1); // Initialize the mutex semaphore with 1
  sem_init(&writer_priority, 0, 1); // Initialize the writer_priority semaphore with 1

  pthread_t readers[100], writers[100];

  printf("\nEnter the number of readers: ");
  scanf("%d", &num_readers);
  printf("Enter the number of writers: ");
  scanf("%d", &num_writers);

  for (i = 1; i <= num_writers; i++) {
    pthread_create(&writers[i], NULL, (void *)writer_thread, (int *)i);
    pthread_join(writers[i], NULL);
  }

  for (i = 1; i <= num_readers; i++) {
    pthread_create(&readers[i], NULL, (void *)reader_thread, (int *)i);
  }

  for (i = 1; i <= num_readers; i++) {
    pthread_join(readers[i], NULL);
  }

  sem_destroy(&writer_priority);
  sem_destroy(&mutex);
}

void *reader_thread(int temp) {
  printf("\nReader %d is trying to enter the database for reading.", temp);
  sem_wait(&mutex);
  read_count++;
  if (read_count == 1) {
    sem_wait(&writer_priority); // Wait for writer priority if it's the first reader
  }
  sem_post(&mutex);

  printf("Reader %d is now reading in the database.", temp);

  sem_wait(&mutex);
  read_count--;
  if (read_count == 0) {
    sem_post(&writer_priority); // Release writer priority if it's the last reader
  }
  sem_post(&mutex);

  printf("Reader %d has left the database.\n", temp);
  sleep(3);
}

void *writer_thread(int temp) {
  printf("\nWriter %d is trying to enter the database for modifying data.", temp);
  sem_wait(&writer_priority); // Request writer priority
  printf("Writer %d is writing in the database.", temp);
  sleep(3);
  printf("Writer %d is leaving the database.\n", temp);
  sem_post(&writer_priority); // Release writer priority
}
