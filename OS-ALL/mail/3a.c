#include <stdio.h>
struct process
{
    int WT, AT, BT, TAT;
};

struct process a[10];

int main()
{
    int i;
    int n, temp[10];
    int count = 0, t = 0, s_P;
    float total_WT = 0, total_TAT = 0, Avg_WT, Avg_TAT;
    printf("Enter the number of the process\n");
    scanf("%d", &n);
    printf("Enter the arrival time and burst time of the process\n");
    printf("AT BT\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &a[i].AT, &a[i].BT);
        temp[i] = a[i].BT;
    }
    a[9].BT = 9999;
    for (t = 0; count != n; t++)
    {
        s_P = 9;
        for (i = 0; i < n; i++)
        {

            if (a[i].BT < a[s_P].BT && (a[i].AT <= t && a[i].BT > 0))
            {

                s_P = i;
            }
        }
        a[s_P].BT = a[s_P].BT - 1;

        if (a[s_P].BT == 0)
        {
            count++;
            // cal
            a[s_P].TAT = t - a[s_P].AT + 1;
            a[s_P].WT = a[s_P].TAT - temp[s_P];
            // total cal
            total_TAT = total_TAT + a[s_P].TAT;
            total_WT = total_WT + a[s_P].WT;
        }
    }
    // avg cal
    Avg_TAT = total_TAT / n;
    Avg_WT = total_WT / n;
    printf("Id     BT      WT      TAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\n", i + 1, temp[i], a[i].WT, a[i].TAT);
    }
    printf("Avg waiting time of the process is %f\n", Avg_WT);
    printf("Avg turn around time of the process %f\n", Avg_TAT);
}

// output
// comp55@comp55:~/Desktop/os$ gcc sjf.c
// comp55@comp55:~/Desktop/os$ ./a.out
// Enter the number of the process
// 4
// Enter the arrival time and burst time of the process
// AT WT
// 0 18
// 1 4
// 2 7
// 3 2
// Id     BT      WT      TAT
// 1	18	13	31
// 2	4	0	4
// 3	7	5	12
// 4	2	2	4
// Avg waiting time of the process is 5.000000
// Avg turn around time of the process 12.750000
