#include <stdio.h>
#include <stdlib.h>

// Function to compare two integers for qsort
int compareIntegers(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to print the order of served requests
void printOrder(int order[], int count) {
    printf("Order of serving requests: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", order[i]);
    }
    printf("\n");
}

// Shortest Seek Time First (SSTF) Disk Scheduling Algorithm
int SSTF() {
    int requests[100], n, totalHeadMovement = 0, initialPosition, count = 0;
    int order[100]; // To store the order of served requests

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the requests sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d", &initialPosition);

    while (count != n) {
        int minSeekDistance = 1000, selectedIndex;
        for (int i = 0; i < n; i++) {
            int seekDistance = abs(requests[i] - initialPosition);
            if (seekDistance < minSeekDistance) {
                minSeekDistance = seekDistance;
                selectedIndex = i;
            }
        }
        totalHeadMovement += minSeekDistance;
        order[count] = requests[selectedIndex]; // Store the served request
        initialPosition = requests[selectedIndex];

        requests[selectedIndex] = 1000; // Mark the request as served
        count++;
    }
    printf("Total head movement is %d\n", totalHeadMovement);
    printOrder(order, n);
    return 0;
}

// SCAN Disk Scheduling Algorithm
int SCAN() {
    int requests[100], n, totalHeadMovement = 0, initialPosition, diskSize, direction;
    int order[100]; // To store the order of served requests

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the requests sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d", &initialPosition);
    printf("Enter total disk size: ");
    scanf("%d", &diskSize);
    printf("Enter the head movement direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                // Sort the requests in ascending order
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (initialPosition < requests[i]) {
            index = i;
            break;
        }
    }
    int count = 0;
    if (direction == 1) {
        // Moving towards higher track numbers
        for (int i = index; i < n; i++) {
            order[count++] = requests[i]; // Store the served request
            totalHeadMovement += abs(requests[i] - initialPosition);
            initialPosition = requests[i];
        }
        totalHeadMovement += abs(diskSize - requests[n - 1] - 1);
        initialPosition = diskSize - 1;
        for (int i = index - 1; i >= 0; i--) {
            order[count++] = requests[i]; // Store the served request
            totalHeadMovement += abs(requests[i] - initialPosition);
            initialPosition = requests[i];
        }
    } else {
        // Moving towards lower track numbers
        for (int i = index - 1; i >= 0; i--) {
            order[count++] = requests[i]; // Store the served request
            totalHeadMovement += abs(requests[i] - initialPosition);
            initialPosition = requests[i];
        }
        totalHeadMovement += abs(requests[0] - 0);
        initialPosition = 0;
        for (int i = index; i < n; i++) {
            order[count++] = requests[i]; // Store the served request
            totalHeadMovement += abs(requests[i] - initialPosition);
            initialPosition = requests[i];
        }
    }
    printf("Total head movement is %d\n", totalHeadMovement);
    printOrder(order, n);
    return 0;
}

// C-LOOK Disk Scheduling Algorithm
int CLOOK() {
    int requests[100], n, totalHeadMovement = 0, initialPosition, diskSize, direction;
    int order[100]; // To store the order of served requests

    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the requests sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d", &initialPosition);
    printf("Enter total disk size: ");
    scanf("%d", &diskSize);
    printf("Enter the head movement direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                // Sort the requests in ascending order
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (initialPosition < requests[i]) {
            index = i;
            break;
        }
    }
    int count = 0;
    if (direction == 1) {
        // Moving towards higher track numbers
        for (int i = index; i < n; i++) {
            order[count++] = requests[i]; // Store the served request
            totalHeadMovement += abs(requests[i] - initialPosition);
            initialPosition = requests[i];
        }
        for (int i = 0; i < index; i++) {
            order[count++] = requests[i]; // Store the served request
            totalHeadMovement += abs(requests[i] - initialPosition);
            initialPosition = requests[i];
        }
    } else {
        // Moving towards lower track numbers
        for (int i = index - 1; i >= 0; i--) {
            order[count++] = requests[i]; // Store the served request
            totalHeadMovement += abs(requests[i] - initialPosition);
            initialPosition = requests[i];
        }
        for (int i = n - 1; i >= index; i--) {
            order[count++] = requests[i]; // Store the served request
            totalHeadMovement += abs(requests[i] - initialPosition);
            initialPosition = requests[i];
        }
    }
    printf("Total head movement is %d\n", totalHeadMovement);
    printOrder(order, n);
    return 0;
}

int main() {
    int choice, continueFlag = 1;
    do {
        // Clear the screen (uncomment if needed)
        //system("clear");

        printf("\n\n\t*********** MENU ***********");
        printf("\n\n\t1: SSTF\n\n\t2: SCAN\n\n\t3: CLOOK\n\n\t4: EXIT");
        printf("\n\n\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                SSTF();
                break;
            case 2:
                SCAN();
                break;
            case 3:
                CLOOK();
                break;
            case 4:
                continueFlag = 0;
                break;
        }

        printf("\n\n\tDo you want to continue? IF YES PRESS 1\n\n\tIF NO PRESS 0: ");
        scanf("%d", &continueFlag);
    } while (continueFlag == 1);
    return 0;
}


