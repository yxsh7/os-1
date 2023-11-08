#include <stdio.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
void *producer();
void *consumer();
typedef struct
{
    int buffer[20];
    sem_t full, empty;
} shared;
shared sh;
int item;
int in = 0, out = 0;
sem_t mutex;
int main()
{
    pthread_t ptid1, ptid2, ctid1;
    sem_init(&sh.empty, 0, 20);
    sem_init(&sh.full, 0, 0);
    sem_init(&mutex, 0, 1);
    pthread_create(&ptid1, NULL, producer, NULL);
    pthread_create(&ptid2, NULL, producer, NULL);
    pthread_create(&ctid1, NULL, consumer, NULL);
    pthread_join(ptid1, NULL);
    pthread_join(ptid2, NULL);
    pthread_join(ctid1, NULL);
    return 0;
}
void *producer()
{
    // pthread_t item;
    int ptid;
    while (1)
    {
        item = in;
        sem_wait(&sh.empty);

        sem_wait(&mutex);
        sh.buffer[in++] = item;
printf("PRODUCER Thread id = %ld and Producer Item = %d \

n",pthread_self(),item);

sem_post(&mutex);
sem_post(&sh.full);
sleep(3);
    }
}
void *consumer()
{
    int ctid;
    while (out <= 19 && in <= 19)
    {
sem_wait(&sh.full);
sem_wait(&mutex);
item = sh.buffer[out++];
printf("\tCONSUMER Thread id = %ld and Consumer Item = %d \

n",syscall(SYS_gettid,ctid),item);
sem_post(&mutex);
sem_post(&sh.empty);
sleep(1);
    }
}
// output:
// comp123@comp123:~/Desktop/os/4$ gcc producer-consumer.c
// comp123@comp123:~/Desktop/os/4$ ./a.out
// PRODUCER Thread id = 139828242937408 and Producer Item = 0
// CONSUMER Thread id = 25193 and Consumer Item = 0
// PRODUCER Thread id = 139828234544704 and Producer Item = 0
// CONSUMER Thread id = 25193 and Consumer Item = 0
// PRODUCER Thread id = 139828242937408 and Producer Item = 2
// PRODUCER Thread id = 139828234544704 and Producer Item = 3
// CONSUMER Thread id = 25193 and Consumer Item = 2
// CONSUMER Thread id = 25193 and Consumer Item = 3
// PRODUCER Thread id = 139828242937408 and Producer Item = 4
// PRODUCER Thread id = 139828234544704 and Producer Item = 4
// CONSUMER Thread id = 25193 and Consumer Item = 4
// CONSUMER Thread id = 25193 and Consumer Item = 4
// PRODUCER Thread id = 139828242937408 and Producer Item = 6
// PRODUCER Thread id = 139828234544704 and Producer Item = 7
// CONSUMER Thread id = 25193 and Consumer Item = 6
// CONSUMER Thread id = 25193 and Consumer Item = 7
// PRODUCER Thread id = 139828242937408 and Producer Item = 8
// PRODUCER Thread id = 139828234544704 and Producer Item = 9

// CONSUMER Thread id = 25193 and Consumer Item = 8
// CONSUMER Thread id = 25193 and Consumer Item = 9
// PRODUCER Thread id = 139828242937408 and Producer Item = 10
// CONSUMER Thread id = 25193 and Consumer Item = 10
// PRODUCER Thread id = 139828234544704 and Producer Item = 11
// CONSUMER Thread id = 25193 and Consumer Item = 11
// PRODUCER Thread id = 139828242937408 and Producer Item = 12
// PRODUCER Thread id = 139828234544704 and Producer Item = 13
// CONSUMER Thread id = 25193 and Consumer Item = 12
// CONSUMER Thread id = 25193 and Consumer Item = 13
// PRODUCER Thread id = 139828234544704 and Producer Item = 14
// PRODUCER Thread id = 139828242937408 and Producer Item = 15
// CONSUMER Thread id = 25193 and Consumer Item = 14
// CONSUMER Thread id = 25193 and Consumer Item = 15
// PRODUCER Thread id = 139828234544704 and Producer Item = 16
// PRODUCER Thread id = 139828242937408 and Producer Item = 17
// CONSUMER Thread id = 25193 and Consumer Item = 16
// CONSUMER Thread id = 25193 and Consumer Item = 17
// PRODUCER Thread id = 139828242937408 and Producer Item = 18
// PRODUCER Thread id = 139828234544704 and Producer Item = 19
// CONSUMER Thread id = 25193 and Consumer Item = 18
// PRODUCER Thread id = 139828242937408 and Producer Item = 20
// PRODUCER Thread id = 139828234544704 and Producer Item = 21
// PRODUCER Thread id = 139828242937408 and Producer Item = 22
// The futex facility returned an unexpected error code.
// PRODUCER Thread id = 139828234544704 and Producer Item = 23
// The futex facility returned an unexpected error code.
// Aborted (core dumped)