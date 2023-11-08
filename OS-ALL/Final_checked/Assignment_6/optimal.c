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

void optimal(char string[], int frameSize, int count) {
    int cnt, cnt2, selector, flag, max, faults = 0;
    int distance[20];
    Queue q;
    q.end = 0;

    printf("\nData Requested\tFrame contents\t    Page Fault\n==============================================");

    for (cnt = 0; cnt < count; cnt += 2) {
        printf("\n\n\t%c", string[cnt]);
        flag = 0;

        for (cnt2 = 0; cnt2 < q.end; cnt2++) {
            if (string[cnt] == q.data[cnt2][0]) {
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            faults++;

            if (q.end < frameSize) {
                enqueue(&q, string[cnt], q.end);
                q.data[q.end][1] = cnt / 2;
                q.end++;
            } else {
                for (cnt2 = 0; cnt2 < q.end; cnt2++) {
                    distance[cnt2] = 0;
                }

                for (selector = 0; selector < q.end; selector++) {
                    for (cnt2 = cnt; cnt2 < count; cnt2 += 2) {
                        if (string[cnt2] == q.data[selector][0]) {
                            distance[selector] = cnt2 / 2;
                            break;
                        }
                        if (distance[selector] == 0) {
                            distance[selector] = 99 - q.data[selector][1];
                        }
                    }
                }

                max = 0;

                for (cnt2 = 0; cnt2 < q.end; cnt2++) {
                    if (distance[cnt2] > max) {
                        max = distance[cnt2];
                        selector = cnt2;
                    }
                }

                dequeue(&q, selector);
                enqueue(&q, string[cnt], selector);
                q.data[selector][1] = cnt / 2;
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

    optimal(string, frameSize, count);

    return 0;
}

