#include <stdio.h>
#include <sys/ipc.h> // Include header file for IPC functions and data structures
#include <sys/shm.h> // Include header file for shared memory and data structures
int main()
{
    // ftok to generate a unique key
    key_t key = ftok("shmfile", 65); // ftok takes a pathname and a project identifier and
    returns a key based on them.

        // shmget returns an identifier in shmid
        /* Use shmget to create or access a shared memory segment. It returns a shared
       memory identifier (shmid). Here, we request a segment of 1024 bytes with read and write
       permissions,
        and we also create the segment if it doesn't exist (IPC_CREAT).
        */
        int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }

    // shmat to attach to shared memory
    // Use shmat to attach to the shared memory segment. It returns a pointer to the shared
    memory.Here, we attach at the default address(0) and don't specify any flags. char *str = (char *)shmat(shmid, (void *)0, 0);

                     printf("Data read from memory: %s\n", str);

    // Detach from shared memory
    shmdt(str);

    // Destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
/* Output */
/*
comp74@comp74:~/Desktop$ gcc assgn7B_2.c -o assgn7B_2
comp74@comp74:~/Desktop$ ./assgn7B_2
Data read from memory: Hello Everone! I am performing Inter-process Communication
using Shared Memory
*/