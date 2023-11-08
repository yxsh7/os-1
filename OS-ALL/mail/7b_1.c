#include <stdio.h>
#include <sys/ipc.h> // Include header file for IPC functions and data
structures
#include <sys/shm.h> // Include header file for shared memory and data
    structures
#include <string.h>
    int
    main()
{
    // ftok to generate unique key
    key_t key = ftok("shmfile", 65); // This key is used to identify the shared memory
    segment.
        // shmget returns an identifier in shmid
        // Create or open a shared memory segment. The size of the shared memory segment is
        1024 bytes,
        and the flags indicate that it should be created if it doesn't exist (IPC_CREAT). int shmid = shmget(key, 1024, 0666 | IPC_CREAT); if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }
    // shmat to attach to shared memory
    // Attach to the shared memory segment using shmat. This returns a pointer to the shared
    memory, which can be treated as a character array.char *str = (char *)shmat(shmid, (void *)0, 0);
    printf("Write Data : ");
    fgets(str, 1024, stdin); // Read a line of input from the user (including spaces) and store
    it in the shared memory using fgets.printf("Data written in memory: %s\n", str);

    // Detach from shared memory
    shmdt(str);
    return 0;
}

/* Output
comp74@comp74:~/Desktop$ gcc assgn7B_1.c -o assgn7B_1
comp74@comp74:~/Desktop$ ./assgn7B_1
Write Data : Hello Everone! I am performing Inter-process Communication using Shared
Memory
Data written in memory: Hello Everone! I am performing Inter-process Communication
using Shared Memory
*/