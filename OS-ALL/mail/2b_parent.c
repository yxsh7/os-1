#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int compareIntegers(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n;

    printf("Enter the number of integers: ");
    scanf("%d", &n);

    int integers[n];

    printf("\nEnter Array Elements seperated by a space: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &integers[i]);
    }

    qsort(integers, n, sizeof(int), compareIntegers);

    printf("\nSorted Integers: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", integers[i]);
    }
    printf("\n");

    const char *stringArray[n];

    for (int i = 0; i < n; i++)
    {
        char temp[20];
        snprintf(temp, sizeof(temp), "%d", integers[i]);
        stringArray[i] = strdup(temp);
    }

    const char *child_argv[n + 2];
    child_argv[0] = "child";

    for (int i = 0; i < n; i++)
    {
        child_argv[i + 1] = stringArray[i];
    }

    child_argv[n + 1] = NULL;

    int err = execve("child", child_argv, NULL);

    perror("execve");
    exit(1);
}

// output:
// comp123@comp123:~/Desktop/os/2$ gcc parent.c -o parent.out
// comp123@comp123:~/Desktop/os/2$ gcc child.c -o child.out
// comp123@comp123:~/Desktop/os/2$ ./parent.out
// Enter the number of elements: 5
// Enter 5 elements:
// 2
// 67
// 32
// 6
// 26
// Reversed Array:
// 67
// 32
// 26
// 6
// 2
// comp123@comp123:~/Desktop/os/2$