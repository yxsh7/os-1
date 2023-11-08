#include <stdio.h>  // Standard I/O library for i/p functions
#include <stdlib.h> // Library for functions like 'exit'
#include <string.h> // Library for string manipulation
#include <unistd.h> // Unix standard library for system calls and constants
// Constants to represent read and write end of pipe
#define READ_END 0
#define WRITE_END 1
int main()
{
    int pipe1[2]; // Pipe for sending sentences from process 1 to process 2
    int pipe2[2]; // Pipe for sending output from process 2 to process 1
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork(); // To fork the current process to create child process. The parent
    and child will communicate through pipes if (pid == -1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        // Child process (Process 2)
        close(pipe1[WRITE_END]);                     // Close the write end of pipe 1
        close(pipe2[READ_END]);                      // Close the read end of pipe 2
        FILE *outputFile = fopen("output.txt", "w"); // opened a file named "output.txt" for writing
        if (outputFile == NULL)                      // checking if file opening failed or not
        {
            perror("Failed to open output.txt");
            exit(EXIT_FAILURE);
        }
        char buffer[4096]; // declare a character buffer to read data from 'pipe1'
        int charCount = 0;
        int wordCount = 0;
        int lineCount = 0;
        // infinite loop to read data from pipe1
        while (1)
        {

            ssize_t bytes_read = read(pipe1[READ_END], buffer, sizeof(buffer)); // Read data from
            'pipe1' into 'buffer' and get no.of bytes read if (bytes_read <= 0) // Checking if end of input has been reached
            {
                break; // End of input
            }
            for (ssize_t i = 0; i < bytes_read; i++) // Loop through 'buffer' to count characters,
                words and lines
                {
                    charCount++;
                    if (buffer[i] == ' ' || buffer[i] == '\n')
                    {
                        wordCount++;
                    }
                    if (buffer[i] == '\n')
                    {
                        lineCount++;
                    }
                }
            fprintf(outputFile, "%s", buffer); // Write data from buffer to output file
        }
        fclose(outputFile);      // Closing output file
        close(pipe1[READ_END]);  // Close the read end of pipe 1
        close(pipe2[WRITE_END]); // Close the write end of pipe 2
        printf("\n");
        printf("The content of file says: \n%s\n", buffer);
        printf("Character count: %d\n", charCount);
        printf("Word count: %d\n", wordCount);
        printf("Line count: %d\n", lineCount);
    }
    else
    {
        // Parent process (Process 1)
        close(pipe1[READ_END]);  // Close the read end of pipe 1
        close(pipe2[WRITE_END]); // Close the write end of pipe 2
        printf("Enter sentences (Ctrl+D to end input):\n");
        char inputBuffer[4096];
        while (fgets(inputBuffer, sizeof(inputBuffer), stdin) != NULL)
        {
            write(pipe1[WRITE_END], inputBuffer, strlen(inputBuffer));
        }
        close(pipe1[WRITE_END]); // Close the write end of pipe 1
        char buffer[4096];
        ssize_t bytes_read;
        while ((bytes_read = read(pipe2[READ_END], buffer, sizeof(buffer))) > 0)
        {
            write(STDOUT_FILENO, buffer, bytes_read);
        }
        close(pipe2[READ_END]); // Close the read end of pipe 2
    }
    return 0;
}

/* Output

comp74@comp74:~/Desktop$ gcc assgn7A.c -o assgn7A
comp74@comp74:~/Desktop$ ./assgn7A
Enter sentences (Ctrl+D to end input):
Hello Everyone! I am performing C program for creating FIFO.
FIFO stands for First In First Out. It is one of the simplest page replacement algorithm
The content of file says:
Hello Everyone! I am performing C program for creating FIFO.
FIFO stands for First In First Out. It is one of the simplest page replacement algorithm
Character count: 150
Word count: 26
Line count: 2
*/