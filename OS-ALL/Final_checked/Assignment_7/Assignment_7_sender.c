#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX_BUFFER 1024

int main() {
    int senderToFifo, receiverFromFifo;
    char *senderFifoPath = "sender_fifo";
    char *receiverFifoPath = "receiver_fifo";

    char buffer[MAX_BUFFER];
    char input;
    int result;

    result = mkfifo(senderFifoPath, 0777);
    if (result == -1) {
        printf("Sender FIFO not created\n");
        return 1;
    }

    printf("Enter the string (end with #):\n");
    senderToFifo = open(senderFifoPath, O_WRONLY);

    int c = 0;
    while ((input = getchar()) != '#') {
        buffer[c++] = input;
    }
    buffer[c] = '\0';

    write(senderToFifo, buffer, strlen(buffer));
    close(senderToFifo);

    receiverFromFifo = open(receiverFifoPath, O_RDONLY);
    read(receiverFromFifo, buffer, MAX_BUFFER);

    printf("\nContents received from receiver:\n%s\n", buffer);
    close(receiverFromFifo);
    unlink(senderFifoPath);

    return 0;
}
