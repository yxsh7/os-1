#include <stdio.h>

typedef struct {
    char data[20][2];
    int end;
} Queue;

void enqueue(Queue *q, char data, int position) {
    q->data[position][0] = data;
}

char dequeue(Queue *q, int position) {
    char value;
    value = q->data[position][0];
    return value;
}

void lru(char string[], int frameSize, int count) {
    int cnt, cnt2, selector, flag, min, faults = 0;
    Queue q;
    q.end = 0;

    printf("\nData Requested\tFrame contents\t    Page Fault\n==============================================");

    for (cnt = 0; cnt < count; cnt += 2) {
        printf("\n\n\t%c", string[cnt]);
        flag = 0;

        for (cnt2 = 0; cnt2 < q.end; cnt2++) {
            if (string[cnt] == q.data[cnt2][0]) {
                q.data[cnt2][1] = (cnt / 2) + 1;
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            faults++;

            if (q.end < frameSize) {
                enqueue(&q, string[cnt], q.end);
                q.data[q.end][1] = (cnt / 2) + 1;
                q.end++;
            } else {
                min = 99;

                for (cnt2 = 0; cnt2 < q.end; cnt2++) {
                    if (q.data[cnt2][1] < min) {
                        min = q.data[cnt2][1];
                        selector = cnt2;
                    }
                }

                dequeue(&q, selector);
                enqueue(&q, string[cnt], selector);
                q.data[selector][1] = (cnt / 2) + 1;
            }

            printf("\t  ");

            for (cnt2 = 0; cnt2 < q.end; cnt2++) {
                printf("%c   ", q.data[cnt2][0]);
            }

            printf("\t\tY");
        } else {
            printf("\t  ");

            for (cnt2 = 0; cnt2 < q.end; cnt2++) {
                printf("%c   ", q.data[cnt2][0]);
            }

            printf("\t\tN");
        }
    }

    printf("\n\n==============================================\n");
    printf("\nTotal number of Page Faults: %d\n\n", faults);
}

int main() {
    int frameSize, count;
    char string[50];

    printf("Enter the string: ");
    count = 0;
    do {
        scanf("%c", &string[count]);
        count++;
    } while (string[count - 1] != '\n');
    count--;

    printf("\nEnter the size of the frame: ");
    scanf("%d", &frameSize);

    lru(string, frameSize, count);

    return 0;
}

