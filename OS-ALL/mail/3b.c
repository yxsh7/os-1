#include <stdio.h>

int main()
{
    int cnt, j, n, t, remain, flag = 0, tq;
    int wt = 0, tat = 0, at[10], bt[10], rt[10];

    printf("Enter Total Process:\t ");
    scanf("%d", &n);

    if (n <= 0 || n > 10)
    {
        printf("Invalid number of processes. Please enter a value between 1 and 10.\n");
        return 1;
    }

    remain = n;

    for (cnt = 0; cnt < n; cnt++)
    {
        printf("Enter Arrival Time and Burst Time for Process %d:\n", cnt + 1);
        scanf("%d", &at[cnt]);
        scanf("%d", &bt[cnt]);

        if (at[cnt] < 0 || bt[cnt] <= 0)
        {
            printf("Invalid arrival time or burst time for Process %d. Please enter non-negative arrival time and positive burst time.\n", cnt + 1);
            return 1;
        }

        rt[cnt] = bt[cnt];
    }

    printf("Enter Time Quantum:\t");
    scanf("%d", &tq);

    if (tq <= 0)
    {
        printf("Invalid time quantum. Please enter a positive value for the time quantum.\n");
        return 1;
    }

    printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");

    for (t = 0, cnt = 0; remain != 0;)
    {
        if (rt[cnt] <= tq && rt[cnt] > 0)
        {
            t += rt[cnt];
            rt[cnt] = 0;
            flag = 1;
        }
        else if (rt[cnt] > 0)
        {
            rt[cnt] -= tq;
            t += tq;
        }

        if (rt[cnt] == 0 && flag == 1)
        {
            remain--;
            printf("P[%d]\t|\t%d\t|\t%d\n", cnt + 1, t - at[cnt], t - at[cnt] - bt[cnt]);
            wt += t - at[cnt] - bt[cnt];
            tat += t - at[cnt];
            flag = 0;
        }

        if (cnt == n - 1)
            cnt = 0;
        else if (at[cnt + 1] <= t)
            cnt++;
        else
            cnt = 0;
    }

    printf("\nAverage Waiting Time= %.2f\n", (float)wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)tat / n);

    return 0;
}

// //output
// 7comp69@comp69:~$ gcc rr.c
// comp69@comp69:~$ ./a.out
// Enter Total Process:	 4
// Enter Arrival Time and Burst Time for Process 1:
// 0
// 5
// Enter Arrival Time and Burst Time for Process 2:
// 1
// 4
// Enter Arrival Time and Burst Time for Process 3:
// 2
// 2
// Enter Arrival Time and Burst Time for Process 4:
// 3
// 1
// Enter Time Quantum:	2

// Process	|Turnaround Time|Waiting Time

// P[3]	|	4	|	2
// P[4]	|	4	|	3
// P[2]	|	10	|	6
// P[1]	|	12	|	7

// Average Waiting Time= 4.50
// Average Turnaround Time = 7.50
