#include <stdio.h>

int main() {
    int num_processes, num_resources;
    
    // Input the number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    int allocation_matrix[num_processes][num_resources];
    int max_matrix[num_processes][num_resources];

    // Input allocation matrix
    printf("\nEnter the allocation matrix (%dx%d):\n", num_processes, num_resources);
    for (int i = 0; i < num_processes; i++) {
        printf("Enter %dth row: ", i + 1);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation_matrix[i][j]);
        }
    }

    // Input maximum matrix
    printf("\nEnter the maximum matrix (%dx%d):\n", num_processes, num_resources);
    for (int i = 0; i < num_processes; i++) {
        printf("Enter %dth row: ", i + 1);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &max_matrix[i][j]);
        }
    }

    int available_resources[num_resources];
    
    // Input available resources
    printf("\nEnter available resources:\n");
    for (int j = 0; j < num_resources; j++) {
        scanf("%d", &available_resources[j]);
    }

    int finish[num_processes], safe_sequence[num_processes], index = 0;
    for (int k = 0; k < num_processes; k++) {
        finish[k] = 0;
    }

    int need_matrix[num_processes][num_resources];

    // Calculate the need matrix
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            need_matrix[i][j] = max_matrix[i][j] - allocation_matrix[i][j];
        }
    }

    int work[num_resources];
    for (int k = 0; k < num_resources; k++) {
        work[k] = available_resources[k];
    }

    int found, y = 0;

    // Check for a safe sequence
    for (int k = 0; k < num_processes; k++) {
        for (int i = 0; i < num_processes; i++) {
            if (finish[i] == 0) {
                int flag = 1;
                for (int j = 0; j < num_resources; j++) {
                    if (need_matrix[i][j] > work[j]) {
                        flag = 0;
                        break;
                    }
                }

                if (flag == 1) {
                    safe_sequence[index++] = i;
                    for (y = 0; y < num_resources; y++) {
                        work[y] += allocation_matrix[i][y];
                    }
                    finish[i] = 1;
                }
            }
        }
    }

    int is_safe = 1;

    for (int i = 0; i < num_processes; i++) {
        if (finish[i] == 0) {
            is_safe = 0;
            printf("The system is not safe.\n");
            break;
        }
    }

    if (is_safe) {
        printf("The following is the safe sequence: ");
        for (int i = 0; i < num_processes - 1; i++) {
            printf("P%d -> ", safe_sequence[i]);
        }
        printf("P%d\n", safe_sequence[num_processes - 1]);
    }

    return 0;
}

/*
OUTPUT:


Enter Number of processes: 4

Enter Number of resources : 2


Enter Details for Allocation matrix:(4X2) 

        Enter 1th row: 1 0

        Enter 2th row: 1 1

        Enter 3th row: 1 2

        Enter 4th row: 1 1


Enter Details for Max matrix:(4X2)

        Enter 1th row: 1 1

        Enter 2th row: 2 3

        Enter 3th row: 2 2

        Enter 4th row: 3 2


Enter Details for Available Resources:
1 1
Following is the SAFE Sequence
 P0 -> P2 -> P3 -> P1*/