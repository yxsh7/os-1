#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_BUFFER 1024

int main() {
    int words = 0, lines = 0, chars = 0;
    char buf[MAX_BUFFER];
    int senderToFifo, receiverToFifo, i = 0;
    char *senderFifoPath = "sender_fifo";
    char *receiverFifoPath = "receiver_fifo";

    mkfifo(receiverFifoPath, 0777);

    senderToFifo = open(senderFifoPath, O_RDONLY);
    read(senderToFifo, buf, MAX_BUFFER);

    printf("Message received: %s\n", buf);

    while (buf[i] != '\0') {
        if (buf[i] == ' ' || buf[i] == '\n') {
            words++;
        } else {
            chars++;
        }

        if (buf[i] == '\n') {
            lines++;
        }

        i++;
    }
    words++;
    lines++;

    printf("Number of lines: %d\n", lines);
    printf("Number of words: %d\n", words);
    printf("Number of characters: %d\n", chars);

    FILE *fp = fopen("result.txt", "w");
    fprintf(fp, "Number of lines: %d\n", lines);
    fprintf(fp, "Number of words: %d\n", words);
    fprintf(fp, "Number of characters: %d\n", chars);
    fclose(fp);

    close(senderToFifo);
    unlink(senderFifoPath);

    receiverToFifo = open(receiverFifoPath, O_WRONLY);
    system("cat result.txt > receiver_fifo");
    close(receiverToFifo);

    return 0;
}




















